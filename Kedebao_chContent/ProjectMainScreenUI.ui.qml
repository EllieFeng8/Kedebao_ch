import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import Core 1.0
import QtQuick.Layouts
import Kedebao_chContent

Rectangle {
    id: root
    width: 1920
    height: 1080
    // color:"#eeeeef"
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#F0F1F3" }
        GradientStop { position: 1.0; color: "#EBEBEB" }
    }
    property alias smallR: smallR
    property alias unWindingTensionPosition: unWindingTensionPosition
    property alias flipImgMouseArea: flipImgMouseArea
    property alias bigRollTensionSetting: bigRollTensionSetting
    property alias smallRollTensionSetting: smallRollTensionSetting
    property alias bigmodelPic : bigmodelPic
    property alias bigCoilTension: bigCoilTension
    property alias smallCoilTension: smallCoilTension
    property alias unwindingTension: unwindingTension
    property alias brakeDistance: brakeDistance
    property alias speedSet: speedSet
    property alias lengthSet: lengthSet
    property bool isbigRoll: false

    property alias lightBelowUIMouseArea: lightBelowUIMouseArea
    property alias lightBelowUI: lightBelowUI
    property alias whiteLightUI: whiteLightUI
    property alias whiteLightMouseArea: whiteLightMouseArea
    property alias uvLampUI: uvLampUI

    property alias brakingDistanceButton: brakingDistanceButton
    property alias brakingDistanceMouseArea: brakingDistanceMouseArea
    property alias speedSettingButton: speedSettingButton
    property alias speedSettingmouseArea: speedSettingmouseArea
    property alias lenthSettingButton: lenthSettingButton
    property alias lenthSettingmouseArea: lenthSettingmouseArea
    property alias bigCoilTensionButton: bigCoilTensionButton
    property alias bigCoilTensionMouseArea: bigCoilTensionMouseArea
    property alias unwindingTensionButton: unwindingTensionButton
    property alias unwindingTensionMouseArea: unwindingTensionMouseArea
    property alias smallCoilTensionButton: smallCoilTensionButton
    property alias smallCoilTensionMouseArea: smallCoilTensionMouseArea
    property alias bigRollCutterSwitch: bigRollCutterSwitch //大捲切刀switchUI
    property alias bigRollCutterSwitchMouseArea: bigRollCutterSwitchMouseArea //大捲切刀MouseArea

    property alias uvLampMouseArea: uvLampMouseArea
    property alias settingButton: settingButton
    property alias settingMouseArea: settingMouseArea
    property alias resetButton: resetButton
    property alias resetMouseArea: resetMouseArea
    property bool clicked: false //紫光燈switch
    property bool clicked1: false //白光燈switch
    property bool clicked2: false //下方照明燈switch
    property bool isFlip: false // 前後翻轉
    property bool clicked4: false // 大捲切刀switch
    property bool smallCoiSwitch: false //小捲張力switch
    property bool bigCoiSwitch: false //大捲張力switch
    property int modifyBrakingDistance: 5
    clip: true


    Item {
        id: group_30

        x: 509
        y: 38

        height: 115
        width: 1171

        Image {
            id: rectangle_21

            x: -63
            y: 0
            width: 1303
            height: 123

            source: "assets/rectangle_21.png"


            RowLayout {
                id: buttonrow
                anchors.centerIn: parent          // ⭐ 上下左右置中
                spacing: 35                      // ⭐ 每顆按鈕等距
                //金屬探測
                Item {
                    id: group_19

                    // x: -40
                    // y: 26

                    height: 72
                    width: 172

                    Text {
                        id: element_14

                        x: 60

                        height: 72
                        width: 64
                        color: "#000000"
                        font.pixelSize: 32
                        font.weight: Font.Normal
                        horizontalAlignment: Text.AlignLeft
                        lineHeight: 36
                        lineHeightMode: Text.FixedHeight
                        text: "金屬探測"
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WordWrap
                    }
                    Image {
                        id: metalDetectorSign

                        y: 6

                        source: "assets/electrical_1.png"
                    }
                    IndicatorUI {
                        id: rectangle_22

                        x: 128
                        y: 7
                        statusColor:Kdb.metalDetector
                    }
                }
                //門E
                Item {
                    id: group_20

                    // x: 162
                    // y: 38

                    height: 40
                    width: 138

                    Text {
                        id: e

                        x: 46
                        y: 1

                        height: 39
                        width: 56

                        color: "#000000"
                        font.pixelSize: 32
                        font.weight: Font.Normal
                        horizontalAlignment: Text.AlignLeft
                        text: "門E"
                        verticalAlignment: Text.AlignTop
                        wrapMode: Text.WordWrap
                    }
                    IndicatorUI {
                        id: doorCSign

                        x: 94
                        y: -9
                        statusColor:Kdb.doorESignal
                    }
                    Image {
                        id: doorway_6

                        source: "assets/doorway_6.png"
                    }
                }
                //門F
                Item {
                    id: group_21
                    height: 40
                    width: 137

                    Text {
                        id: f
                        x: 46
                        y: 1
                        height: 39
                        width: 69
                        color: "#000000"
                        font.pixelSize: 32
                        font.weight: Font.Normal
                        horizontalAlignment: Text.AlignLeft
                        text: "門F"
                        verticalAlignment: Text.AlignTop
                        wrapMode: Text.WordWrap
                    }
                    IndicatorUI {
                        id: doorDSign
                        x: 93
                        y: -9
                        statusColor:Kdb.doorFSignal
                    }
                    Image {
                        id: doorway_8
                        source: "assets/doorway_8.png"
                    }
                }
                //門G
                Item {
                    id: group_23
                    height: 40
                    width: 138

                    Text {
                        id: g
                        x: 46
                        y: 1
                        height: 39
                        width: 56
                        color: "#000000"
                        font.pixelSize: 32
                        font.weight: Font.Normal
                        horizontalAlignment: Text.AlignLeft
                        text: "門G"
                        verticalAlignment: Text.AlignTop
                        wrapMode: Text.WordWrap
                    }
                    //doorG
                    IndicatorUI {
                        id: doorGSign
                        x: 94
                        y: -9
                        statusColor:Kdb.doorGSignal
                    }
                    Image {
                        id: doorway_5
                        source: "assets/doorway_5.png"
                    }
                }
                //門H
                Item {
                    id: group_24
                    height: 40
                    width: 136

                    Text {
                        id: h
                        x: 45
                        y: 1
                        height: 39
                        width: 56
                        color: "#000000"
                        font.pixelSize: 32
                        font.weight: Font.Normal
                        horizontalAlignment: Text.AlignLeft
                        text: "門H"
                        verticalAlignment: Text.AlignTop
                        wrapMode: Text.WordWrap
                    }
                    //door H
                    IndicatorUI {
                        id: doorHSign
                        x: 92
                        y: -9
                        statusColor:Kdb.doorHSignal
                    }
                    Image {
                        id: doorway_7
                        source: "assets/doorway_7.png"
                    }
                }
                //光柵檢測
                Item {
                    id: group_3
                    height: 72
                    width: 152

                    Text {
                        id: element_15
                        x: 46
                        height: 72
                        width: 64
                        color: "#000000"
                        font.pixelSize: 32
                        font.weight: Font.Normal
                        horizontalAlignment: Text.AlignLeft
                        lineHeight: 36
                        lineHeightMode: Text.FixedHeight
                        text: "光柵檢測"
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WordWrap
                    }
                    //光柵檢測
                    IndicatorUI {
                        id: gratingDetectionSign
                        x: 108
                        y: 7
                        statusColor:Kdb.gratingDetection
                    }
                    Image {
                        id: feed_3
                        y: 16
                        source: "assets/feed_3.png"
                    }
                }
                //門I
                Item {
                    id: group_35
                    width: 136
                    height: 40
                    Text {
                        id: i
                        x: 45
                        y: 1
                        width: 56
                        height: 39
                        color: "#000000"
                        text: "門I"
                        font.pixelSize: 32
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignTop
                        wrapMode: Text.WordWrap
                        font.weight: Font.Normal
                    }

                    IndicatorUI {
                        id: doorISign
                        x: 92
                        y: -9
                        statusColor:Kdb.doorISignal
                    }

                    Image {
                        id: doorway_9
                        source: "assets/doorway_7.png"
                    }
                }
            }

        }

    }

    Image {
        id: rectangle_16
        x: 420
        y: 940
        source: "assets/rectangle_16.png"

        RowLayout {
            id: buttonrow1
            anchors.centerIn: parent          // ⭐ 上下左右置中
            spacing: 35                      // ⭐ 每顆按鈕等距
            //光柵檢測
            Item {
                id: group_22
                height: 72
                width: 152

                Text {
                    id: element
                    x: 46
                    height: 72
                    width: 64
                    color: "#000000"
                    font.pixelSize: 32
                    font.weight: Font.Normal
                    horizontalAlignment: Text.AlignLeft
                    lineHeight: 36
                    lineHeightMode: Text.FixedHeight
                    text: "光柵檢測"
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                }
                IndicatorUI {
                    id: gratingDetection2
                    x: 108
                    y: 7
                    statusColor:Kdb.gratingDetection
                }
                Image {
                    id: feed_1
                    y: 16
                    source: "assets/feed_1.png"
                }
            }
            //對邊
            Item {
                id: group_29
                height: 42
                width: 149

                Text {
                    id: element_13
                    x: 43
                    height: 42
                    width: 64
                    color: "#000000"
                    font.pixelSize: 32
                    font.weight: Font.Normal
                    horizontalAlignment: Text.AlignLeft
                    lineHeight: 22
                    lineHeightMode: Text.FixedHeight
                    text: "對邊"
                    verticalAlignment: Text.AlignVCenter
                }
                Image {
                    id: left_alignment_1
                    y: 1
                    source: "assets/left_alignment_1.png"
                }
                //對邊
                IndicatorUI {
                    id: oppositeSideSign
                    x: 105
                    y: -8
                    statusColor:Kdb.oppositeSide
                }
            }
            //門A
            Item {
                id: group_28
                height: 40
                width: 140
                Text {
                    id: a
                    x: 48
                    y: 0
                    height: 39
                    width: 66
                    color: "#000000"
                    font.pixelSize: 32
                    font.weight: Font.Normal
                    horizontalAlignment: Text.AlignLeft
                    text: "門A"
                    verticalAlignment: Text.AlignTop
                    wrapMode: Text.WordWrap
                }
                //door A
                IndicatorUI {
                    id: doorASign
                    x: 96
                    y: -9
                    statusColor:Kdb.doorASignal
                }
                Image {
                    id: doorway_3
                    source: "assets/doorway_3.png"
                }
            }
            //門B
            Item {
                id: group_27
                height: 40
                width: 139

                Text {
                    id: b
                    x: 48
                    height: 39
                    width: 53
                    color: "#000000"
                    font.pixelSize: 32
                    font.weight: Font.Normal
                    horizontalAlignment: Text.AlignLeft
                    text: "門B"
                    verticalAlignment: Text.AlignTop
                    wrapMode: Text.WordWrap
                }
                //doorB
                IndicatorUI {
                    id: doorBSign
                    x: 95
                    y: -9
                    statusColor:Kdb.doorBSignal
                }
                Image {
                    id: doorway_4
                    source: "assets/doorway_4.png"
                }

            }
            //門c
            Item {
                id: group_26
                height: 40
                width: 138
                Text {
                    id: c
                    x: 48
                    height: 39
                    width: 58
                    color: "#000000"
                    font.pixelSize: 32
                    font.weight: Font.Normal
                    horizontalAlignment: Text.AlignLeft
                    text: "門C"
                    verticalAlignment: Text.AlignTop
                    wrapMode: Text.WordWrap
                }
                //doorE
                IndicatorUI {
                    id: doorESign
                    x: 94
                    y: -9
                    statusColor:Kdb.doorCSignal
                }
                Image {
                    id: doorway_1
                    source: "assets/doorway_1.png"
                }
            }
            //門D
            Item {
                id: group_25
                height: 40
                width: 137

                Text {
                    id: d
                    x: 48
                    height: 39
                    width: 58
                    color: "#000000"
                    font.pixelSize: 32
                    font.weight: Font.Normal
                    horizontalAlignment: Text.AlignLeft
                    text: "門D"
                    verticalAlignment: Text.AlignTop
                    wrapMode: Text.WordWrap
                }
                //doorF
                IndicatorUI {
                    id: doorFSign
                    x: 93
                    y: -9
                    statusColor:Kdb.doorDSignal
                }
                Image {
                    id: doorway_2
                    source: "assets/doorway_2.png"
                }
            }
            //光柵檢測
            Item {
                id: group_49
                height: 72
                width: 152

                Text {
                    id: element_1
                    x: 46
                    height: 72
                    width: 64
                    color: "#000000"
                    font.pixelSize: 32
                    font.weight: Font.Normal
                    horizontalAlignment: Text.AlignLeft
                    lineHeight: 36
                    lineHeightMode: Text.FixedHeight
                    text: "光柵檢測"
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                }

                IndicatorUI {
                    id: gratingDetection3
                    x: 108
                    y: 7
                    statusColor:Kdb.gratingDetection
                }
                Image {
                    id: feed_2
                    y: 16
                    source: "assets/feed_2.png"
                }
            }
        }
    }

    Image {
        id: settingButton
        x: 20
        y: 957
        height: 100
        width: 100
        source: "assets/rectangle_13.png"

        Image {
            id: gear_1_1

            x: 28
            y: 28

            source: "assets/gear_1_1.png"
        }

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: settingMouseArea.containsMouse ? true : false
            shadowColor: "#58000000"
            shadowBlur: 0.8
        }

        MouseArea {
            id: settingMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
        }
    }
    Item {
        id: group_43
        x: 1763
        y: 47
        height: 100
        width: 100
        Image {
            id: flipImg
            x: -4
            source: "assets/rectangle_2.png"

            layer.enabled: true
            layer.effect: MultiEffect {
                shadowEnabled: flipImgMouseArea.containsMouse ? true : false
                shadowColor: "#58000000"
                shadowBlur: 0.8
            }

            MouseArea {
                id: flipImgMouseArea
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
            }
        }
        Image {
            id: flip_1
            x: 28
            y: 28
            source: "assets/flip_1.png"
        }
    }



    Item {
        id: group_33
        x: 1034
        y: 190
        height: 111
        width: 333

        Image {
            id: rectangle_5
            x: -4
            source: "assets/rectangle_5.png"
        }
        Text {
            id: element_6
            x: 94
            y: 32
            height: 48
            width: 96
            color: "#000000"
            font.pixelSize: 32
            font.weight: Font.DemiBold
            horizontalAlignment: Text.AlignLeft
            lineHeight: 22
            lineHeightMode: Text.FixedHeight
            text: "白光燈"
            verticalAlignment: Text.AlignVCenter
        }
        Image {
            id: light_bulb_1
            x: 20
            y: 26
            source: "assets/light_bulb_1.png"
        }
        Item {
            id: group_34
            x: 214
            y: 32
            height: 48
            width: 97

            Image {
                id: whiteLightUI
                x: -4
                source: Kdb.whiteLight ?"assets/Group11.png" : "assets/Group 34.png"
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: whiteLightMouseArea.containsMouse ? true : false
                    shadowColor: "gray"
                    shadowBlur: 0.8
                }
            }

            MouseArea {
                id: whiteLightMouseArea
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
            }
        }
    }
    Item {
        id: group_50
        x: 1404
        y: 190
        height: 111
        width: 333

        Image {
            id: rectangle_6
            x: -4
            source: "assets/rectangle_6.png"
        }
        Text {
            id: element_7
            x: 94
            y: 32
            height: 48
            width: 100
            color: "#000000"
            font.pixelSize: 32
            font.weight: Font.DemiBold
            horizontalAlignment: Text.AlignLeft
            lineHeight: 32
            lineHeightMode: Text.FixedHeight
            text: "下方
照明燈"
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
        }
        Image {
            id: light_bulb_2
            x: 20
            y: 26
            source: "assets/light_bulb_2.png"
        }
        Item {
            id: group_4
            x: 214
            y: 32
            height: 48
            width: 97

            Image {
                id: lightBelowUI
                x: -4
                source: Kdb.bottomLight ?"assets/Group11.png" : "assets/Group 34.png"
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: lightBelowUIMouseArea.containsMouse ? true : false
                    shadowColor: "gray"
                    shadowBlur: 0.8
                }
            }

            MouseArea {
                id: lightBelowUIMouseArea
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
            }
        }
    }
    Item {
        id: group_5
        x: 664
        y: 190
        height: 111
        width: 333

        Image {
            id: rectangle_8
            x: -4
            source: "assets/rectangle_8.png"
        }
        Text {
            id: element_8
            x: 94
            y: 32
            height: 48
            width: 96

            color: "#000000"
            font.pixelSize: 32
            font.weight: Font.DemiBold
            horizontalAlignment: Text.AlignLeft
            lineHeight: 22
            lineHeightMode: Text.FixedHeight
            text: "紫光燈"
            verticalAlignment: Text.AlignVCenter
        }
        Image {
            id: light_bulb_3
            x: 20
            y: 26
            source: "assets/light_bulb_3.png"
        }
        Item {
            id: uvLamp
            x: 202
            y: 32
            height: 48
            width: 97

            Image {
                id: uvLampUI
                x: -4
                source: Kdb.uvLight ?"assets/Group11.png" : "assets/Group 34.png"
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: uvLampMouseArea.containsMouse ? true : false
                    shadowColor: "gray"
                    shadowBlur: 0.8
                }
            }

            MouseArea {
                id: uvLampMouseArea
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor

            }
        }
    }
    Item {
        id: bigRollTensionSetting
        x: 422
        y: 612
        height: 274
        width: 274
        visible: AppState.isBig ? true : false
        Image {
            id: bigmodelPic
            x: 0
            y: -345
            width: 1364
            height: 689
            source: isFlip ? "assets/bigPic_reverse.png" : "assets/bigPic_positive.png"
        }
        Image {
            id: rectangle_10
            x: -4
            source: "assets/rectangle_10.png"
        }
        Image {
            id: bigCoilTensionButton
            x: 99.64
            y: 203.01
            height: 54.80
            width: 62.27
            source: "assets/rectangle_4.png"
            layer.enabled: true
            layer.effect: MultiEffect {
                shadowEnabled: bigCoilTensionMouseArea.containsMouse ? true : false
                shadowColor: "#58000000"
                shadowBlur: 0.8
            }

            MouseArea {
                id: bigCoilTensionMouseArea
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked:{
                    if(Kdb.modifyLargeWinderTensionOver !== Number(bigCoilTension.text)) {
                        Kdb.modifyLargeWinderTensionOver = bigCoilTension.text
                        //console.log("11 modifyLargeWinderTensionOver changed~~~", Kdb.modifyLargeWinderTensionOver);
                    }
                }
            }
        }
        Text {
            id: element_9
            x: 19.93
            y: 23.66
            height: 42.35
            width: 159.42
            color: "#000000"
            font.pixelSize: 32
            font.weight: Font.DemiBold
            horizontalAlignment: Text.AlignLeft
            lineHeight: 22
            lineHeightMode: Text.FixedHeight
            text: "大捲張力"
            verticalAlignment: Text.AlignVCenter
        }
        Text {
            id: element_10
            x: 19.93
            y: 164.40
            height: 27.40
            width: 89.67
            color: "#565656"
            font.pixelSize: 24
            font.weight: Font.Normal
            horizontalAlignment: Text.AlignLeft
            lineHeight: 22
            lineHeightMode: Text.FixedHeight
            text: "設定值"
            verticalAlignment: Text.AlignVCenter
        }
        Text {
            id: element_11
            x: 90.92
            y: 92.16
            height: 44.84
            width: 92.16
            color: "#000000"
            font.pixelSize: 54
            font.weight: Font.Normal
            horizontalAlignment: Text.AlignLeft
            lineHeight: 36
            lineHeightMode: Text.FixedHeight
            text: Kdb.largeRollTension
            verticalAlignment: Text.AlignVCenter
        }

        TextField {
            id: bigCoilTension
            x: 20
            y: 203
            height: 55
            width: 74
            color: "#565656"
            font.pixelSize: 24
            font.weight: Font.Normal
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            font.styleName: "Bold"
            text: Kdb.modifyLargeWinderTensionOver
            validator: DoubleValidator {}//限制只能輸入整數/double
            inputMethodHints: Qt.ImhDigitsOnly
        }
        Image {
            id: servo_2
            x: 166.89
            y: 166.89
            source: "assets/servo_2.png"
        }

        Rectangle{
            id: bigRollCutterRec1
            width:267
            height:158
            anchors.top:bigRollTensionSetting.top
            anchors.topMargin:-220
            color: "#00ffffff"
            Image {
                id: bigRollCutterBg1
                source: "assets/Rectangle 1500.png"
            }
            Text{
                x:35
                y:33
                color: "#000000"
                font.pixelSize: 32
                font.weight: Font.DemiBold
                horizontalAlignment: Text.AlignLeft
                lineHeight: 22
                lineHeightMode: Text.FixedHeight
                text: "大捲切刀"
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
            }

            Image {
                id: bigRollCutterSwitch
                x: 33
                y:87
                source: Kdb.bigRollCutter ? "assets/Group11.png" : "assets/Group 34.png"

                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: bigRollCutterSwitchMouseArea.containsMouse ? true : false
                    shadowColor: "white"
                    shadowBlur: 0.8
                }

                MouseArea {
                    id: bigRollCutterSwitchMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                }
            }

        }

    }
    Item {
        id: group_45
        x: 20
        y: 725
        height: 178
        width: 332

        Image {
            id: rectangle_29
            x: -4
            source: "assets/rectangle_29.png"
        }
        Image {
            id: brakingDistanceButton
            x: 270
            y: 102
            height: 44
            width: 50
            source: "assets/rectangle_32.png"

            layer.enabled: true
            layer.effect: MultiEffect {
                shadowEnabled: brakingDistanceMouseArea.containsMouse ? true : false
                shadowColor: "#58000000"
                shadowBlur: 0.8
            }

            MouseArea {
                id: brakingDistanceMouseArea
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked:{
                    if(Kdb.modifyBrakingDistance !== Number(brakeDistance.text)) {
                        Kdb.modifyBrakingDistance = brakeDistance.text
                        //console.log("11 modifyBrakingDistance changed~~~", Kdb.modifyBrakingDistance);
                    }
                }
            }
        }
        Text {
            id: m_
            x: 26.92
            y: 32
            height: 22
            width: 275
            color: "#000000"
            font.pixelSize: 32
            font.weight: Font.DemiBold
            horizontalAlignment: Text.AlignLeft
            lineHeight: 22
            lineHeightMode: Text.FixedHeight
            text: "剎車距離(m)"
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
        }
        Text {
            id: element_16
            x: 126
            y: 113
            height: 27
            width: 72
            color: "#565656"
            font.pixelSize: 24
            font.weight: Font.Normal
            horizontalAlignment: Text.AlignLeft
            lineHeight: 22
            lineHeightMode: Text.FixedHeight
            text: "設定值"
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
        }
        Text {
            id: element_17
            x: 24
            y: 72
            height: 78
            width: 82.75
            color: "#000000"
            font.pixelSize: 72
            font.weight: Font.Normal
            horizontalAlignment: Text.AlignLeft
            text: Kdb.brakingDistance
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
        }

        TextField {
            id: brakeDistance
            x: 204
            y: 102
            height: 44
            width: 59
            color: "#565656"
            font.pixelSize: 20
            font.weight: Font.Normal
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            font.styleName: "Bold"
            //maximumLength: 6 //限制輸入2位整數
            text: Kdb.modifyBrakingDistance
            validator: DoubleValidator {}//限制只能輸入整數/double
            inputMethodHints: Qt.ImhDigitsOnly
        }
    }
    Item {
        id: group_48
        x: 20
        y: 38
        height: 385
        width: 389
        //目前長度
        Item {
            id: group_32
            height: 385
            width: 389

            Image {
                id: rectangle_31
                x: -4
                source: "assets/rectangle_31.png"
            }
            Text {
                id: m__1
                x: 27
                y: 19
                height: 49
                width: 179
                color: "#000000"
                font.pixelSize: 32
                font.weight: Font.DemiBold
                horizontalAlignment: Text.AlignLeft
                lineHeight: 22
                lineHeightMode: Text.FixedHeight
                text: "目前長度(m)"
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                id: element_19
                x: 27
                y: 95
                height: 78
                width: 165
                color: "#000000"
                font.pixelSize: 72
                font.weight: Font.Normal
                horizontalAlignment: Text.AlignLeft
                text: Kdb.currentLength
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
            }
            Image {
                id: goal_1
                x: 240
                y: 253
                source: "assets/goal_1.png"
            }
            Item {
                id: group_8
                x: 28
                y: 267
                height: 98
                width: 172

                Text {
                    id: element_20
                    height: 22
                    width: 72
                    color: "#565656"
                    font.pixelSize: 24
                    font.weight: Font.Normal
                    horizontalAlignment: Text.AlignLeft
                    lineHeight: 22
                    lineHeightMode: Text.FixedHeight
                    text: "設定值"
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                }
                TextField {
                    id: lengthSet
                    x: -7
                    y: 28
                    height: 78
                    width: 123
                    color: "#565656"
                    font.pixelSize: 54
                    font.weight: Font.Normal
                    horizontalAlignment: Text.AlignLeft
                    text: Kdb.modifyCurrentLength
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                    validator: IntValidator{}//限制只能輸入整數
                    inputMethodHints: Qt.ImhDigitsOnly
                }
                Image {
                    id: lenthSettingButton
                    x: 122
                    y: 54
                    height: 44
                    width: 50
                    source: "assets/rectangle_32.png"
                    layer.enabled: true
                    layer.effect: MultiEffect {
                        shadowEnabled: lenthSettingmouseArea.containsMouse ? true : false
                        shadowColor: "#58000000"
                        shadowBlur: 0.8
                    }

                    MouseArea {
                        id: lenthSettingmouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked:{
                            if(Kdb.modifyCurrentLength !== Number(lengthSet.text)) {
                                Kdb.modifyCurrentLength = lengthSet.text
                                //console.log("11 modifyCurrentLength changed~~~", Kdb.modifyCurrentLength);
                            }
                        }
                    }
                }
            }
        }
        Image {
            id: resetButton
            x: 227
            y: 26
            height: 138
            width: 138
            source: "assets/rectangle_33.png"

            Image {
                id: reset_1_1
                x: 23
                y: 23
                source: "assets/reset_1_1.png"
            }

            layer.enabled: true
            layer.effect: MultiEffect {
                shadowEnabled: resetMouseArea.containsMouse ? true : false
                shadowColor: "white"
                shadowBlur: 0.8
            }

            MouseArea {
                id: resetMouseArea
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
            }
        }
    }
    Item {
        id: group_47
        x: 20
        y: 448
        height: 259
        width: 333

        Item {
            id: group_31
            height: 259
            width: 333

            Image {
                id: rectangle_34
                x: -4
                source: "assets/rectangle_34.png"
            }
            Text {
                id: m_min_
                x: 26.92
                y: 19
                height: 49
                width: 178.46
                color: "#000000"
                font.pixelSize: 32
                font.weight: Font.DemiBold
                horizontalAlignment: Text.AlignLeft
                lineHeight: 22
                lineHeightMode: Text.FixedHeight
                text: "速度(m/min)"
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                id: element_22
                x: 27
                y: 158
                height: 33
                width: 72
                color: "#565656"
                font.pixelSize: 24
                font.weight: Font.Normal
                horizontalAlignment: Text.AlignLeft
                lineHeight: 22
                lineHeightMode: Text.FixedHeight
                text: "設定值"
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
            }
            Text {
                id: element_23
                x: 130.61
                y: 76
                height: 78
                width: 82.75
                color: "#000000"
                font.pixelSize: 72
                font.weight: Font.Normal
                horizontalAlignment: Text.AlignLeft
                text: Kdb.speed
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
            }
            TextField {
                id: speedSet
                x: 27
                y: 197
                height: 54
                width: 113
                color: "#565656"
                font.pixelSize: 36
                font.weight: Font.Normal
                horizontalAlignment: Text.AlignLeft
                text:Kdb.modifySpeed
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
                validator: IntValidator{}//限制只能輸入整數
                inputMethodHints: Qt.ImhDigitsOnly
            }
            Image {
                id: speedometer_1
                x: 213.18
                y: 139.09
                source: "assets/speedometer_1.png"
            }
        }
        Image {
            id: speedSettingButton
            x: 156
            y: 206
            source: "assets/rectangle_32.png"
            layer.enabled: true
            layer.effect: MultiEffect {
                shadowEnabled: speedSettingmouseArea.containsMouse ? true : false
                shadowColor: "#58000000"
                shadowBlur: 0.8
            }

            MouseArea {
                id: speedSettingmouseArea
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked:{
                    if(Kdb.modifySpeed !== Number(speedSet.text)) {
                        Kdb.modifySpeed = speedSet.text
                        //console.log("11 modifySpeed changed~~~", Kdb.modifySpeed);
                    }
                }
            }
        }
    }
    Item {
        id:smallRollTensionSetting
        x: 847
        y: 310
        visible:AppState.isBig ? false : true
        height: 274
        width: 274
        Image {
            id: smallmodelPic
            x: -450
            y: 0
            width: 1364
            height: 689
            source: isFlip ? "assets/smallPic_reverse.png" : "assets/smallPic_positive.png"
        }
        Item {
            id: smallR
            height: 274
            width: 274
            Image {
                id: rectangle_36
                x: -4
                source: "assets/rectangle_36.png"
            }
            Text {
                id: element_25
                x: 19.93
                y: 23.66
                height: 42.35
                width: 159.42
                color: "#000000"
                font.pixelSize: 32
                font.weight: Font.DemiBold
                horizontalAlignment: Text.AlignLeft
                lineHeight: 22
                lineHeightMode: Text.FixedHeight
                text: "小捲張力"
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                id: element_26
                x: 19.93
                y: 153.19
                height: 27.40
                width: 89.67
                color: "#565656"
                font.pixelSize: 24
                font.weight: Font.Normal
                horizontalAlignment: Text.AlignLeft
                lineHeight: 22
                lineHeightMode: Text.FixedHeight
                text: "設定值"
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                id: element_27
                x: 90.92
                y: 92.16
                height: 44.84
                width: 92.16
                color: "#000000"
                font.pixelSize: 54
                font.weight: Font.Normal
                horizontalAlignment: Text.AlignLeft
                lineHeight: 36
                lineHeightMode: Text.FixedHeight
                text: Kdb.smallRollTension
                verticalAlignment: Text.AlignVCenter
            }

            //小捲張力
            TextField {
                id: smallCoilTension
                x: 8
                y: 196
                height: 50
                width: 90
                color: "#565656"
                font.pixelSize: 24
                font.weight: Font.Normal
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
                font.styleName: "Bold"
                text: Kdb.modifySmallWinderTensionOver
                //maximumLength: 4 //限制輸入2位整數
                validator: DoubleValidator {}//限制只能輸入整數/double
                inputMethodHints: Qt.ImhDigitsOnly
            }
            Image {
                id: servo_3
                x: 166.89
                y: 166.89
                source: "assets/servo_3.png"
            }
        }
        Image {
            id: smallCoilTensionButton
            x: 97.15
            y: 195.54
            height: 54.80
            width: 62.27
            source: "assets/rectangle_4.png"
            layer.enabled: true
            layer.effect: MultiEffect {
                shadowEnabled: smallCoilTensionMouseArea.containsMouse ? true : false
                shadowColor: "#58000000"
                shadowBlur: 0.8
            }

            MouseArea {
                id: smallCoilTensionMouseArea
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked:{
                    if(Kdb.modifySmallWinderTensionOver !== Number(smallCoilTension.text)) {
                        Kdb.modifySmallWinderTensionOver = smallCoilTension.text
                        // console.log("11 modifySmallWinderTensionOver changed~~~", Kdb.modifySmallWinderTensionOver);
                    }
                }
            }
        }

        Rectangle{
            id: smallRollCutterRec1
            width:576
            height:158
            anchors.top:smallR.bottom
            anchors.topMargin:184
            color: "#00ffffff"
            Image {
                id: smallRollCutterBg1
                source: "assets/Rectangle 1511.png"
            }
            Text{
                x:35
                y:33
                color: "#000000"
                font.pixelSize: 32
                font.weight: Font.DemiBold
                horizontalAlignment: Text.AlignLeft
                lineHeight: 22
                lineHeightMode: Text.FixedHeight
                text: "小捲切刀"
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap

            }
            CheckBox {
                id: checkBox
                x: 21
                y: 83
                height: 35
                text: qsTr("1號")
                contentItem: Text {
                    text: parent.text
                    color: "black"
                    leftPadding: 30
                    font.styleName: "Bold"
                    font.pointSize: 16
                    verticalAlignment: Text.AlignVCenter
                }
                icon.width: 10
                icon.height: 10
                spacing: 15
                checkState: Kdb.smallRollCutter1//Qt.Checked
            }
            CheckBox {
                id: checkBox2
                anchors.left: checkBox.right
                anchors.leftMargin:10
                y: 83
                height: 35

                text: qsTr("2號")
                contentItem: Text {
                    text: parent.text
                    color: "black"
                    leftPadding: 30
                    font.styleName: "Bold"
                    font.pointSize: 16
                    verticalAlignment: Text.AlignVCenter
                }
                icon.width: 10
                icon.height: 10
                spacing: 15
                checkState: Kdb.smallRollCutter2
            }
            CheckBox {
                id: checkBox3
                anchors.left: checkBox2.right
                anchors.leftMargin:10
                y: 83
                height: 35
                text: qsTr("3號")
                contentItem: Text {
                    text: parent.text
                    color: "black"
                    leftPadding: 30
                    font.styleName: "Bold"
                    font.pointSize: 16
                    verticalAlignment: Text.AlignVCenter
                }
                icon.width: 10
                icon.height: 10
                spacing: 15
                checkState: Kdb.smallRollCutter3
            }
            CheckBox {
                id: checkBox4
                anchors.left: checkBox3.right
                anchors.leftMargin:10
                y: 83
                height: 35
                text: qsTr("4號")
                contentItem: Text {
                    text: parent.text
                    color: "black"
                    leftPadding: 30
                    font.styleName: "Bold"
                    font.pointSize: 16
                    verticalAlignment: Text.AlignVCenter
                }
                icon.width: 10
                icon.height: 10
                spacing: 15
                checkState: Kdb.smallRollCutter4
            }
            CheckBox {
                id: checkBox5
                anchors.left: checkBox4.right
                anchors.leftMargin:10
                y: 83
                height: 35
                text: qsTr("5號")
                contentItem: Text {
                    text: parent.text
                    color: "black"
                    leftPadding: 30
                    font.styleName: "Bold"
                    font.pointSize: 16
                    verticalAlignment: Text.AlignVCenter
                }
                icon.width: 10
                icon.height: 10
                spacing: 15

                checkState: Kdb.smallRollCutter5
            }
        }

    }
    Item {
        id: unWindingTensionPosition
        x: 1535
        y: 641
        height: 274
        width: 274

        Image {
            id: rectangle_15
            x: -4
            source: "assets/rectangle_15.png"
        }
        Text {
            id: element_2
            x: 19.93
            y: 23.66
            height: 42.35
            width: 159.42
            color: "#000000"
            font.pixelSize: 32
            font.weight: Font.DemiBold
            horizontalAlignment: Text.AlignLeft
            lineHeight: 22
            lineHeightMode: Text.FixedHeight
            text: "放捲張力"
            verticalAlignment: Text.AlignVCenter
        }
        Text {
            id: element_3
            x: 19.93
            y: 164.40
            height: 27.40
            width: 89.67
            color: "#565656"
            font.pixelSize: 24
            font.weight: Font.Normal
            horizontalAlignment: Text.AlignLeft
            lineHeight: 22
            lineHeightMode: Text.FixedHeight
            text: "設定值"
            verticalAlignment: Text.AlignVCenter
        }
        Text {
            id: element_4
            x: 90.92
            y: 92.16
            height: 44.84
            width: 92.16
            color: "#000000"
            font.pixelSize: 54
            font.weight: Font.Normal
            horizontalAlignment: Text.AlignLeft
            lineHeight: 36
            lineHeightMode: Text.FixedHeight
            text: Kdb.unwindingTension
            verticalAlignment: Text.AlignVCenter
        }

        //放捲張力set
        TextField {
            id: unwindingTension
            x: 20
            y: 202
            height: 55
            width: 74
            color: "#565656"
            font.pixelSize: 20
            font.weight: Font.Normal
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            font.styleName: "Bold"
            //maximumLength: 4 //限制輸入2位整數
            text: Kdb.modifyUnwindingTension
            validator: DoubleValidator {}//限制只能輸入整數/double
            inputMethodHints: Qt.ImhDigitsOnly
        }
        Image {
            id: servo_1
            x: 166.89
            y: 166.89
            source: "assets/servo_1.png"
        }
        Image {
            id: unwindingTensionButton
            x: 99.64
            y: 201.76
            height: 54.80
            width: 62.27
            source: "assets/rectangle_4.png"

            layer.enabled: true
            layer.effect: MultiEffect {
                shadowEnabled: unwindingTensionMouseArea.containsMouse ? true : false
                shadowColor: "#58000000"
                shadowBlur: 0.8
            }

            MouseArea {
                id: unwindingTensionMouseArea
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked:{
                    if(Kdb.modifyUnwindingTension !== Number(unwindingTension.text)) {
                        Kdb.modifyUnwindingTension = unwindingTension.text
                        //console.log("11 modifyUnwindingTension changed~~~", Kdb.modifyUnwindingTension);
                    }
                }
            }
        }
    }
}
