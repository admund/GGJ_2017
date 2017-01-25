#ifndef AIRPORTLOGIC_H
#define AIRPORTLOGIC_H

#include <QObject>

#include "airportgridmodel.h"
#include "flagcontrollerlogic.h"
#include "planelistmodel.h"
#include "spawnpointmodel.h"
#include "scoremodel.h"
#include "skillslogic.h"
#include "../macros.h"

struct PlaneConfigStruct {
    float speedMulti;
    float speedMax;
    float rotation;
    float maxFuell;
    QString planeName;
    QString planeCrushName;
};

class AirportLogic : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(bool, editMode)
    AUTO_Q_PROPERTY(int, selectedPlane)
    AUTO_Q_PROPERTY(bool, playCrashSound)
    AUTO_Q_PROPERTY(bool, playLoadupSound)
    AUTO_Q_PROPERTY(bool, playFlyawaySound)

    AUTO_Q_PROPERTY(AirportGridModel*, airportGrid)
    AUTO_Q_PROPERTY(PlaneListModel*, planeList)
    AUTO_Q_PROPERTY(FlagControllerLogic*, flagController)
    AUTO_Q_PROPERTY(ScoreModel*, score)
    AUTO_Q_PROPERTY(SkillsLogic*, skills)

public:
    explicit AirportLogic(QObject* parent = 0);

    Q_INVOKABLE void setCellSize();
    Q_INVOKABLE void checkCollisions();
    Q_INVOKABLE void changeMoveDirection(int moveDirection);
    Q_INVOKABLE void changeSelectedPlane();
    Q_INVOKABLE void spawn();
    Q_INVOKABLE void exit();
    Q_INVOKABLE void playAgain(int levelId);

    Q_INVOKABLE void clearMap();
    void saveMap();

private slots:
    void init(int levelId);
    void onPlaneDestroyed(int planeId);
    void onCheckPlaneControll(int planeId);

    void onSpeedUpSkill();
    void onFuelSkill();
    void onDoubleSkill();

private:
    void loadPlanesConfig();

    bool isInited = false;
    int cellSize = 0;
    QList<QRect> gridRects;
    QList<SpawnPointModel*> spawnList;
    QVector<QString> pallet;
    QVector<PlaneConfigStruct> planeConfigList;
};

#endif // AIRPORTLOGIC_H
