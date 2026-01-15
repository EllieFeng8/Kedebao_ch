import QtQuick
import QtQuick.Studio.DesignEffects
import QtQuick.Controls
import QtQuick.Effects

Rectangle {
    id: modeSwitch

    width: 1920
    height: 1080

    clip: true
    color:"#eeeeef"
    property alias controlMouseArea: controlMouseArea
    property alias parameter: parameter
    property alias parameterMouseArea: parameterMouseArea
    property alias bigRollText: bigRollText
    property alias smallRollText: smallRollText
    property alias basicSwitchbig: basicSwitchbig
    property alias basicSwitchbigMouseArea: basicSwitchbigMouseArea

    property alias backMouseArea: backMouseArea

    Image {
        id: back
        x:22
        y:20
        source: "assets/Group 36.png"

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: backMouseArea.containsMouse ? true : false
            shadowColor: "#58000000"
            shadowBlur: 0.8
        }
        MouseArea {
            id: backMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            //onClicked: modeSwitch.visible = false
        }
    }
    //模式
    Rectangle {
        width: 830
        height: 766
        //anchors.horizontalCenter: parent.horizontalCenter
        y: 226
        x: 85
        radius: 40
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "#FEFBFC"
            }
            GradientStop {
                position: 0.5
                color: "#eaeaea"
            }
        }
        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowColor: "#c4c4c6"
            shadowBlur: 0.8
            shadowHorizontalOffset: 3
            shadowVerticalOffset: 3
        }

        Text {
            id: element

            x: 27
            y: 24

            height: 49
            width: 179

            color: "#000000"
            font.pixelSize: 64
            font.weight: Font.DemiBold
            horizontalAlignment: Text.AlignLeft
            //lineHeight: 22
            lineHeightMode: Text.FixedHeight
            font.bold: true
            text: "模式切換"
            padding:10
            //verticalAlignment: Text.AlignVCenter
        }
        Image {
            id: basicSwitchbig
            x: 138
            y: 275
            source: AppState.isBig ? "assets/basicSwitch.png":"assets/basicSwitchL.png"

            layer.enabled: true
            layer.effect: MultiEffect {
                shadowEnabled: basicSwitchbigMouseArea.containsMouse ? true : false
                shadowColor: "#58000000"
                shadowBlur: 0.8
            }

            MouseArea {
                id: basicSwitchbigMouseArea
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
            }
        }
        Text {
            id: smallRollText

            x: 85
            y: 509

            //height: 59
            width: 65

            color: AppState.isBig ?   "#8f8f8f" : "#000000"
            font.pixelSize: AppState.isBig ? 64 : 68
            font.weight: Font.Bold
            verticalAlignment: Text.AlignVCenter//文字垂直置中
            horizontalAlignment: Text.AlignHCenter//文字水平之中
            text: "小\n捲"

            layer.enabled: true
            layer.effect: MultiEffect {
                shadowEnabled: AppState.isBig ? false : true
                shadowColor: "#58000000"
                shadowBlur: 0.8
            }
        }
        Text {
            id: bigRollText

            x: 690
            y: 509

            //height: 59
            width: 65

            color: AppState.isBig ?  "#000000":"#8f8f8f"
            font.pixelSize: AppState.isBig ? 68 : 64
            font.weight: Font.Bold
            verticalAlignment: Text.AlignVCenter//文字垂直置中
            horizontalAlignment: Text.AlignHCenter//文字水平之中
            text: "大\n捲"
            layer.enabled: true
            layer.effect: MultiEffect {
                shadowEnabled: AppState.isBig ? true :  false
                shadowColor: "#58000000"
                shadowBlur: 0.8
            }
        }
    }
    //參數
    Rectangle {
        width: 842
        height: 360
        //anchors.horizontalCenter: parent.horizontalCenter
        y: 226
        x:993
        radius: 40
        //border.color:"#b7c6c6c6"
        gradient: Gradient {
            //orientation: Gradient.Horizontal
            GradientStop {
                position: 0.0
                color: "#FEFBFC"
            }
            GradientStop {
                position: 0.5
                color: "#eaeaea"
            }
        }

        Text {
            id: parameter
            font.weight: Font.Bold
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: parameterMouseArea.containsMouse ? 54 : 48
            text: "參數介面"
            color:"#16121c"
        }

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled:  true
            shadowColor: parameterMouseArea.containsMouse ?"#58000000" : "#c4c4c6"
            shadowBlur: 0.8
        }
        MouseArea {
            id: parameterMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
        }
    }
    //控制
    Rectangle {
        width: 842
        height: 360
        //anchors.horizontalCenter: parent.horizontalCenter
        y: 632
        x:993
        radius: 40
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "#FEFBFC"
            }
            GradientStop {
                position: 0.5
                color: "#eaeaea"
            }
        }
        Text {
            id: control
            font.weight: Font.Bold
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: controlMouseArea.containsMouse ? 54 : 48
            text: "控制介面"
            color:"#16121c"
        }

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowColor: controlMouseArea.containsMouse ? "#58000000" : "#c4c4c6"
            shadowBlur: 0.8
        }
        MouseArea {
            id: controlMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
        }
    }
}
