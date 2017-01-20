import QtQuick 2.7

import "Colors.js" as Colors

Rectangle {
    id: toast

    property var _textQueue: []

    implicitWidth: toastText.width + 50
    implicitHeight: toastText.height + 20
    radius: height / 2
    color: Colors.DarkGray
    opacity: 0.0

    OpenSansText {
        id: toastText
        anchors.centerIn: parent
        font.pointSize: toastDimensions.textPointSize
    }

    SequentialAnimation {
        id: showAnimation

        ScriptAction {
            script: {
                toastText.text = toast._textQueue[0]
            }
        }
        NumberAnimation { target: toast; property: "opacity"; from: 0.0; to: 1.0; duration: 250 }
        PauseAnimation { duration: 2000 }
        NumberAnimation { target: toast; property: "opacity"; from: 1.0; to: 0.0; duration: 250 }
        ScriptAction {
            script: {
                if (toast._textQueue.length > 0) {
                    toast._textQueue.splice(0,1)
                    timer.start()
                }
            }
        }
    }

    Timer {
        id: timer
        interval: 0

        onTriggered: updateQueue()
    }

    function show(text) {
        _textQueue.push(text)
        toast.updateQueue()
    }

    function updateQueue() {
        if (_textQueue.length < 1 || showAnimation.running) {
            return
        }

        showAnimation.start();
    }
}
