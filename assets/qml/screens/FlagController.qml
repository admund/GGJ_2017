import QtQuick 2.0

import "../views/Colors.js" as Colors

Rectangle {
    width: 200
    height: 300

    property QtObject planeFlagModel

    color: Colors.LightBlue

    Image {
        anchors.fill: parent

        source: getFlagImg(planeFlagModel)
    }

    function getFlagImg(planFlagModel) {
        if (planFlagModel.isRightFlagUp === planFlagModel.isLeftFlagUp) {
            if (planFlagModel.isRightFlagUp) {
                return "../../images/flag_go.png"
            } else {
                return "../../images/flag_stop.png"
            }
        } else {
            if (planFlagModel.isRightFlagUp) {
                return "../../images/flag_right.png"
            } else {
                return "../../images/flag_left.png"
            }
        }
    }
}
