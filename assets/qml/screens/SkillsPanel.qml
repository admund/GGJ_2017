import QtQuick 2.0

import "../views/Colors.js" as Colors

Image {
    property QtObject skillsLogic

    source: "../../images/panel_objectives.png"

    Rectangle {
        id: fuellSkill

        width: parent.width / 3
        height: parent.height

        anchors {
            left: parent.left
        }

        color: Colors.Transparent

        Image {
            width: 30
            height: 30

            anchors {
                centerIn: parent
                verticalCenterOffset: 8
            }

            source: skillsLogic.fuellSkillCnt > 0
                    ? "../../images/poweruppanel_fuel.png" : "../../images/poweruppanel_inactive_fuel.png"
        }

        MouseArea {
            anchors.fill: parent

            onClicked: skillsLogic.fuellSkill()
        }
    }

    Rectangle {
        id: speedUpSkill

        width: parent.width / 3
        height: parent.height

        anchors {
            left: fuellSkill.right
        }

        color: Colors.Transparent

        Image {
            width: 30
            height: 30

            anchors {
                centerIn: parent
                verticalCenterOffset: 8
            }

            source: skillsLogic.speedUpSkillCnt > 0
                    ? "../../images/powerup_speed.png" : "../../images/poweruppanel_inactive_speed.png"
        }

        MouseArea {
            anchors.fill: parent

            onClicked: skillsLogic.speedUpSkill()
        }
    }

    Rectangle {
        id: doubleSkill

        width: parent.width / 3
        height: parent.height

        anchors {
            left: speedUpSkill.right
        }

        color: Colors.Transparent

        Image {
            width: 30
            height: 30

            anchors {
                centerIn: parent
                verticalCenterOffset: 8
            }

            source: skillsLogic.doubleSkillCnt > 0
                    ? "../../images/poweruppanel_doubleboost.png" : "../../images/poweruppanel_inactive_doubleboost.png"
        }

        MouseArea {
            anchors.fill: parent

            onClicked: skillsLogic.doubleSkill()
        }
    }
}
