TEMPLATE = app
QT += qml quick quickcontrols2 xml #core gui qml quick quickcontrols2 xml

CONFIG += c++11
CONFIG += resources_big

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
    src/jsonhelpers.h \
    src/features/flagcontrollerlogic.h \
    src/features/planeflagmodel.h \
    src/features/planemodel.h \
    src/features/planelistmodel.h \
    src/features/spawnpointmodel.h \
    src/features/scoremodel.h \
    src/features/skillslogic.h


SOURCES += src/main.cpp \
    src/unnamedapplication.cpp \
    src/spinacz.cpp \
    src/features/rootlogic.cpp \
    src/features/airportlogic.cpp \
    src/features/airportgridmodel.cpp \
    src/features/airporttilemodel.cpp \
    src/keyboardfilter.cpp \
    src/jsonhelpers.cpp \
    src/features/flagcontrollerlogic.cpp \
    src/features/planeflagmodel.cpp \
    src/features/planemodel.cpp \
    src/features/planelistmodel.cpp \
    src/features/spawnpointmodel.cpp \
    src/features/scoremodel.cpp \
    src/features/skillslogic.cpp


RESOURCES += assets/qml/_qml.qrc \
    assets/fonts/_fonts.qrc \
    assets/tests/_tests.qrc \
    assets/fakes/_fakes.qrc \
    assets/images/_images_xx.qrc

DISTFILES += \
    assets/images/plane_2.png \
    assets/images/flag_panel.png \
    assets/images/map_london.png \
    assets/images/panel_objectives.png \
    assets/images/tlo_ciemne.png \
    assets/images/tlo_hangar.png \
    assets/images/tlo_jasne.png \
    assets/images/tlo_parking.png \
    assets/images/tlo_parking2.png \
    assets/images/tlo_pas.png \
    assets/images/tlo_pas2.png \
    assets/images/tlo_pas_poczatek.png \
    assets/images/tlo_rozek.png \
    assets/images/play_hover.png \
    assets/images/play_onpress.png \
    assets/images/play_button.png \
    assets/images/miasto_odblokowac.png \
    assets/images/miasto_wynik.png \
    assets/images/zegar_tarcza.png \
    assets/images/zegar_wskazowka2.png \
    assets/images/kanister_25.png \
    assets/images/kanister_50.png \
    assets/images/kanister_75.png \
    assets/images/kanister_empty.png \
    assets/images/kanister_full.png \
    assets/images/plane_1.png \
    assets/images/plane_2.png \
    assets/images/plane_3.png \
    assets/images/plane_4.png \
    assets/images/plane_crushed_1.png \
    assets/images/plane_crushed_2.png \
    assets/images/plane_crushed_3.png \
    assets/images/plane_crushed_4.png \
    src/features/SkillsLogic.qml \
    assets/images/button_back.png \
    assets/images/button_back_hover.png \
    assets/fonts/bezpieczne_parkowanie_1.wav
