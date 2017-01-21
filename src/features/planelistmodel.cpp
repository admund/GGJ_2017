#include "planelistmodel.h"

PlaneListModel::PlaneListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

void PlaneListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
        for (int i=0; i<mPlaneModelList.size(); ++i)
        {
            mPlaneModelList.at(i)->clear();
            delete mPlaneModelList.at(i);
        }
        mPlaneModelList.clear();
    endRemoveRows();

    set_count(size());
}

int PlaneListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return mPlaneModelList.size();
}

QVariant PlaneListModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= mPlaneModelList.size())
    {
        return QVariant();
    }

    if (role == PlaneModelRole)
    {
        PlaneModel* planeModel = mPlaneModelList[index.row()];
        return QVariant::fromValue<PlaneModel*>(planeModel);
    }

    return QVariant();
}

QHash<int, QByteArray> PlaneListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PlaneModelRole] = "planeModelRole";
    return roles;
}

PlaneModel* PlaneListModel::get(int index)
{
    if (index < 0 || index >= mPlaneModelList.size())
    {
        return nullptr;
    }

    return mPlaneModelList[index];
}

PlaneModel* PlaneListModel::getById(int id)
{
    return mPlaneModelMap.find(id).value();
}

int PlaneListModel::size()
{
    return mPlaneModelList.size();
}

void PlaneListModel::addPlaneModel(PlaneModel* planeModel)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
        mPlaneModelList.append(planeModel);
    endInsertRows();

    set_count(size());
//    mPlaneModelList.insert(planeModel->id(), planeModel);
}

