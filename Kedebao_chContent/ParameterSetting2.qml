import QtQuick
import QtQuick.Controls
import QtQuick.Studio.DesignEffects
import QtQuick.Effects

Rectangle {
    id: root
    width: 1920
    height: 1080
    color: "#F0F0F2"

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
                root.visible = false
            }
        }
    }

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
                root.visible = false
                //root.visible = false
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
                parameterSetting3.visible = true
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
                parameterSetting3.visible = true
                //root.visible = false
            }
        }
    }

    //input4
    Rectangle{
        id: input4Rec
        // anchors.left: input3Rec.right
        // anchors.leftMargin: groupLeftMargin
        x:100
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
            id: input1_4Text
            text: "INPUT-4"
            font.pointSize: 14
            font.weight: Font.Bold
            anchors.horizontalCenter: parent.horizontalCenter
        }
        // //放卷區圓盤檢知-1
        Text {
            id:text_4_0
            x: 8
            y: 75
            width: 223
            height: 24
            text: qsTr("放卷區圍籬檢知-1")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input4_01
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                //color: "white"
                x: 243
                text:"I0.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input4_01.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status0
                x: 386
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
        //放卷區圓盤檢知-2
        Text {
            id:text_4_1
            anchors.top: text_4_0.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 85
            width: 223
            height: 24
            text: qsTr("放卷區圍籬檢知-2")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input4_11
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:"I1.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input4_11.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status1
                x: 386
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

        //大捲收卷區圓盤檢知-3
        Text {
            id:text_4_2
            anchors.top: text_4_1.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 125
            width: 223
            height: 24
            text: qsTr("大捲收卷區圍籬檢知-3")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input4_21
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:"I2.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input4_21.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status2
                x: 386
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

        //大捲收卷區圓盤檢知-4
        Text {
            id:text_4_3
            anchors.top: text_4_2.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 165
            width: 223
            height: 24
            text: qsTr("大捲收卷區圍籬檢知-4")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input4_31
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:"I3.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input4_31.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status3
                x: 386
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
        //放卷區安全光柵異常
        Text {
            id:text_4_4
            anchors.top: text_4_3.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 205
            width: 223
            height: 24
            text: qsTr("放卷區安全光柵異常")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input4_41
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:"I4.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input4_41.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status4
                x: 386
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
        //檢測區安全光柵異常
        Text {
            id:text_4_5
            anchors.top: text_4_4.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 205
            width: 223
            height: 24
            text: qsTr("檢測區安全光柵異常 ")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input4_51
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:"I5.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input4_51.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status5
                x: 386
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
        //大卷收捲區光柵異常
        Text {
            id:text_4_6
            anchors.top: text_4_5.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 245
            width: 223
            height: 24
            text: qsTr("大卷收捲區光柵異常")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input4_61
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:"I6.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input4_61.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status6
                x: 386
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
        //小卷收捲軸零速檢出
        Text {
            id:text_4_7
            anchors.top: text_4_6.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 285
            width: 223
            height: 24
            text: qsTr("小卷收捲軸零速檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input4_71
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:"I7.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input4_71.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status7
                x: 386
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
        //大卷收捲軸零速檢出
        Text {
            id:text_4_8
            anchors.top: text_4_7.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 325
            width: 223
            height: 24
            text: qsTr("大卷收捲軸零速檢出")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input4_81
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:"I8.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input4_81.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status8
                x: 386
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
        //放卷張力過大
        Text {
            id:text_4_9
            anchors.top: text_4_8.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 365
            width: 223
            height: 24
            text: qsTr("放卷張力過大")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input4_91
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:"I9.00"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input4_91.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status9
                x: 386
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
        //小卷收卷張力過大
        Text {
            id:text_4_10
            anchors.top: text_4_9.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 405
            width: 223
            height: 24
            text: qsTr("小卷收卷張力過大")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input4_10_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:"I0.10"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input4_10_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status10
                x: 386
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
        //大卷收卷張力過大
        Text {
            id:text_4_11
            anchors.top: text_4_10.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 445
            width: 223
            height: 24
            text: qsTr("大卷收卷張力過大")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input4_11_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:"I0.11"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input4_11_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status11
                x: 386
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
        //左側耳料收捲角度異常
        Text {
            id:text_4_12
            anchors.top: text_4_11.bottom
            anchors.topMargin: topMargin
            x: 8
            y: 485
            width: 223
            height: 24
            text: qsTr("左側耳料收捲角度異常")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {

                id: input4_12_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:"I0.12"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input4_12_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status12
                x: 386
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
        //右側耳料收捲角度異常
        Text {
            id:text_4_13
            anchors.top: text_4_12.bottom
            anchors.topMargin: topMargin
            x: 8
            //y: 525
            width: 223
            height: 24
            text: qsTr("右側耳料收捲角度異常")
            font.pixelSize: 19
            horizontalAlignment: Text.AlignRight

            Text {
                id: input4_13_1
                width: 100
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                x: 243
                text:"I0.13"
                color: "#aaaaaa"
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:22
                    width: input4_13_1.width
                    color: "#aaaaaa"
                }
            }
            Rectangle {
                id:status13
                x: 386
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
        // }
    }
    ParameterSetting3{
        id: parameterSetting3
        visible: false
    }

}
