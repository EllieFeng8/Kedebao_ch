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


    property int topMargin: 25
    property int groupLeftMargin: 100
    property int textWidth: 218
    property int textLeft: 213

    property int textLeft2: 253
    property int input2TextLeft:30
    property int signLeft: 356


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

    }
    //previousPage
    Image {
        id: previousPage
        x:284
        y:20
        source: "assets/Group 39.png"

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
                parameterSetting2.visible = true
                //root.visible = false
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
                parameterSetting2.visible = true
                //root.visible = false
            }
        }
    }
    //input1
    Rectangle{
        id: input1Rec
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
            id: input1_1Text
            text: "INPUT-1"
            font.pointSize: 14
            font.weight: Font.Bold
            anchors.horizontalCenter: parent.horizontalCenter
        }
        //放卷輪變頻異常
        Text {
            id:text_0
            //anchors.top: text_0.bottom
            //anchors.topMargin: 40
            x: 8
            y: 75
            width: 193
            height: 24
            text: qsTr("放卷輪變頻異常")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input0_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Kdb.unwinderVfdFreqAlarm//"I0.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: false

                Rectangle {
                    height: 2
                    y:22
                    width: input0_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status0
                x: signLeft
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.unwinderVfdFreqAlarmLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.unwinderVfdFreqAlarmLight ? "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status0MouseArea
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
        //主傳動輪變頻異常
        Text {
            id:text_1
            anchors.top: text_0.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 85
            width: 193
            height: 24
            text: qsTr("主傳動輪變頻異常")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input1_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Kdb.mainDriveVfdFreqAlarm//"I0.00"
                color: "#aaaaaa"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input1_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status1
                x: signLeft
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color:Kdb.mainDriveVfdFreqAlarmLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.mainDriveVfdFreqAlarmLight ?  "#88FF0A" : "red"
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

        //小卷收捲變頻異常
        Text {
            id:text_2
            anchors.top: text_1.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 125
            width: 193
            height: 24
            text: qsTr("小卷收捲變頻異常")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input2_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Kdb.smallWinderVfdFreqAlarm//"I3.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {

                    height: 2
                    y:22
                    width: input2_1.width
                    color: "#aaaaaa"

                }
            }
            Rectangle {
                id:status2
                x: signLeft
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.smallWinderVfdFreqAlarmLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.smallWinderVfdFreqAlarmLight ?  "#88FF0A" : "red"
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

        //大卷收捲變頻異常
        Text {
            id:text_3
            anchors.top: text_2.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 165
            width: 193
            height: 24
            text: qsTr("大卷收捲變頻異常")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input3_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Kdb.largeWinderVfdFreqAlarm//"I4.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status3
                x: signLeft
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.largeWinderVfdFreqAlarmLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.largeWinderVfdFreqAlarmLight ?  "#88FF0A" : "red"
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
        //小捲切刀輪變頻異常
        Text {
            id:text_4
            anchors.top: text_3.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 205
            width: 193
            height: 24
            text: qsTr("小捲切刀輪變頻異常")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input4_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Kdb.smallCutterVfdFreqAlarm//"I5.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input4_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status4
                x: signLeft
                y:-10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.smallCutterVfdFreqAlarmLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.smallCutterVfdFreqAlarmLight ?  "#88FF0A" : "red"
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
        //耳料抽風變頻異常
        Text {
            id:text_5
            anchors.top: text_4.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 205
            width: 193
            height: 24
            text: qsTr("耳料抽風變頻異常")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input5_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Kdb.selvedgeFanVfdFreqAlarm//"I6.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input5_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status5
                x: signLeft
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.selvedgeFanVfdFreqAlarmLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.selvedgeFanVfdFreqAlarmLight ?  "#88FF0A" : "red"
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
        //左側抽風過載
        Text {
            id:text_6
            anchors.top: text_5.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 245
            width: 193
            height: 24
            text: qsTr("左側抽風過載")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input6_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Kdb.leftFanOverloadAlarm//"I7.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input6_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status6
                x: signLeft
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.leftFanOverloadAlarmLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.leftFanOverloadAlarmLight ?  "#88FF0A" : "red"
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
        //右側抽風過載
        Text {
            id:text_7
            anchors.top: text_6.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 285
            width: 193
            height: 24
            text: qsTr("右側抽風過載")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input7_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Kdb.rightFanOverloadAlarm//"I8.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input6_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status7
                x: signLeft
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.leftFanOverloadAlarmLirightFanOverloadAlarmLightght ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.leftFanOverloadAlarmLirightFanOverloadAlarmLightght ?  "#88FF0A" : "red"
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
        //大捲切刀輪變頻異常
        Text {
            id:text_8
            anchors.top: text_7.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 325
            width: 193
            height: 24
            text: qsTr("大捲切刀輪變頻異常")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input8_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Kdb.largeCutterVfdFreqAlarm//"I9.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input8_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status8
                x: signLeft
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.largeCutterVfdFreqAlarmLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.largeCutterVfdFreqAlarmLight ?  "#88FF0A" : "red"
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
        //左側耳料收捲變頻異常
        Text {
            id:text_9
            anchors.top: text_8.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 365
            width: 193
            height: 24
            text: qsTr("左側耳料收捲變頻異常")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input9_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Kdb.leftSelvedgeWinderVfdAlarm//"I0.10"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input9_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status9
                x: signLeft
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.leftSelvedgeWinderVfdAlarmLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.leftSelvedgeWinderVfdAlarmLight ?  "#88FF0A" : "red"
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
        //右側耳料收捲變頻異常
        Text {
            id:text_10
            anchors.top: text_9.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 405
            width: 193
            height: 24
            text: qsTr("右側耳料收捲變頻異常")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input10_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Kdb.rightSelvedgeWinderVfdAlarm//"I0.11"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input10_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status10
                x: signLeft
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.rightSelvedgeWinderVfdAlarmLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.rightSelvedgeWinderVfdAlarmLight ?  "#88FF0A" : "red"
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
        //對邊機變頻異常
        Text {
            id:text_11
            anchors.top: text_10.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 445
            width: 193
            height: 24
            text: qsTr("對邊機變頻異常")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input11_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Kdb.webAlignerVfdFreqAlarm//"I0.12"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input11_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status11
                x: signLeft
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.webAlignerVfdFreqAlarmLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.webAlignerVfdFreqAlarmLight ?  "#88FF0A" : "red"
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
        //放卷軸電源檢出
        Text {
            id:text_12
            anchors.top: text_11.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 485
            width: 193
            height: 24
            text: qsTr("放卷軸電源檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {

                id: input12_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Kdb.unwinderPowerLoss//"I0.13"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input12_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status13
                x: signLeft
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.unwinderPowerLossLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.unwinderPowerLossLight ?  "#88FF0A" : "red"
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
        //主傳動輪電源檢出
        Text {
            id:text_13
            anchors.top: text_12.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 525
            width: 193
            height: 24
            text: qsTr("主傳動輪電源檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input13_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft
                text:Kdb.mainDrivePowerLoss//"I0.14"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input13_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status14
                x: signLeft
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.mainDrivePowerLossLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.mainDrivePowerLossLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status14MouseArea
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
        //小卷收捲電源檢出
        Text {
            id:text_14
            anchors.top: text_13.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 565
            width: 193
            height: 24
            text: qsTr("小卷收捲電源檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input14_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 203
                text:Kdb.smallWinderPowerLoss//"I0.15"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input14_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status15
                x: signLeft
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.smallWinderPowerLossLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.smallWinderPowerLossLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status15MouseArea
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
        //大卷收捲電源檢出
        Text {
            id:text_15
            x: 8
            anchors.top: text_14.bottom
            anchors.topMargin: topMargin
            width: 193
            height: 24
            text: qsTr("大卷收捲電源檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input15_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 203
                text:Kdb.largeWinderPowerLoss//"I0.16"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input15_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status16
                x: signLeft
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.largeWinderPowerLossLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.largeWinderPowerLossLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status16MouseArea
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

    //input2
    Rectangle{
        id: input2Rec
        anchors.left: input1Rec.right
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
            id: input1_2Text
            text: "INPUT-2"
            font.pointSize: 14
            font.weight: Font.Bold
            anchors.horizontalCenter: parent.horizontalCenter
        }
        //小捲切刀輪電源檢出
        Text {
            id:text_2_0
            x: 8
            y: 75
            width: 223
            height: 24
            text: qsTr("小捲切刀輪電源檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input2_01
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                //color: "white"
                x: textLeft2
                text:Kdb.smallCutterPowerLoss//"I1.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input2_01.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status17
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.smallCutterPowerLossLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.smallCutterPowerLossLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status17MouseArea
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
        //耳料抽風電源檢出
        Text {
            id:text_2_1
            anchors.top: text_2_0.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 85
            width: 223
            height: 24
            text: qsTr("耳料抽風電源檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input2_11
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Kdb.selvedgeFanPowerLoss//"I2.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input2_11.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status18
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.selvedgeFanPowerLossLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.selvedgeFanPowerLossLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status18MouseArea
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

        //大捲切刀輪電源檢出
        Text {
            id:text_2_2
            anchors.top: text_2_1.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 125
            width: 223
            height: 24
            text: qsTr("大捲切刀輪電源檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input2_21
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Kdb.largeCutterPowerLoss//"I3.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input2_21.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status19
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.largeCutterPowerLossLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.largeCutterPowerLossLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status19MouseArea
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

        //左側耳料收捲電源檢出
        Text {
            id:text_2_3
            anchors.top: text_2_2.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 165
            width: 223
            height: 24
            text: qsTr("左側耳料收捲電源檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input2_31
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Kdb.leftSelvedgeWinderPowerLoss//"I4.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input2_31.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status20
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.leftSelvedgeWinderPowerLossLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.leftSelvedgeWinderPowerLossLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status20MouseArea
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
        //右側耳料收捲電源檢出
        Text {
            id:text_2_4
            anchors.top: text_2_3.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 205
            width: 223
            height: 24
            text: qsTr("右側耳料收捲電源檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input2_41
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Kdb.rightSelvedgeWinderPowerLoss//"I5.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input2_41.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status21
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.rightSelvedgeWinderPowerLossLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.rightSelvedgeWinderPowerLossLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status21MouseArea
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
        //對邊機電源檢出
        Text {
            id:text_2_5
            anchors.top: text_2_4.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 205
            width: 223
            height: 24
            text: qsTr("對邊機電源檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input2_51
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Kdb.webAlignerPowerLoss//"I6.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input2_51.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status22
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.webAlignerPowerLossLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.webAlignerPowerLossLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status22MouseArea
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
        //放卷軸切斷關聯檢出
        Text {
            id:text_2_6
            anchors.top: text_2_5.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 245
            width: 223
            height: 24
            text: qsTr("放卷軸切斷開關檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input2_61
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Kdb.unwinderDisconnect//"I7.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input2_61.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status23
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.unwinderDisconnectLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.unwinderDisconnectLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status23MouseArea
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
        //主傳動輪切斷關聯檢出
        Text {
            id:text_2_7
            anchors.top: text_2_6.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 285
            width: 223
            height: 24
            text: qsTr("主傳動輪切斷開關檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input2_71
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Kdb.mainDriveDisconnect//"I8.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input6_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status24
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.mainDriveDisconnectLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.mainDriveDisconnectLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status24MouseArea
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
        //小卷收捲切斷關聯檢出
        Text {
            id:text_2_8
            anchors.top: text_2_7.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 325
            width: 223
            height: 24
            text: qsTr("小卷收捲切斷開關檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input2_81
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Kdb.smallWinderDisconnect//"I9.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input2_81.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status25
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.smallWinderDisconnectLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.smallWinderDisconnectLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status25MouseArea
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
        //大卷收捲切斷關聯檢出
        Text {
            id:text_2_9
            anchors.top: text_2_8.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 365
            width: 223
            height: 24
            text: qsTr("大卷收捲切斷開關檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input2_91
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Kdb.largeWinderDisconnect//"I0.10"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input2_91.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status26
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.largeWinderDisconnectLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.largeWinderDisconnectLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status26MouseArea
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
        //小捲切刀輪切斷關聯檢出
        Text {
            id:text_2_10
            anchors.top: text_2_9.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 405
            width: 223
            height: 24
            text: qsTr("小捲切刀輪切斷開關檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input2_10_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Kdb.smallCutterDisconnect//"I0.11"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input2_10_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status27
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.smallCutterDisconnectLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.smallCutterDisconnectLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status27MouseArea
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
        //左側抽風切斷關聯檢出
        Text {
            id:text_2_11
            anchors.top: text_2_10.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 445
            width: 223
            height: 24
            text: qsTr("左側抽風切斷開關檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input2_11_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Kdb.leftFanDisconnect//"I0.12"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input2_11_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status28
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.leftFanDisconnectLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.leftFanDisconnectLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status28MouseArea
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
        //右側抽風切斷關聯檢出
        Text {
            id:text_2_12
            anchors.top: text_2_11.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 485
            width: 223
            height: 24
            text: qsTr("右側抽風切斷開關檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {

                id: input2_12_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Kdb.rightFanDisconnect//"I0.13"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input2_12_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status29
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.rightFanDisconnectLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.rightFanDisconnectLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status29MouseArea
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
        //大捲切刀輪切斷關聯檢出
        Text {
            id:text_2_13
            anchors.top: text_2_12.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 525
            width: 223
            height: 24
            text: qsTr("大捲切刀輪切斷開關檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input2_13_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Kdb.largeCutterDisconnect//"I0.14"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input2_13_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status30
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.largeCutterDisconnectLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.largeCutterDisconnectLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status30MouseArea
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
        //左側耳料收捲切斷關檢出
        Text {
            id:text_2_14
            anchors.top: text_2_13.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 565
            width: 241
            height: 24
            text: qsTr("左側耳料收捲切斷開關檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input2_14_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Kdb.leftSelvedgeWinderDisconnect//"I0.15"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input2_14_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status31
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.leftSelvedgeWinderDisconnectLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.leftSelvedgeWinderDisconnectLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status31MouseArea
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
        //右側耳料收捲切斷關檢出
        Text {
            id:text_2_15
            x: 8
            anchors.top: text_2_14.bottom
            anchors.topMargin: topMargin
            width: 241
            height: 24
            text: qsTr("右側耳料收捲切斷開關檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input2_15_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: textLeft2
                text:Kdb.rightSelvedgeWinderDisconnect//"I0.16"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input2_15_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status32
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.rightSelvedgeWinderDisconnectLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.rightSelvedgeWinderDisconnectLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status32MouseArea
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

    //input3
    Rectangle{
        id: input3Rec
        anchors.left: input2Rec.right
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
            id: input1_3Text
            text: "INPUT-3"
            font.pointSize: 14
            font.weight: Font.Bold
            anchors.horizontalCenter: parent.horizontalCenter
        }
        // //對邊機切斷關聯檢出
        Text {
            id:text_3_0
            x: 8
            y: 75
            width: 223
            height: 24
            text: qsTr("對邊機切斷開關檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input3_01
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                //color: "white"
                x: 243
                text:Kdb.webAlignerDisconnect//"I0.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_01.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status33
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.webAlignerDisconnectLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.webAlignerDisconnectLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status33MouseArea
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
        // //緊急停止-1
        Text {
            id:text_3_1
            anchors.top: text_3_0.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 85
            width: 223
            height: 24
            text: qsTr("緊急停止-1")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input3_11
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                y: parent.top
                text:Kdb.emergencyStop1//"I1.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_11.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status34
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.emergencyStop1Light ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.emergencyStop1Light ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status34MouseArea
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

        //緊急停止-2
        Text {
            id:text_3_2
            anchors.top: text_3_1.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 125
            width: 223
            height: 24
            text: qsTr("緊急停止-2")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input3_21
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                y: parent.top
                text:Kdb.emergencyStop2//"I2.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_21.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status35
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.emergencyStop2Light ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.emergencyStop2Light ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status35MouseArea
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

        //緊急停止-3
        Text {
            id:text_3_3
            anchors.top: text_3_2.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 165
            width: 223
            height: 24
            text: qsTr("緊急停止-3")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input3_31
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                y: parent.top
                text:Kdb.emergencyStop3//"I3.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_31.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status36
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.emergencyStop3Light ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.emergencyStop3Light ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status36MouseArea
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
        //緊急停止-4
        Text {
            id:text_3_4
            anchors.top: text_3_3.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 205
            width: 223
            height: 24
            text: qsTr("緊急停止-4")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input3_41
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                y: parent.top
                text:Kdb.emergencyStop4//"I4.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_41.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status37
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.emergencyStop4Light ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.emergencyStop4Light ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status37MouseArea
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
        //緊急停止-5
        Text {
            id:text_3_5
            anchors.top: text_3_4.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 205
            width: 223
            height: 24
            text: qsTr("緊急停止-5 ")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input3_51
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                y: parent.top
                text:Kdb.emergencyStop5//"I5.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_51.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status38
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.emergencyStop5Light ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.emergencyStop5Light ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status38MouseArea
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
        //緊急停止-6
        Text {
            id:text_3_6
            anchors.top: text_3_5.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 245
            width: 223
            height: 24
            text: qsTr("緊急停止-6")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input3_61
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                y: parent.top
                text:Kdb.emergencyStop6//"I6.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_61.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status39
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.emergencyStop6Light ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.emergencyStop6Light ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status39MouseArea
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
        //緊急停止-7
        Text {
            id:text_3_7
            anchors.top: text_3_6.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 285
            width: 223
            height: 24
            text: qsTr("緊急停止-7")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input3_71
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                y: parent.top
                text:Kdb.emergencyStop7//"I7.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_71.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status40
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.emergencyStop7Light ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.emergencyStop7Light ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status40MouseArea
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
        //主傳動左側門1開啟中
        Text {
            id:text_3_8
            anchors.top: text_3_7.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 325
            width: 223
            height: 24
            text: qsTr("主傳動左側門1開啟中")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input3_81
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:Kdb.mainDriveLeftDoor1Open//"I8.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_81.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status41
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.mainDriveLeftDoor1OpenLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.mainDriveLeftDoor1OpenLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status41MouseArea
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
        //主傳動左側門2開啟中
        Text {
            id:text_3_9
            anchors.top: text_3_8.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 365
            width: 223
            height: 24
            text: qsTr("主傳動左側門2開啟中")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input3_91
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:Kdb.mainDriveLeftDoor2Open//"I9.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_91.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status42
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.mainDriveLeftDoor2OpenLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.mainDriveLeftDoor2OpenLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status42MouseArea
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
        //主傳動左側門3開啟中
        Text {
            id:text_3_10
            anchors.top: text_3_9.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 405
            width: 223
            height: 24
            text: qsTr("主傳動右側門3開啟中")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input3_10_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:Kdb.mainDriveRightDoor3Open//"I0.10"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_10_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status43
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.mainDriveLeftDoor3OpenLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.mainDriveLeftDoor3OpenLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status43MouseArea
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
        //主傳動左側門4開啟中
        Text {
            id:text_3_11
            anchors.top: text_3_10.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 445
            width: 223
            height: 24
            text: qsTr("主傳動右側門4開啟中")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input3_11_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:Kdb.mainDriveRightDoor4Open//"I0.11"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_11_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status44
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.mainDriveLeftDoor4OpenLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.mainDriveLeftDoor4OpenLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status44MouseArea
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
        //大捲收捲機左側門5開啟中
        Text {
            id:text_3_12
            anchors.top: text_3_11.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 485
            width: 223
            height: 24
            text: qsTr("大卷收捲機左側門5開啟中")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {

                id: input3_12_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:Kdb.largeWinderLeftDoor5Open//"I0.12"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_12_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status45
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.mainDriveLeftDoor5OpenLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.mainDriveLeftDoor5OpenLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status45MouseArea
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
        //大捲收捲機左側門6開啟中
        Text {
            id:text_3_13
            anchors.top: text_3_12.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 525
            width: 223
            height: 24
            text: qsTr("大卷收捲機左側門6開啟中")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input3_13_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:Kdb.largeWinderLeftDoor6Open//"I0.13"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_13_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status46
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.mainDriveLeftDoor6OpenLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.mainDriveLeftDoor6OpenLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status46MouseArea
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
        //大捲收捲機左側門7開啟中
        Text {
            id:text_3_14
            anchors.top: text_3_13.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 565
            width: 223
            height: 24
            text: qsTr("大卷收捲機右側門7開啟中")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input3_14_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:Kdb.largeWinderRightDoor7Open//"I0.14"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_14_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status47
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.mainDriveLeftDoor7OpenLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.mainDriveLeftDoor7OpenLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status47MouseArea
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
        //大捲收捲機左側門8開啟中
        Text {
            id:text_3_15
            x: 8
            anchors.top: text_3_14.bottom
            anchors.topMargin: topMargin
            width: 223
            height: 24
            text: qsTr("大卷收捲機右側門8開啟中")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input3_15_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:Kdb.largeWinderRightDoor8Open//"I0.15"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input3_15_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status48
                x: 386
                y: -10
                height: 30
                width:30
                radius:50
                //width: input0_2.width
                color: Kdb.mainDriveLeftDoor8OpenLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.mainDriveLeftDoor8OpenLight ?  "#88FF0A" : "red"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id:status48MouseArea
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

    ParameterSetting2{
        id: parameterSetting2
        visible: false
    }
}
