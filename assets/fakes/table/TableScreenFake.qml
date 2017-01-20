import QtQuick 2.0

Item {
    property QtObject model: QtObject {
        property bool isDealer: true
    }

    property QtObject actionsPanel: QtObject {
        property QtObject model: QtObject {
            property bool isPlayerTurn: true
            property bool canCheck: false
            property bool canCall: true
            property bool canRaise: true
            property int callValue: 12
            property int minRaise: 23
            property int maxRaise: 34
        }
    }

    property QtObject playerSlot: QtObject {
        property QtObject model: QtObject {
            property string nick: "JosevStallone"
            property int money: 3492
            property double moveTime: 0.7
            property ListModel cards: ListModel {
                property bool isDimmed: false
            }
        }
    }

    property QtObject villainSlot: QtObject {
        property QtObject model: QtObject {
            property string nick: "AdolfoHeller"
            property int money: 5432
            property double moveTime: 0.7
            property int potWon: 433
            property ListModel cards: ListModel {
                property bool isDimmed: true
            }
        }
    }

    Component.onCompleted: {
        var component = Qt.createComponent("CardFake.qml")

        var card1 = component.createObject(parent, {figure:1, color:4, isSelected:false})
        var card2 = component.createObject(parent, {figure:2, color:3, isSelected:true})
        playerSlot.model.cards.append(card1)
        playerSlot.model.cards.append(card2)

        var card3 = component.createObject(parent, {figure:3, color:2, isSelected:false})
        var card4 = component.createObject(parent, {figure:4, color:1, isSelected:true})
        villainSlot.model.cards.append(card3)
        villainSlot.model.cards.append(card4)
    }
}
