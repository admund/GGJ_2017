#ifndef PLANELISTMODEL_H
#define PLANELISTMODEL_H

#include <QAbstractListModel>

#include "planemodel.h"
#include "../macros.h"

class PlaneListModel : public QAbstractListModel
{
    Q_OBJECT

    AUTO_Q_PROPERTY(int, count)

public:
    enum DataRoles
    {
        PlaneModelRole = Qt::UserRole + 1,
    };

    explicit PlaneListModel(QObject* parent = 0);

    virtual void clear();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    PlaneModel* get(int index);
    PlaneModel* getById(int id);
    int size();

    void addPlaneModel(PlaneModel* planeModel);

private:
    QList<PlaneModel*> mPlaneModelList;
    QMap<int, PlaneModel*> mPlaneModelMap;
};

#endif // PLANELISTMODEL_H
