import QtQuick.Controls 2.0
import QtQuick 2.7
import QtMultimedia 5.5

import "../views/Colors.js" as Colors
import "../appStructure"
import "../views"
import ".."

GameScreen {
    id: airportSCreen

    SoundEffect {
        id: crashSound
        loops: 1
        source: "../../fonts/wypadek_1.wav"
    }

    Timer {
        interval: 1
        running: _logic.airportLogic.playCrashSound
        repeat: true
        onTriggered: {
            _logic.airportLogic.playCrashSound = false
            crashSound.play()
        }
    }

    SoundEffect {
        id: loadupSound
        loops: 1
        source: "../../fonts/loadup_1.wav"
    }

    Timer {
        interval: 1
        running: _logic.airportLogic.playLoadupSound
        repeat: true
        onTriggered: {
            _logic.airportLogic.playLoadupSound = false
            loadupSound.play()
        }
    }

    SoundEffect {
        id: flyawaySound
        loops: 1
        source: "../../fonts/wylot_1.wav"
    }

    Timer {
        interval: 1
        running: _logic.airportLogic.playFlyawaySound
        repeat: true
        onTriggered: {
            _logic.airportLogic.playFlyawaySound = false
            flyawaySound.play()
        }
    }

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

    WinLoosePopUp {
        anchors.fill: airportGrid

        showLoose: _logic.airportLogic.score.badScore > 4
        showWin: _logic.airportLogic.score.goodScore > 2
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
        id: exitButton
        width: 50
        height: 50

        color: Colors.Transparent

        anchors {
            right: flagController.left
            top: parent.top
        }

        Image {
            id: name

            width: 50
            height: 50

            anchors.fill: parent

            source: backMouse.containsMouse ? "../../images/button_back_hover.png" : "../../images/button_back.png"
        }

        MouseArea {
            id: backMouse
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                _logic.showAirport = false
                airportLogic.exit()
            }
        }
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

    Rectangle {
        id: clearButton
        width: 10
        height: 10

        anchors.top: magicButton.bottom

        color: airportLogic.editMode ? Colors.Red : Colors.Transparent

        MouseArea {
            anchors.fill: parent

            onClicked: airportLogic.clearMap()
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
        id: spawnTimer1
        interval: 0
        repeat: false
        running: _logic.showAirport

        onTriggered: {
            airportLogic.spawn()
        }
    }

    Timer {
        id: spawnTimer
        interval: 30000 // TODO CONFIG!!!
        repeat: true
        running: !airportLogic.editMode && _logic.showAirport

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
