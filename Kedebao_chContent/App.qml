import QtQuick
import Kedebao_ch
import QtQuick.VirtualKeyboard
import QtQuick.Controls

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

    // 取消輸入focus的 MouseArea
    MouseArea {
        anchors.fill: parent
        z: 0
        // 只想在空白處點到才觸發，所以不攔截內容的點擊
        propagateComposedEvents: true

        onPressed: (mouse) => {
            // 如果點到的是 TextInput/TextField 就不要清（讓它正常取得 focus）
            const o = root.contentItem.childAt(mouse.x, mouse.y)
            console.log(o.acceptsInputMethod,o.inputMethodComposing);
            if (o && (o.acceptsInputMethod || o.inputMethodComposing !== undefined)) {
                mouse.accepted = false
                return
            }

            // 清掉 focus + 收鍵盤
            root.contentItem.forceActiveFocus()
            Qt.inputMethod.hide()
            mouse.accepted = false
        }
    }


    // InputPanel {
    //     id: inputPanel
    //     parent: Overlay.overlay
    //     z: 9999
    //     width: 800
    //     x: (parent.width - width) / 2
    //     y: parent.height - height - 20
    //
    //     visible: Qt.inputMethod.visible
    //
    //     // 拖曳把手（不要蓋住鍵盤按鍵）
    //     Rectangle {
    //         id: handle
    //         width: parent.width
    //         height: 28
    //         radius: 8
    //         anchors.top: parent.top
    //         anchors.horizontalCenter: parent.horizontalCenter
    //         opacity: 0.15
    //     }
    //
    //     MouseArea {
    //         anchors.fill: handle
    //         drag.target: inputPanel
    //         drag.axis: Drag.XAndYAxis
    //     }
    // }

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


}

