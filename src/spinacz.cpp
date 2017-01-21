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

        if (keyEvent->key() == Qt::Key_Q) {
            root()->airportLogic()->changeFlag(false);
            return true;
        }

        if (keyEvent->key() == Qt::Key_W) {
            root()->airportLogic()->changeFlag(true);
            return true;
        }

        if (keyEvent->key() == Qt::Key_Space) {
            root()->airportLogic()->changeSelectedPlane();
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
}

// Data sources
void Spinacz::connectFeedsSource() const
{
}

void Spinacz::connectLocalSource() const
{
}

// Features
