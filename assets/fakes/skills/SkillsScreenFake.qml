import QtQuick 2.0

Item {
    property QtObject model : QtObject {
        property bool showSkillsScreen: false

        property int slotIdSelected: -1
        property int skillIdSelected: -1

        property QtObject playerSkills: ListModel {
            property int count: 4
        }

        property QtObject allSkills: ListModel {
            property int count: 100
        }

        Component.onCompleted: {
            var playerSkillSlotComponent = Qt.createComponent("PlayerSkillSlotFake.qml")
            playerSkills.append(playerSkillSlotComponent.createObject(parent, {isLocked:false, skillName:"EMPTY"}))
            playerSkills.append(playerSkillSlotComponent.createObject(parent, {isLocked:false, skillName:"EMPTY"}))
            playerSkills.append(playerSkillSlotComponent.createObject(parent, {isLocked:true, skillName:"EMPTY"}))
            playerSkills.append(playerSkillSlotComponent.createObject(parent, {isLocked:false, skillName:"EMPTY"}))

            var skillComponent = Qt.createComponent("SkillFake.qml")
            var cnt = 0;
            for(var i=0; i<allSkills.count; i++) {
                var skillName = "all_skill" + i
                allSkills.append(skillComponent.createObject(parent, {skillName: skillName}))
            }
        }
    }

    function onClickPlayerSlot(index) {
        model.slotIdSelected = model.slotIdSelected !== index ? index : -1
        if (model.slotIdSelected === -1) {
            model.skillIdSelected = -1
        }
    }

    function onClickSkillItem(index) {
        if (model.slotIdSelected !== -1) {
            model.skillIdSelected = model.skillIdSelected !== index ? index : -1

            if (model.skillIdSelected !== -1) {
                timer.start()
            }
        }
    }

    Timer {
        id: timer

        property bool isInit: false
        interval: 500
        repeat: false

        onTriggered: {
            model.playerSkills.get(model.slotIdSelected).skillName = model.allSkills.get(model.skillIdSelected).skillName

            model.slotIdSelected = -1
            model.skillIdSelected = -1
        }
    }

    function delay(delayTime, cb) {
        timer.interval = delayTime;
        timer.repeat = false;
        timer.triggered.connect(cb);
        timer.start();
    }
}
