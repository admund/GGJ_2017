import QtQuick 2.7

import "../appStructure/ImagePath.js" as ImagePath

Image {
    id: backgroundImage

    property alias background: backgroundImage.source
    property alias foreground: foregroundImage.source

    property real value

    Image {
        id: foregroundImage
        width: parent.width * parent.value
        height: parent.height

        fillMode: Image.PreserveAspectCrop
        horizontalAlignment: Image.AlignLeft
    }

//    Behavior on value { NumberAnimation { duration: 500 } }
}
