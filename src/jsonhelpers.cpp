#include <QJsonDocument>

#include "jsonhelpers.h"

bool JsonHelpers::jsonObjectFromString(const QString& data, QJsonObject& jsonObj)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
    if (!jsonDoc.isNull() && jsonDoc.isObject())
    {
        jsonObj = jsonDoc.object();

        return !(jsonObj.isEmpty());
    }

    return false;
}

bool JsonHelpers::jsonArrayFromString(const QString& data, QJsonArray& jsonArray)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
    if (!jsonDoc.isNull() && jsonDoc.isArray())
    {
        jsonArray = jsonDoc.array();

        return !jsonArray.isEmpty();
    }

    return false;
}
