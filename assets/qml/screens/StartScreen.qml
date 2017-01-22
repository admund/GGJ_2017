import QtQuick 2.0

import "../appStructure"

GameScreen {
    Image {
        anchors.fill: parent

        source: "../../images/loading_1.png"

        Image {
            id: name

            width: 133
            height: 44

            anchors {
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
                bottomMargin: 95
            }

            source: startMouse.pressed ? "../../images/play_onpress.png"
                         : (startMouse.containsMouse ? "../../images/play_hover.png"
                                                    : "../../images/play_button.png")

            MouseArea {
                id: startMouse
                anchors.fill: parent

                hoverEnabled: true

                onClicked: _logic.showChooseMap = true
            }
        }
    }
}
