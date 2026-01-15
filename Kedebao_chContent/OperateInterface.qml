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


    property int topMargin: 95
    property int topMargin2: 45
    //property int groupLeftMargin: 100
    property int setWidth: 220
    property int setWidth1: 200

    property int textInputLeft:213
    property int textInputLeft2:335

    property int textLeft: 90

    property int fontSize: 28
    property int inputTextSize:24
    property int dashPos: 28
    property int btnPos:-15

        Text {
        id: title
        x:935
        y:49
        text: "控制介面"
        font.weight: Font.Bold
        font.pointSize: 20
        anchors.horizontalCenter: parent.horizontalCenter
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

    //ANALOG OUTPUT
    Rectangle{
        id: smallMotor
        //x:groupLeftMargin
        y:119
        width: 1208
        height: 948
        radius: 40
        //anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
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

        Rectangle{
            id: switchRect
            x: 834
            y: 25
            width: 240
            height: 71
            color: "#00ffffff"
            Text {
                id: switchText
                x:110
                y:15
                text: Kdb.singleActionMode ? qsTr("單動模式開啟") : qsTr("單動模式關閉")
                color: Kdb.singleActionMode ? "black" : "red"
                font.weight: Font.Bold
                font.pointSize: 15
                //anchors.verticalCenter:  parent.verticalCenter
            }
            Image{
                id: singleActionSwitch
                anchors.verticalCenter:  parent.verticalCenter
                source: Kdb.singleActionMode ?  "assets/Group11.png" : "assets/Group 34.png"


                MouseArea{
                    id:singleActionSwitchMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        Kdb.singleActionMode = !Kdb.singleActionMode

                        btnMouseArea.enabled=Kdb.singleActionMode ? true :false
                        btnMainMouseArea.enabled=Kdb.singleActionMode ? true :false
                        btnLargeMouseArea.enabled=Kdb.singleActionMode ? true :false
                        btnWasteBMouseArea.enabled=Kdb.singleActionMode ? true :false
                        unwindingMouseArea.enabled=Kdb.singleActionMode ? true :false
                        btnOppositeMouseArea.enabled=Kdb.singleActionMode ? true :false
                        btnCutterMouseArea.enabled=Kdb.singleActionMode ? true :false
                        btnWasteAMouseArea.enabled=Kdb.singleActionMode ? true :false
                        btnTensionMouseArea.enabled=Kdb.singleActionMode ? true :false
                        btnSmallRollTensioMouseArea.enabled=Kdb.singleActionMode ? true :false
                        btnLargeRollTensioMouseArea.enabled=Kdb.singleActionMode ? true :false
                        output0_1.enabled = Kdb.singleActionMode ? true :false
                        output1_1.enabled = Kdb.singleActionMode ? true :false
                        output2_1.enabled = Kdb.singleActionMode ? true :false
                        output3_1.enabled = Kdb.singleActionMode ? true :false
                        output4_1.enabled = Kdb.singleActionMode ? true :false
                        output5_1.enabled = Kdb.singleActionMode ? true :false
                        output6_1.enabled = Kdb.singleActionMode ? true :false
                        output7_1.enabled = Kdb.singleActionMode ? true :false
                        output8_1.enabled = Kdb.singleActionMode ? true :false
                        output9_1.enabled = Kdb.singleActionMode ? true :false
                        output10_1.enabled = Kdb.singleActionMode ? true :false

                    }
                }
            }
        }


        Text {
            id:text_0
            x: textLeft
            y: 135
            width: setWidth1
            height: 24
            text: qsTr("小捲馬達")
            font.pixelSize: fontSize
            horizontalAlignment: Text.AlignRight

            TextInput {
                id: output0_1
                width: 100
                font.pixelSize: inputTextSize
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:Number(Kdb.smallRollMotor).toFixed(2)//Kdb.smallRollMotor
                validator: DoubleValidator {}//限制只能輸入整數/double
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:dashPos
                    width: output0_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: btnSmallMotor
                x:350
                y:btnPos
                source: "assets/rectangle_35.png"
                Text {
                    id: btName
                    text: qsTr("吋動")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btnMouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btnMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        if(Kdb.smallRollMotor !== Number(output0_1.text)) {
                            Kdb.smallRollMotor = output0_1.text
                            //console.log("11 smallRollMotor changed~~~", Kdb.smallRollMotor);
                        }
                    }
                    //onClicked: root.visible = false
                }
            }
        }

        Text {
            id:text_1
            x: textLeft
            anchors.top: text_0.bottom
            anchors.topMargin: topMargin
            //y: smallMotor.bottom
            width: setWidth1
            height: 24
            text: qsTr("主傳馬達")
            font.pixelSize: fontSize
            horizontalAlignment: Text.AlignRight

            TextInput {
                id: output1_1
                width: 100
                font.pixelSize: inputTextSize
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:Number(Kdb.mainDriveMotor).toFixed(2)//Kdb.mainDriveMotor
                validator: DoubleValidator {}//限制只能輸入整數/double
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:dashPos
                    width: output1_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: btnMainMotor
                x:350
                y:btnPos
                source: "assets/rectangle_35.png"
                Text {
                    id: btnMainName
                    text: qsTr("吋動")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btnMainMouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btnMainMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    enabled: true
                    onClicked: {
                        if(Kdb.mainDriveMotor !== Number(output1_1.text)) {
                            Kdb.mainDriveMotor = output1_1.text
                            //console.log("11 mainDriveMotor changed~~~", Kdb.mainDriveMotor);
                        }
                    }
                }
            }
        }

        Text {
            id:text_2
            x: textLeft
            anchors.top: text_1.bottom
            anchors.topMargin: topMargin
            width: setWidth1
            height: 24
            text: qsTr("大捲馬達")
            font.pixelSize: fontSize
            horizontalAlignment: Text.AlignRight

            TextInput {
                id: output2_1
                width: 100
                font.pixelSize: inputTextSize
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:Number(Kdb.largeRollMotor).toFixed(2)//Kdb.largeRollMotor
                validator: DoubleValidator {}//限制只能輸入整數/double
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:dashPos
                    width: output2_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: btnLargeMotor
                x:350
                y:btnPos
                source: "assets/rectangle_35.png"
                Text {
                    id: btnLargeName
                    text: qsTr("吋動")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btnLargeMouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btnLargeMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if(Kdb.largeRollMotor !== Number(output2_1.text)) {
                            Kdb.largeRollMotor = output2_1.text
                            //console.log("11 largeRollMotor changed~~~", Kdb.largeRollMotor);
                        }
                    }
                }
            }
        }

        Text {
    id:text_3
    x: textLeft
    anchors.top: text_2.bottom
    anchors.topMargin: topMargin
    width: setWidth1
    height: 24
    text: qsTr("捲廢料馬達B")
    font.pixelSize: fontSize
    horizontalAlignment: Text.AlignRight

    TextInput {
        id: output3_1
        width: 100
        font.pixelSize: inputTextSize
        horizontalAlignment: Text.AlignHCenter
        x: textInputLeft
        y: 0
        text:Number(Kdb.wasteRollMotorB).toFixed(2)//Kdb.wasteRollMotorB
        validator: DoubleValidator {}//限制只能輸入整數/double
        //placeholderText: "請輸入內容"
        focus: true

        Rectangle {
            height: 2
            y:dashPos
            width: output3_1.width
            color: "#aaaaaa"
        }
    }
    Image {
        id: btnWasteBMotor
        x:350
        y:btnPos
        source: "assets/rectangle_35.png"
        Text {
            id: btnWasteBName
            text: qsTr("吋動")
            color: "#aaaaaa"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
            font.bold: true
        }
        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: btnWasteBMouseArea.containsMouse ? true : false
            shadowColor: "#58000000"
            shadowBlur: 0.8
        }
        MouseArea {
            id: btnWasteBMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                if(Kdb.wasteRollMotorB !== Number(output3_1.text)) {
                    Kdb.wasteRollMotorB = output3_1.text
                    //console.log("11 wasteRollMotorB changed~~~", Kdb.wasteRollMotorB);
                }
            }
        }
    }
}

        Text {
            id:text_4
            x: textLeft
            anchors.top: text_3.bottom
            anchors.topMargin: topMargin
            width: setWidth1
            height: 24
            text: qsTr("放布馬達")
            font.pixelSize: fontSize
            horizontalAlignment: Text.AlignRight

            TextInput {
                id: output4_1
                width: 100
                font.pixelSize: inputTextSize
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:Number(Kdb.unwindingMotor).toFixed(2)//Kdb.unwindingMotor
                validator: DoubleValidator {}//限制只能輸入整數/double
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:dashPos
                    width: output4_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: unwindingMotor
                x:350
                y:btnPos
                source: "assets/rectangle_35.png"
                Text {
                    id: unwindingName
                    text: qsTr("吋動")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: unwindingMouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: unwindingMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if(Kdb.unwindingMotor !== Number(output4_1.text)) {
                            Kdb.unwindingMotor = output4_1.text
                            //console.log("11 unwindingMotor changed~~~", Kdb.unwindingMotor);
                        }
                    }
                }
            }
        }

        Text {
            id:text_5
            x: textLeft
            anchors.top: text_4.bottom
            anchors.topMargin: topMargin
            width: setWidth1
            //height: 24
            text: qsTr("對邊馬達")
            font.pixelSize: fontSize
            horizontalAlignment: Text.AlignRight

            TextInput {
                id: output5_1
                width: 100
                font.pixelSize: inputTextSize
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:Number(Kdb.edgeAlignMotor).toFixed(2)//Kdb.edgeAlignMotor
                validator: DoubleValidator {}//限制只能輸入整數/double
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:dashPos
                    width: output5_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: btnOppositeMotor
                x:350
                y:btnPos
                source: "assets/rectangle_35.png"
                Text {
                    id: btnOppositeName
                    text: qsTr("吋動")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btnOppositeMouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btnOppositeMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if(Kdb.edgeAlignMotor !== Number(output5_1.text)) {
                            Kdb.edgeAlignMotor = output5_1.text
                            //console.log("11 edgeAlignMotor changed~~~", Kdb.edgeAlignMotor);
                        }
                    }
                }
            }
        }

        Text {
            id:text_6
            anchors.left: text_5.left
            anchors.top: text_5.bottom
            anchors.topMargin: topMargin
            //y: smallMotor.bottom
            width: setWidth1
            //height: 24
            text: qsTr("切刀輪馬達")
            font.pixelSize: fontSize
            horizontalAlignment: Text.AlignRight

            TextInput {
                id: output6_1
                width: 100
                font.pixelSize: inputTextSize
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:Number(Kdb.cutterWheelMotor).toFixed(2)//Kdb.cutterWheelMotor
                validator: DoubleValidator {}//限制只能輸入整數/double
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:dashPos
                    width: output5_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: btnCutterMotor
                x:350
                y:btnPos
                source: "assets/rectangle_35.png"
                Text {
                    id: btnCutterName
                    text: qsTr("吋動")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btnCutterMouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btnCutterMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        if(Kdb.cutterWheelMotor !== Number(output6_1.text)) {
                            Kdb.cutterWheelMotor = output6_1.text
                            //console.log("11 cutterWheelMotor changed~~~", Kdb.cutterWheelMotor);
                        }
                    }
                }
            }
        }

        Text {
            id:text_7
            x: 700
            y: 136
            //anchors.topMargin: topMargin
            //y: smallMotor.bottom
            width: setWidth1
            height: 24
            text: qsTr("捲廢料馬達A")
            font.pixelSize: fontSize
            horizontalAlignment: Text.AlignRight

            TextInput {
                id: output7_1
                width: 100
                font.pixelSize: inputTextSize
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:Number(Kdb.wasteRollMotorA).toFixed(2)//Kdb.wasteRollMotorA
                validator: DoubleValidator {}//限制只能輸入整數/double
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:dashPos
                    width: output5_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: btnWasteAMotor
                x:350
                y:btnPos
                source: "assets/rectangle_35.png"
                Text {
                    id: btnWasteAName
                    text: qsTr("吋動")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btnWasteAMouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btnWasteAMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if(Kdb.wasteRollMotorA !== Number(output7_1.text)) {
                            Kdb.wasteRollMotorA = output7_1.text
                            //console.log("11 wasteRollMotorA changed~~~", Kdb.wasteRollMotorA);
                        }
                    }
                }
            }
        }


        Text {
            id:text_8
            anchors.left: text_7.left
            anchors.top: text_7.bottom
            anchors.topMargin: topMargin
            //y: smallMotor.bottom
            width: setWidth1
            //height: 24
            text: qsTr("放捲張力")
            font.pixelSize: fontSize
            horizontalAlignment: Text.AlignRight

            TextInput {
                id: output8_1
                width: 100
                font.pixelSize: inputTextSize
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:Number(Kdb.unwindingTension).toFixed(2)//Kdb.unwindingTension
                validator: DoubleValidator {}//限制只能輸入整數/double
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:dashPos
                    width: output8_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: btnTensionMotor
                x:350
                y:btnPos
                source: "assets/rectangle_35.png"
                Text {
                    id: btnTensionName
                    text: qsTr("OK")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btnTensionMouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btnTensionMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if(Kdb.unwindingTension !== Number(output8_1.text)){
                            Kdb.unwindingTension = output8_1.text
                            //console.log("11 unwindingTension changed~~~",Kdb.unwindingTension);
                        }
                    }
                }
            }
        }

        Text {
            id:text_9

            anchors.left: text_8.left
            anchors.top: text_8.bottom
            anchors.topMargin: topMargin
            //y: smallMotor.bottom
            width: setWidth1
            //height: 24
            text: qsTr("小捲張力")
            font.pixelSize: fontSize
            horizontalAlignment: Text.AlignRight

            TextInput {
                id: output9_1
                width: 100
                font.pixelSize: inputTextSize
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:Number(Kdb.smallRollTension).toFixed(2)//Kdb.smallRollTension
                validator: DoubleValidator {}//限制只能輸入整數/double
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:dashPos
                    width: output9_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: btnSmallRollTensionMotor
                x:350
                y:btnPos
                source: "assets/rectangle_35.png"
                Text {
                    id: btnSmallRollTensioName
                    text: qsTr("OK")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btnSmallRollTensioMouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btnSmallRollTensioMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if(Kdb.smallRollTension !== Number(output9_1.text)) {
                            Kdb.smallRollTension = output9_1.text
                            //console.log("11 smallRollTension changed~~~", Kdb.smallRollTension);
                        }
                    }
                }
            }
        }

        Text {
            id:text_10

            anchors.left: text_9.left
            anchors.top: text_9.bottom
            anchors.topMargin: topMargin
            width: setWidth1
            //height: 24
            text: qsTr("大捲張力")
            font.pixelSize: fontSize
            horizontalAlignment: Text.AlignRight

            TextInput {
                id: output10_1
                width: 100
                font.pixelSize: inputTextSize
                horizontalAlignment: Text.AlignHCenter
                x: textInputLeft
                y: 0
                text:Number(Kdb.largeRollTension).toFixed(2)//Kdb.largeRollTension
                validator: DoubleValidator {}//限制只能輸入整數/double
                //placeholderText: "請輸入內容"
                focus: true

                Rectangle {
                    height: 2
                    y:dashPos
                    width: output10_1.width
                    color: "#aaaaaa"
                }
            }
            Image {
                id: btnLargeRollTensionMotor
                x:350
                y:btnPos
                source: "assets/rectangle_35.png"
                Text {
                    id: btnLargeRollTensioName
                    text: qsTr("OK")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btnLargeRollTensioMouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btnLargeRollTensioMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if(Kdb.largeRollTension !== Number(output10_1.text)) {
                            Kdb.largeRollTension = output10_1.text
                            //console.log("11 largeRollTension changed~~~", Kdb.largeRollTension);
                        }
                    }
                }
            }
        }

    }

}
