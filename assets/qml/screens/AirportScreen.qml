import QtQuick.Controls 2.0
import QtQuick 2.7

import "../views/Colors.js" as Colors
import "../appStructure"
import "../views"

GameScreen {
    id: airportSCreen

    property QtObject airportLogic: _logic.airportLogic

    Rectangle {
        anchors.fill: parent

        color: Colors.DarkGreen
    }

    GridView {
        id: airportGrid

        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
            right: flagController.left
        }

        cellWidth: (parent.width - flagController.width) / 17
        cellHeight: cellWidth

        Component.onCompleted: {
            airportLogic.setCellSize()
        }

        interactive: false

        model: airportLogic.airportGrid
        clip: true

        delegate: Rectangle {
            width: airportGrid.cellWidth
            height: airportGrid.cellHeight

            color: Colors.Red

            Rectangle {
                width: parent.width * .95
                height: parent.height * .95

                anchors.centerIn: parent

                OpenSansText {
                    anchors.fill: parent
                    anchors.centerIn: parent

                    text: airportGridModelRole.touchedBy

                    color: Colors.Black
                }

                color: getTile(airportGridModelRole.tileType)
            }

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    if (airportLogic.editMode) {
                        airportGridModelRole.tileType = (airportGridModelRole.tileType + 1) % 6
                    }
                }
            }
        }
    }

    Repeater {
        model: airportLogic.planeList

        delegate: Item {
            Plane {
                id: plane
                planModel: planeModelRole

                isSelected: airportLogic.selectedPlane === index

                }

//                              TODO collider samolotu
//            Rectangle {
//                x: plane.x
//                y: plane.y
//                width: plane.width
//                height: plane.height
//                radius: width/2

//                color: Colors.Yellow
//            }
            }
    }

    FlagController {
        id: flagController

        width: 300

        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }

        planeModel: airportLogic.flagController.selectedPlane

        onClickFlagPanel: {
            if (index == 4) {
                airportLogic.changeSelectedPlane()
            } else {
                airportLogic.changeMoveDirection(index)
            }
        }
    }

    OpenSansText {
        id: goodScore

        width: 100
        height: 10

        text: "Good Score: " + airportLogic.score.goodScore
    }

    OpenSansText {
        id: badScore

        width: 100
        height: 10

        anchors.top: goodScore.bottom

        text: "Bad Score: " + airportLogic.score.badScore
    }

    Timer {
        interval: 100
        repeat: true
        running: airportLogic.planeList.count > 0

        onTriggered: {
            airportLogic.checkCollisions()
        }
    }

    Timer {
        id: spawnTimer
        interval: 0//20000
        repeat: false//true
        running: true

        onTriggered: {
            airportLogic.spawn()
        }
    }

    function getTile(tileType) {
        if (tileType === 1) {
            return Colors.Gray
        } else if (tileType === 2) {
            return Colors.White
        } else if (tileType === 3) {
            return Colors.Blue
        } else if (tileType === 4) {
            return Colors.Yellow
        } else if (tileType === 5) {
            return Colors.Red
        } else {
            return Colors.DarkGreen;
        }
    }
}
