import QtQuick
import QtQuick.Controls
import QtQuick.Studio.DesignEffects
import QtQuick.Effects

Rectangle {
    id: root
    width: 1920
    height: 1080
    color: "#F0F0F2"


    property int topMargin: 65
    property int topMargin2: 25
    property int groupLeftMargin: 100
    property int setWidth: 190
    property int setWidth1: 173

    property int textInputLeft:203
    property int textInputLeft2:335


    Text {
        id: title
        x:935
        y:49
        text: "點位顯示"
        font.weight: Font.Bold
        font.pointSize: 20
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

    Image {
        id: firstPage
        x:164
        y:20
        source: "assets/Group 40.png"
        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: firstPageMouseArea.containsMouse ? true : false
            shadowColor: "#58000000"
            shadowBlur: 0.8
        }
        MouseArea {
            id: firstPageMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                //parameterSetting2.visible = true
                root.visible = false
            }
        }
    }
    //previousPage
    Image {
        id: previousPage
        x:284
        y:20
        source: "assets/Group 39.png"
        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: previousPageMouseArea.containsMouse ? true : false
            shadowColor: "#58000000"
            shadowBlur: 0.8
        }
        MouseArea {
            id: previousPageMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                //parameterSetting2.visible = true
                root.visible = false
            }
        }
    }

    Image {
        id: nextPage
        x:1613
        y:20
        source: "assets/Group 37.png"


    }
    Image {
        id: lastPage
        x:1733
        y:20
        source: "assets/Group 38.png"
    }
    //ANALOG OUTPUT
    Rectangle{
        id: output4Rec
        x:groupLeftMargin
        y:142
        width: 548
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
            id: output4_1Text
            text: "ANALOG OUTPUT"
            font.pointSize: 14
            font.weight: Font.Bold
            anchors.horizontalCenter: parent.horizontalCenter
        }
        //類比電壓輸出-1
        //放卷軸、主傳動輪
        Text {
            id:text_0
            //anchors.top: text_0.bottom
            //anchors.topMargin: 40
            x: 8
            y: 75
            width: setWidth1
            height: 24
            text: qsTr("類比電壓輸出-1
放卷軸、主傳動輪")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output4_0
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 203
                y: 20
                text:"V0"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output4_0.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch4_0
                x:282
                y:6
                scale: 0.5
                source: root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch4_0MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked = !root.clicked
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
            TextInput {
                id: output0_2
                width: 60
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                //color: "white"
                x: 386
                y: 20
                maximumLength: 4 //限制輸入4位整數
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output0_2.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: btn0
                x:460
                y:5
                scale: 0.8
                source: "assets/rectangle_35.png"
                Text {
                    id: btn0Name
                    text: qsTr("OK")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btn0MouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btn0MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    //onClicked: root.visible = false
                }
            }
        }
        //類比電壓輸出-2
        //大、小收卷軸
        Text {
            id:text_1
            anchors.top: text_0.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 85
            width: setWidth1
            height: 24
            text: qsTr("類比電壓輸出-2
大、小收卷軸")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output4_1
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 203
                y: 20
                text:"V1"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output4_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch4_1
                x:282
                y:6
                scale: 0.5
                source: root.clicked1 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch4_1MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked1 = !root.clicked1
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
            TextInput {
                id: output0_3
                width: 60
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                //color: "white"
                x: 386
                y: 20
                maximumLength: 4 //限制輸入4位整數
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output0_3.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: btn2
                x:460
                y:5
                scale: 0.8
                source: "assets/rectangle_35.png"
                Text {
                    id: btn2Name
                    text: qsTr("OK")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btn2MouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btn2MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    //onClicked: root.visible = false
                }
            }
        }

        //類比電壓輸出-3
        //切刀輪
        Text {
            id:text_2
            anchors.top: text_1.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 125
            width: setWidth1
            height: 24
            text: qsTr("類比電壓輸出-3
切刀輪")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output4_2
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 203
                y: 20
                text:"V2"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output4_2.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch4_2
                x:282
                y:6
                scale: 0.5
                source: root.clicked2 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch4_2MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked2 = !root.clicked2
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
            TextInput {
                id: output1_2
                width: 60
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                //color: "white"
                x: 386
                y: 20
                maximumLength: 4 //限制輸入4位整數
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output0_2.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: btn1
                x:460
                y:5
                scale: 0.8
                source: "assets/rectangle_35.png"
                Text {
                    id: btn1Name
                    text: qsTr("OK")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btn1MouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btn1MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    //onClicked: root.visible = false
                }
            }
        }

        //類比電壓輸出-4
        //耳料收卷
        Text {
            id:text_3
            anchors.top: text_2.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 165
            width: setWidth1
            height: 24
            text: qsTr("類比電壓輸出-4
耳料收卷")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output4_3
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 203
                y: 20
                text:"V3"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output4_3.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch4_3
                x:282
                y:6
                scale: 0.5
                source: root.clicked3 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch4_3MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked3 = !root.clicked3
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
            TextInput {
                id: output0_5
                width: 60
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                //color: "white"
                x: 386
                y: 20
                maximumLength: 4 //限制輸入4位整數
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output0_5.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: btn4
                x:460
                y:5
                scale: 0.8
                source: "assets/rectangle_35.png"
                Text {
                    id: btn4Name
                    text: qsTr("OK")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btn4MouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btn4MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    //onClicked: root.visible = false
                }
            }
        }

    }

    //IPC-INPUT
    Rectangle{
        id: output5Rec
        anchors.left: output4Rec.right
        anchors.leftMargin: groupLeftMargin
        y:142
        width: 488
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
            id: output1_2Text
            text: "IPC-INPUT"
            font.pointSize: 14
            font.weight: Font.Bold
            anchors.horizontalCenter: parent.horizontalCenter
        }
        //啟動
        Text {
            id:text_2_0
            x: 8
            y: 75
            width: setWidth
            height: 24
            text: qsTr("啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output2_01
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:"I4.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output2_01.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status1
                x: 336
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status1MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    //cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        // status0.color = "red"
                        // status0.layer.effect.shadowColor = "red"
                    }
                }
            }
        }
        //放卷張力自動
        Text {
            id:text_2_1
            anchors.top: text_2_0.bottom
            anchors.topMargin: topMargin2
            x: 8
            //y: 85
            width: setWidth
            height: 24
            text: qsTr("停止")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output2_11
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: parent.top
                text:"I4.01"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output2_11.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status2
                x: 336
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: "#88FF0A"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: "#88FF0A"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status2MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    //cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        // status0.color = "red"
                        // status0.layer.effect.shadowColor = "red"
                    }
                }
            }
        }

        //異常復歸
        Text {
            id:text_2_2
            anchors.top: text_2_1.bottom
            anchors.topMargin: topMargin2
            x: 8
            //y: 125
            width: setWidth
            height: 24
            text: qsTr("異常復歸")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output2_21
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: parent.top
                text:"I4.02"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output2_21.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status3
                x: 336
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: "#88FF0A"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: "#88FF0A"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status3MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    //cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        // status0.color = "red"
                        // status0.layer.effect.shadowColor = "red"
                    }
                }
            }
        }

        //主機寸動正轉
        Text {
            id:text_2_3
            anchors.top: text_2_2.bottom
            anchors.topMargin: topMargin2
            x: 8
            //y: 165
            width: setWidth
            height: 24
            text: qsTr("主機寸動正轉")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output2_31
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: parent.top
                text:"I4.03"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output2_31.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status4
                x: 336
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: "#88FF0A"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: "#88FF0A"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status4MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    //cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        // status0.color = "red"
                        // status0.layer.effect.shadowColor = "red"
                    }
                }
            }
        }
        //主機寸動反轉
        Text {
            id:text_2_4
            anchors.top: text_2_3.bottom
            anchors.topMargin: topMargin2
            x: 8
            y: 205
            width: setWidth
            height: 24
            text: qsTr("主機寸動反轉")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output2_41
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: parent.top
                text:"I4.04"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output2_41.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status5
                x: 336
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: "#88FF0A"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: "#88FF0A"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status5MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    //cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        // status0.color = "red"
                        // status0.layer.effect.shadowColor = "red"
                    }
                }
            }
        }
        //小卷收卷寸動正轉
        Text {
            id:text_2_5
            anchors.top: text_2_4.bottom
            anchors.topMargin: topMargin2
            x: 8
            y: 205
            width: setWidth
            height: 24
            text: qsTr("小卷收卷寸動正轉")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output2_51
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: parent.top
                text:"I4.05"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output2_51.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status6
                x: 336
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: "#88FF0A"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: "#88FF0A"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status6MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    //cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        // status0.color = "red"
                        // status0.layer.effect.shadowColor = "red"
                    }
                }
            }
        }
        //小卷收卷寸動反轉
        Text {
            id:text_2_6
            anchors.top: text_2_5.bottom
            anchors.topMargin: topMargin2
            x: 8
            //y: 245
            width: setWidth
            height: 24
            text: qsTr("小卷收卷寸動反轉")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output2_61
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:"I4.06"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output2_61.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status7
                x: 336
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: "#88FF0A"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: "#88FF0A"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status7MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    //cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        // status0.color = "red"
                        // status0.layer.effect.shadowColor = "red"
                    }
                }
            }
        }
        //放卷軸寸動反轉選擇
        Text {
            id:text_2_7
            anchors.top: text_2_6.bottom
            anchors.topMargin: topMargin2
            x: 8
            //y: 285
            width: setWidth
            height: 24
            text: qsTr("放卷軸寸動反轉選擇")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output2_71
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:"I4.07"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output2_71.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status8
                x: 336
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: "#88FF0A"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: "#88FF0A"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status8MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    //cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        // status0.color = "red"
                        // status0.layer.effect.shadowColor = "red"
                    }
                }
            }
        }
        //放卷軸寸動啟動
        Text {
            id:text_2_8
            anchors.top: text_2_7.bottom
            anchors.topMargin: topMargin2
            x: 8
            //y: 325
            width: setWidth
            height: 24
            text: qsTr("放卷軸寸動啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output2_81
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:"I4.08"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output2_81.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status9
                x: 336
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: "#88FF0A"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: "#88FF0A"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status9MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    //cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        // status0.color = "red"
                        // status0.layer.effect.shadowColor = "red"
                    }
                }
            }
        }
        //收卷寸動反轉選擇
        Text {
            id:text_2_9
            anchors.top: text_2_8.bottom
            anchors.topMargin: topMargin2
            x: 8
            //y: 365
            width: setWidth
            height: 24
            text: qsTr("收卷寸動反轉選擇")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output2_91
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:"I4.09"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output2_91.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status10
                x: 336
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: "#88FF0A"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: "#88FF0A"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status10MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    //cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        // status0.color = "red"
                        // status0.layer.effect.shadowColor = "red"
                    }
                }
            }
        }
        //收卷寸動啟動
        Text {
            id:text_2_10
            anchors.top: text_2_9.bottom
            anchors.topMargin: topMargin2
            x: 8
            //y: 405
            width: setWidth
            height: 24
            text: qsTr("收卷寸動啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output2_10_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:"I4.10"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output2_10_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status11
                x: 336
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: "#88FF0A"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: "#88FF0A"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status11MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    //cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        // status0.color = "red"
                        // status0.layer.effect.shadowColor = "red"
                    }
                }
            }
        }
        //左側耳料收卷選擇
        Text {
            id:text_2_11
            anchors.top: text_2_10.bottom
            anchors.topMargin: topMargin2
            x: 8
            //y: 405
            width: setWidth
            height: 24
            text: qsTr("左側耳料收卷選擇")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output2_11_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:"I4.10"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output2_11_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status12
                x: 336
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: "#88FF0A"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: "#88FF0A"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status12MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    //cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        // status0.color = "red"
                        // status0.layer.effect.shadowColor = "red"
                    }
                }
            }
        }
        //右側耳料收卷選擇
        Text {
            id:text_2_12
            anchors.top: text_2_11.bottom
            anchors.topMargin: topMargin2
            x: 8
            //y: 445
            width: setWidth
            height: 24
            text: qsTr("右側耳料收卷選擇")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output2_12_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:"I4.10"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output2_12_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status13
                x: 336
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: "#88FF0A"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: "#88FF0A"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status13MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    //cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        // status0.color = "red"
                        // status0.layer.effect.shadowColor = "red"
                    }
                }
            }
        }


    }

    // //output3
    // Rectangle{
    //     id: output3Rec
    //     anchors.left: output2Rec.right
    //     anchors.leftMargin: groupLeftMargin
    //     y:142
    //     width: 488
    //     height: 908
    //     radius: 40
    //     //border.color: "#2a000000"

    //     gradient: Gradient {
    //         GradientStop {
    //             position: 0.0
    //             color: "#FEFBFC"
    //         }
    //         GradientStop {
    //             position: 1
    //             color: "#eaeaea"
    //         }
    //     }

    //     layer.enabled: true
    //     layer.effect: MultiEffect {
    //         shadowEnabled: true
    //         shadowColor: "#82413f3f"
    //         shadowBlur: 0.8
    //         shadowHorizontalOffset: 0
    //         shadowVerticalOffset: 0
    //     }

    //     Text {
    //         id: output1_3Text
    //         text: "OUTPUT-3"
    //         font.pointSize: 14
    //         font.weight: Font.Bold
    //         anchors.horizontalCenter: parent.horizontalCenter
    //     }
    //     // //大卷切刀進
    //     Text {
    //         id:text_3_0
    //         x: 8
    //         y: 75
    //         width: 223
    //         height: 24
    //         text: qsTr("大卷切刀進")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: output3_01
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             //color: "white"
    //             x: 243
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: output3_01.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: output3_02
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             //color: "white"
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: output3_02.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }
    //     // //運轉指示燈
    //     Text {
    //         id:text_3_1
    //         anchors.top: text_3_0.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         //y: 85
    //         width: 223
    //         height: 24
    //         text: qsTr("運轉指示燈")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: output3_11
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: output3_11.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: output3_12
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: output3_02.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }

    //     //異常指示燈
    //     Text {
    //         id:text_3_2
    //         anchors.top: text_3_1.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         //y: 125
    //         width: 223
    //         height: 24
    //         text: qsTr("異常指示燈")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: output3_21
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: output3_21.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: output3_22
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             //color: "white"
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: output3_22.width
    //                 color: "#aaaaaa"   // 聚焦藍色、未聚焦灰色
    //             }
    //         }
    //     }

    //     //停止指示燈
    //     Text {
    //         id:text_3_3
    //         anchors.top: text_3_2.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         //y: 165
    //         width: 223
    //         height: 24
    //         text: qsTr("停止指示燈")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: output3_31
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: output3_31.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: output3_32
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: output3_32.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }
    //     //蜂鳴器
    //     Text {
    //         id:text_3_4
    //         anchors.top: text_3_3.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         y: 205
    //         width: 223
    //         height: 24
    //         text: qsTr("蜂鳴器")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: output3_41
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: output3_41.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: output3_42
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: output3_42.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }

    // }

    //input4
    // Rectangle{
    //     id: input4Rec
    //     anchors.left: input3Rec.right
    //     anchors.leftMargin: groupLeftMargin
    //     y:142
    //     width: 488
    //     height: 908
    //     radius: 40
    //     //border.color: "#2a000000"

    //     gradient: Gradient {
    //         GradientStop {
    //             position: 0.0
    //             color: "#FEFBFC"
    //         }
    //         GradientStop {
    //             position: 1
    //             color: "#eaeaea"
    //         }
    //     }

    //     layer.enabled: true
    //     layer.effect: MultiEffect {
    //         shadowEnabled: true
    //         shadowColor: "#82413f3f"
    //         shadowBlur: 0.8
    //         shadowHorizontalOffset: 0
    //         shadowVerticalOffset: 0
    //     }

    //     Text {
    //         id: input1_4Text
    //         text: "INPUT-4"
    //         font.pointSize: 14
    //         font.weight: Font.Bold
    //         anchors.horizontalCenter: parent.horizontalCenter
    //     }
    //     // //放卷區圓盤檢知-1
    //     Text {
    //         id:text_4_0
    //         x: 8
    //         y: 75
    //         width: 223
    //         height: 24
    //         text: qsTr("放卷區圓盤檢知-1")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: input4_01
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             //color: "white"
    //             x: 243
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_01.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: input4_02
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             //color: "white"
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_02.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }
    //     //放卷區圓盤檢知-2
    //     Text {
    //         id:text_4_1
    //         anchors.top: text_4_0.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         //y: 85
    //         width: 223
    //         height: 24
    //         text: qsTr("放卷區圓盤檢知-2")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: input4_11
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_11.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: input4_12
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_02.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }

    //     //大捲收卷區圓盤檢知-3
    //     Text {
    //         id:text_4_2
    //         anchors.top: text_4_1.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         //y: 125
    //         width: 223
    //         height: 24
    //         text: qsTr("大捲收卷區圓盤檢知-3")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: input4_21
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_21.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: input4_22
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             //color: "white"
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_22.width
    //                 color: "#aaaaaa"   // 聚焦藍色、未聚焦灰色
    //             }
    //         }
    //     }

    //     //大捲收卷區圓盤檢知-4
    //     Text {
    //         id:text_4_3
    //         anchors.top: text_4_2.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         //y: 165
    //         width: 223
    //         height: 24
    //         text: qsTr("大捲收卷區圓盤檢知-4")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: input4_31
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_31.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: input4_32
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_32.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }
    //     //放卷區安全光柵異常
    //     Text {
    //         id:text_4_4
    //         anchors.top: text_4_3.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         y: 205
    //         width: 223
    //         height: 24
    //         text: qsTr("放卷區安全光柵異常")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: input4_41
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_41.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: input4_42
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_42.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }
    //     //檢測區安全光柵異常
    //     Text {
    //         id:text_4_5
    //         anchors.top: text_4_4.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         y: 205
    //         width: 223
    //         height: 24
    //         text: qsTr("檢測區安全光柵異常 ")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: input4_51
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_51.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: input4_52
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_52.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }
    //     //大卷收捲區光柵異常
    //     Text {
    //         id:text_4_6
    //         anchors.top: text_4_5.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         //y: 245
    //         width: 223
    //         height: 24
    //         text: qsTr("大卷收捲區光柵異常")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: input4_61
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_61.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: input4_62
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_62.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }
    //     //小卷收捲軸零速檢出
    //     Text {
    //         id:text_4_7
    //         anchors.top: text_4_6.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         //y: 285
    //         width: 223
    //         height: 24
    //         text: qsTr("小卷收捲軸零速檢出")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: input4_71
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_71.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: input4_72
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_72.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }
    //     //大卷收捲軸零速檢出
    //     Text {
    //         id:text_4_8
    //         anchors.top: text_4_7.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         //y: 325
    //         width: 223
    //         height: 24
    //         text: qsTr("大卷收捲軸零速檢出")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: input4_81
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_81.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: input4_82
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_82.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }
    //     //放卷張力過大
    //     Text {
    //         id:text_4_9
    //         anchors.top: text_4_8.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         //y: 365
    //         width: 223
    //         height: 24
    //         text: qsTr("放卷張力過大")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: input4_91
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_91.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: input4_92
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_92.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }
    //     //小卷收卷張力過大
    //     Text {
    //         id:text_4_10
    //         anchors.top: text_4_9.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         //y: 405
    //         width: 223
    //         height: 24
    //         text: qsTr("小卷收卷張力過大")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: input4_10_1
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_10_1.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: input4_10_2
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_10_2.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }
    //     //大卷收卷張力過大
    //     Text {
    //         id:text_4_11
    //         anchors.top: text_4_10.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         //y: 445
    //         width: 223
    //         height: 24
    //         text: qsTr("大卷收卷張力過大")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: input4_11_1
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_11_1.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: input4_11_2
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_11_2.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }
    //     //左側耳料收捲角度異常
    //     Text {
    //         id:text_4_12
    //         anchors.top: text_4_11.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         y: 485
    //         width: 223
    //         height: 24
    //         text: qsTr("左側耳料收捲角度異常")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {

    //             id: input4_12_1
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_12_1.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: input4_12_2
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_12_2.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }
    //     //右側耳料收捲角度異常
    //     Text {
    //         id:text_4_13
    //         anchors.top: text_4_12.bottom
    //         anchors.topMargin: topMargin
    //         x: 8
    //         //y: 525
    //         width: 223
    //         height: 24
    //         text: qsTr("右側耳料收捲角度異常")
    //         font.pixelSize: 19
    //         horizontalAlignment: Text.AlignRight

    //         TextInput {
    //             id: input4_13_1
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 243
    //             y: parent.top
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_13_1.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //         TextInput {
    //             id: input4_13_2
    //             width: 100
    //             font.pixelSize: 20
    //             horizontalAlignment: Text.AlignHCenter
    //             x: 365
    //             y: 0
    //             //placeholderText: "請輸入內容"
    //             focus: true

    //             Rectangle {
    //                 height: 2
    //                 y:22
    //                 width: input4_13_2.width
    //                 color: "#aaaaaa"
    //             }
    //         }
    //     }
    //     // //大捲收捲機左側門7開啟中
    //     // Text {
    //     //     id:text_3_14
    //     //     anchors.top: text_3_13.bottom
    //     //     anchors.topMargin: topMargin
    //     //     x: 8
    //     //     //y: 565
    //     //     width: 223
    //     //     height: 24
    //     //     text: qsTr("大捲收捲機左側門7開啟中")
    //     //     font.pixelSize: 19
    //     //     horizontalAlignment: Text.AlignRight

    //     //     TextInput {
    //     //         id: input3_14_1
    //     //         width: 100
    //     //         font.pixelSize: 20
    //     //         horizontalAlignment: Text.AlignHCenter
    //     //         x: 243
    //     //         y: parent.top
    //     //         //placeholderText: "請輸入內容"
    //     //         focus: true

    //     //         Rectangle {
    //     //             height: 2
    //     //             y:22
    //     //             width: input3_14_1.width
    //     //             color: "#aaaaaa"
    //     //         }
    //     //     }
    //     //     TextInput {
    //     //         id: input3_14_2
    //     //         width: 100
    //     //         font.pixelSize: 20
    //     //         horizontalAlignment: Text.AlignHCenter
    //     //         x: 365
    //     //         y: 0
    //     //         //placeholderText: "請輸入內容"
    //     //         focus: true

    //     //         Rectangle {
    //     //             height: 2
    //     //             y:22
    //     //             width: input3_14_2.width
    //     //             color: "#aaaaaa"
    //     //         }
    //     //     }
    //     // }
    //     // //大捲收捲機左側門8開啟中
    //     // Text {
    //     //     id:text_3_15
    //     //     x: 8
    //     //     anchors.top: text_3_14.bottom
    //     //     anchors.topMargin: topMargin
    //     //     width: 223
    //     //     height: 24
    //     //     text: qsTr("大捲收捲機左側門8開啟中")
    //     //     font.pixelSize: 19
    //     //     horizontalAlignment: Text.AlignRight

    //     //     TextInput {
    //     //         id: input3_15_1
    //     //         width: 100
    //     //         font.pixelSize: 20
    //     //         horizontalAlignment: Text.AlignHCenter
    //     //         x: 243
    //     //         y: parent.top
    //     //         //placeholderText: "請輸入內容"
    //     //         focus: true

    //     //         Rectangle {
    //     //             height: 2
    //     //             y:22
    //     //             width: input3_15_1.width
    //     //             color: "#aaaaaa"
    //     //         }
    //     //     }
    //     //     TextInput {
    //     //         id: input3_15_2
    //     //         width: 100
    //     //         font.pixelSize: 20
    //     //         horizontalAlignment: Text.AlignHCenter
    //     //         x: 365
    //     //         y: 0
    //     //         //placeholderText: "請輸入內容"
    //     //         focus: true

    //     //         Rectangle {
    //     //             height: 2
    //     //             y:22
    //     //             width: input3_15_2.width
    //     //             color: "#aaaaaa"
    //     //         }
    //     //     }
    //     // }
    // }

}
