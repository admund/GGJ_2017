import QtQuick 2.0

import "../views/Colors.js" as Colors
import "../appStructure"

GameScreen {
    Image {
        anchors.fill: parent

        source: "../../images/wybor_mapy_tlo.png"

        ChooseMapElement {
            id: swiebodzinMap
            anchors {
                top: londonMap.top
                right: londonMap.left
                rightMargin: 30
            }

            level: 1
            imageName: "../../images/miasto_ilu_1.png"
            buttonName: "../../images/miasto_name_1.png"
            buttonHoverName: "../../images/miasto_name_1_hover.png"
        }

        ChooseMapElement {
            id: londonMap
            anchors.centerIn: parent

            level: 2
            imageName: "../../images/miasto_ilu_1.png"
            buttonName: "../../images/miasto_name_1.png"
            buttonHoverName: "../../images/miasto_name_1_hover.png"
        }

        ChooseMapElement {
            id: wypizdowMap
            anchors {
                top: londonMap.top
                left: londonMap.right
                leftMargin: 30
            }

            level: 2 // TODO add level 3
            imageName: "../../images/miasto_ilu_1.png"
            buttonName: "../../images/miasto_name_1.png"
            buttonHoverName: "../../images/miasto_name_1_hover.png"
        }
    }
}
