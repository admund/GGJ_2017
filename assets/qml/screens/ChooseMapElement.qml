import QtQuick 2.0

import "../views/Colors.js" as Colors

Rectangle {
    id: map1

    property int level
    property string imageName
    property string buttonName
    property string buttonHoverName

    width: 388
    height: mapImage.height + mapButton.height + mapButton.anchors.topMargin

    color: Colors.Transparent

    Image {
        id: mapImage

        width: 388
        height: 341

        anchors {
            top: map1.top
            horizontalCenter: map1.horizontalCenter
        }
        source: imageName
    }

    Rectangle {
        id: mapButton

        width: 299
        height: 107

        anchors {
            top: mapImage.bottom
            topMargin: 15
            horizontalCenter: map1.horizontalCenter
        }

        Image {
            anchors.fill: parent

            source: mouseHover.containsMouse ? buttonHoverName : buttonName
        }

        MouseArea {
            id: mouseHover
            anchors.fill: parent

            hoverEnabled: true
            onClicked: {
                _logic.initLevel(level)
                _logic.loadinglevelId = level
                _logic.showLoading = true
            }
        }
    }
}
