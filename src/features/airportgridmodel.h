#ifndef AIRPORTGRIDMODEL_H
#define AIRPORTGRIDMODEL_H

#include <QAbstractListModel>

#include "airporttilemodel.h"

class AirportGridModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DataRoles
    {
        AirportGridModelRole = Qt::UserRole + 1,
    };

    explicit AirportGridModel(QObject* parent = 0);

    virtual void clear();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    AirportTileModel* get(int index);
    int size();

    void addAirportTile(AirportTileModel* airportTileModel);

private:
    QList<AirportTileModel*> mAirportTileModelList;
};

#endif // AIRPORTGRIDMODEL_H
