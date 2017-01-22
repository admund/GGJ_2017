import QtQuick 2.0

import "../appStructure"

GameScreen {
    Image {
        id: loadingScreen

        anchors.fill: parent

        source: "../../images/loading_" + (_logic.loadinglevelId + 1) + ".png"

        Timer {
            interval: 5//3000
            repeat: false
            running: _logic.showLoading

            onTriggered: {
                _logic.showLoading = false
                _logic.showAirport = true
            }
        }
    }
}
