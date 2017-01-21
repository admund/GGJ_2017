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
        }
    }

    flagController()->set_selectedPlane(planeList()->get(selectedPlane()));
}

bool isInited = false;
int cellSize = cellSize;
QList<QRect> gridRects;
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
//                qDebug() << grid.top() << grid.left() << grid.bottom() << grid.right();
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
        QRect planeRect(plane->posX(), plane->posY(), 30, 30);

        for (int j=0; j<gridRects.size(); j++) {

            bool intersect = gridRects.at(j).intersects(planeRect);
            if (intersect) {
                airportGrid()->get(j)->set_touchedBy(QString::number(plane->id()));
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

void AirportLogic::changeFlag(bool isRight)
{
//    qDebug() << "AirportLogic::changeFlag()" << isRight;
    if (isRight) {
        bool changeTo = !planeList()->get(selectedPlane())->isRightFlagUp();
        planeList()->get(selectedPlane())->set_isRightFlagUp(changeTo);
    } else {
        bool changeTo = !planeList()->get(selectedPlane())->isLeftFlagUp();
        planeList()->get(selectedPlane())->set_isLeftFlagUp(changeTo);
    }

    planeList()->get(selectedPlane())->changeMoveDirection();
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
