import QtQuick 2.7

Item {
    id: gameScreen

    signal androidBackPressed

    width: parent.width
    height: parent.height

    visible: false
    focus: true

    Keys.onBackPressed: {
        gameScreen.androidBackPressed()
    }

    function screenWillAppear(forwardAnimation) { }
    function screenDidDisappear() { }
}
