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

    x: planModel.posX
    y: planModel.posY

    color: "#0000B000"

    Image {
        id: planeImage
        anchors.fill: parent

        rotation: planModel.moveRotation

        smooth: true
        visible: false

        source: "../../images/plane.png"
    }

    ColorOverlay {
        anchors.fill: planeImage
        source: planeImage
        color: isSelected ? planModel.colorName : Colors.Black

        rotation: planModel.moveRotation
    }

    Rectangle {
        width: fuellText.width
        height: 10

        radius: 3

//        visible: mouseForHover.containsMouse TODO

        anchors {
            horizontalCenter: plane.horizontalCenter
            bottom: plane.top
        }

        OpenSansText {
            id: fuellText

            anchors.centerIn: parent

            text: planModel.fuell + "/" + planModel.fuellMax

            font.pointSize: 8
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
        running: planModel.isAlive

        onTriggered: planModel.move(deltaTime)
    }

    Timer {
        id: scoredTimer

        interval: 15
        repeat: true
        running: planModel.isScored

        onTriggered: {
            plane.scale += .01
        }
    }
}
