#include "spinacz.h"

#include <QEvent>
#include <QKeyEvent>

Spinacz::Spinacz(QObject* parent)
    : QObject(parent)
    , m_root(new RootLogic(this))
//    , mDataManager(new DataManager(this))
//    , mDataSource(new DataSource(this))
{
}

void Spinacz::init()
{
    connectNativeIntegration();
    connectDataManager();
    connectDataSource();
    connectFeatures();

    initData();
}

#include <QDebug>
bool Spinacz::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->key() == Qt::Key_F12) {
            root()->airportLogic()->saveMap();
            return true;
        }

        if (keyEvent->key() == Qt::Key_Space) {
            root()->airportLogic()->changeSelectedPlane();
            return true;
        }

        if (keyEvent->key() == Qt::Key_S) {
            root()->airportLogic()->spawn();
            return true;
        }

        if (keyEvent->key() == Qt::Key_Escape) {
            root()->airportLogic()->exit();
            root()->set_showAirport(false);
//            root()->set_showChooseMap(true);
            return true;
        }
    }

    return false;
}

void Spinacz::initData(bool useLocalServer)
{
    Q_UNUSED(useLocalServer)
//    mDataSource->init(useLocalServer);
}

void Spinacz::connectNativeIntegration() const
{
}

void Spinacz::connectDataManager() const
{
}

void Spinacz::connectDataSource() const
{
    connectFeedsSource();
    connectLocalSource();
}

void Spinacz::connectFeatures() const
{
    connect(root(), SIGNAL(initLevel(int)), root()->airportLogic(), SLOT(init(int)));


     connect(root()->airportLogic()->skills(), SIGNAL(speedUpSkillSignal()),
            root()->airportLogic(), SLOT(onSpeedUpSkill()));

     connect(root()->airportLogic()->skills(), SIGNAL(fuellSkillSignal()),
            root()->airportLogic(), SLOT(onFuelSkill()));

     connect(root()->airportLogic()->skills(), SIGNAL(doubleSkillSignal()),
            root()->airportLogic(), SLOT(onDoubleSkill()));
}

// Data sources
void Spinacz::connectFeedsSource() const
{
}

void Spinacz::connectLocalSource() const
{
}

// Features
