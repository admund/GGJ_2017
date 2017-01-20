import QtQuick 2.7

Item {
    id: sceneSwitcher

    signal screenSwitched

    property int animationDuration: 400
    property GameScreen nextScreen
    property GameScreen currentScreen

    anchors.fill: parent

    ParallelAnimation {
        id: switchAnimation
        onStarted: sceneSwitcher.nextScreen.visible = true
        onStopped: {
            sceneSwitcher.currentScreen.visible = false
            sceneSwitcher.currentScreen.screenDidDisappear()
            sceneSwitcher.currentScreen = sceneSwitcher.nextScreen
            sceneSwitcher.nextScreen = null

            sceneSwitcher.screenSwitched()
        }

        NumberAnimation {
            id: opacityAnimation1
            property: "opacity"
            duration: sceneSwitcher.animationDuration
            easing.type: Easing.OutCubic
            from: 1.0
            to: 0.0
        }

        NumberAnimation {
            id: xAnimation1
            property: "x"
            duration: sceneSwitcher.animationDuration
            easing.type: Easing.OutCubic
            from: 0
        }

        NumberAnimation {
            id: opacityAnimation2
            property: "opacity"
            duration: sceneSwitcher.animationDuration
            easing.type: Easing.OutCubic
            from: 0.0
            to: 1.0
        }

        NumberAnimation {
            id: xAnimation2
            property: "x"
            duration: sceneSwitcher.animationDuration
            easing.type: Easing.OutCubic
            to: 0
        }
    }

    function initWithScreen(screen) {
        currentScreen = screen
        currentScreen.visible = true
    }

    function switchScreenForward(targetScreen) {
        innerSwitchScreen(targetScreen, true)
    }

    function switchScreenBackward(targetScreen) {
        innerSwitchScreen(targetScreen, false)
    }

    function innerSwitchScreen(targetScreen, forward) {
        if (currentScreen === targetScreen) {
            return
        }

        if (switchAnimation.running && nextScreen === targetScreen) {
            return
        }

        if (switchAnimation.running) {
            switchAnimation.stop()
        }

        nextScreen = targetScreen

        nextScreen.screenWillAppear(forward)

        opacityAnimation1.target = currentScreen
        opacityAnimation2.target = nextScreen

        xAnimation1.target = currentScreen
        xAnimation1.to = (forward ? -1 : 1) * width * 0.5
        xAnimation2.target = nextScreen
        xAnimation2.from = (forward ? 1 : -1) * width * 0.5

        switchAnimation.start()
        targetScreen.focus = true
    }
}
