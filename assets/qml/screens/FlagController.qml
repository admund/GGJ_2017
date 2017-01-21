import QtQuick 2.0

import "../views/Colors.js" as Colors

Rectangle {
    width: 200
    height: 300

    property QtObject planeModel

    property bool isRightFlagUp: planeModel ? planeModel.isRightFlagUp : false
    property bool isLeftFlagUp: planeModel ? planeModel.isLeftFlagUp : false

    color: Colors.LightBlue

    Image {
        anchors.fill: parent

//        source: getFlagImg(planeFlagModel)
        source: getFlagImg()
    }

    function getFlagImg() {
        if (isRightFlagUp === isLeftFlagUp) {
            if (isRightFlagUp) {
                return "../../images/flag_go.png"
            } else {
                return "../../images/flag_stop.png"
            }
        } else {
            if (isRightFlagUp) {
                return "../../images/flag_right.png"
            } else {
                return "../../images/flag_left.png"
            }
        }
    }
}
