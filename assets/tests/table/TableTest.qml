import QtQuick 2.7

Item {
    Timer {
        id: timer
        interval: 100

        onTriggered: {
            screenSwitcher.switchScreenForward(screenTable)
        }
    }

    Component.onCompleted: {
        timer.start()
    }
}

