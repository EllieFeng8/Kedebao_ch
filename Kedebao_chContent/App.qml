import QtQuick
import Kedebao_ch
import QtQuick.VirtualKeyboard
import QtQuick.Controls
import QtQuick.Layouts
import Core 1.0

Window {
    id:root
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "Kedebao_ch"
    //property bool isBig: false

    property var activeAppWindow: root

    function toggleFullscreenForActiveWindow() {
        var w = activeAppWindow || root
        if (w.visibility === Window.FullScreen)
            w.showNormal();
        else
            w.showFullScreen();
    }



    Component.onCompleted: {
        root.showFullScreen();
    }

    ProjectMainScreen {
        id: mainScreen
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

    }
    // 鍵盤快捷鍵：對目前滑鼠點擊(Active)的視窗切換全螢幕
    Shortcut {
        sequence: "F11"
        onActivated: root.toggleFullscreenForActiveWindow()
    }

    Item {
        id: kbContainer
        parent: Overlay.overlay
        z: 9999
        width: parent.width * 0.4

        // 顯示/隱藏跟著輸入法
        visible: Qt.inputMethod.visible

        // 容器位置（你要懸浮）
        x: (parent.width - width) / 2
        y: parent.height - height - 20

        // ⭐ 把手（在鍵盤外面）
        // Rectangle {
        //     id: handle
        //     width: parent.width
        //     height: 28
        //     radius: 8
        //     opacity: 0.35
        //     anchors.top: parent.top
        // }

        Rectangle {
            id: handle
            width: parent.width
            height: 28
            radius: 8
            color: "#888888"
            opacity: 0.25
            anchors.top: parent.top
        }

        MouseArea {
            anchors.fill: handle
            drag.target: kbContainer
            drag.axis: Drag.XAndYAxis
        }

        // ⭐ 鍵盤本體往下放，避開把手
        InputPanel {
            id: inputPanel
            anchors.top: handle.bottom
            width: parent.width
        }

        // ⭐ 容器高度 = 把手 + 鍵盤
        height: handle.height + inputPanel.height
    }
    // ===== 對外呼叫 =====
    function showAbnormal(msg) {
        abnormalDialog.message = msg
        abnormalDialog.open()
        autoCloseTimer.restart()
    }
    // ===== 10秒計時器 =====
    Timer {
        id: autoCloseTimer
        interval: 5 * 1000
        repeat: false
        onTriggered: abnormalDialog.close()
    }

    Connections {
        target:Kdb // ← 這是你 main.cpp 設進來的 contextProperty 名稱
        function onAbnormalRaised(msg) {
            root.showAbnormal(msg)
        }
    }
    Item {
        id: root1
        width: 800
        height: 480
        anchors.centerIn: parent


        // ===== 異常 Dialog =====
        Dialog {
            id: abnormalDialog

            modal: true          // 是否阻擋背景操作
            focus: true
            anchors.centerIn: parent

            property string message: "異常發生"

            width: 400
            height: 180

            background: Rectangle {
                radius: 12
                color: "#2b2b2b"
                border.color: "#ff4444"
                border.width: 2
            }

            contentItem: ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 15

                Label {
                    text: "⚠ 異常警告"
                    color: "#ff4444"
                    font.pixelSize: 20
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                }

                Label {
                    text: abnormalDialog.message
                    color: "white"
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }

                Button {
                    text: "確定"
                    Layout.alignment: Qt.AlignHCenter
                    onClicked: {
                        autoCloseTimer.stop()
                        abnormalDialog.close()
                    }
                }
            }

        }

        // ===== 測試 =====
        Component.onCompleted: {
            Qt.callLater(function() {
                showAbnormal("異常提醒！")
            })
        }
    }
}

