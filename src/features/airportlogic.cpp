#include "airportlogic.h"

#include <QEvent>
#include <QKeyEvent>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDateTime>
#include <QFileInfo>
#include "../jsonhelpers.h"

AirportLogic::AirportLogic(QObject* parent)
    : QObject(parent)
    , m_editMode(false)
    , m_selectedPlane(0)
    , m_airportGrid(new AirportGridModel(this))
    , m_planeList(new PlaneListModel(this))
    , m_flagController(new FlagControllerLogic(this))
{
}

void getStringFromFile(const QString& fileName, QString& data) {
    QString filename(fileName);
    QFile file(filename);
    file.open(QFile::ReadOnly);
    data = QString(file.readAll());
}

#include <QDebug>
int planeCnt = 0;
void AirportLogic::init()
{
    qDebug() << "void AirportLogic::init()";

    QString levelData("");
    const QString fileNameLevel(("E:\\Projekty\\ggj2017\\UNNAMED\\level_") + QString::number(1) + QString(".json"));
    getStringFromFile(fileNameLevel, levelData);

    QJsonObject gridObj;
    if (JsonHelpers::jsonObjectFromString(levelData, gridObj)) {
        QJsonArray grid = gridObj["grid"].toArray();
//        qDebug() << "grid" << grid.size();
        for (int i=0; i<grid.size(); i++) {
            QJsonObject tile = grid.at(i).toObject();

            AirportTileModel* airportTileModel = new AirportTileModel(this);
            airportTileModel->set_tileType(tile["tile_type"].toInt());

            airportGrid()->addAirportTile(airportTileModel);
        }
    }

    QString planesData("");
    const QString fileNamePlanes(("E:\\Projekty\\ggj2017\\UNNAMED\\planes_level_") + QString::number(1) + QString(".json"));
    getStringFromFile(fileNamePlanes, planesData);

    QJsonObject planesObj;
    if (JsonHelpers::jsonObjectFromString(planesData, planesObj)) {
        QJsonArray planes = planesObj["planes"].toArray();
//        qDebug() << "planes" << planes.size();
        for (int i=0; i<planes.size(); i++) {
            QJsonObject planeJson = planes.at(i).toObject();

            PlaneModel* planeModel = new PlaneModel(this);
            planeModel->set_id(planeJson["plane_id"].toInt());
            planeModel->set_posX(planeJson["start_pos_x"].toInt());//200 + 100 * i);
            planeModel->set_posY(planeJson["start_pos_y"].toInt());//200 + 50 * i);

            planeModel->set_speed(planeJson["speed"].toDouble());
            planeModel->set_rotation(planeJson["rotation"].toDouble());

            planeModel->set_fuell(qrand() % planeJson["max_fuell"].toInt());
            planeModel->set_fuellMax(planeJson["max_fuell"].toInt());

            planeList()->addPlaneModel(planeModel);

            planeCnt++;

            connect(planeModel, SIGNAL(planeDestroyed(int)), this, SLOT(onPlaneDestroyed(int)));
        }
    }

    flagController()->set_selectedPlane(planeList()->get(selectedPlane()));
}

void AirportLogic::setCellSize()
{
    qDebug() << "void AirportLogic::setCellSize()";

    if (!isInited) {
        init();
        isInited = true;
        cellSize = (1280 - 300) / 17;

        for (int j=0; j<12; j++) {
            for (int i=0; i<17; i++) {
                QRect grid(i * cellSize, j * cellSize, cellSize, cellSize);
                gridRects.append(grid);
            }
        }
    }
}

void AirportLogic::checkCollisions()
{
    // clear
    for (int j=0; j<airportGrid()->size(); j++) {
        airportGrid()->get(j)->set_touchedBy("");
    }

    for (int i=0; i<planeList()->size(); i++) {
        PlaneModel* plane = planeList()->get(i);
        plane->goOnGrass(false);

        QRect planeRect(plane->posX(), plane->posY(), 30, 30);

        for (int j=0; j<gridRects.size(); j++) {

            bool intersect = gridRects.at(j).intersects(planeRect);
            if (intersect) {
                airportGrid()->get(j)->set_touchedBy(QString::number(plane->id()));

                int tileType = airportGrid()->get(j)->tileType();
                if (tileType == AirportTileModel::TILE_TYPE_GRASS) {
                    plane->goOnGrass(true);
                } else if (tileType == AirportTileModel::TILE_TYPE_BUILDING) {
                    plane->hitBuilding();
                } else if (tileType == AirportTileModel::TILE_TYPE_SEA) {
                    plane->goToSea();
                }
            }
        }

        for (int j=0; j<planeList()->size(); j++) {
            PlaneModel* planeSec = planeList()->get(j);
            if (plane != planeSec) {
                QRect planeSecRect(planeSec->posX(), planeSec->posY(), 30, 30);
                if (planeSecRect.intersects(planeRect)) {
                    plane->hitOtherPlane();
                    planeSec->hitOtherPlane();
                }
            }
        }
    }
}

void AirportLogic::saveMap()
{
    if (editMode()) {
        qDebug() << "saveMap";
        QJsonObject obj;
        QJsonArray tileArray;
        for (int i=0; i<airportGrid()->size(); i++) {
            QJsonObject grid;
            grid.insert("tile_type", airportGrid()->get(i)->tileType());
            tileArray.append(grid);
        }
        obj.insert("grid", tileArray);

        QJsonDocument doc(obj);
        QString strJson(doc.toJson(QJsonDocument::Compact));

        QString filename(QString("E:\\Projekty\\ggj2017\\UNNAMED\\data_") + QString::number(QDateTime::currentMSecsSinceEpoch()) + QString(".json"));
        QFile file(filename);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            stream << strJson << endl;
            qDebug() << "SAVED " << filename;
        }
    }
}

void AirportLogic::onPlaneDestroyed(int planeId)
{
    qDebug() << "AirportLogic::onPlaneDestroyed(int planeId)" << planeId;
    if (planeList()->get(selectedPlane())->id() == planeId) {
        changeSelectedPlane();
    }
}

void AirportLogic::changeMoveDirection(int moveDirection)
{
    planeList()->get(selectedPlane())->changeMoveDirection(moveDirection);
}

void AirportLogic::changeSelectedPlane()
{
//    qDebug() << "AirportLogic::changeSelectedPlane()";
    set_selectedPlane(selectedPlane() + 1);
    if (selectedPlane() >= planeList()->size()) {
        set_selectedPlane(0);
    }

    flagController()->set_selectedPlane(planeList()->get(selectedPlane()));

//    qDebug() << "selectedPlane" << selectedPlane();
}
