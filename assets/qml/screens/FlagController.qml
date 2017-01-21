import QtQuick 2.0

import "../views/Colors.js" as Colors

Item {
    id: root
    width: 300

    property QtObject planeModel

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

//        color: "#1C195B"
//        color: "#478052"
        color: "#ff6e00"

        Image {
            anchors.fill: parent
            source: getFlagImg()
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
