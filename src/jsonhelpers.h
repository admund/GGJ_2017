#ifndef JSONHELPERS_H
#define JSONHELPERS_H

#include <QJsonObject>
#include <QJsonArray>

class JsonHelpers
{
public:
    static bool jsonObjectFromString(const QString& data, QJsonObject& jsonObj);
    static bool jsonArrayFromString(const QString& data, QJsonArray& jsonArray);
};

#endif // JSONHELPERS_H
