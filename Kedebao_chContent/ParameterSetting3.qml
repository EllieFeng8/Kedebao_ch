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

    property int textLeft: 213
    property int switchLeft:282
    property int textLeft2: 243
    property int switchLeft2:312
    property int topMargin2: 31
    property int topMargin3: 40
    property int fontSize: 17
    property bool clicked0:Kdb.vfdAlarmResetSwitch
    property bool clicked:Kdb.unwinderForwardSwitch
    property bool clicked1:Kdb.unwinderReverseSwitch
    property bool clicked2:Kdb.mainDriveForwardSwitch
    property bool clicked3:Kdb.mainDriveReverseSwitch
    property bool clicked4:Kdb.smallWinderForwardSwitch
    property bool clicked5:Kdb.smallWinderReverseSwitch
    property bool clicked6:Kdb.largeWinderForwardSwitch
    property bool clicked7:Kdb.largeWinderReverseSwitch
    property bool clicked8:Kdb.smallCutterStartSwitch
    property bool clicked9:Kdb.selvedgeFanStartSwitch
    property bool clicked10:Kdb.largeCutterStartSwitch
    property bool clicked11:Kdb.leftSelvedgeWinderForwardSwitch
    property bool clicked12:Kdb.leftSelvedgeWinderReverseSwitch
    property bool clicked13:Kdb.rightSelvedgeWinderForwardSwitch
    property bool clicked14:Kdb.rightSelvedgeWinderReverseSwitch
    property bool clicked15:Kdb.webAlignerStartSwitch
    property bool clicked16:Kdb.unwindingTensionAutoSwitch
    property bool clicked17:Kdb.unwindingDiameterResetSwitch
    property bool clicked18:Kdb.smallWinderTensionAutoSwitch
    property bool clicked19:Kdb.smallWinderDiameterResetSwitch
    property bool clicked20:Kdb.largeWinderTensionAutoSwitch
    property bool clicked21:Kdb.largeWinderDiameterResetSwitch
    property bool clicked22:Kdb.leftSelvedgeWinderAutoSwitch
    property bool clicked23:Kdb.rightSelvedgeWinderAutoSwitch
    property bool clicked24:Kdb.nipRollUpSwitch
    property bool clicked25:Kdb.nipRollDownSwitch
    property bool clicked26:Kdb.leftPressPlateForwardSwitch
    property bool clicked27:Kdb.leftPressPlateBackwardSwitch
    property bool clicked28:Kdb.rightPressPlateForwardSwitch
    property bool clicked29:Kdb.rightPressPlateBackwardSwitch
    property bool clicked30:Kdb.smallCutterInSwitch
    property bool clicked31:Kdb.largeCutterInSwitch
    property bool clicked32:Kdb.modeSelectSwitch
    property bool clicked33:Kdb.runIndicatorSwitch
    property bool clicked34:Kdb.alarmIndicatorSwitch
    property bool clicked35:Kdb.stopIndicatorSwitch
    property bool clicked36:Kdb.buzzerSwitch
    property bool clicked37:Kdb.smallRollModeSelectSwitch

    property int topMargin: 25
    property int groupLeftMargin: 100


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
            onClicked: {
                // parameterSetting4.visible = true
                //root.visible = false
                AppState.pageNum = 0;
                setParameterInterface(AppState.pageNum);
            }
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
                // parameterSetting4.visible = true
                //root.visible = false
                AppState.pageNum = 1;
                setParameterInterface(AppState.pageNum);
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
                // parameterSetting4.visible = true
                //root.visible = false
                AppState.pageNum = 2;
                setParameterInterface(AppState.pageNum);
            }
        }
    }

    Image {
        id: nextPage
        x:1613
        y:20
        source: "assets/Group 37.png"

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: nextPageMouseArea.containsMouse ? true : false
            shadowColor: "#58000000"
            shadowBlur: 0.8
        }
        MouseArea {
            id: nextPageMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                // parameterSetting4.visible = true
                //root.visible = false
                AppState.pageNum = 4;
                setParameterInterface(AppState.pageNum);
            }
        }
    }
    Image {
        id: lastPage
        x:1733
        y:20
        source: "assets/Group 38.png"

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: lastPageMouseArea.containsMouse ? true : false
            shadowColor: "#58000000"
            shadowBlur: 0.8
        }
        MouseArea {
            id: lastPageMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                // parameterSetting4.visible = true
                //root.visible = false
                AppState.pageNum = 4;
                setParameterInterface(AppState.pageNum);
            }
        }
    }
    //OUTPUT-1
    Rectangle{
        id: output1Rec
        x:groupLeftMargin
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
            id: output1_1Text
            text: "OUTPUT-1"
            font.pointSize: 14
            padding:10
            font.weight: Font.Bold
            anchors.horizontalCenter: parent.horizontalCenter
        }
        //變頻異常復歸
        Text {
            id:text_00
            //anchors.top: text_0.bottom
            //anchors.topMargin: 40
            x: 38
            y: 75
            width: 193
            height: 24
            text: qsTr("變頻異常復歸")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output0_01
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Number(Kdb.vfdAlarmReset).toFixed(2)//Kdb.vfdAlarmReset//"Q0.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output0_01.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch00
                x:switchLeft
                y:-16
                scale: 0.5
                source: root.clicked0 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch00MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked0 = !root.clicked0
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //放卷軸正轉啟動
        Text {
            id:text_0
            anchors.top: text_00.bottom
            anchors.left: text_00.left
            anchors.topMargin: topMargin
            // x: 8
            // y: 75
            width: 193
            height: 24
            text: qsTr("放卷軸正轉啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output0_1
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Number(Kdb.unwinderForward).toFixed(2)//Kdb.unwinderForward//"Q0.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output0_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch0
                x:switchLeft
                y:-16
                scale: 0.5
                source: root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch0MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked = !root.clicked
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //放卷軸反轉啟動
        Text {
            id:text_1
            anchors.top: text_0.bottom
            anchors.left: text_0.left
            anchors.topMargin: topMargin
            //x: 8
            //y: 85
            width: 193
            height: 24
            text: qsTr("放卷軸反轉啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output1_1
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Number(Kdb.unwinderReverse).toFixed(2)//Kdb.unwinderReverse//"Q1.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output1_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch1
                x:switchLeft
                y:-16
                scale: 0.5
                source: root.clicked1 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch1MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked1 = !root.clicked1
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }

        //主傳動正轉啟動
        Text {
            id:text_2
            anchors.top: text_1.bottom
            anchors.left: text_1.left
            anchors.topMargin: topMargin
            x: 8
            //y: 125
            width: 193
            height: 24
            text: qsTr("主傳動正轉啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output2_1
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Number(Kdb.mainDriveForward).toFixed(2)//Kdb.mainDriveForward//"Q0.02"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output1_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2
                x:switchLeft
                y:-16
                scale: 0.5
                source: root.clicked2 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked2 = !root.clicked2
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }

        //主傳動反轉啟動
        Text {
            id:text_3
            anchors.top: text_2.bottom
            anchors.left: text_2.left
            anchors.topMargin: topMargin
            x: 8
            //y: 165
            width: 193
            height: 24
            text: qsTr("主傳動反轉啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output3_1
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Number(Kdb.mainDriveReverse).toFixed(2)//Kdb.mainDriveReverse//"Q0.03"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output1_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch3
                x:switchLeft
                y:-16
                scale: 0.5
                source: root.clicked3 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch3MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked3 = !root.clicked3
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //小卷收捲軸正轉啟動
        Text {
            id:text_4
            anchors.top: text_3.bottom
            anchors.left: text_3.left
            anchors.topMargin: topMargin
            x: 8
            y: 205
            width: 193
            height: 24
            text: qsTr("小卷收捲軸正轉啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output4_1
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Number(Kdb.smallWinderForward).toFixed(2)//Kdb.smallWinderForward//"Q0.04"
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
                id: switch4
                x:switchLeft
                y:-16
                scale: 0.5
                source: root.clicked4 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch4MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked4 = !root.clicked4
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //小卷收捲軸反轉啟動
        Text {
            id:text_5
            anchors.top: text_4.bottom
            anchors.left: text_4.left
            anchors.topMargin: topMargin
            x: 8
            y: 205
            width: 193
            height: 24
            text: qsTr("小卷收捲軸反轉啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output5_1
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Number(Kdb.smallWinderReverse).toFixed(2)//Kdb.smallWinderReverse//"Q0.05"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output5_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch5
                x:switchLeft
                y:-16
                scale: 0.5
                source: root.clicked5 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch5MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked5 = !root.clicked5
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //大卷收捲軸正轉啟動
        Text {
            id:text_6
            anchors.top: text_5.bottom
            anchors.left: text_5.left
            anchors.topMargin: topMargin
            x: 8
            //y: 245
            width: 193
            height: 24
            text: qsTr("大卷收捲軸正轉啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output7_11
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Number(Kdb.largeWinderForward).toFixed(2)//Kdb.largeWinderForward//"Q0.06"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output7_11.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch7
                x:switchLeft
                y:-16
                scale: 0.5
                source: root.clicked6 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch7MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked6 = !root.clicked6
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //大卷收捲軸反轉啟動
        Text {
            id:text_7
            anchors.top: text_6.bottom
            anchors.left: text_6.left
            anchors.topMargin: topMargin
            x: 8
            //y: 285
            width: 193
            height: 24
            text: qsTr("大卷收捲軸反轉啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output8_11
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Number(Kdb.largeWinderReverse).toFixed(2)//Kdb.largeWinderReverse//"Q0.07"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output8_11.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch8
                x:switchLeft
                y:-16
                scale: 0.5
                source: root.clicked7 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch8MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked7 = !root.clicked7
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //小卷切刀輪啟動
        Text {
            id:text_8
            anchors.top: text_7.bottom
            anchors.left: text_7.left
            anchors.topMargin: topMargin
            x: 8
            //y: 325
            width: 193
            height: 24
            text: qsTr("小卷切刀輪啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output9_11
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Number(Kdb.smallCutterStart).toFixed(2)//Kdb.smallCutterStart//"Q0.08"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output9_11.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch9
                x:switchLeft
                y:-16
                scale: 0.5
                source: root.clicked8 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch9MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked8 = !root.clicked8
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //耳料抽風啟動
        Text {
            id:text_9
            anchors.top: text_8.bottom
            anchors.left: text_8.left
            anchors.topMargin: topMargin
            x: 8
            //y: 365
            width: 193
            height: 24
            text: qsTr("耳料抽風啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output10_11
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Number(Kdb.selvedgeFanStart).toFixed(2)//Kdb.selvedgeFanStart//"Q0.10"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output10_11.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch10
                x:switchLeft
                y:-16
                scale: 0.5
                source: root.clicked9 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch10MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked9 = !root.clicked9
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //大卷切刀輪啟動
        Text {
            id:text_10
            anchors.top: text_9.bottom
            anchors.left: text_9.left
            anchors.topMargin: topMargin
            x: 8
            //y: 405
            width: 193
            height: 24
            text: qsTr("大卷切刀輪啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output11_11
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Number(Kdb.largeCutterStart).toFixed(2)//Kdb.largeCutterStart//"Q0.11"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output11_11.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch11
                x:switchLeft
                y:-16
                scale: 0.5
                source: root.clicked10 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch11MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked10 = !root.clicked10
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //左側耳料收捲正轉啟動
        Text {
            id:text_11
            anchors.top: text_10.bottom
            anchors.left: text_10.left
            anchors.topMargin: topMargin
            x: 8
            //y: 445
            width: 193
            height: 24
            text: qsTr("左側耳料收捲正轉啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output12_11
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Number(Kdb.leftSelvedgeWinderForward).toFixed(2)//Kdb.leftSelvedgeWinderForward//"Q0.12"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output12_11.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch12
                x:switchLeft
                y:-16
                scale: 0.5
                source: root.clicked11 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch12MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked11 = !root.clicked11
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //左側耳料收捲反轉啟動
        Text {
            id:text_12
            anchors.top: text_11.bottom
            anchors.left: text_11.left
            anchors.topMargin: topMargin
            x: 8
            y: 485
            width: 193
            height: 24
            text: qsTr("左側耳料收捲反轉啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output13_11
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Number(Kdb.leftSelvedgeWinderReverse).toFixed(2)//Kdb.leftSelvedgeWinderReverse//"Q0.11"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output13_11.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch13
                x:switchLeft
                y:-16
                scale: 0.5
                source: root.clicked12 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch13MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked12 = !root.clicked12
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //右側耳料收捲正轉啟動
        Text {
            id:text_13
            anchors.top: text_12.bottom
            anchors.left: text_12.left
            anchors.topMargin: topMargin
            x: 8
            //y: 525
            width: 193
            height: 24
            text: qsTr("右側耳料收捲正轉啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output14_11
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Number(Kdb.rightSelvedgeWinderForward).toFixed(2)//Kdb.rightSelvedgeWinderForward//"Q0.14"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output14_11.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch14
                x:switchLeft
                y:-16
                scale: 0.5
                source: root.clicked13 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch14MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked13 = !root.clicked13
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //右側耳料收捲反轉啟動
        Text {
            id:text_14
            anchors.top: text_13.bottom
            anchors.left: text_13.left
            anchors.topMargin: topMargin
            x: 8
            //y: 565
            width: 193
            height: 24
            text: qsTr("右側耳料收捲反轉啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output15_1
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Number(Kdb.rightSelvedgeWinderReverse).toFixed(2)//Kdb.rightSelvedgeWinderReverse//"Q0.15"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output15_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch15
                x:switchLeft
                y:-16
                scale: 0.5
                source: root.clicked14 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch15MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked14 = !root.clicked14
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }

    }

    //output2
    Rectangle{
        id: output2Rec
        anchors.left: output1Rec.right
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
            text: "OUTPUT-2"
            padding:10
            font.pointSize: 14
            font.weight: Font.Bold
            anchors.horizontalCenter: parent.horizontalCenter
        }
        //對邊機啟動
        Text {
            id:text_2_0
            x: 8
            y: 75
            width: 223
            height: 24
            text: qsTr("對邊機啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output02_1
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.webAlignerStart).toFixed(2)//Kdb.webAlignerStart//"Q1.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output1_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2_0
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked15 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2_0MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked15 = !root.clicked15
                        //source: root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //放卷張力自動
        Text {
            id:text_2_1
            anchors.top: text_2_0.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 85
            width: 223
            height: 24
            text: qsTr("放卷張力自動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output02_3
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.unwindingTensionAuto).toFixed(2)//Kdb.unwindingTensionAuto//"Q1.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output02_3.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2_1
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked16 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2_1MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked16 = !root.clicked16
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }

        //放卷卷徑復歸
        Text {
            id:text_2_2
            anchors.top: text_2_1.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 125
            width: 223
            height: 24
            text: qsTr("放卷卷徑復歸")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output02_03
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.unwindingDiameterReset).toFixed(2)//Kdb.unwindingDiameterReset//"Q1.03"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output02_03.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2_3
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked17 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2_3MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked17 = !root.clicked17
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }

        //小卷收捲張力自動
        Text {
            id:text_2_3
            anchors.top: text_2_2.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 165
            width: 223
            height: 24
            text: qsTr("小卷收捲張力自動 ")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output02_04
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.smallWinderTensionAuto).toFixed(2)//Kdb.smallWinderTensionAuto//"Q1.03"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output02_04.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2_4
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked18 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2_4MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked18 = !root.clicked18
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //小卷收捲卷徑復歸
        Text {
            id:text_2_4
            anchors.top: text_2_3.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 205
            width: 223
            height: 24
            text: qsTr("小卷收捲卷徑復歸")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output02_05
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.smallWinderDiameterReset).toFixed(2)//Kdb.smallWinderDiameterReset//"Q1.04"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output02_05.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2_5
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked19 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2_5MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked19 = !root.clicked19
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //大卷收捲張力自動
        Text {
            id:text_2_5
            anchors.top: text_2_4.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 205
            width: 223
            height: 24
            text: qsTr("大卷收捲張力自動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output02_06
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.largeWinderTensionAuto).toFixed(2)//Kdb.largeWinderTensionAuto//"Q1.06"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output02_06.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2_6
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked20 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2_6MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked20 = !root.clicked20
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //大卷收捲卷徑復歸
        Text {
            id:text_2_6
            anchors.top: text_2_5.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 245
            width: 223
            height: 24
            text: qsTr("大卷收捲卷徑復歸")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output02_07
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.largeWinderDiameterReset).toFixed(2)//Kdb.largeWinderDiameterReset//"Q1.07"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output02_07.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2_7
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked21 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2_7MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked21 = !root.clicked21
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //左側耳料收捲自動啟動
        Text {
            id:text_2_7
            anchors.top: text_2_6.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 285
            width: 223
            height: 24
            text: qsTr("左側耳料收捲自動啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output02_08
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.leftSelvedgeWinderAuto).toFixed(2)//Kdb.leftSelvedgeWinderAuto//"Q1.08"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output02_08.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2_8
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked22 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2_8MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked22 = !root.clicked22
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //右側耳料收捲自動啟動
        Text {
            id:text_2_8
            anchors.top: text_2_7.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 325
            width: 223
            height: 24
            text: qsTr("右側耳料收捲自動啟動")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output02_09
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.rightSelvedgeWinderAuto).toFixed(2)//Kdb.rightSelvedgeWinderAuto//"Q1.09"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output02_09.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2_9
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked23 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2_9MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked23 = !root.clicked23
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //捲取壓輪上升
        Text {
            id:text_2_9
            anchors.top: text_2_8.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 365
            width: 223
            height: 24
            text: qsTr("捲取壓輪上升")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output02_10
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.nipRollUp).toFixed(2)//Kdb.nipRollUp//"Q1.10"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output02_10.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2_10
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked24 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2_10MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked24 = !root.clicked24
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //捲取壓輪下降
        Text {
            id:text_2_10
            anchors.top: text_2_9.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 405
            width: 223
            height: 24
            text: qsTr("捲取壓輪下降")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output02_11
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.nipRollDown).toFixed(2)//Kdb.nipRollDown//"Q1.11"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output02_11.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2_11
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked25 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2_11MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked25 = !root.clicked25
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //左側壓板前進
        Text {
            id:text_2_11
            anchors.top: text_2_10.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 445
            width: 223
            height: 24
            text: qsTr("左側壓板前進")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output02_12
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.leftPressPlateForward).toFixed(2)//Kdb.leftPressPlateForward//"Q1.12"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output02_12.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2_12
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked26 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2_12MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked26 = !root.clicked26
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //左側壓板後退
        Text {
            id:text_2_12
            anchors.top: text_2_11.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 485
            width: 223
            height: 24
            text: qsTr("左側壓板後退")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output02_13
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.leftPressPlateBackward).toFixed(2)//Kdb.leftPressPlateBackward//"Q1.13"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output02_13.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2_13
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked27 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2_13MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked27 = !root.clicked27
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //右側壓板前進
        Text {
            id:text_2_13
            anchors.top: text_2_12.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 525
            width: 223
            height: 24
            text: qsTr("右側壓板前進")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output02_14
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.rightPressPlateForward).toFixed(2)//Kdb.rightPressPlateForward//"Q1.14"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output02_14.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2_14
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked28 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2_14MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked28 = !root.clicked28
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //右側壓板後退
        Text {
            id:text_2_14
            anchors.top: text_2_13.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 565
            width: 223
            height: 24
            text: qsTr("右側壓板後退")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output02_15
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.rightPressPlateBackward).toFixed(2)//Kdb.rightPressPlateBackward//"Q1.15"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output02_15.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2_15
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked29 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2_15MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked29 = !root.clicked29
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //小卷切刀進
        Text {
            id:text_2_15
            x: 8
            anchors.top: text_2_14.bottom
            anchors.topMargin: topMargin
            width: 223
            height: 24
            text: qsTr("小卷切刀進")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output02_16
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.smallCutterIn).toFixed(2)//Kdb.smallCutterIn//"Q1.10"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output02_16.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch2_16
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked30 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch2_16MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked30 = !root.clicked30
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
    }

    //output3
    Rectangle{
        id: output3Rec
        anchors.left: output2Rec.right
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
            id: output1_3Text
            text: "OUTPUT-3"
            padding:10
            font.pointSize: 14
            font.weight: Font.Bold
            anchors.horizontalCenter: parent.horizontalCenter
        }
        // //大卷切刀進
        Text {
            id:text_3_0
            x: 8
            y: 75
            width: 223
            height: 24
            text: qsTr("大卷切刀進")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output03_1
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.largeCutterIn).toFixed(2)//Kdb.largeCutterIn//"Q2.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output03_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch3_0
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked31 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch3_0MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked31 = !root.clicked31
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }

        // //模式選擇
        Text {
            id:text_3_1
            anchors.top: text_3_0.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 85
            width: 223
            height: 24
            text: qsTr("模式選擇")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output03_02
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.modeSelect).toFixed(2)//Kdb.modeSelect//"Q2.01"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output03_02.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch3_1
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked32 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch3_1MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked32 = !root.clicked32
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        // //運轉指示燈
        Text {
            id:text_3_2
            anchors.top: text_3_1.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 85
            width: 223
            height: 24
            text: qsTr("運轉指示燈")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output03_03
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.runIndicator).toFixed(2)//Kdb.runIndicator//"Q2.02"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output02_09.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch3_3
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked33 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch3_3MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked33 = !root.clicked33
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }

        //異常指示燈
        Text {
            id:text_3_3
            anchors.top: text_3_2.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 125
            width: 223
            height: 24
            text: qsTr("異常指示燈")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output03_04
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Number(Kdb.alarmIndicator).toFixed(2)//Kdb.alarmIndicator//"Q2.03"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output03_04.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch3_4
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked34 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch3_4MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked34 = !root.clicked34
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }

        //停止指示燈
        Text {
            id:text_3_4
            anchors.top: text_3_3.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 165
            width: 223
            height: 24
            text: qsTr("停止指示燈")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output03_05
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                y: 0
                text:Number(Kdb.stopIndicator).toFixed(2)//Kdb.stopIndicator//"Q2.04"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output03_05.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch3_5
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked35 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch3_5MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked35 = !root.clicked35
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //蜂鳴器
        Text {
            id:text_3_5
            anchors.top: text_3_4.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 205
            width: 223
            height: 24
            text: qsTr("蜂鳴器")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output03_06
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                y: 0
                text:Number(Kdb.buzzer).toFixed(2)//Kdb.buzzer//"Q2.04"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output03_05.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch3_6
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked36 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch3_6MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked36 = !root.clicked36
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }
        //小卷模式選擇
        Text {
            id:text_3_6
            anchors.top: text_3_5.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 205
            width: 223
            height: 24
            text: qsTr("小卷模式選擇")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: output03_07
                width: 80
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                y: 0
                text:Number(Kdb.smallRollModeSelect).toFixed(2)//Kdb.smallRollModeSelect//"Q2.04"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: output03_05.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: switch3_7
                x:switchLeft2
                y:-16
                scale: 0.5
                source: root.clicked37 ?"assets/Group11.png" : "assets/Group 34.png"
                MouseArea{
                    id:switch3_7MouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        root.clicked37 = !root.clicked37
                        //root.clicked ?"assets/Group11.png" : "assets/Group 34.png"
                    }
                }
            }
        }

    }


    // ParameterSetting4{
    //     id: parameterSetting4
    //     visible: false
    // }
}
