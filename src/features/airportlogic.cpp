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
    , m_airportGrid(new AirportGridModel(this))
{
    init();

    installEventFilter(this);
}

#include <QDebug>
void AirportLogic::init()
{
    QString filename(QString("E:\\Projekty\\ggj2017\\UNNAMED\\level_") + QString::number(1) + QString(".json"));
    QFile file(filename);
    file.open(QFile::ReadOnly);
    QString data(file.readAll());

    QJsonObject obj;
    if (JsonHelpers::jsonObjectFromString(data, obj)) {
        QJsonArray grid = obj["grid"].toArray();

        for (int i=0; i<grid.size(); i++) {
            QJsonObject tile = grid.at(i).toObject();

            AirportTileModel* airportTileModel = new AirportTileModel(this);
            airportTileModel->set_tileType(tile["tile_type"].toInt());

            airportGrid()->addAirportTile(airportTileModel);
        }
    }
}

void AirportLogic::saveMap()
{
    if (editMode()) {
        qDebug() << "saveMap";
        QJsonObject obj;
        QJsonArray tileArray;
        for (int i=0; i<airportGrid()->size(); i++) {
            QJsonObject grid;
            grid.insert("tile_type", airportGrid()->get(i)->tileType());
            tileArray.append(grid);
        }
        obj.insert("grid", tileArray);

        QJsonDocument doc(obj);
        QString strJson(doc.toJson(QJsonDocument::Compact));

        QString filename(QString("E:\\Projekty\\ggj2017\\UNNAMED\\data_") + QString::number(QDateTime::currentMSecsSinceEpoch()) + QString(".json"));
        QFile file(filename);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            stream << strJson << endl;
            qDebug() << "SAVED " << filename;
        }
    }
}


