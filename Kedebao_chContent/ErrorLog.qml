import QtQuick
import QtQuick.Controls
import QtQuick.Studio.DesignEffects
import QtQuick.Effects
import Core 1.0

Rectangle {
    id: root
    width: 1920
    height: 1080
    color: "#F0F0F2"

    MouseArea {
        anchors.fill: parent
    }
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
            onClicked: root.visible = false
        }
    }
    Rectangle {
        id: logRec
        x: 120
        y: 142
        width: 1688
        height: 908
        radius: 40
        //border.color: "#2a000000"

        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "#FEFBFC"
            }
            GradientStop {
                position: 1
                color: "#eaeaea"
            }
        }

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowColor: "#82413f3f"
            shadowBlur: 0.8
            shadowHorizontalOffset: 0
            shadowVerticalOffset: 0
        }

        Text {
            id: output1_1Text
            text: "Error Log"
            font.pointSize: 14
            padding: 10
            font.weight: Font.Bold
            anchors.horizontalCenter: parent.horizontalCenter
        }

        ScrollView {
            id: scrollView

            anchors.fill:parent

            Text {
                id: report
                // anchors.fill:parent
                width: 1600
                height: 800
                anchors.left: parent.left
                anchors.leftMargin:50
                anchors.top: parent.top
                anchors.topMargin:80
                font.pixelSize: 30
                font.weight: Font.Bold
                lineHeight:1.5
                lineHeightMode: Text.ProportionalHeight
                font.bold: true
                color: "#ed384a"
                wrapMode: TextArea.Wrap
                text: Kdb.errorLog
            }
        }
    }
}