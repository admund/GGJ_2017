#ifndef SPINACZ_H
#define SPINACZ_H

//#include "dataManager/datamanager.h"
//#include "dataSource/datasource.h"
#include "features/rootlogic.h"

class Spinacz : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(RootLogic*, root)

public:
    explicit Spinacz(QObject* parent = 0);

    void init();

private:
    void initData(bool useLocalServer = false);

    void connectNativeIntegration() const;
    void connectDataManager() const;
    void connectDataSource() const;
    void connectFeatures() const;

    // Data sources
    void connectFeedsSource() const;
    void connectLocalSource() const;

    // Features
};

#endif // SPINACZ_H
