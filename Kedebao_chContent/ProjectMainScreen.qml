import QtQuick
import QtQuick.Controls
import Core 1.0
import Kedebao_ch
ProjectMainScreenUI {
    id: mainSwitch

    resetMouseArea.onClicked: {
        //console.log("resetMouseAreaonClicked")
        lengthSet.text = "0"
        speedSet.text = "0"
        brakeDistance.text = "0"
        unwindingTension.text = "0"
        smallCoilTension.text = "0"
        bigCoilTension.text = "0"
        Kdb.restBtn = !Kdb.restBtn
        console.log("restBtn",Kdb.restBtn)
    }

    settingMouseArea.onClicked: {
        modeScreen.visible = true
    }

    uvLampMouseArea.onClicked: {
        Kdb.uvLight = !Kdb.uvLight
        // uvLampUI.source = Kdb.uvLight ?"assets/Group11.png" : "assets/Group 34.png"
    }
    whiteLightMouseArea.onClicked: {
        Kdb.whiteLight = !Kdb.whiteLight
        //whiteLightUI.source = Kdb.whiteLight ?"assets/Group11.png" : "assets/Group 34.png"
    }
    lightBelowUIMouseArea.onClicked: {
        Kdb.bottomLight = !Kdb.bottomLight
        // lightBelowUI.source = Kdb.bottomLight ?"assets/Group11.png" : "assets/Group 34.png"
    }
    bigRollCutterSwitchMouseArea.onClicked: {
        Kdb.bigRollCutter = !Kdb.bigRollCutter
    //console.log("Kdb.bigRollCutter",Kdb.bigRollCutter)
    }

    flipImgMouseArea.onClicked: {
        isFlip = !isFlip
        //console.log("isFlip:",isFlip)
        //modelPic.source = clicked3 ? "assets/bigpic.png" : "assets/image 5.png"
        bigRollTensionSetting.x =isFlip ? 1596 :  422
        bigmodelPic.x = isFlip ? -1100 :  0
        // bigRollTensionSetting.y =isFlip ? 580 :  651
        unWindingTensionPosition.x =isFlip ? 370 :  1545
        smallRollCutterRec1.x = isFlip ? -187 :  100

        pressurePlate.x = isFlip ? 1260 :  370//小
        pressureRollerUp.x =isFlip ? 1550 :  660//小




    }
    ModeSwitch{
        id: modeScreen
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

}
