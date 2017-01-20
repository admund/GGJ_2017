#ifndef UNNAMEDAPPLICATION_H
#define UNNAMEDAPPLICATION_H

#include <QQmlApplicationEngine>
#include <QGuiApplication>

#include "spinacz.h"

class UnNamedApplication : public QGuiApplication
{
public:
    explicit UnNamedApplication(int& argc, char** argv);
    ~UnNamedApplication();

private:
    void registerAllQmlModelTypes() const;
    void registerAllMetaTypes() const;
    void showQml() const;

    QQmlApplicationEngine* mQmlApplicationEngine;
    Spinacz* mSpinacz;
};

#endif // UNNAMEDAPPLICATION_H
