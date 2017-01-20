import QtQuick 2.7
import QtQuick.Controls 2.0

Image {
    id: autoRefreshingImage

    property int refreshInterval: 10000

    BusyIndicator {
        id: busyIndicator

        width: 30
        height: width
        anchors.centerIn: parent

        running: parent.status === Image.Loading
    }

    Timer {
        id: refreshTimer

        running: autoRefreshingImage.status === Image.Error
        interval: autoRefreshingImage.refreshInterval

        onTriggered: {
            autoRefreshingImage.refresh()
        }
    }

    function refresh() {
        var networkSource = source
        source = ""
        source = networkSource
    }
}
