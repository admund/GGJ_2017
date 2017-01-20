import QtGraphicalEffects 1.0
import QtQuick.Controls 2.0
import QtQuick 2.7

Popup {
    id: baseDialog

    property Item screen

    property bool blurBackground: false
    property bool dimBackground: false

    property bool closeOnClickOutsideContent: false
    property bool isClosing: false
    property bool isOpen: false

    width: parent.width
    height: parent.height

    closePolicy: Popup.NoAutoClose
    padding: 0

    background: Item {
        id: background

        Rectangle {
            id: blackRect

            anchors.fill: parent
            opacity: dimBackground ? 0.6 : 0.0
            visible: opacity > 0
            color: "black"

            Behavior on opacity { NumberAnimation { duration: 250 } }
        }

        FastBlur {
            id: overlayBlur

            anchors.fill: parent
            opacity: blurBackground ? 1.0 : 0.0
            radius: 64
            visible: opacity > 0

            source: visible ? baseDialog.screen : undefined

            Behavior on opacity { NumberAnimation { duration: 250 } }

            Rectangle {
                anchors.fill: parent

                color: "black"
                opacity: 0.2
            }
        }
    }

    enter: Transition {
        NumberAnimation { property: "opacity"; from: 0.0; to: 1.0 }
    }

    exit: Transition {
        NumberAnimation { property: "opacity"; from: 1.0; to: 0.0 }
    }

    onClosed: {
        isClosing = false
        doAfterClose()
    }

    MouseArea {
        id: mouseArea

        anchors.fill: baseDialog.contentItem
        enabled: baseDialog.closeOnClickOutsideContent
        onClicked: {
            if (!isClosing && baseDialog.contentItem.childAt(mouse.x, mouse.y) === mouseArea) {
                doClose()
            }
        }
    }

    Connections {
        target: game
        ignoreUnknownSignals: true
        onNeedCloseAllDialogs: {
            doClose()
        }
    }

    function doOpen() {
        if (!isOpen && !isClosing) {
            doBeforeOpen()
            open()
            isOpen = true
        }
    }

    function doClose() {
        if (isOpen) {
            isClosing = true
            close()
            isOpen = false
        }
    }

    function doBeforeOpen() { }
    function doAfterClose() { }
}
