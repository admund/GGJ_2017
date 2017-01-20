#include <QLoggingCategory>

#include "unnamedapplication.h"

int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules("qt.network.ssl=false");

    QCoreApplication::setApplicationName("UnNamed");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    UnNamedApplication unNamedApplication(argc, argv);

    return unNamedApplication.exec();
}
