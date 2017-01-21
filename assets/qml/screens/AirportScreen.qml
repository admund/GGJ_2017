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

        cellWidth: parent.width / 21
        cellHeight: cellWidth

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

                color: getTile(airportGridModelRole.tileType)
            }

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    if (airportLogic.editMode) {
                        airportGridModelRole.tileType = (airportGridModelRole.tileType + 1) % 4
                    }
                }
            }
        }
    }

    FlagController {
        id: flagController

        anchors {
            bottom: parent.bottom
            right: parent.right
        }

        planeFlagModel: airportLogic.flagController.planeFlag
    }

    function getTile(tileType) {
        if (tileType === 1) {
            return Colors.Gray
        } else if (tileType === 2) {
            return Colors.White
        } else if (tileType === 3) {
            return Colors.Blue
        } else {
            return Colors.DarkGreen;
        }
    }
}
