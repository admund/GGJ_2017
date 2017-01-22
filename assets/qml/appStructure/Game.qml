import QtQuick 2.7
import QtQuick.Controls 2.0

import "ImagePath.js" as ImagePath
import "../screens"
import "../views"

Item {
    id: game

    signal needCloseAllDialogs

    property bool isCppAvailable: (typeof _cppLogic !== "undefined")
    property QtObject _logic: game.isCppAvailable ? _cppLogic : loader.item.root

    Loader {
        id: loader

        active: !game.isCppAvailable

        // QMLLive replacement for _cpp
        source: "../../fakes/FakeCpp.qml"
    }

    // Fonts
    FontLoader {
        id: openSansFont
        source: "../../fonts/open_sans_cond_bold.ttf"
    }

    ScreenSwitcher {
        id: screenSwitcher

        StartScreen {
            id: startScreen
        }

        ChooseMapScreen {
            id: chooseMapScreen
        }

        LoadingScreen {
            id: loadingScreen
        }

        AirportScreen {
            id: airportScreen
        }
    }

    Timer {
        id: qmlLoadedTimer

        interval: Qt.platform.os == "android" ? 500 : 0
        onTriggered: _logic.qmlFullyLoaded()
    }

//    Connections {
//        target: _logic.login.model

//        onIsLoggedChanged: {
//            if (_logic.login.model.isLogged) {
//                screenSwitcher.switchScreenForward(matchingScreen)
//            } else {
//                screenSwitcher.switchScreenBackward(loginScreen)
//            }
//        }
//    }

    Connections {
        target: _logic

        onShowChooseMapChanged: {
            if (_logic.showChooseMap) {
                screenSwitcher.switchScreenForward(chooseMapScreen)
            }
        }

        onShowLoadingChanged: {
            if (_logic.showLoadingChanged) {
                screenSwitcher.switchScreenForward(loadingScreen)
            }
        }

        onShowAirportChanged: {
            if (_logic.showAirport) {
                screenSwitcher.switchScreenForward(airportScreen)
            } else {
                screenSwitcher.switchScreenBackward(chooseMapScreen)
            }
        }
    }


    Component.onCompleted: {
        qmlLoadedTimer.start()
        screenSwitcher.initWithScreen(startScreen)
//        screenSwitcher.initWithScreen(airportScreen)
    }

    function closeAllDialogs() {
        game.needCloseAllDialogs()
    }
}
