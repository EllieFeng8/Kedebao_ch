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


    property int topMargin: 65
    property int topMargin2: 35
    property int groupLeftMargin: 100
    property int setWidth: 190
    property int setWidth1: 173

    property int textInputLeft:203
    property int textInputLeft2:335

    property bool clicked:Kdb.analogOutUnwinderMainDriveSwitch
    property bool clicked1:Kdb.modifyAnalogOutWinderSwitch
    property bool clicked2:Kdb.modifyAnalogOutCutterSwitch
    property bool clicked3:Kdb.modifyAnalogOutSelvedgeWinderSwitch
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
                AppState.pageNum = 1;
                setParameterInterface(AppState.pageNum);
                //parameterSetting2.visible = true
                // root.visible = false
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
                // root.visible = false
                AppState.pageNum = 3;
                setParameterInterface(AppState.pageNum);
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
        width: 713
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
            padding:10
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
            y: 90
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
                text:Number(Kdb.analogOutUnwinderMainDrive).toFixed(2)//Kdb.analogOutUnwinderMainDrive//"V0"
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
                text:Number(Kdb.modifyAnalogOutUnwinderMainDrive).toFixed(2)//Kdb.modifyAnalogOutUnwinderMainDrive
                x: 386
                y: 20
                focus: true
                validator: DoubleValidator {}//限制只能輸入整數/double
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
                    onClicked:{
                        if(Kdb.modifyAnalogOutUnwinderMainDrive !== Number(output0_2.text)) {
                            Kdb.modifyAnalogOutUnwinderMainDrive = output0_2.text
                            console.log("11 modifyAnalogOutUnwinderMainDrive changed~~~", Kdb.modifyAnalogOutUnwinderMainDrive);
                        }
                    }
                }
            }
            TextInput {
                id: output0_20
                width: 60
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                text:Number(Kdb.analogOutUnwinderMainDrivePc).toFixed(2)//Kdb.modifyAnalogOutUnwinderMainDrive
                x: 531
                y: 20
                focus: true
                validator: DoubleValidator {}//限制只能輸入整數/double
                Rectangle {
                    height: 2
                    y:22
                    width: output0_2.width
                    color: "#aaaaaa"
                }

            }
            Text {
                id:output0_201
                anchors.left:output0_20.right
                y: 23
                text:"%"
            }
            Image {
                id: btn00
                anchors.left:output0_201.right
                anchors.leftMargin:10
                y:5
                scale: 0.8
                source: "assets/rectangle_35.png"
                Text {
                    text: qsTr("OK")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btn00MouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btn00MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        if(Kdb.analogOutUnwinderMainDrivePc !== Number(output0_20.text)) {
                            Kdb.analogOutUnwinderMainDrivePc = Number(output0_20.text)
                            console.log("11 analogOutUnwinderMainDrivePc changed~~~", Kdb.analogOutUnwinderMainDrivePc);
                        }
                    }
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
                text:Number(Kdb.analogOutWinder).toFixed(2)//Kdb.analogOutWinder//"V1"
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
                text:Number(Kdb.modifyAnalogOutWinder).toFixed(2)//Kdb.modifyAnalogOutWinder
                validator: DoubleValidator {}//限制只能輸入整數/double
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
                    onClicked:{
                        if(Kdb.modifyAnalogOutWinder !== Number(output0_3.text)) {
                            Kdb.modifyAnalogOutWinder = output0_3.text
                            console.log("11 modifyAnalogOutWinder changed~~~", Kdb.modifyAnalogOutWinder);
                        }
                    }
                }
            }
            TextInput {
                id: output0_21
                width: 60
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                text:Number(Kdb.analogOutWinderPc).toFixed(2)//Kdb.modifyAnalogOutUnwinderMainDrive
                x: 531
                y: 20
                focus: true
                validator: DoubleValidator {}//限制只能輸入整數/double
                Rectangle {
                    height: 2
                    y:22
                    width: output0_2.width
                    color: "#aaaaaa"
                }

            }
            Text {
                id:output0_202
                anchors.left:output0_21.right
                y: 23
                text:"%"
            }
            Image {
                id: btn01
                anchors.left:output0_202.right
                anchors.leftMargin:10
                y:6
                scale: 0.8
                source: "assets/rectangle_35.png"
                Text {
                    text: qsTr("OK")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btn01MouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btn01MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        if(Kdb.analogOutWinderPc !== Number(output0_21.text)) {
                            Kdb.analogOutWinderPc = output0_21.text
                            console.log("11 analogOutWinderPc changed~~~", Kdb.analogOutWinderPc);
                        }
                    }
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
                text:Number(Kdb.analogOutCutter).toFixed(2)//Kdb.analogOutCutter//"V2"
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
                text:Number(Kdb.modifyAnalogOutCutter).toFixed(2)//Kdb.modifyAnalogOutCutter
                x: 386
                y: 20
                validator: DoubleValidator {}//限制只能輸入整數/double
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
                    onClicked:{
                        if(Kdb.modifyAnalogOutCutter !== Number(output1_2.text)) {
                            Kdb.modifyAnalogOutCutter = output1_2.text
                            console.log("11 modifyAnalogOutCutter changed~~~", Kdb.modifyAnalogOutCutter);
                        }
                    }
                }
            }
            TextInput {
                id: output0_22
                width: 60
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                text:Number(Kdb.analogOutCutterPc).toFixed(2)//Kdb.modifyAnalogOutUnwinderMainDrive
                x: 531
                y: 20
                focus: true
                validator: DoubleValidator {}//限制只能輸入整數/double
                Rectangle {
                    height: 2
                    y:22
                    width: output0_2.width
                    color: "#aaaaaa"
                }

            }
            Text {
                id:output0_203
                anchors.left:output0_22.right
                y: 23
                text:"%"
            }
            Image {
                id: btn02
                anchors.left:output0_203.right
                anchors.leftMargin:10
                y:6
                scale: 0.8
                source: "assets/rectangle_35.png"
                Text {
                    text: qsTr("OK")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btn02MouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btn02MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        if(Kdb.analogOutCutterPc !== Number(output0_22.text)) {
                            Kdb.analogOutCutterPc = output0_22.text
                            console.log("11 analogOutCutterPc changed~~~", Kdb.analogOutCutterPc);
                        }
                    }
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
                text:Number(Kdb.analogOutSelvedgeWinder).toFixed(2)//Kdb.analogOutSelvedgeWinder//"V3"
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
                text:Number(Kdb.modifyAnalogOutSelvedgeWinder).toFixed(2)//Kdb.modifyAnalogOutSelvedgeWinder
                x: 386
                y: 20
                validator: DoubleValidator {}//限制只能輸入整數/double
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
                    onClicked:{
                        if(Kdb.modifyAnalogOutSelvedgeWinder !== Number(output0_5.text)) {
                            Kdb.modifyAnalogOutSelvedgeWinder = output0_5.text
                            console.log("11 modifyAnalogOutSelvedgeWinder changed~~~", Kdb.modifyAnalogOutSelvedgeWinder);
                        }
                    }
                }
            }
            TextInput {
                id: output0_23
                width: 60
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                text:Number(Kdb.analogOutSelvedgeWinderPc).toFixed(2)//Kdb.modifyAnalogOutUnwinderMainDrive
                x: 531
                y: 20
                focus: true
                validator: DoubleValidator {}//限制只能輸入整數/double
                Rectangle {
                    height: 2
                    y:22
                    width: output0_2.width
                    color: "#aaaaaa"
                }

            }
            Text {
                id:output0_204
                anchors.left:output0_23.right
                y: 23
                text:"%"
            }
            Image {
                id: btn03
                anchors.left:output0_204.right
                anchors.leftMargin:10
                y:6
                scale: 0.8
                source: "assets/rectangle_35.png"
                Text {
                    text: qsTr("OK")
                    color: "#aaaaaa"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter // 垂直文字置中
                    font.bold: true
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: btn03MouseArea.containsMouse ? true : false
                    shadowColor: "#58000000"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: btn03MouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        if(Kdb.analogOutSelvedgeWinderPc !== Number(output0_23.text)) {
                            Kdb.analogOutSelvedgeWinderPc = output0_23.text
                            console.log("11 analogOutSelvedgeWinderPc changed~~~", Kdb.analogOutSelvedgeWinderPc);
                        }
                    }
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
            padding:10
            font.pointSize: 14
            font.weight: Font.Bold
            anchors.horizontalCenter: parent.horizontalCenter
        }
        //啟動
        Text {
            id:text_2_0
            x: 38
            y: 90
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
                text:Number(Kdb.ipcStart).toFixed(2)//Kdb.ipcStart//"I4.00"
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
                color: Kdb.ipcStartLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.ipcStartLight ?  "#88FF0A" : "red"
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
            anchors.left: text_2_0.left
            anchors.topMargin: topMargin2
            // x: 8
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
                text:Number(Kdb.ipcStop).toFixed(2)//Kdb.ipcStop//"I4.01"
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
                color: Kdb.ipcStopLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.ipcStopLight ?  "#88FF0A" : "red"
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
            anchors.left: text_2_1.left
            anchors.topMargin: topMargin2
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
                text:Number(Kdb.ipcAlarmReset).toFixed(2)//Kdb.ipcAlarmReset//"I4.02"
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
                color: Kdb.ipcAlarmResetLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.ipcAlarmResetLight ?  "#88FF0A" : "red"
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
            anchors.left: text_2_2.left
            anchors.topMargin: topMargin2
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
                text:Number(Kdb.mainJogForward).toFixed(2)//Kdb.mainJogForward//"I4.03"
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
                color: Kdb.mainJogForwardLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.mainJogForwardLight ?  "#88FF0A" : "red"
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
            anchors.left: text_2_3.left
            anchors.topMargin: topMargin2

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
                text:Number(Kdb.mainJogReverse).toFixed(2)//Kdb.mainJogReverse//"I4.04"
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
                color: Kdb.mainJogReverseLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.mainJogReverseLight ?  "#88FF0A" : "red"
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
            anchors.left: text_2_4.left
            anchors.topMargin: topMargin2
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
                text:Number(Kdb.smallWinderJogForward).toFixed(2)//Kdb.smallWinderJogForward//"I4.05"
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
                color: Kdb.mainJogReverseLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.mainJogReverseLight ?  "#88FF0A" : "red"
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
            anchors.left: text_2_5.left
            anchors.topMargin: topMargin2
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
                text:Number(Kdb.smallWinderJogReverse).toFixed(2)//Kdb.smallWinderJogReverse//"I4.06"
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
                color: Kdb.smallWinderJogForwardLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.smallWinderJogForwardLight ?  "#88FF0A" : "red"
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
            anchors.left: text_2_6.left
            anchors.topMargin: topMargin2
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
                text:Number(Kdb.unwinderJogReverseSelect).toFixed(2)//Kdb.unwinderJogReverseSelect//"I4.07"
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
                color: Kdb.unwinderJogReverseSelectLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.unwinderJogReverseSelectLight ?  "#88FF0A" : "red"
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
            anchors.left: text_2_7.left
            anchors.topMargin: topMargin2
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
                text:Number(Kdb.unwinderJogStart).toFixed(2)//Kdb.unwinderJogStart//"I4.08"
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
                color: Kdb.unwinderJogStartLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.unwinderJogStartLight ?  "#88FF0A" : "red"
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
            anchors.left: text_2_8.left
            anchors.topMargin: topMargin2
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
                text:Number(Kdb.winderJogReverseSelect).toFixed(2)//Kdb.winderJogReverseSelect//"I4.09"
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
                color: Kdb.winderJogReverseSelectLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.winderJogReverseSelectLight ?  "#88FF0A" : "red"
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
            anchors.left: text_2_9.left
            anchors.topMargin: topMargin2
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
                text:Number(Kdb.winderJogStart).toFixed(2)//Kdb.winderJogStart//"I4.10"
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
                color: Kdb.winderJogStartLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.winderJogStartLight ?  "#88FF0A" : "red"
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
            anchors.left: text_2_10.left
            anchors.topMargin: topMargin2
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
                text:Number(Kdb.leftSelvedgeWinderSelect).toFixed(2)//Kdb.leftSelvedgeWinderSelect//"I4.10"
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
                color: Kdb.leftSelvedgeWinderSelectLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.leftSelvedgeWinderSelectLight ?  "#88FF0A" : "red"
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
            anchors.left: text_2_11.left
            anchors.topMargin: topMargin2
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
                text:Number(Kdb.rightSelvedgeWinderSelect).toFixed(2)//Kdb.rightSelvedgeWinderSelect//"I4.10"
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
                color: Kdb.rightSelvedgeWinderSelectLight ?  "#88FF0A" : "red"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled:  true
                    shadowColor: Kdb.rightSelvedgeWinderSelectLight ?  "#88FF0A" : "red"
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


}
