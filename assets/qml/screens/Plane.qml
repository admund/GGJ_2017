import QtQuick 2.0

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

//    color: isSelected ? Colors.LightBlue : "#0000B000"

    rotation: planModel.moveRotation

    Image {
        anchors.fill: parent

        source: "../../images/plane.png"
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

        color: Colors.Red

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
        running: planModel.fuell > 0

        onTriggered: planModel.move(deltaTime)
    }
}
