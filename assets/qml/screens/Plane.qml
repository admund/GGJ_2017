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

    color: isSelected ? Colors.LightBlue : "#0000B000"

    rotation: planModel.moveRotation

    Image {
        anchors.fill: parent

        source: "../../images/plane.png"
    }

    Rectangle {
        anchors {
            bottom: plane.top
            left: plane.left
            right: plane.right
        }

        color: Colors.White

//        OpenSansText {

//        }
    }

    Timer {
        interval: deltaTime
        repeat: true
        running: planModel.isAlive

        onTriggered: planModel.move(deltaTime)
    }
}
