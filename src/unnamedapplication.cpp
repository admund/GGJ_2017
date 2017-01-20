#include "unnamedapplication.h"

#include <QQmlFileSelector>
#include <QFileSelector>
#include <QTranslator>
#include <QQmlContext>
#include <QScreen>
#include <QFile>

#include "macros.h"

#include <QDebug>

UnNamedApplication::UnNamedApplication(int& argc, char** argv)
    : QGuiApplication(argc, argv)
    , mQmlApplicationEngine(nullptr)
    , mSpinacz(nullptr)
{
    mSpinacz = new Spinacz();

    mQmlApplicationEngine = new QQmlApplicationEngine();
    mQmlApplicationEngine->rootContext()->setContextProperty("_cppLogic", mSpinacz->root());

    registerAllQmlModelTypes();
    registerAllMetaTypes();

    mSpinacz->init();

    showQml();
}

UnNamedApplication::~UnNamedApplication()
{
    delete mQmlApplicationEngine;
    delete mSpinacz;
}

void UnNamedApplication::registerAllQmlModelTypes() const
{
    // All model classes exposed to QML must be registered here
//    QML_REGISTER_UNCREATABLE_TYPE(CardModel)
}

void UnNamedApplication::registerAllMetaTypes() const
{
//    qRegisterMetaType<std::string>("std::string");
}

void UnNamedApplication::showQml() const
{
    mQmlApplicationEngine->load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
}
