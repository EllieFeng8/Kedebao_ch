import QtQuick
import QtQuick.Controls

ProjectMainScreenUI {
    id: mainSwitch



    resetMouseArea.onClicked: {
        console.log("resetMouseAreaonClicked")
        lengthSet.text = "0"
        speedSet.text = "0"
        brakeDistance.text = "0"
        unwindingTension.text = "0"
        smallCoilTension.text = "0"
        bigCoilTension.text = "0"
    }

    lenthSettingmouseArea.onClicked: {
        //lenthSettingButton.scale = 1.5
        console.log("lenthSettingmouseAreaonClicked")
    }

    speedSettingmouseArea.onClicked: {
        //speedSettingButton.scale = 1.5
        console.log("speedSettingmouseAreaonClicked")
    }

    brakingDistanceMouseArea.onClicked: {
        console.log("brakingDistanceMouseAreaonClicked")
    }

    unwindingTensionMouseArea.onClicked: {
        console.log("unwindingTensionMouseAreaonClicked")
    }

    smallCoilTensionMouseArea.onClicked: {
        console.log("smallCoilTensionMouseAreaonClicked")
    }
    bigCoilTensionMouseArea.onClicked: {
        console.log("bigCoilTensionMouseAreaonClicked")
    }

    settingMouseArea.onClicked: {
        modeScreen.visible = true
        //bigRollTensionSetting.visible = modeScreen.isBig ? false : true
        //smallRollTensionSetting.visible =modeScreen.isBig ? true : false
        //modelPic.source = modeScreen.isBig ? "assets/bigpic.png" : "assets/smallpic.png"
        console.log("modeScreen.isBig:",modeScreen.isBig)

    }

    uvLampMouseArea.onClicked: {
        clicked = !clicked
        uvLampUI.source = clicked ?"assets/Group11.png" : "assets/Group 34.png"
    }
    whiteLightMouseArea.onClicked: {
        clicked1 = !clicked1
        whiteLightUI.source = clicked1 ?"assets/Group11.png" : "assets/Group 34.png"
    }
    lightBelowUIMouseArea.onClicked: {
        clicked2 = !clicked2
        lightBelowUI.source = clicked2 ?"assets/Group11.png" : "assets/Group 34.png"
    }

    flipImgMouseArea.onClicked: {
        clicked3 = !clicked3
        modelPic.source = clicked3 ? "assets/bigpic.png" : "assets/image 5.png"
        bigRollTensionSetting.x =clicked3 ? 415 :  1596
        bigRollTensionSetting.y =clicked3 ? 311 :  411
        unWindingTension.x = clicked3 ? 1295  : 445
        smallRollTensionSetting.x =clicked3 ? 723  :  1229

    }
    ModeSwitch{
        id: modeScreen

        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
