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

//        visible: mouseForHover.containsMouse TODO

        anchors {
            horizontalCenter: plane.horizontalCenter
            bottom: plane.top
        }

        OpenSansText {
            id: fuellText

            anchors.centerIn: parent

            text: planModel ? planModel.fuell + "/" + planModel.fuellMax : ""

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
