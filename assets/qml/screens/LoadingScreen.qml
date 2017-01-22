import QtQuick 2.0

import "../appStructure"

GameScreen {
    Image {
        id: loadingScreen

        anchors.fill: parent

        source: "../../images/loading_2.png"

        Timer {
            interval: 3000
            repeat: false
            running: _logic.showLoading

            onTriggered: {
                _logic.showLoading = false
                _logic.showAirport = true
            }
        }
    }
}
