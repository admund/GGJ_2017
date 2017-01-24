import QtQuick 2.0

import "views/Colors.js" as Colors

Rectangle {
    property QtObject airportLogic

    property bool showWin
    property bool showLoose

    color: showWin || showLoose ? "#66000000" : Colors.Transparent

    Image {
        id: winPopUp

        width: 725
        height: 393

        anchors.centerIn: parent

        visible: showWin

        source: "../images/popup_win.png"

        Image {
            id: playAgainButton

            width: 114
            height: 30

            anchors {
                right: winPopUp.horizontalCenter
                rightMargin: width/2
                bottom: winPopUp.bottom
                bottomMargin: height*3
            }

            source: mousePlayAgain.containsMouse ? "../images/button_playagain_hover.png" : "../images/button_playagain.png"

            MouseArea {
                id: mousePlayAgain
                anchors.fill: parent
                hoverEnabled: true

                onClicked: _logic.airportLogic.playAgain(_logic.loadinglevelId)
            }
        }

        Image {
            id: backButton

            width: 114
            height: 30

            source: mouseGoBack.containsMouse ? "../images/button_goback_hover.png" : "../images/button_goback.png"

            anchors {
                left: winPopUp.horizontalCenter
                leftMargin: width/2
                bottom: winPopUp.bottom
                bottomMargin: height*3
            }

            MouseArea {
                id: mouseGoBack
                anchors.fill: parent
                hoverEnabled: true

                onClicked: {
                    _logic.airportLogic.exit()
                    _logic.showAirport = false
                }
            }
        }
    }

    Image {
        id: loosePopUp

        width: 725
        height: 393

        anchors.centerIn: parent

        visible: showLoose

        source: "../images/popup_lose.png"

        Image {
            id: loosePlayAgainButton

            width: 114
            height: 30

            anchors {
                right: loosePopUp.horizontalCenter
                rightMargin: width/2
                bottom: loosePopUp.bottom
                bottomMargin: height*3
            }

            source: looseMousePlayAgain.containsMouse ? "../images/button_playagain_hover.png" : "../images/button_playagain.png"

            MouseArea {
                id: looseMousePlayAgain
                anchors.fill: parent
                hoverEnabled: true

                onClicked: _logic.airportLogic.playAgain(_logic.loadinglevelId)
            }
        }

        Image {
            id: looseBackButton

            width: 114
            height: 30

            source: looseMouseGoBack.containsMouse ? "../images/button_goback_hover.png" : "../images/button_goback.png"

            anchors {
                left: loosePopUp.horizontalCenter
                leftMargin: width/2
                bottom: loosePopUp.bottom
                bottomMargin: height*3
            }

            MouseArea {
                id: looseMouseGoBack
                anchors.fill: parent
                hoverEnabled: true

                onClicked: {
                    _logic.airportLogic.exit()
                    _logic.showAirport = false
                }
            }
        }
    }
}
