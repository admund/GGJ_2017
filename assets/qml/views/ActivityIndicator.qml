import QtQuick 2.7
import QtQuick.Controls 2.0

BusyIndicator {
    id: loader

    width: 40
    height: width

    opacity: running ? 1.0 : 0.0
    visible: opacity > 0.0

    Behavior on opacity { NumberAnimation { duration: 200 } }
}
