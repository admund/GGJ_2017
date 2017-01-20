import QtQuick 2.7

Item {
    id: fakeCpp

    property QtObject root: QtObject {
        property bool isDebugModeOn: false

        function qmlFullyLoaded() {
            console.log("FAKE: qmlFullyLoaded")
        }
    }

// ######################################################################
// Tests
//    SkillsTest {}
}
