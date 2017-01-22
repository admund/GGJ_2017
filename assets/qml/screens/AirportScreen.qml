import QtQuick.Controls 2.0
import QtQuick 2.7

import "../views/Colors.js" as Colors
import "../appStructure"
import "../views"

GameScreen {
    id: airportSCreen

    property QtObject airportLogic: _logic.airportLogic

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

            Image {
                width: parent.width
                height: parent.height

                anchors.centerIn: parent

                rotation: airportGridModelRole.tileRotation

//                OpenSansText {
//                    anchors.fill: parent
//                    anchors.centerIn: parent

//                    text: airportGridModelRole.touchedBy

//                    color: Colors.Black
//                }

                source: getTile(airportGridModelRole.tileType)
            }

            MouseArea {
                id: tileTypeClick
                width: parent.width/2
                height: parent.height

                onClicked: {
                    if (airportLogic.editMode) {
                        airportGridModelRole.tileType = (airportGridModelRole.tileType + 1) % 10
                    }
                }
            }

            MouseArea {
                id: tileRotationClick
                width: parent.width/2
                height: parent.height

                anchors.left: tileTypeClick.right

                onClicked: {
                    if (airportLogic.editMode) {
                        airportGridModelRole.tileRotation = airportGridModelRole.tileRotation + 90
                        if (airportGridModelRole.tileRotation >= 360) {
                            airportGridModelRole.tileRotation = airportGridModelRole.tileRotation - 360
                        }
                    }
                }
            }
        }
    }

    Repeater {
        model: airportLogic.planeList

        delegate: Plane {
            id: plane
            planModel: planeModelRole

            isSelected: airportLogic.selectedPlane === index
        }
    }

    FlagController {
        id: flagController

        width: 300

        flagControllerLogic: airportLogic.flagController

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

    Image {
        height: 36
        anchors {
            left: parent.left
            right: flagController.left
            bottom: parent.bottom
        }

        source: "../../images/pasekdolny.png"
    }

    DropPowerUp {
        skillsLogic: airportLogic.skills
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

    Rectangle {
        id: magicButton
        width: 10
        height: 10

        color: airportLogic.editMode ? Colors.Yellow : Colors.Transparent

        MouseArea {
            anchors.fill: parent

            onClicked: airportLogic.editMode = !airportLogic.editMode
        }
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
        running: _logic.showAirport

        onTriggered: {
            airportLogic.spawn()
        }
    }

    function getTile(tileType) {
        if (tileType === 1) {
            return "../../images/tlo_pas.png"//ROAD
        } else if (tileType === 2) {
            return "../../images/tlo_hangar.png"//BUILDINGS
        } else if (tileType === 3) {
            return "../../images/tlo_woda.png"//SEA
        } else if (tileType === 4) {
            return "../../images/tlo_pas_poczatek.png"//RUNWAY_START
        } else if (tileType === 5) {
            return "../../images/tlo_parking2.png"//Colors.Red
        } else if (tileType === 6) {
            return "../../images/tlo_rozek.png"//GRASS_2
        } else if (tileType === 7) {
            return "../../images/tlo_parking.png"//ROAD_2
        } else if (tileType === 8) {
            return "../../images/tlo_lampki.png"//GRASS_3
        } else if (tileType === 9) {
            return "../../images/tlo_wiatrolap.png"//GRASS_4
        } else {
            return "../../images/tlo_ciemne.png"//GRASS
        }
    }
}
