import QtQuick 2.7

Item {
    Timer {
        id: timer
        interval: 100

        onTriggered: {
            screenSwitcher.switchScreenForward(skillsScreen)
            fakeCpp.root.skills.model.showSkillsScreen = true
        }
    }

    Component.onCompleted: {
        timer.start()
    }
}
