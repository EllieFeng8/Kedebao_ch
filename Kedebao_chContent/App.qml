import QtQuick
import Kedebao_ch

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "Kedebao_ch"

    ProjectMainScreen {
        id: mainScreen
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }


}

