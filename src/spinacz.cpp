#include "spinacz.h"

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

void Spinacz::initData(bool useLocalServer)
{
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
