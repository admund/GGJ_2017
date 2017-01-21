#include "airportgridmodel.h"

AirportGridModel::AirportGridModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

void AirportGridModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
        for (int i=0; i<mAirportTileModelList.size(); ++i)
        {
            mAirportTileModelList.at(i)->clear();
            delete mAirportTileModelList.at(i);
        }
        mAirportTileModelList.clear();
    endRemoveRows();
}

int AirportGridModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return mAirportTileModelList.size();
}

QVariant AirportGridModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= mAirportTileModelList.size())
    {
        return QVariant();
    }

    if (role == AirportGridModelRole)
    {
        AirportTileModel* airportTileModel = mAirportTileModelList[index.row()];
        return QVariant::fromValue<AirportTileModel*>(airportTileModel);
    }

    return QVariant();
}

QHash<int, QByteArray> AirportGridModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[AirportGridModelRole] = "airportGridModelRole";
    return roles;
}

AirportTileModel* AirportGridModel::get(int index)
{
    if (index < 0 || index >= mAirportTileModelList.size())
    {
        return nullptr;
    }

    return mAirportTileModelList[index];
}

int AirportGridModel::size()
{
    return mAirportTileModelList.size();
}

void AirportGridModel::addAirportTile(AirportTileModel* airportTileModel)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
        mAirportTileModelList.append(airportTileModel);
    endInsertRows();
}
