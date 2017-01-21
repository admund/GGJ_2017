import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

import "appStructure"

ApplicationWindow {
    id: rootWindow

    width: 1280//1366
    height: 720//768

    maximumWidth: width
    maximumHeight: height

    minimumWidth: width
    minimumHeight: height

    visibility: Window.AutomaticVisibility
    visible: true

    GameLoader {
        anchors.fill: parent
    }
}
