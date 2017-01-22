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
    , m_selectedPlane(-1)
    , m_airportGrid(new AirportGridModel(this))
    , m_planeList(new PlaneListModel(this))
    , m_flagController(new FlagControllerLogic(this))
    , m_score(new ScoreModel(this))
{
    pallet.append(QString("#e92f18"));
    pallet.append(QString("#1c195b"));
    pallet.append(QString("#ff6e00"));
    pallet.append(QString("#ff6640"));
    pallet.append(QString("#4e5fb4"));
    pallet.append(QString("#ffc747"));
    pallet.append(QString("#478052"));
    pallet.append(QString("#2ca67f"));
}

void getStringFromFile(const QString& fileName, QString& data) {
    QString filename(fileName);
    QFile file(filename);
    file.open(QFile::ReadOnly);
    data = QString(file.readAll());
}

const QString path("E:\\Projekty\\ggj2017\\UNNAMED\\UNNAMED\\json\\");
//const QString path("json\\");

#include <QDebug>
void AirportLogic::init(int levelNr)
{
    qDebug() << "void AirportLogic::init()" << levelNr;

    qsrand(QDateTime::currentMSecsSinceEpoch());

    QString levelData("");
    const QString fileNameLevel(path + QString("level_") + QString::number(levelNr) + QString(".json"));
    getStringFromFile(fileNameLevel, levelData);

    QJsonObject gridObj;
    if (JsonHelpers::jsonObjectFromString(levelData, gridObj)) {
        QJsonArray grid = gridObj["grid"].toArray();
//        qDebug() << "grid" << grid.size();
        for (int i=0; i<grid.size(); i++) {
            QJsonObject tile = grid.at(i).toObject();

            AirportTileModel* airportTileModel = new AirportTileModel(this);
            airportTileModel->set_tileType(tile["tile_type"].toInt());
            airportTileModel->set_tileRotation(tile["tile_rotation"].toInt());

            airportGrid()->addAirportTile(airportTileModel);
        }
    }

    QString spawnsData("");
    const QString fileNameSpawns(path + QString("spawns_level_") + QString::number(levelNr) + QString(".json"));
    getStringFromFile(fileNameSpawns, spawnsData);

    QJsonObject spawnsObj;
    if (JsonHelpers::jsonObjectFromString(spawnsData, spawnsObj)) {
        QJsonArray spawns = spawnsObj["spawns"].toArray();
//        qDebug() << "spawns" << spawns.size();
        for (int i=0; i<spawns.size(); i++) {
            QJsonObject spawnJson = spawns.at(i).toObject();

            SpawnPointModel* spawnPointModel = new SpawnPointModel(this);
            spawnPointModel->set_posX(spawnJson["pos_x"].toInt());
            spawnPointModel->set_posY(spawnJson["pos_y"].toInt());
            spawnPointModel->set_moveRotation(spawnJson["move_rotation"].toInt());

            spawnList.append(spawnPointModel);
        }
    }

//    QString planesData("");
//    const QString fileNamePlanes(path + QString(planes_level_") + QString::number(1) + QString(".json"));
//    getStringFromFile(fileNamePlanes, planesData);

//    QJsonObject planesObj;
//    if (JsonHelpers::jsonObjectFromString(planesData, planesObj)) {
//        QJsonArray planes = planesObj["planes"].toArray();
////        qDebug() << "planes" << planes.size();
//        for (int i=0; i<planes.size(); i++) {
//            QJsonObject planeJson = planes.at(i).toObject();

//            PlaneModel* planeModel = new PlaneModel(this);
//            planeModel->set_id(planeJson["plane_id"].toInt());
//            planeModel->set_posX(planeJson["start_pos_x"].toInt());//200 + 100 * i);
//            planeModel->set_posY(planeJson["start_pos_y"].toInt());//200 + 50 * i);

//            planeModel->set_speed(planeJson["speed"].toDouble());
//            planeModel->set_rotation(planeJson["rotation"].toDouble());

//            planeModel->set_fuell(qrand() % planeJson["max_fuell"].toInt());
//            planeModel->set_fuellMax(planeJson["max_fuell"].toInt());

//            planeList()->addPlaneModel(planeModel);

//            connect(planeModel, SIGNAL(planeDestroyed(int)), this, SLOT(onPlaneDestroyed(int)));
//        }
//    }

//    if (planeList()->size() > 0) {
//        set_selectedPlane(0);
//        flagController()->set_selectedPlane(planeList()->get(selectedPlane()));
//    }
}

bool cellCalculated = false;
void AirportLogic::setCellSize()
{
    if (!cellCalculated) {
//        init();
        cellCalculated = true;
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
        if (!plane->isAlive()) {
            continue;
        }
        plane->goOnGrass(false);

        QRect planeRect(plane->posX(), plane->posY(), 30, 30);

        for (int j=0; j<gridRects.size(); j++) {

            bool intersect = gridRects.at(j).intersects(planeRect);
            if (intersect) {
                airportGrid()->get(j)->set_touchedBy(QString::number(plane->id()));

                int tileType = airportGrid()->get(j)->tileType();
                if (tileType == AirportTileModel::TILE_TYPE_GRASS || tileType == AirportTileModel::TILE_TYPE_GRASS_2) {
                    plane->goOnGrass(true);
                } else if (tileType == AirportTileModel::TILE_TYPE_BUILDING) {
                    plane->hitBuilding();
                } else if (tileType == AirportTileModel::TILE_TYPE_SEA) {
                    plane->goToSea();
                } else if (tileType == AirportTileModel::TILE_TYPE_RUNWAY_START) {
                    plane->goToRunwayStart();
                } else if (tileType == AirportTileModel::TILE_TYPE_RAMP) {
                    plane->goToRamp();
                }
            }
        }

        for (int j=0; j<planeList()->size(); j++) {
            PlaneModel* planeSec = planeList()->get(j);
            if (plane != planeSec && (plane->isAlive() || planeSec->isAlive())) {
                QRect planeSecRect(planeSec->posX(), planeSec->posY(), 30, 30);
                if (planeSecRect.intersects(planeRect)) {
                    if (plane->isAlive()) {
                        plane->hitOtherPlane();
                    }
                    if (planeSec->isAlive()) {
                        planeSec->hitOtherPlane();
                    }
                }
            }
        }
    }
}

int cnt = 0;
void AirportLogic::spawn()
{
//    qDebug() << "void AirportLogic::spawn()";

    int spawnItem = qrand() % spawnList.size();
    SpawnPointModel* spawnPoint = spawnList.at(spawnItem);

    PlaneModel* planeModel = new PlaneModel(this);
    planeModel->set_id(cnt);
    planeModel->set_posX(spawnPoint->posX());
    planeModel->set_posY(spawnPoint->posY());
    planeModel->set_moveRotation(spawnPoint->moveRotation());
    planeModel->set_moveDirection(PlaneModel::MOVE_GO);

    planeModel->set_speed(.5); // TODO
    planeModel->set_rotation(.5); // TODO

    planeModel->set_fuell(10 + qrand() % 90); // TODO
    planeModel->set_fuellMax(10 + 90); // TODO

    planeModel->set_colorName(pallet.at(cnt % pallet.size()));

    planeList()->addPlaneModel(planeModel);

    connect(planeModel, SIGNAL(planeDestroyed(int)), this, SLOT(onPlaneDestroyed(int)));
    connect(planeModel, SIGNAL(checkPlaneControll(int)), this, SLOT(onCheckPlaneControll(int)));
    connect(planeModel, SIGNAL(planeGoAway()), score(), SLOT(onPlaneGoAway()));
    connect(planeModel, SIGNAL(planeDestroyed(int)), score(), SLOT(onPlaneDestroyed(int)));
    connect(planeModel, SIGNAL(planeGoAway()), flagController(), SLOT(onPlaneGoAway()));

    cnt++;
}

void AirportLogic::saveMap()
{
    if (editMode()) {
        QJsonObject obj;
        QJsonArray tileArray;
        for (int i=0; i<airportGrid()->size(); i++) {
            QJsonObject grid;
            grid.insert("tile_type", airportGrid()->get(i)->tileType());
            grid.insert("tile_rotation", airportGrid()->get(i)->tileRotation());
            tileArray.append(grid);
        }
        obj.insert("grid", tileArray);

        QJsonDocument doc(obj);
        QString strJson(doc.toJson(QJsonDocument::Compact));

        QString filename(path + QString("level_") + QString::number(QDateTime::currentMSecsSinceEpoch()) + QString(".json"));
        QFile file(filename);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            stream << strJson << endl;
        }
    }
}

void AirportLogic::exit()
{
    qDebug() << "void AirportLogic::exit()";

    planeList()->clear();
    airportGrid()->clear();

    for (int i=0; i<spawnList.size(); i++) {
        delete spawnList.at(i);
    }
    spawnList.clear();

    isInited = false;
}

void AirportLogic::onPlaneDestroyed(int planeId)
{
//    qDebug() << "void AirportLogic::onPlaneDestroyed(int planeId)" << planeId;
    if (selectedPlane() == -1 || planeList()->get(selectedPlane())->id() == planeId) {
        changeSelectedPlane();
    }
}

void AirportLogic::onCheckPlaneControll(int planeId)
{
//    qDebug() << "void AirportLogic::onCheckPlaneControll(int planeId)" << planeId;
    if (selectedPlane() == -1 || selectedPlane() == planeId) {
        changeSelectedPlane();
    }
}

void AirportLogic::changeMoveDirection(int moveDirection)
{
    if (selectedPlane() != -1) {
        planeList()->get(selectedPlane())->changeMoveDirection(moveDirection);
    }
}

void AirportLogic::changeSelectedPlane()
{
    int maxCnt = planeList()->size();
//    qDebug() << "AirportLogic::changeSelectedPlane()" << maxCnt;

    set_selectedPlane(selectedPlane() + 1);
    if (selectedPlane() >= planeList()->size()) {
        set_selectedPlane(0);
    }

    while (maxCnt > 0 && (!planeList()->get(selectedPlane())->canBeControlled()
           || !planeList()->get(selectedPlane())->isAlive()))
    {
        set_selectedPlane(selectedPlane() + 1);
        if (selectedPlane() >= planeList()->size()) {
            set_selectedPlane(0);
        }
        maxCnt--;
    }

    if (maxCnt > 0) {
        flagController()->set_selectedPlane(planeList()->get(selectedPlane()));
    } else {
        flagController()->set_selectedPlane(nullptr);
        set_selectedPlane(-1);
    }
}
