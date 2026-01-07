import QtQuick
import QtQuick.Studio.DesignEffects
import QtQuick.Controls
import QtQuick.Effects

Rectangle {
    id: modeSwitch

    width: 1920
    height: 1080

    clip: true
    color: "#ffffff"
    property alias controlMouseArea: controlMouseArea
    property alias parameter: parameter
    property alias parameterMouseArea: parameterMouseArea
    property alias bigRollText: bigRollText
    property alias smallRollText: smallRollText
    property alias basicSwitchbig: basicSwitchbig
    property alias basicSwitchbigMouseArea: basicSwitchbigMouseArea
    property bool isBig: true

    Rectangle {
        width: 773
        height: 259
        anchors.horizontalCenter: parent.horizontalCenter
        y: 59
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
            id: element

            x: 27
            y: 24

            height: 49
            width: 179

            color: "#000000"
            font.pixelSize: 32
            font.weight: Font.DemiBold
            horizontalAlignment: Text.AlignLeft
            lineHeight: 22
            lineHeightMode: Text.FixedHeight
            font.bold: true
            text: "模式切換"
            verticalAlignment: Text.AlignVCenter
        }
        Image {
            id: basicSwitchbig
            x: 327
            y: 104
            source: "assets/basicSwitch.png"

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

            x: 174
            y: 168

            height: 39
            width: 75

            color: "#8f8f8f"
            font.pixelSize: 32
            font.weight: Font.Bold
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignTop
            text: "小捲"
        }
        Text {
            id: bigRollText

            x: 514
            y: 168

            height: 39
            width: 87

            color: "#000000"
            font.pixelSize: 32
            font.weight: Font.Bold
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignTop
            text: "大捲"
        }
    }
    Rectangle {
        width: 366
        height: 259
        anchors.horizontalCenter: parent.horizontalCenter
        y: 439
        radius: 40
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
            font.pointSize: parameterMouseArea.containsMouse ? 22 : 20
            text: "參數介面"
        }

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: parameterMouseArea.containsMouse ? true : false
            shadowColor: "#58000000"
            shadowBlur: 0.8
        }
        MouseArea {
            id: parameterMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
        }
    }

    Rectangle {
        width: 366
        height: 259
        anchors.horizontalCenter: parent.horizontalCenter
        y: 772
        radius: 40
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
            id: control
            font.weight: Font.Bold
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: controlMouseArea.containsMouse ? 22 : 20
            text: "控制介面"
        }

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: controlMouseArea.containsMouse ? true : false
            shadowColor: "#58000000"
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
