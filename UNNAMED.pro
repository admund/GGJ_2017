TEMPLATE = app
QT += qml quick quickcontrols2 xml #core gui qml quick quickcontrols2 xml

CONFIG += c++11

HEADERS += \
    src/unnamedapplication.h \
    src/enums.h \
    src/macros.h \
    src/spinacz.h \
    src/features/rootlogic.h \
    src/features/airportlogic.h \
    src/features/airportgridmodel.h \
    src/features/airporttilemodel.h \
    src/keyboardfilter.h \
    src/jsonhelpers.h


SOURCES += src/main.cpp \
    src/unnamedapplication.cpp \
    src/spinacz.cpp \
    src/features/rootlogic.cpp \
    src/features/airportlogic.cpp \
    src/features/airportgridmodel.cpp \
    src/features/airporttilemodel.cpp \
    src/keyboardfilter.cpp \
    src/jsonhelpers.cpp


RESOURCES += assets/qml/_qml.qrc \
    assets/fonts/_fonts.qrc \
#    assets/translations/_translations.qrc \
    assets/tests/_tests.qrc \
    assets/fakes/_fakes.qrc \
    assets/images/_images_xx.qrc
