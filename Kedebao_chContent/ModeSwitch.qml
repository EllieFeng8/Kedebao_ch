import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import Kedebao_chContent

ModeSwitchUI {
    id: modeSwitch
    //property int pageNum = 1;
    basicSwitchbigMouseArea.onClicked: {
        AppState.isBig = !AppState.isBig
        //console.log("mode isbig",AppState.isBig)
        modeSwitch.visible = false
    }
    backMouseArea.onClicked: {
        modeSwitch.visible = false
    }
    parameterMouseArea.onClicked: {
        // parameterSetting.visible = true
        setParameterInterface(1);
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

    ParameterSetting2{
        id: parameterSetting2
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
    ParameterSetting3{
        id: parameterSetting3
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
    ParameterSetting4{
        id: parameterSetting4
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

    function setParameterInterface(pageNum){
        if(pageNum ==1){
            parameterSetting.visible = true
            parameterSetting2.visible = false
            parameterSetting3.visible = false
            parameterSetting4.visible = false
        }
        else if(pageNum ==2){
            parameterSetting.visible = false
            parameterSetting2.visible = true
            parameterSetting3.visible = false
            parameterSetting4.visible = false
        }
        else if(pageNum ==3){
            parameterSetting.visible = false
            parameterSetting2.visible = false
            parameterSetting3.visible = true
            parameterSetting4.visible = false
        }
        else if(pageNum ==4){
            parameterSetting.visible = false
            parameterSetting2.visible = false
            parameterSetting3.visible = false
            parameterSetting4.visible = true
        }
        else{
            parameterSetting.visible = false
            parameterSetting2.visible = false
            parameterSetting3.visible = false
            parameterSetting4.visible = false
        }

    }
}
