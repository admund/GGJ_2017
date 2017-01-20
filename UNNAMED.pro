TEMPLATE = app
QT += core gui qml quick quickcontrols2 xml

CONFIG += c++11

HEADERS += \
    src/unnamedapplication.h \
    src/enums.h \
    src/macros.h \
    src/spinacz.h \
    src/features/rootlogic.h


SOURCES += src/main.cpp \
    src/unnamedapplication.cpp \
    src/spinacz.cpp \
    src/features/rootlogic.cpp


RESOURCES += assets/qml/_qml.qrc \
    assets/fonts/_fonts.qrc \
#    assets/translations/_translations.qrc \
    assets/tests/_tests.qrc \
    assets/fakes/_fakes.qrc \
    assets/images/_images_xx.qrc
