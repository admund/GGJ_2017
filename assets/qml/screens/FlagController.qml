import QtQuick 2.0

import "../views/Colors.js" as Colors
import "../views"

Item {
    id: root
    width: 300

    property QtObject planeModel
    property QtObject flagControllerLogic

    property bool isRightFlagUp: planeModel ? planeModel.isRightFlagUp : false
    property bool isLeftFlagUp: planeModel ? planeModel.isLeftFlagUp : false

    Image {
        id: mapImage
        height: 107
        width: root.width

        anchors {
            right: parent.right
        }

        source: "../../images/map_london.png"
    }

    Image {
        id: objectivesImage

        height: 107
        width: root.width

        anchors {
            top: mapImage.bottom
            right: parent.right
        }

        source: "../../images/panel_objectives.png"
    }

    Rectangle {
        id: walterHerrmanImage

        width: root.width
        height: 431

        anchors {
            top: objectivesImage.bottom
            right: parent.right
        }

        color: planeModel ? planeModel.colorName : "#ff6e00"

        Image {
            anchors.fill: parent
            source: getFlagImg()
        }

        OpenSansText {
            height: 20
            anchors.horizontalCenter: parent.horizontalCenter

            text: "Great Job!"

            color: "#e92f18"

            font.pointSize: 40

            visible: flagControllerLogic.greatJobTime % 300 > 100

            Timer {
                interval: 10
                running: flagControllerLogic.greatJobTime > 0
                repeat: true
                onTriggered: {
                    flagControllerLogic.greatJobTime = flagControllerLogic.greatJobTime - 10
                }
            }
        }
    }

    Image {
        id: flagPanelImage

        width: root.width
        height: 75

        anchors {
            top: walterHerrmanImage.bottom
            right: parent.right
        }

        source: "../../images/flag_panel.png"

        Repeater {
            model: 5
            delegate: MouseArea {
                width: flagPanelImage.width / 5
                height: flagPanelImage.height

                x: width * index

                onClicked: clickFlagPanel(index)
            }
        }
    }

    signal clickFlagPanel(int index)

    function getFlagImg() {
        if (isRightFlagUp === isLeftFlagUp) {
            if (isRightFlagUp) {
                return "../../images/flag_go.png"
            } else {
                return "../../images/flag_stop.png"
            }
        } else {
            if (isRightFlagUp) {
                return "../../images/flag_right.png"
            } else {
                return "../../images/flag_left.png"
            }
        }
    }
}
