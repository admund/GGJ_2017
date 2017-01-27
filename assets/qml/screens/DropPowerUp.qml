import QtQuick 2.0

import "../views/Colors.js" as Colors

Item {
    property QtObject skillsLogic

    property int dropedSkill: -1 // 0 - fuel, 1 - speedUp, 2 - double
    property int dropedTime: 20000 //20
    property int moveDownSpeed: 2

    Timer {
        running: _logic.showAirport
        interval: dropedTime
        repeat: true
        onTriggered: {
            Math.random()
            dropRec.x = 100 + Math.random() * 700
            dropRec.y = -100

            dropedSkill = Math.random() * 3
        }
    }

    Timer {
        running: dropedSkill !== -1
        interval: 15
        repeat: true
        onTriggered: {
            dropRec.y += moveDownSpeed

            if (dropRec.y > 800) {
                dropedSkill = -1
            }
        }
    }

    Rectangle {
        id: dropRec

        width: parachute.width
        height: parachute.height + skill.height

        x: -500
        y: -500

        color: Colors.Transparent

        Image {
            id: parachute
            width: 30
            height: 30

            source: "../../images/spadochron.png"
        }

        Image {
            id: skill
            width: 22
            height: 22

            anchors {
                horizontalCenter: parachute.horizontalCenter
                top: parachute.bottom
            }

            source: getPowerUpImage(dropedSkill)

            function getPowerUpImage(skillId) {
                if (skillId === 1) {
                    return "../../images/powerup_speed.png"
                } else if (skillId === 2) {
                    return "../../images/powerup_doubleboost.png"
                } else {
                    return "../../images/powerup_fuel.png"
                }
            }
        }

        MouseArea {
            anchors.fill: parent

            onClicked: {
                skillsLogic.getSkill(dropedSkill)

                dropedSkill = -1
                dropRec.x = -500
                dropRec.y = -500
            }
        }
    }
}
