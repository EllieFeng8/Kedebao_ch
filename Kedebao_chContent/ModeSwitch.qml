import QtQuick
import QtQuick.Controls
import QtQuick.Effects

ModeSwitchUI {
    id: modeSwitch

    basicSwitchbigMouseArea.onClicked: {
        isBig = !isBig
        basicSwitchbig.source = isBig ? "assets/basicSwitch.png":"assets/basicSwitchL.png"
        bigRollText.color = isBig ?  "#000000" : "#8f8f8f"
        smallRollText.color = isBig ? "#8f8f8f" :"#000000"

        modeSwitch.visible = false
    }

    parameterMouseArea.onClicked: {
        parameterSetting.visible = true
    }

    controlMouseArea.onClicked: {
        operateScreen.visible = true
    }


    ParameterSetting{
        id: parameterSetting
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }



    OperateInterface{
        id: operateScreen
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
