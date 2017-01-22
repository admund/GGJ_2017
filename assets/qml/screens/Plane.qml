import QtQuick 2.0
import QtGraphicalEffects 1.0

import "../views/Colors.js" as Colors
import "../views/"

Rectangle {
    id: plane

    property QtObject planModel

    property int deltaTime: 15

    property bool isSelected

    width: 30
    height: 30

    x: planModel ? planModel.posX : 0
    y: planModel ? planModel.posY : 0

    color: Colors.Transparent

    Image {
        id: planeImage
        anchors.fill: parent

        rotation: planModel ? planModel.moveRotation : 0

        smooth: true
        visible: planModel ? !planModel.isAlive : false

        source:  planModel && planModel.isAlive ? "../../images/plane.png" : "../../images/plane_crushed.png"
    }

    ColorOverlay {
        anchors.fill: planeImage
        source: planeImage
        color: isSelected && planModel ? planModel.colorName : Colors.Black

        visible: planModel ? planModel.isAlive : false

        rotation: planModel ? planModel.moveRotation : 0
    }

    Rectangle {
        width: fuellText.width
        height: 10
        radius: 3

        anchors {
            horizontalCenter: plane.horizontalCenter
//            bottom: plane.top
            top: plane.bottom
        }

        OpenSansText {
            id: fuellText

            anchors.centerIn: parent
            text: planModel ? planModel.fuell + "/" + planModel.fuellMax : ""
            font.pointSize: 8
        }
    }

    Image {
        id: fuellIdicator

        width: 21
        height: 22

        visible: isIndicatorVisible()

        anchors {
            bottom: plane.top
            right: plane.left
        }

        source: getFuellImage()

        function isIndicatorVisible() {
            if (!planModel || !planModel.isAlive) {
                return false
            }

            if (isSelected) {
                return true
            }

            var percent = planModel.fuell / planModel.fuellMax
            if (percent < .2) {
                return true
            }

            return false
        }

        function getFuellImage() {
            if (!planModel) {
                return "../../images/kanister_empty.png"
            }

            var percent = planModel.fuell / planModel.fuellMax
            if (percent > .8) {
                return "../../images/kanister_full.png"
            } else if (percent > .6) {
                return "../../images/kanister_75.png"
            } else if (percent > .4) {
                return "../../images/kanister_50.png"
            } else if (percent > .2) {
                return "../../images/kanister_25.png"
            } else {
                return "../../images/kanister_empty.png"
            }
        }
    }

    MouseArea {
        id: mouseForHover

        anchors.fill: parent

        hoverEnabled: true
    }

    Timer {
        interval: deltaTime
        repeat: true
        running: planModel ? planModel.isAlive : false

        onTriggered: planModel.move(deltaTime)
    }

    Timer {
        id: scoredTimer

        interval: 15
        repeat: true
        running: planModel ? planModel.isScored : false

        onTriggered: {
            plane.scale += .01
        }
    }
}
