import QtQuick
import Kedebao_ch
import QtQuick.VirtualKeyboard

Window {
    id:root
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "Kedebao_ch"
    //property bool isBig: false


    ProjectMainScreen {
        id: mainScreen
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }



}

