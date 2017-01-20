import QtQuick 2.7

import "../views/Colors.js" as Colors

Loader {
    id: gameLoader

    property bool isCppAvailable: (typeof _cppLogic !== "undefined")

    Text {
        visible: !isCppAvailable
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 5
        }
        z: 10

        color: Colors.DefaultTextColor
        font.pointSize: 20
        opacity: 0.15

        text: visible ? (gameLoader.width + " x " + gameLoader.height + " " + _sizeSelector.deviceType) : ""
    }

    Connections {
        target: gameLoader

        onWidthChanged: updateDeviceType()
        onHeightChanged: updateDeviceType()
    }

    Connections {
        target: isCppAvailable ? null : _sizeSelector
        enabled: !isCppAvailable

        ignoreUnknownSignals: true

        onQmlFileSelectorChanged: {
            print ("-------------------------> Device type is now", _sizeSelector.deviceType)
            gameLoader.source = "DeviceSizeDependentGame.qml"
        }
    }

    function updateDeviceType() {
        if (!isCppAvailable) {
            _sizeSelector.screenSizeChanged(width, height)
        }
    }

    Component.onCompleted: {
        if (!isCppAvailable) {
            updateDeviceType()
        } else {
            gameLoader.source = "DeviceSizeDependentGame.qml"
        }
    }
}
