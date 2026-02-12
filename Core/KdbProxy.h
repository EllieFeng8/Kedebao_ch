#pragma once
#include <QObject>
#include <QQmlEngine>
//#include "opcuaKepwareRepository.h"
#include <QString>
#include <sstream>
#include <iomanip>
#include <string>

class KdbProxy : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    //默認大捲模式(1大捲模式,0小捲模式)
    Q_PROPERTY(int bigRollMode READ getBigRollMode WRITE setBigRollMode NOTIFY bigRollModeChanged)
    Q_PROPERTY(int restBtn READ getRestBtn WRITE setRestBtn NOTIFY restBtnChanged)

    Q_PROPERTY(int metalDetector READ getMetalDetector NOTIFY metalDetectorChanged)
    Q_PROPERTY(int gratingDetection READ getGratingDetection NOTIFY gratingDetectionChanged)
    Q_PROPERTY(int oppositeSide READ getOppositeSide NOTIFY oppositeSideChanged)

    Q_PROPERTY(int doorASignal READ getDoorASignal NOTIFY doorASignalChanged)
    Q_PROPERTY(int doorBSignal READ getDoorBSignal NOTIFY doorBSignalChanged)
    Q_PROPERTY(int doorCSignal READ getDoorCSignal NOTIFY doorCSignalChanged)
    Q_PROPERTY(int doorDSignal READ getDoorDSignal NOTIFY doorDSignalChanged)
    Q_PROPERTY(int doorESignal READ getDoorESignal NOTIFY doorESignalChanged)
    Q_PROPERTY(int doorFSignal READ getDoorFSignal NOTIFY doorFSignalChanged)
    Q_PROPERTY(int doorGSignal READ getDoorGSignal NOTIFY doorGSignalChanged)
    Q_PROPERTY(int doorHSignal READ getDoorHSignal NOTIFY doorHSignalChanged)
    Q_PROPERTY(int doorISignal READ getDoorISignal NOTIFY doorISignalChanged)

    Q_PROPERTY(int uvLight READ getUvLight WRITE setUvLight NOTIFY uvLightChanged)
    Q_PROPERTY(int whiteLight READ getWhiteLight WRITE setWhiteLight NOTIFY whiteLightChanged)
    Q_PROPERTY(int bottomLight READ getBottomLight WRITE setBottomLight NOTIFY bottomLightChanged)

    Q_PROPERTY(double currentLength READ getCurrentLength NOTIFY currentLengthChanged)
    Q_PROPERTY(double speed READ getSpeed NOTIFY speedChanged)
    Q_PROPERTY(double brakingDistance READ getBrakingDistance NOTIFY brakingDistanceChanged)

    Q_PROPERTY(int modifyCurrentLength READ getModifyCurrentLength WRITE setModifyCurrentLength NOTIFY modifyCurrentLengthChanged)
    Q_PROPERTY(int modifySpeed READ getModifySpeed WRITE setModifySpeed NOTIFY modifySpeedChanged)
    Q_PROPERTY(double modifyBrakingDistance READ getModifyBrakingDistance WRITE setModifyBrakingDistance NOTIFY modifyBrakingDistanceChanged)

    Q_PROPERTY(double modifyUnwindingTension READ getModifyUnwindingTension WRITE setModifyUnwindingTension NOTIFY modifyUnwindingTensionChanged)
    Q_PROPERTY(double modifySmallWinderTensionOver READ getModifySmallWinderTensionOver WRITE setModifySmallWinderTensionOver NOTIFY modifySmallWinderTensionOverChanged)
    Q_PROPERTY(double modifyLargeWinderTensionOver READ getModifyLargeWinderTensionOver WRITE setModifyLargeWinderTensionOver NOTIFY modifyLargeWinderTensionOverChanged)

    //壓板
    Q_PROPERTY(int pressurePlate READ getPressurePlate WRITE setPressurePlate NOTIFY pressurePlateChanged)
    //壓板
    Q_PROPERTY(int pressurePlateBack READ getPressurePlateBack WRITE setPressurePlateBack NOTIFY pressurePlateBackChanged)
    //壓輪
    Q_PROPERTY(int pressureRoller READ getPressureRoller WRITE setPressureRoller NOTIFY pressureRollerChanged)
    //壓輪
    Q_PROPERTY(int pressureRollerDown READ getPressureRollerDown WRITE setPressureRollerDown NOTIFY pressureRollerDownChanged)


    // ===== INPUT-1 Alarm Signals =====
    Q_PROPERTY(double unwinderVfdFreqAlarm READ getUnwinderVfdFreqAlarm NOTIFY unwinderVfdFreqAlarmChanged)
    Q_PROPERTY(double mainDriveVfdFreqAlarm READ getMainDriveVfdFreqAlarm NOTIFY mainDriveVfdFreqAlarmChanged)
    Q_PROPERTY(double smallWinderVfdFreqAlarm READ getSmallWinderVfdFreqAlarm NOTIFY smallWinderVfdFreqAlarmChanged)
    Q_PROPERTY(double largeWinderVfdFreqAlarm READ getLargeWinderVfdFreqAlarm NOTIFY largeWinderVfdFreqAlarmChanged)
    Q_PROPERTY(double smallCutterVfdFreqAlarm READ getSmallCutterVfdFreqAlarm NOTIFY smallCutterVfdFreqAlarmChanged)
    Q_PROPERTY(double selvedgeFanVfdFreqAlarm READ getSelvedgeFanVfdFreqAlarm NOTIFY selvedgeFanVfdFreqAlarmChanged)

    Q_PROPERTY(double leftFanOverloadAlarm READ getLeftFanOverloadAlarm NOTIFY leftFanOverloadAlarmChanged)
    Q_PROPERTY(double rightFanOverloadAlarm READ getRightFanOverloadAlarm NOTIFY rightFanOverloadAlarmChanged)

    Q_PROPERTY(double largeCutterVfdFreqAlarm READ getLargeCutterVfdFreqAlarm NOTIFY largeCutterVfdFreqAlarmChanged)
    Q_PROPERTY(double leftSelvedgeWinderVfdAlarm READ getLeftSelvedgeWinderVfdAlarm NOTIFY leftSelvedgeWinderVfdAlarmChanged)
    Q_PROPERTY(double rightSelvedgeWinderVfdAlarm READ getRightSelvedgeWinderVfdAlarm NOTIFY rightSelvedgeWinderVfdAlarmChanged)

    Q_PROPERTY(double webAlignerVfdFreqAlarm READ getWebAlignerVfdFreqAlarm NOTIFY webAlignerVfdFreqAlarmChanged)

    Q_PROPERTY(double unwinderPowerLoss READ getUnwinderPowerLoss NOTIFY unwinderPowerLossChanged)
    Q_PROPERTY(double mainDrivePowerLoss READ getMainDrivePowerLoss NOTIFY mainDrivePowerLossChanged)
    Q_PROPERTY(double smallWinderPowerLoss READ getSmallWinderPowerLoss NOTIFY smallWinderPowerLossChanged)
    Q_PROPERTY(double largeWinderPowerLoss READ getLargeWinderPowerLoss NOTIFY largeWinderPowerLossChanged)

    //信號燈
    Q_PROPERTY(int unwinderVfdFreqAlarmLight READ getUnwinderVfdFreqAlarmLight NOTIFY unwinderVfdFreqAlarmLightChanged)
    Q_PROPERTY(int mainDriveVfdFreqAlarmLight READ getMainDriveVfdFreqAlarmLight NOTIFY mainDriveVfdFreqAlarmLightChanged)
    Q_PROPERTY(int smallWinderVfdFreqAlarmLight READ getSmallWinderVfdFreqAlarmLight NOTIFY smallWinderVfdFreqAlarmLightChanged)
    Q_PROPERTY(int largeWinderVfdFreqAlarmLight READ getLargeWinderVfdFreqAlarmLight NOTIFY largeWinderVfdFreqAlarmLightChanged)
    Q_PROPERTY(int smallCutterVfdFreqAlarmLight READ getSmallCutterVfdFreqAlarmLight NOTIFY smallCutterVfdFreqAlarmLightChanged)
    Q_PROPERTY(int selvedgeFanVfdFreqAlarmLight READ getSelvedgeFanVfdFreqAlarmLight NOTIFY selvedgeFanVfdFreqAlarmLightChanged)

    Q_PROPERTY(int leftFanOverloadAlarmLight READ getLeftFanOverloadAlarmLight NOTIFY leftFanOverloadAlarmLightChanged)
    Q_PROPERTY(int rightFanOverloadAlarmLight READ getRightFanOverloadAlarmLight NOTIFY rightFanOverloadAlarmLightChanged)

    Q_PROPERTY(int largeCutterVfdFreqAlarmLight READ getLargeCutterVfdFreqAlarmLight NOTIFY largeCutterVfdFreqAlarmLightChanged)
    Q_PROPERTY(int leftSelvedgeWinderVfdAlarmLight READ getLeftSelvedgeWinderVfdAlarmLight NOTIFY leftSelvedgeWinderVfdAlarmLightChanged)
    Q_PROPERTY(int rightSelvedgeWinderVfdAlarmLight READ getRightSelvedgeWinderVfdAlarmLight NOTIFY rightSelvedgeWinderVfdAlarmLightChanged)

    Q_PROPERTY(int webAlignerVfdFreqAlarmLight READ getWebAlignerVfdFreqAlarmLight NOTIFY webAlignerVfdFreqAlarmLightChanged)

    Q_PROPERTY(int unwinderPowerLossLight READ getUnwinderPowerLossLight NOTIFY unwinderPowerLossLightChanged)
    Q_PROPERTY(int mainDrivePowerLossLight READ getMainDrivePowerLossLight NOTIFY mainDrivePowerLossLightChanged)
    Q_PROPERTY(int smallWinderPowerLossLight READ getSmallWinderPowerLossLight NOTIFY smallWinderPowerLossLightChanged)
    Q_PROPERTY(int largeWinderPowerLossLight READ getLargeWinderPowerLossLight NOTIFY largeWinderPowerLossLightChanged)



    // ===== INPUT-2 Power Loss =====
    Q_PROPERTY(double smallCutterPowerLoss READ getSmallCutterPowerLoss NOTIFY smallCutterPowerLossChanged)
    Q_PROPERTY(double selvedgeFanPowerLoss READ getSelvedgeFanPowerLoss NOTIFY selvedgeFanPowerLossChanged)
    Q_PROPERTY(double largeCutterPowerLoss READ getLargeCutterPowerLoss NOTIFY largeCutterPowerLossChanged)
    Q_PROPERTY(double leftSelvedgeWinderPowerLoss READ getLeftSelvedgeWinderPowerLoss NOTIFY leftSelvedgeWinderPowerLossChanged)
    Q_PROPERTY(double rightSelvedgeWinderPowerLoss READ getRightSelvedgeWinderPowerLoss NOTIFY rightSelvedgeWinderPowerLossChanged)
    Q_PROPERTY(double webAlignerPowerLoss READ getWebAlignerPowerLoss NOTIFY webAlignerPowerLossChanged)
    Q_PROPERTY(double unwinderDisconnect READ getUnwinderDisconnect NOTIFY unwinderDisconnectChanged)
    Q_PROPERTY(double mainDriveDisconnect READ getMainDriveDisconnect NOTIFY mainDriveDisconnectChanged)
    Q_PROPERTY(double smallWinderDisconnect READ getSmallWinderDisconnect NOTIFY smallWinderDisconnectChanged)
    Q_PROPERTY(double largeWinderDisconnect READ getLargeWinderDisconnect NOTIFY largeWinderDisconnectChanged)
    Q_PROPERTY(double smallCutterDisconnect READ getSmallCutterDisconnect NOTIFY smallCutterDisconnectChanged)
    Q_PROPERTY(double leftFanDisconnect READ getLeftFanDisconnect NOTIFY leftFanDisconnectChanged)
    Q_PROPERTY(double rightFanDisconnect READ getRightFanDisconnect NOTIFY rightFanDisconnectChanged)
    Q_PROPERTY(double largeCutterDisconnect READ getLargeCutterDisconnect NOTIFY largeCutterDisconnectChanged)
    Q_PROPERTY(double leftSelvedgeWinderDisconnect READ getLeftSelvedgeWinderDisconnect NOTIFY leftSelvedgeWinderDisconnectChanged)
    Q_PROPERTY(double rightSelvedgeWinderDisconnect READ getRightSelvedgeWinderDisconnect NOTIFY rightSelvedgeWinderDisconnectChanged)

    //信號燈
    Q_PROPERTY(int smallCutterPowerLossLight READ getSmallCutterPowerLossLight NOTIFY smallCutterPowerLossLightChanged)
    Q_PROPERTY(int selvedgeFanPowerLossLight READ getSelvedgeFanPowerLossLight NOTIFY selvedgeFanPowerLossLightChanged)
    Q_PROPERTY(int largeCutterPowerLossLight READ getLargeCutterPowerLossLight NOTIFY largeCutterPowerLossLightChanged)
    Q_PROPERTY(int leftSelvedgeWinderPowerLossLight READ getLeftSelvedgeWinderPowerLossLight NOTIFY leftSelvedgeWinderPowerLossLightChanged)
    Q_PROPERTY(int rightSelvedgeWinderPowerLossLight READ getRightSelvedgeWinderPowerLossLight NOTIFY rightSelvedgeWinderPowerLossLightChanged)
    Q_PROPERTY(int webAlignerPowerLossLight READ getWebAlignerPowerLossLight NOTIFY webAlignerPowerLossLightChanged)
    Q_PROPERTY(int unwinderDisconnectLight READ getUnwinderDisconnectLight NOTIFY unwinderDisconnectLightChanged)
    Q_PROPERTY(int mainDriveDisconnectLight READ getMainDriveDisconnectLight NOTIFY mainDriveDisconnectLightChanged)
    Q_PROPERTY(int smallWinderDisconnectLight READ getSmallWinderDisconnectLight NOTIFY smallWinderDisconnectLightChanged)
    Q_PROPERTY(int largeWinderDisconnectLight READ getLargeWinderDisconnectLight NOTIFY largeWinderDisconnectLightChanged)
    Q_PROPERTY(int smallCutterDisconnectLight READ getSmallCutterDisconnectLight NOTIFY smallCutterDisconnectLightChanged)
    Q_PROPERTY(int leftFanDisconnectLight READ getLeftFanDisconnectLight NOTIFY leftFanDisconnectLightChanged)
    Q_PROPERTY(int rightFanDisconnectLight READ getRightFanDisconnectLight NOTIFY rightFanDisconnectLightChanged)
    Q_PROPERTY(int largeCutterDisconnectLight READ getLargeCutterDisconnectLight NOTIFY largeCutterDisconnectLightChanged)
    Q_PROPERTY(int leftSelvedgeWinderDisconnectLight READ getLeftSelvedgeWinderDisconnectLight NOTIFY leftSelvedgeWinderDisconnectLightChanged)
    Q_PROPERTY(int rightSelvedgeWinderDisconnectLight READ getRightSelvedgeWinderDisconnectLight NOTIFY rightSelvedgeWinderDisconnectLightChanged)


    // ===== INPUT-3 =====
    Q_PROPERTY(double webAlignerDisconnect READ getWebAlignerDisconnect NOTIFY webAlignerDisconnectChanged)
    Q_PROPERTY(double emergencyStop1 READ getEmergencyStop1 NOTIFY emergencyStop1Changed)
    Q_PROPERTY(double emergencyStop2 READ getEmergencyStop2 NOTIFY emergencyStop2Changed)
    Q_PROPERTY(double emergencyStop3 READ getEmergencyStop3 NOTIFY emergencyStop3Changed)
    Q_PROPERTY(double emergencyStop4 READ getEmergencyStop4 NOTIFY emergencyStop4Changed)
    Q_PROPERTY(double emergencyStop5 READ getEmergencyStop5 NOTIFY emergencyStop5Changed)
    Q_PROPERTY(double emergencyStop6 READ getEmergencyStop6 NOTIFY emergencyStop6Changed)
    Q_PROPERTY(double emergencyStop7 READ getEmergencyStop7 NOTIFY emergencyStop7Changed)

    Q_PROPERTY(double mainDriveLeftDoor1Open READ getMainDriveLeftDoor1Open NOTIFY mainDriveLeftDoor1OpenChanged)
    Q_PROPERTY(double mainDriveLeftDoor2Open READ getMainDriveLeftDoor2Open NOTIFY mainDriveLeftDoor2OpenChanged)
    Q_PROPERTY(double mainDriveRightDoor3Open READ getMainDriveRightDoor3Open NOTIFY mainDriveRightDoor3OpenChanged)
    Q_PROPERTY(double mainDriveRightDoor4Open READ getMainDriveRightDoor4Open NOTIFY mainDriveRightDoor4OpenChanged)
    Q_PROPERTY(double largeWinderLeftDoor5Open READ getLargeWinderLeftDoor5Open NOTIFY largeWinderLeftDoor5OpenChanged)
    Q_PROPERTY(double largeWinderLeftDoor6Open READ getLargeWinderLeftDoor6Open NOTIFY largeWinderLeftDoor6OpenChanged)
    Q_PROPERTY(double largeWinderRightDoor7Open READ getLargeWinderRightDoor7Open NOTIFY largeWinderRightDoor7OpenChanged)
    Q_PROPERTY(double largeWinderRightDoor8Open READ getLargeWinderRightDoor8Open NOTIFY largeWinderRightDoor8OpenChanged)

    //信號燈
    Q_PROPERTY(int webAlignerDisconnectLight READ getWebAlignerDisconnectLight NOTIFY webAlignerDisconnectLightChanged)
    Q_PROPERTY(int emergencyStop1Light READ getEmergencyStop1Light NOTIFY emergencyStop1LightChanged)
    Q_PROPERTY(int emergencyStop2Light READ getEmergencyStop2Light NOTIFY emergencyStop2LightChanged)
    Q_PROPERTY(int emergencyStop3Light READ getEmergencyStop3Light NOTIFY emergencyStop3LightChanged)
    Q_PROPERTY(int emergencyStop4Light READ getEmergencyStop4Light NOTIFY emergencyStop4LightChanged)
    Q_PROPERTY(int emergencyStop5Light READ getEmergencyStop5Light NOTIFY emergencyStop5LightChanged)
    Q_PROPERTY(int emergencyStop6Light READ getEmergencyStop6Light NOTIFY emergencyStop6LightChanged)
    Q_PROPERTY(int emergencyStop7Light READ getEmergencyStop7Light NOTIFY emergencyStop7LightChanged)

    Q_PROPERTY(int mainDriveLeftDoor1OpenLight READ getMainDriveLeftDoor1OpenLight NOTIFY mainDriveLeftDoor1OpenLightChanged)
    Q_PROPERTY(int mainDriveLeftDoor2OpenLight READ getMainDriveLeftDoor2OpenLight NOTIFY mainDriveLeftDoor2OpenLightChanged)
    Q_PROPERTY(int mainDriveRightDoor3OpenLight READ getMainDriveRightDoor3OpenLight NOTIFY mainDriveRightDoor3OpenLightChanged)
    Q_PROPERTY(int mainDriveRightDoor4OpenLight READ getMainDriveRightDoor4OpenLight NOTIFY mainDriveRightDoor4OpenLightChanged)
    Q_PROPERTY(int largeWinderLeftDoor5OpenLight READ getLargeWinderLeftDoor5OpenLight NOTIFY largeWinderLeftDoor5OpenLightChanged)
    Q_PROPERTY(int largeWinderLeftDoor6OpenLight READ getLargeWinderLeftDoor6OpenLight NOTIFY largeWinderLeftDoor6OpenLightChanged)
    Q_PROPERTY(int largeWinderRightDoor7OpenLight READ getLargeWinderRightDoor7OpenLight NOTIFY largeWinderRightDoor7OpenLightChanged)
    Q_PROPERTY(int largeWinderRightDoor8OpenLight READ getLargeWinderRightDoor8OpenLight NOTIFY largeWinderRightDoor8OpenLightChanged)

    // ===== INPUT-4 Fence Detect =====
    Q_PROPERTY(double unwindingFenceDetect1 READ getUnwindingFenceDetect1 NOTIFY unwindingFenceDetect1Changed)
    Q_PROPERTY(double unwindingFenceDetect2 READ getUnwindingFenceDetect2 NOTIFY unwindingFenceDetect2Changed)
    Q_PROPERTY(double largeWinderFenceDetect3 READ getLargeWinderFenceDetect3 NOTIFY largeWinderFenceDetect3Changed)
    Q_PROPERTY(double largeWinderFenceDetect4 READ getLargeWinderFenceDetect4 NOTIFY largeWinderFenceDetect4Changed)

    //信號燈
    Q_PROPERTY(int unwindingFenceDetect1Light READ getUnwindingFenceDetect1Light NOTIFY unwindingFenceDetect1LightChanged)
    Q_PROPERTY(int unwindingFenceDetect2Light READ getUnwindingFenceDetect2Light NOTIFY unwindingFenceDetect2LightChanged)
    Q_PROPERTY(int largeWinderFenceDetect3Light READ getLargeWinderFenceDetect3Light NOTIFY largeWinderFenceDetect3LightChanged)
    Q_PROPERTY(int largeWinderFenceDetect4Light READ getLargeWinderFenceDetect4Light NOTIFY largeWinderFenceDetect4LightChanged)


    // ===== INPUT-4 Safety Light Curtain =====
    Q_PROPERTY(double unwindingSafetyLightCurtainAlarm READ getUnwindingSafetyLightCurtainAlarm NOTIFY unwindingSafetyLightCurtainAlarmChanged)
    Q_PROPERTY(double inspectionSafetyLightCurtainAlarm READ getInspectionSafetyLightCurtainAlarm NOTIFY inspectionSafetyLightCurtainAlarmChanged)
    Q_PROPERTY(double largeWinderSafetyLightCurtainAlarm READ getLargeWinderSafetyLightCurtainAlarm NOTIFY largeWinderSafetyLightCurtainAlarmChanged)

    //信號燈
    Q_PROPERTY(int unwindingSafetyLightCurtainAlarmLight READ getUnwindingSafetyLightCurtainAlarmLight NOTIFY unwindingSafetyLightCurtainAlarmLightChanged)
    Q_PROPERTY(int inspectionSafetyLightCurtainAlarmLight READ getInspectionSafetyLightCurtainAlarmLight NOTIFY inspectionSafetyLightCurtainAlarmLightChanged)
    Q_PROPERTY(int largeWinderSafetyLightCurtainAlarmLight READ getLargeWinderSafetyLightCurtainAlarmLight NOTIFY largeWinderSafetyLightCurtainAlarmLightChanged)

    // ===== INPUT-4 Zero Speed Detect =====
    Q_PROPERTY(double smallWinderZeroSpeedDetect READ getSmallWinderZeroSpeedDetect NOTIFY smallWinderZeroSpeedDetectChanged)
    Q_PROPERTY(double largeWinderZeroSpeedDetect READ getLargeWinderZeroSpeedDetect NOTIFY largeWinderZeroSpeedDetectChanged)

    // ===== INPUT-4 信號燈 =====
    Q_PROPERTY(int smallWinderZeroSpeedDetectLight READ getSmallWinderZeroSpeedDetectLight NOTIFY smallWinderZeroSpeedDetectLightChanged)
    Q_PROPERTY(int largeWinderZeroSpeedDetectLight READ getLargeWinderZeroSpeedDetectLight NOTIFY largeWinderZeroSpeedDetectLightChanged)

    // ===== INPUT-4 Tension Over =====
    Q_PROPERTY(double unwindingTensionOver READ getUnwindingTensionOver NOTIFY unwindingTensionOverChanged)
    Q_PROPERTY(double smallWinderTensionOver READ getSmallWinderTensionOver NOTIFY smallWinderTensionOverChanged)
    Q_PROPERTY(double largeWinderTensionOver READ getLargeWinderTensionOver NOTIFY largeWinderTensionOverChanged)

    //信號燈
    Q_PROPERTY(int unwindingTensionOverLight READ getUnwindingTensionOverLight NOTIFY unwindingTensionOverLightChanged)
    Q_PROPERTY(int smallWinderTensionOverLight READ getSmallWinderTensionOverLight NOTIFY smallWinderTensionOverLightChanged)
    Q_PROPERTY(int largeWinderTensionOverLight READ getLargeWinderTensionOverLight NOTIFY largeWinderTensionOverLightChanged)

    // ===== INPUT-4 Angle Alarm =====
    Q_PROPERTY(double leftSelvedgeWinderAngleAlarm READ getLeftSelvedgeWinderAngleAlarm NOTIFY leftSelvedgeWinderAngleAlarmChanged)
    Q_PROPERTY(double rightSelvedgeWinderAngleAlarm READ getRightSelvedgeWinderAngleAlarm NOTIFY rightSelvedgeWinderAngleAlarmChanged)

    //信號燈
    Q_PROPERTY(int leftSelvedgeWinderAngleAlarmLight READ getLeftSelvedgeWinderAngleAlarmLight NOTIFY leftSelvedgeWinderAngleAlarmLightChanged)
    Q_PROPERTY(int rightSelvedgeWinderAngleAlarmLight READ getRightSelvedgeWinderAngleAlarmLight NOTIFY rightSelvedgeWinderAngleAlarmLightChanged)


    // ===== OUTPUT Control =====
    Q_PROPERTY(double vfdAlarmReset READ getVfdAlarmReset WRITE setVfdAlarmReset NOTIFY vfdAlarmResetChanged)
    Q_PROPERTY(double unwinderForward READ getUnwinderForward WRITE setUnwinderForward NOTIFY unwinderForwardChanged)
    Q_PROPERTY(double unwinderReverse READ getUnwinderReverse WRITE setUnwinderReverse NOTIFY unwinderReverseChanged)

    Q_PROPERTY(double mainDriveForward READ getMainDriveForward WRITE setMainDriveForward NOTIFY mainDriveForwardChanged)
    Q_PROPERTY(double mainDriveReverse READ getMainDriveReverse WRITE setMainDriveReverse NOTIFY mainDriveReverseChanged)

    Q_PROPERTY(double smallWinderForward READ getSmallWinderForward WRITE setSmallWinderForward NOTIFY smallWinderForwardChanged)
    Q_PROPERTY(double smallWinderReverse READ getSmallWinderReverse WRITE setSmallWinderReverse NOTIFY smallWinderReverseChanged)

    Q_PROPERTY(double largeWinderForward READ getLargeWinderForward WRITE setLargeWinderForward NOTIFY largeWinderForwardChanged)
    Q_PROPERTY(double largeWinderReverse READ getLargeWinderReverse WRITE setLargeWinderReverse NOTIFY largeWinderReverseChanged)

    Q_PROPERTY(double smallCutterStart READ getSmallCutterStart WRITE setSmallCutterStart NOTIFY smallCutterStartChanged)
    Q_PROPERTY(double selvedgeFanStart READ getSelvedgeFanStart WRITE setSelvedgeFanStart NOTIFY selvedgeFanStartChanged)
    Q_PROPERTY(double largeCutterStart READ getLargeCutterStart WRITE setLargeCutterStart NOTIFY largeCutterStartChanged)

    Q_PROPERTY(double leftSelvedgeWinderForward READ getLeftSelvedgeWinderForward WRITE setLeftSelvedgeWinderForward NOTIFY leftSelvedgeWinderForwardChanged)
    Q_PROPERTY(double leftSelvedgeWinderReverse READ getLeftSelvedgeWinderReverse WRITE setLeftSelvedgeWinderReverse NOTIFY leftSelvedgeWinderReverseChanged)

    Q_PROPERTY(double rightSelvedgeWinderForward READ getRightSelvedgeWinderForward WRITE setRightSelvedgeWinderForward NOTIFY rightSelvedgeWinderForwardChanged)
    Q_PROPERTY(double rightSelvedgeWinderReverse READ getRightSelvedgeWinderReverse WRITE setRightSelvedgeWinderReverse NOTIFY rightSelvedgeWinderReverseChanged)

    //OUTPUT1 switch
    Q_PROPERTY(int vfdAlarmResetSwitch READ getVfdAlarmResetSwitch WRITE setVfdAlarmResetSwitch NOTIFY vfdAlarmResetSwitchChanged)
    Q_PROPERTY(int unwinderForwardSwitch READ getUnwinderForwardSwitch WRITE setUnwinderForwardSwitch NOTIFY unwinderForwardSwitchChanged)
    Q_PROPERTY(int unwinderReverseSwitch READ getUnwinderReverseSwitch WRITE setUnwinderReverseSwitch NOTIFY unwinderReverseSwitchChanged)

    Q_PROPERTY(int mainDriveForwardSwitch READ getMainDriveForwardSwitch WRITE setMainDriveForwardSwitch NOTIFY mainDriveForwardSwitchChanged)
    Q_PROPERTY(int mainDriveReverseSwitch READ getMainDriveReverseSwitch WRITE setMainDriveReverseSwitch NOTIFY mainDriveReverseSwitchChanged)

    Q_PROPERTY(int smallWinderForwardSwitch READ getSmallWinderForwardSwitch WRITE setSmallWinderForwardSwitch NOTIFY smallWinderForwardSwitchChanged)
    Q_PROPERTY(int smallWinderReverseSwitch READ getSmallWinderReverseSwitch WRITE setSmallWinderReverseSwitch NOTIFY smallWinderReverseSwitchChanged)

    Q_PROPERTY(int largeWinderForwardSwitch READ getLargeWinderForwardSwitch WRITE setLargeWinderForwardSwitch NOTIFY largeWinderForwardSwitchChanged)
    Q_PROPERTY(int largeWinderReverseSwitch READ getLargeWinderReverseSwitch WRITE setLargeWinderReverseSwitch NOTIFY largeWinderReverseSwitchChanged)

    Q_PROPERTY(int smallCutterStartSwitch READ getSmallCutterStartSwitch WRITE setSmallCutterStartSwitch NOTIFY smallCutterStartSwitchChanged)
    Q_PROPERTY(int selvedgeFanStartSwitch READ getSelvedgeFanStartSwitch WRITE setSelvedgeFanStartSwitch NOTIFY selvedgeFanStartSwitchChanged)
    Q_PROPERTY(int largeCutterStartSwitch READ getLargeCutterStartSwitch WRITE setLargeCutterStartSwitch NOTIFY largeCutterStartSwitchChanged)

    Q_PROPERTY(int leftSelvedgeWinderForwardSwitch READ getLeftSelvedgeWinderForwardSwitch WRITE setLeftSelvedgeWinderForwardSwitch NOTIFY leftSelvedgeWinderForwardSwitchChanged)
    Q_PROPERTY(int leftSelvedgeWinderReverseSwitch READ getLeftSelvedgeWinderReverseSwitch WRITE setLeftSelvedgeWinderReverseSwitch NOTIFY leftSelvedgeWinderReverseSwitchChanged)

    Q_PROPERTY(int rightSelvedgeWinderForwardSwitch READ getRightSelvedgeWinderForwardSwitch WRITE setRightSelvedgeWinderForwardSwitch NOTIFY rightSelvedgeWinderForwardSwitchChanged)
    Q_PROPERTY(int rightSelvedgeWinderReverseSwitch READ getRightSelvedgeWinderReverseSwitch WRITE setRightSelvedgeWinderReverseSwitch NOTIFY rightSelvedgeWinderReverseSwitchChanged)

    // ===== OUTPUT-2 Control =====
    Q_PROPERTY(double webAlignerStart READ getWebAlignerStart WRITE setWebAlignerStart NOTIFY webAlignerStartChanged)
    Q_PROPERTY(double unwindingTensionAuto READ getUnwindingTensionAuto WRITE setUnwindingTensionAuto NOTIFY unwindingTensionAutoChanged)
    Q_PROPERTY(double unwindingDiameterReset READ getUnwindingDiameterReset WRITE setUnwindingDiameterReset NOTIFY unwindingDiameterResetChanged)

    Q_PROPERTY(double smallWinderTensionAuto READ getSmallWinderTensionAuto WRITE setSmallWinderTensionAuto NOTIFY smallWinderTensionAutoChanged)
    Q_PROPERTY(double smallWinderDiameterReset READ getSmallWinderDiameterReset WRITE setSmallWinderDiameterReset NOTIFY smallWinderDiameterResetChanged)

    Q_PROPERTY(double largeWinderTensionAuto READ getLargeWinderTensionAuto WRITE setLargeWinderTensionAuto NOTIFY largeWinderTensionAutoChanged)
    Q_PROPERTY(double largeWinderDiameterReset READ getLargeWinderDiameterReset WRITE setLargeWinderDiameterReset NOTIFY largeWinderDiameterResetChanged)

    Q_PROPERTY(double leftSelvedgeWinderAuto READ getLeftSelvedgeWinderAuto WRITE setLeftSelvedgeWinderAuto NOTIFY leftSelvedgeWinderAutoChanged)
    Q_PROPERTY(double rightSelvedgeWinderAuto READ getRightSelvedgeWinderAuto WRITE setRightSelvedgeWinderAuto NOTIFY rightSelvedgeWinderAutoChanged)

    Q_PROPERTY(double nipRollUp READ getNipRollUp WRITE setNipRollUp NOTIFY nipRollUpChanged)
    Q_PROPERTY(double nipRollDown READ getNipRollDown WRITE setNipRollDown NOTIFY nipRollDownChanged)

    Q_PROPERTY(double leftPressPlateForward READ getLeftPressPlateForward WRITE setLeftPressPlateForward NOTIFY leftPressPlateForwardChanged)
    Q_PROPERTY(double leftPressPlateBackward READ getLeftPressPlateBackward WRITE setLeftPressPlateBackward NOTIFY leftPressPlateBackwardChanged)

    Q_PROPERTY(double rightPressPlateForward READ getRightPressPlateForward WRITE setRightPressPlateForward NOTIFY rightPressPlateForwardChanged)
    Q_PROPERTY(double rightPressPlateBackward READ getRightPressPlateBackward WRITE setRightPressPlateBackward NOTIFY rightPressPlateBackwardChanged)

    Q_PROPERTY(double smallCutterIn READ getSmallCutterIn WRITE setSmallCutterIn NOTIFY smallCutterInChanged)

    // ===== OUTPUT-2 Switch =====
    Q_PROPERTY(int webAlignerStartSwitch READ getWebAlignerStartSwitch WRITE setWebAlignerStartSwitch NOTIFY webAlignerStartSwitchChanged)
    Q_PROPERTY(int unwindingTensionAutoSwitch READ getUnwindingTensionAutoSwitch WRITE setUnwindingTensionAutoSwitch NOTIFY unwindingTensionAutoSwitchChanged)
    Q_PROPERTY(int unwindingDiameterResetSwitch READ getUnwindingDiameterResetSwitch WRITE setUnwindingDiameterResetSwitch NOTIFY unwindingDiameterResetSwitchChanged)

    Q_PROPERTY(int smallWinderTensionAutoSwitch READ getSmallWinderTensionAutoSwitch WRITE setSmallWinderTensionAutoSwitch NOTIFY smallWinderTensionAutoSwitchChanged)
    Q_PROPERTY(int smallWinderDiameterResetSwitch READ getSmallWinderDiameterResetSwitch WRITE setSmallWinderDiameterResetSwitch NOTIFY smallWinderDiameterResetSwitchChanged)

    Q_PROPERTY(int largeWinderTensionAutoSwitch READ getLargeWinderTensionAutoSwitch WRITE setLargeWinderTensionAutoSwitch NOTIFY largeWinderTensionAutoSwitchChanged)
    Q_PROPERTY(int largeWinderDiameterResetSwitch READ getLargeWinderDiameterResetSwitch WRITE setLargeWinderDiameterResetSwitch NOTIFY largeWinderDiameterResetSwitchChanged)

    Q_PROPERTY(int leftSelvedgeWinderAutoSwitch READ getLeftSelvedgeWinderAutoSwitch WRITE setLeftSelvedgeWinderAutoSwitch NOTIFY leftSelvedgeWinderAutoSwitchChanged)
    Q_PROPERTY(int rightSelvedgeWinderAutoSwitch READ getRightSelvedgeWinderAutoSwitch WRITE setRightSelvedgeWinderAutoSwitch NOTIFY rightSelvedgeWinderAutoSwitchChanged)

    Q_PROPERTY(int nipRollUpSwitch READ getNipRollUpSwitch WRITE setNipRollUpSwitch NOTIFY nipRollUpSwitchChanged)
    Q_PROPERTY(int nipRollDownSwitch READ getNipRollDownSwitch WRITE setNipRollDownSwitch NOTIFY nipRollDownSwitchChanged)

    Q_PROPERTY(int leftPressPlateForwardSwitch READ getLeftPressPlateForwardSwitch WRITE setLeftPressPlateForwardSwitch NOTIFY leftPressPlateForwardSwitchChanged)
    Q_PROPERTY(int leftPressPlateBackwardSwitch READ getLeftPressPlateBackwardSwitch WRITE setLeftPressPlateBackwardSwitch NOTIFY leftPressPlateBackwardSwitchChanged)

    Q_PROPERTY(int rightPressPlateForwardSwitch READ getRightPressPlateForwardSwitch WRITE setRightPressPlateForwardSwitch NOTIFY rightPressPlateForwardSwitchChanged)
    Q_PROPERTY(int rightPressPlateBackwardSwitch READ getRightPressPlateBackwardSwitch WRITE setRightPressPlateBackwardSwitch NOTIFY rightPressPlateBackwardSwitchChanged)

    Q_PROPERTY(int smallCutterInSwitch READ getSmallCutterInSwitch WRITE setSmallCutterInSwitch NOTIFY smallCutterInSwitchChanged)

    // ===== OUTPUT-3 Control =====
    Q_PROPERTY(double largeCutterIn READ getLargeCutterIn WRITE setLargeCutterIn NOTIFY largeCutterInChanged)
    Q_PROPERTY(double modeSelect READ getModeSelect WRITE setModeSelect NOTIFY modeSelectChanged)

    Q_PROPERTY(double runIndicator READ getRunIndicator WRITE setRunIndicator NOTIFY runIndicatorChanged)
    Q_PROPERTY(double alarmIndicator READ getAlarmIndicator WRITE setAlarmIndicator NOTIFY alarmIndicatorChanged)
    Q_PROPERTY(double stopIndicator READ getStopIndicator WRITE setStopIndicator NOTIFY stopIndicatorChanged)

    Q_PROPERTY(double buzzer READ getBuzzer WRITE setBuzzer NOTIFY buzzerChanged)
    Q_PROPERTY(double smallRollModeSelect READ getSmallRollModeSelect WRITE setSmallRollModeSelect NOTIFY smallRollModeSelectChanged)

    //8
    Q_PROPERTY(double output8 READ getOutput8 WRITE setOutput8 NOTIFY output8Changed)
    //9
    Q_PROPERTY(double output9 READ getOutput9 WRITE setOutput9 NOTIFY output9Changed)
    //10
    Q_PROPERTY(double output10 READ getOutput10 WRITE setOutput10 NOTIFY output10Changed)
    //11
    Q_PROPERTY(double output11 READ getOutput11 WRITE setOutput11 NOTIFY output11Changed)
    //12
    Q_PROPERTY(double output12 READ getOutput12 WRITE setOutput12 NOTIFY output12Changed)
    //13
    Q_PROPERTY(double output13 READ getOutput13 WRITE setOutput13 NOTIFY output13Changed)
    //14
    Q_PROPERTY(double output14 READ getOutput14 WRITE setOutput14 NOTIFY output14Changed)
    //15
    Q_PROPERTY(double output15 READ getOutput15 WRITE setOutput15 NOTIFY output15Changed)
    //16
    Q_PROPERTY(double output16 READ getOutput16 WRITE setOutput16 NOTIFY output16Changed)
    //17
    Q_PROPERTY(double output17 READ getOutput17 WRITE setOutput17 NOTIFY output17Changed)

    // ===== OUTPUT-3 Switch =====
    Q_PROPERTY(int largeCutterInSwitch READ getLargeCutterInSwitch WRITE setLargeCutterInSwitch NOTIFY largeCutterInSwitchChanged)
    Q_PROPERTY(int modeSelectSwitch READ getModeSelectSwitch WRITE setModeSelectSwitch NOTIFY modeSelectSwitchChanged)

    Q_PROPERTY(int runIndicatorSwitch READ getRunIndicatorSwitch WRITE setRunIndicatorSwitch NOTIFY runIndicatorSwitchChanged)
    Q_PROPERTY(int alarmIndicatorSwitch READ getAlarmIndicatorSwitch WRITE setAlarmIndicatorSwitch NOTIFY alarmIndicatorSwitchChanged)
    Q_PROPERTY(int stopIndicatorSwitch READ getStopIndicatorSwitch WRITE setStopIndicatorSwitch NOTIFY stopIndicatorSwitchChanged)

    Q_PROPERTY(int buzzerSwitch READ getBuzzerSwitch WRITE setBuzzerSwitch NOTIFY buzzerSwitchChanged)
    Q_PROPERTY(int smallRollModeSelectSwitch READ getSmallRollModeSelectSwitch WRITE setSmallRollModeSelectSwitch NOTIFY smallRollModeSelectSwitchChanged)

    //8
    Q_PROPERTY(int output8Switch READ getOutput8Switch WRITE setOutput8Switch NOTIFY output8SwitchChanged)
    //9
    Q_PROPERTY(int output9Switch READ getOutput9Switch WRITE setOutput9Switch NOTIFY output9SwitchChanged)
    //10
    Q_PROPERTY(int output10Switch READ getOutput10Switch WRITE setOutput10Switch NOTIFY output10SwitchChanged)
    //11
    Q_PROPERTY(int output11Switch READ getOutput11Switch WRITE setOutput11Switch NOTIFY output11SwitchChanged)
    //12
    Q_PROPERTY(int output12Switch READ getOutput12Switch WRITE setOutput12Switch NOTIFY output12SwitchChanged)
    //13
    Q_PROPERTY(int output13Switch READ getOutput13Switch WRITE setOutput13Switch NOTIFY output13SwitchChanged)
    //14
    Q_PROPERTY(int output14Switch READ getOutput14Switch WRITE setOutput14Switch NOTIFY output14SwitchChanged)
    //15
    Q_PROPERTY(int output15Switch READ getOutput15Switch WRITE setOutput15Switch NOTIFY output15SwitchChanged)
    //16
    Q_PROPERTY(int output16Switch READ getOutput16Switch WRITE setOutput16Switch NOTIFY output16SwitchChanged)
    //17
    Q_PROPERTY(int output17Switch READ getOutput17Switch WRITE setOutput17Switch NOTIFY output17SwitchChanged)

    // ===== ANALOG OUTPUT =====
    Q_PROPERTY(double analogOutUnwinderMainDrive READ getAnalogOutUnwinderMainDrive WRITE setAnalogOutUnwinderMainDrive NOTIFY analogOutUnwinderMainDriveChanged)
    Q_PROPERTY(double analogOutWinder READ getAnalogOutWinder WRITE setAnalogOutWinder NOTIFY analogOutWinderChanged)
    Q_PROPERTY(double analogOutCutter READ getAnalogOutCutter WRITE setAnalogOutCutter NOTIFY analogOutCutterChanged)
    Q_PROPERTY(double analogOutSelvedgeWinder READ getAnalogOutSelvedgeWinder WRITE setAnalogOutSelvedgeWinder NOTIFY analogOutSelvedgeWinderChanged)

    //%
    Q_PROPERTY(double analogOutUnwinderMainDrivePc READ getAnalogOutUnwinderMainDrivePc WRITE setAnalogOutUnwinderMainDrivePc NOTIFY analogOutUnwinderMainDrivePcChanged)
    Q_PROPERTY(double analogOutWinderPc READ getAnalogOutWinderPc WRITE setAnalogOutWinderPc NOTIFY analogOutWinderPcChanged)
    Q_PROPERTY(double analogOutCutterPc READ getAnalogOutCutterPc WRITE setAnalogOutCutterPc NOTIFY analogOutCutterPcChanged)
    Q_PROPERTY(double analogOutSelvedgeWinderPc READ getAnalogOutSelvedgeWinderPc WRITE setAnalogOutSelvedgeWinderPc NOTIFY analogOutSelvedgeWinderPcChanged)


    Q_PROPERTY(double modifyAnalogOutUnwinderMainDrive READ getModifyAnalogOutUnwinderMainDrive WRITE setModifyAnalogOutUnwinderMainDrive NOTIFY modifyAnalogOutUnwinderMainDriveChanged)
    Q_PROPERTY(double modifyAnalogOutWinder READ getModifyAnalogOutWinder WRITE setModifyAnalogOutWinder NOTIFY modifyAnalogOutWinderChanged)
    Q_PROPERTY(double modifyAnalogOutCutter READ getModifyAnalogOutCutter WRITE setModifyAnalogOutCutter NOTIFY modifyAnalogOutCutterChanged)
    Q_PROPERTY(double modifyAnalogOutSelvedgeWinder READ getModifyAnalogOutSelvedgeWinder WRITE setModifyAnalogOutSelvedgeWinder NOTIFY modifyAnalogOutSelvedgeWinderChanged)

    // ===== ANALOG OUTPUT Switch=====
    Q_PROPERTY(int analogOutUnwinderMainDriveSwitch READ getAnalogOutUnwinderMainDriveSwitch WRITE setAnalogOutUnwinderMainDriveSwitch NOTIFY analogOutUnwinderMainDriveSwitchChanged)
    Q_PROPERTY(int analogOutWinderSwitch READ getAnalogOutWinderSwitch WRITE setAnalogOutWinderSwitch NOTIFY analogOutWinderSwitchChanged)
    Q_PROPERTY(int analogOutCutterSwitch READ getAnalogOutCutterSwitch WRITE setAnalogOutCutterSwitch NOTIFY analogOutCutterSwitchChanged)
    Q_PROPERTY(int analogOutSelvedgeWinderSwitch READ getAnalogOutSelvedgeWinderSwitch WRITE setAnalogOutSelvedgeWinderSwitch NOTIFY analogOutSelvedgeWinderSwitchChanged)

    Q_PROPERTY(int modifyAnalogOutUnwinderMainDriveSwitch READ getModifyAnalogOutUnwinderMainDriveSwitch WRITE setModifyAnalogOutUnwinderMainDriveSwitch NOTIFY modifyAnalogOutUnwinderMainDriveSwitchChanged)
    Q_PROPERTY(int modifyAnalogOutWinderSwitch READ getModifyAnalogOutWinderSwitch WRITE setModifyAnalogOutWinderSwitch NOTIFY modifyAnalogOutWinderSwitchChanged)
    Q_PROPERTY(int modifyAnalogOutCutterSwitch READ getModifyAnalogOutCutterSwitch WRITE setModifyAnalogOutCutterSwitch NOTIFY modifyAnalogOutCutterSwitchChanged)
    Q_PROPERTY(int modifyAnalogOutSelvedgeWinderSwitch READ getModifyAnalogOutSelvedgeWinderSwitch WRITE setModifyAnalogOutSelvedgeWinderSwitch NOTIFY modifyAnalogOutSelvedgeWinderSwitchChanged)


    // ===== IPC INPUT =====
    Q_PROPERTY(double ipcStart READ getIpcStart NOTIFY ipcStartChanged)
    Q_PROPERTY(double ipcStop READ getIpcStop NOTIFY ipcStopChanged)
    Q_PROPERTY(double ipcAlarmReset READ getIpcAlarmReset NOTIFY ipcAlarmResetChanged)

    Q_PROPERTY(double mainJogForward READ getMainJogForward NOTIFY mainJogForwardChanged)
    Q_PROPERTY(double mainJogReverse READ getMainJogReverse NOTIFY mainJogReverseChanged)

    Q_PROPERTY(double smallWinderJogForward READ getSmallWinderJogForward NOTIFY smallWinderJogForwardChanged)
    Q_PROPERTY(double smallWinderJogReverse READ getSmallWinderJogReverse NOTIFY smallWinderJogReverseChanged)

    Q_PROPERTY(double unwinderJogReverseSelect READ getUnwinderJogReverseSelect NOTIFY unwinderJogReverseSelectChanged)
    Q_PROPERTY(double unwinderJogStart READ getUnwinderJogStart NOTIFY unwinderJogStartChanged)

    Q_PROPERTY(double winderJogReverseSelect READ getWinderJogReverseSelect NOTIFY winderJogReverseSelectChanged)
    Q_PROPERTY(double winderJogStart READ getWinderJogStart NOTIFY winderJogStartChanged)

    Q_PROPERTY(double leftSelvedgeWinderSelect READ getLeftSelvedgeWinderSelect NOTIFY leftSelvedgeWinderSelectChanged)
    Q_PROPERTY(double rightSelvedgeWinderSelect READ getRightSelvedgeWinderSelect NOTIFY rightSelvedgeWinderSelectChanged)

    // ===== IPC INPUT Light=====
    Q_PROPERTY(int ipcStartLight READ getIpcStartLight NOTIFY ipcStartLightChanged)
    Q_PROPERTY(int ipcStopLight READ getIpcStopLight NOTIFY ipcStopLightChanged)
    Q_PROPERTY(int ipcAlarmResetLight READ getIpcAlarmResetLight NOTIFY ipcAlarmResetLightChanged)

    Q_PROPERTY(int mainJogForwardLight READ getMainJogForwardLight NOTIFY mainJogForwardLightChanged)
    Q_PROPERTY(int mainJogReverseLight READ getMainJogReverseLight NOTIFY mainJogReverseLightChanged)

    Q_PROPERTY(int smallWinderJogForwardLight READ getSmallWinderJogForwardLight NOTIFY smallWinderJogForwardLightChanged)
    Q_PROPERTY(int smallWinderJogReverseLight READ getSmallWinderJogReverseLight NOTIFY smallWinderJogReverseLightChanged)

    Q_PROPERTY(int unwinderJogReverseSelectLight READ getUnwinderJogReverseSelectLight NOTIFY unwinderJogReverseSelectLightChanged)
    Q_PROPERTY(int unwinderJogStartLight READ getUnwinderJogStartLight NOTIFY unwinderJogStartLightChanged)

    Q_PROPERTY(int winderJogReverseSelectLight READ getWinderJogReverseSelectLight NOTIFY winderJogReverseSelectLightChanged)
    Q_PROPERTY(int winderJogStartLight READ getWinderJogStartLight NOTIFY winderJogStartLightChanged)

    Q_PROPERTY(int leftSelvedgeWinderSelectLight READ getLeftSelvedgeWinderSelectLight NOTIFY leftSelvedgeWinderSelectLightChanged)
    Q_PROPERTY(int rightSelvedgeWinderSelectLight READ getRightSelvedgeWinderSelectLight NOTIFY rightSelvedgeWinderSelectLightChanged)



    // ===== 控制介面 =====
    Q_PROPERTY(double smallRollMotor READ getSmallRollMotor WRITE setSmallRollMotor NOTIFY smallRollMotorChanged)
    Q_PROPERTY(double mainDriveMotor READ getMainDriveMotor WRITE setMainDriveMotor NOTIFY mainDriveMotorChanged)
    Q_PROPERTY(double largeRollMotor READ getLargeRollMotor WRITE setLargeRollMotor NOTIFY largeRollMotorChanged)
    Q_PROPERTY(double wasteRollMotorB READ getWasteRollMotorB WRITE setWasteRollMotorB NOTIFY wasteRollMotorBChanged)
    Q_PROPERTY(double unwindingMotor READ getUnwindingMotor WRITE setUnwindingMotor NOTIFY unwindingMotorChanged)
    Q_PROPERTY(double edgeAlignMotor READ getEdgeAlignMotor WRITE setEdgeAlignMotor NOTIFY edgeAlignMotorChanged)
    Q_PROPERTY(double cutterWheelMotor READ getCutterWheelMotor WRITE setCutterWheelMotor NOTIFY cutterWheelMotorChanged)
    Q_PROPERTY(double wasteRollMotorA READ getWasteRollMotorA WRITE setWasteRollMotorA NOTIFY wasteRollMotorAChanged)

    Q_PROPERTY(double unwindingTension READ getUnwindingTension WRITE setUnwindingTension NOTIFY unwindingTensionChanged)
    Q_PROPERTY(double smallRollTension READ getSmallRollTension WRITE setSmallRollTension NOTIFY smallRollTensionChanged)
    Q_PROPERTY(double largeRollTension READ getLargeRollTension WRITE setLargeRollTension NOTIFY largeRollTensionChanged)

    // ===== 控制介面 switch=====
    Q_PROPERTY(int smallRollMotorSwitch READ getSmallRollMotorSwitch WRITE setSmallRollMotorSwitch NOTIFY smallRollMotorSwitchChanged)
    Q_PROPERTY(int mainDriveMotorSwitch READ getMainDriveMotorSwitch WRITE setMainDriveMotorSwitch NOTIFY mainDriveMotorSwitchChanged)
    Q_PROPERTY(int largeRollMotorSwitch READ getLargeRollMotorSwitch WRITE setLargeRollMotorSwitch NOTIFY largeRollMotorSwitchChanged)
    Q_PROPERTY(int wasteRollMotorBSwitch READ getWasteRollMotorBSwitch WRITE setWasteRollMotorBSwitch NOTIFY wasteRollMotorBSwitchChanged)
    Q_PROPERTY(int unwindingMotorSwitch READ getUnwindingMotorSwitch WRITE setUnwindingMotorSwitch NOTIFY unwindingMotorSwitchChanged)
    Q_PROPERTY(int edgeAlignMotorSwitch READ getEdgeAlignMotorSwitch WRITE setEdgeAlignMotorSwitch NOTIFY edgeAlignMotorSwitchChanged)
    Q_PROPERTY(int cutterWheelMotorSwitch READ getCutterWheelMotorSwitch WRITE setCutterWheelMotorSwitch NOTIFY cutterWheelMotorSwitchChanged)
    Q_PROPERTY(int wasteRollMotorASwitch READ getWasteRollMotorASwitch WRITE setWasteRollMotorASwitch NOTIFY wasteRollMotorASwitchChanged)

    Q_PROPERTY(int unwindingTensionSwitch READ getUnwindingTensionSwitch WRITE setUnwindingTensionSwitch NOTIFY unwindingTensionSwitchChanged)
    Q_PROPERTY(int smallRollTensionSwitch READ getSmallRollTensionSwitch WRITE setSmallRollTensionSwitch NOTIFY smallRollTensionSwitchChanged)
    Q_PROPERTY(int largeRollTensionSwitch READ getLargeRollTensionSwitch WRITE setLargeRollTensionSwitch NOTIFY largeRollTensionSwitchChanged)

    // ===== cutter=====
    Q_PROPERTY(int smallRollCutter1 READ getSmallRollCutter1 WRITE setSmallRollCutter1 NOTIFY smallRollCutter1Changed)
    Q_PROPERTY(int smallRollCutter2 READ getSmallRollCutter2 WRITE setSmallRollCutter2 NOTIFY smallRollCutter2Changed)
    Q_PROPERTY(int smallRollCutter3 READ getSmallRollCutter3 WRITE setSmallRollCutter3 NOTIFY smallRollCutter3Changed)
    Q_PROPERTY(int smallRollCutter4 READ getSmallRollCutter4 WRITE setSmallRollCutter4 NOTIFY smallRollCutter4Changed)
    Q_PROPERTY(int smallRollCutter5 READ getSmallRollCutter5 WRITE setSmallRollCutter5 NOTIFY smallRollCutter5Changed)
    Q_PROPERTY(int bigRollCutter READ getBigRollCutter WRITE setBigRollCutter NOTIFY bigRollCutterChanged)

    // ===== Single Action Mode=====
    Q_PROPERTY(int singleActionMode READ getSingleActionMode WRITE setSingleActionMode NOTIFY singleActionModeChanged)


public:
    explicit KdbProxy(QObject* parent = nullptr) : QObject(parent) {}
    //默認大捲模式(m_bigRollMode = 1大捲模式,0小捲模式)
    Q_INVOKABLE int getBigRollMode() const { return m_bigRollMode; }
    void setBigRollMode(int value) { m_bigRollMode = value; emit bigRollModeChanged(m_bigRollMode);}

    Q_INVOKABLE int getRestBtn() const { return m_restBtn; }
    void setRestBtn(int value) { m_restBtn = value; emit restBtnChanged(m_restBtn);}


     Q_INVOKABLE int getMetalDetector() const { return m_metalDetector; }
     Q_INVOKABLE int getGratingDetection() const { return m_gratingDetection; }
     Q_INVOKABLE int getOppositeSide() const { return m_OppositeSideSignal; }

     Q_INVOKABLE int getDoorASignal() const { return m_doorASignal; }
     Q_INVOKABLE int getDoorBSignal() const { return m_doorBSignal; }
     Q_INVOKABLE int getDoorCSignal() const { return m_doorCSignal; }
     Q_INVOKABLE int getDoorDSignal() const { return m_doorDSignal; }
     Q_INVOKABLE int getDoorESignal() const { return m_doorESignal; }
     Q_INVOKABLE int getDoorFSignal() const { return m_doorFSignal; }
     Q_INVOKABLE int getDoorGSignal() const { return m_doorGSignal; }
     Q_INVOKABLE int getDoorHSignal() const { return m_doorHSignal; }
     Q_INVOKABLE int getDoorISignal() const { return m_doorISignal; }

     Q_INVOKABLE int getUvLight() const { return m_uvLight; }
    void setUvLight(int value)
    {
        if (m_uvLight != value)
            m_uvLight = value;
        emit uvLightChanged(m_uvLight);
    }
    Q_INVOKABLE int getWhiteLight() const { return m_whiteLight; }
    void setWhiteLight(int value)
    {
        if (m_whiteLight != value)
            m_whiteLight = value;
        emit whiteLightChanged(m_whiteLight);
    }
    Q_INVOKABLE int getBottomLight() const { return m_bottomLight; }
    void setBottomLight(int value)
    {
        if (m_bottomLight != value)
            m_bottomLight = value;
        emit bottomLightChanged(m_bottomLight);
    }
     Q_INVOKABLE double getCurrentLength() const { return m_currentLength; }
     Q_INVOKABLE double getSpeed() const { return m_speed; }
     Q_INVOKABLE double getBrakingDistance() const { return m_brakingDistance;}

     Q_INVOKABLE int getModifyCurrentLength() const { return m_modifycurrentLength; }
     Q_INVOKABLE int getModifySpeed() const { return m_modifyspeed; }
     Q_INVOKABLE double getModifyBrakingDistance() const { return m_modifybrakingDistance;}
     void setModifyCurrentLength(int value){m_modifycurrentLength = value; emit modifyCurrentLengthChanged(m_brakingDistance);};
     void setModifySpeed(int value){m_modifyspeed = value; emit modifySpeedChanged(m_modifyspeed);};
     void setModifyBrakingDistance(double value){m_modifybrakingDistance = value; emit modifyBrakingDistanceChanged(m_modifybrakingDistance);};

    Q_INVOKABLE double getModifyUnwindingTension() const { return m_modifyUnwindingTension; }
    Q_INVOKABLE double getModifySmallWinderTensionOver() const { return m_modifySmallWinderTensionOver; }
    Q_INVOKABLE double getModifyLargeWinderTensionOver() const { return m_modifyLargeWinderTensionOver;}
    void setModifyUnwindingTension(double value){m_modifyUnwindingTension = value; emit modifyUnwindingTensionChanged(m_modifyUnwindingTension);};
    void setModifySmallWinderTensionOver(double value){m_modifySmallWinderTensionOver = value; emit modifySmallWinderTensionOverChanged(m_modifySmallWinderTensionOver);};
    void setModifyLargeWinderTensionOver(double value){m_modifyLargeWinderTensionOver = value; emit modifyLargeWinderTensionOverChanged(m_modifyLargeWinderTensionOver);};

    Q_INVOKABLE int getPressurePlate() const { return m_pressurePlate; }
    Q_INVOKABLE int getPressureRoller() const { return m_pressureRoller; }
    void setPressurePlate(int value){m_pressurePlate = value; emit pressurePlateChanged(m_pressurePlate);};
    void setPressureRoller(int value){m_pressureRoller = value; emit pressureRollerChanged(m_pressureRoller);};

    Q_INVOKABLE int getPressurePlateBack() const { return m_pressurePlateBack; }
    Q_INVOKABLE int getPressureRollerDown() const { return m_pressureRollerDown; }
    void setPressurePlateBack(int value){m_pressurePlateBack = value; emit pressurePlateBackChanged(m_pressurePlateBack);};
    void setPressureRollerDown(int value){m_pressureRollerDown = value; emit pressureRollerDownChanged(m_pressureRollerDown);};

     //=====INPUT-1 READ functions =====
     //=====INPUT-1 READ functions =====
    Q_INVOKABLE double getUnwinderVfdFreqAlarm() const { return m_unwinderVfdFreqAlarm; }
    void setUnwinderVfdFreqAlarm(double value)
    {
        if (m_unwinderVfdFreqAlarm == value)
            return;
        m_unwinderVfdFreqAlarm = value;
        emit unwinderVfdFreqAlarmChanged(m_unwinderVfdFreqAlarm);
    }
    Q_INVOKABLE double getMainDriveVfdFreqAlarm() const { return m_mainDriveVfdFreqAlarm; }
    void setMainDriveVfdFreqAlarm(double value)
    {
        if (m_mainDriveVfdFreqAlarm == value)
            return;
        m_mainDriveVfdFreqAlarm = value;
        emit mainDriveVfdFreqAlarmChanged(m_mainDriveVfdFreqAlarm);
    }
    Q_INVOKABLE double getSmallWinderVfdFreqAlarm() const { return m_smallWinderVfdFreqAlarm; }
    void setSmallWinderVfdFreqAlarm(double value)
    {
        if (m_smallWinderVfdFreqAlarm == value)
            return;
        m_smallWinderVfdFreqAlarm = value;
        emit smallWinderVfdFreqAlarmChanged(m_smallWinderVfdFreqAlarm);
    }
    Q_INVOKABLE double getLargeWinderVfdFreqAlarm() const { return m_largeWinderVfdFreqAlarm; }
    void setLargeWinderVfdFreqAlarm(double value)
    {
        if (m_largeWinderVfdFreqAlarm == value)
            return;
        m_largeWinderVfdFreqAlarm = value;
        emit largeWinderVfdFreqAlarmChanged(m_largeWinderVfdFreqAlarm);
    }
    Q_INVOKABLE double getSmallCutterVfdFreqAlarm() const { return m_smallCutterVfdFreqAlarm; }
    void setSmallCutterVfdFreqAlarm(double value)
    {
        if (m_smallCutterVfdFreqAlarm == value)
            return;
        m_smallCutterVfdFreqAlarm = value;
        emit smallCutterVfdFreqAlarmChanged(m_smallCutterVfdFreqAlarm);
    }
    Q_INVOKABLE double getSelvedgeFanVfdFreqAlarm() const { return m_selvedgeFanVfdFreqAlarm; }
    void setSelvedgeFanVfdFreqAlarm(double value)
    {
        if (m_selvedgeFanVfdFreqAlarm == value)
            return;
        m_selvedgeFanVfdFreqAlarm = value;
        emit selvedgeFanVfdFreqAlarmChanged(m_selvedgeFanVfdFreqAlarm);
    }
    Q_INVOKABLE double getLeftFanOverloadAlarm() const { return m_leftFanOverloadAlarm; }
    void setLeftFanOverloadAlarm(double value)
    {
        if (m_leftFanOverloadAlarm == value)
            return;
        m_leftFanOverloadAlarm = value;
        emit leftFanOverloadAlarmChanged(m_leftFanOverloadAlarm);
    }

    Q_INVOKABLE double getRightFanOverloadAlarm() const { return m_rightFanOverloadAlarm; }
    void setRightFanOverloadAlarm(double value)
    {
        if (m_rightFanOverloadAlarm == value)
            return;
        m_rightFanOverloadAlarm = value;
        emit rightFanOverloadAlarmChanged(m_rightFanOverloadAlarm);
    }
    Q_INVOKABLE double getLargeCutterVfdFreqAlarm() const { return m_largeCutterVfdFreqAlarm; }
    void setLargeCutterVfdFreqAlarm(double value)
    {
        if (m_largeCutterVfdFreqAlarm == value)
            return;
        m_largeCutterVfdFreqAlarm = value;
        emit largeCutterVfdFreqAlarmChanged(m_largeCutterVfdFreqAlarm);
    }
    Q_INVOKABLE double getLeftSelvedgeWinderVfdAlarm() const { return m_leftSelvedgeWinderVfdAlarm; }
    void setLeftSelvedgeWinderVfdAlarm(double value)
    {
        if (m_leftSelvedgeWinderVfdAlarm == value)
            return;
        m_leftSelvedgeWinderVfdAlarm = value;
        emit leftSelvedgeWinderVfdAlarmChanged(m_leftSelvedgeWinderVfdAlarm);
    }
    Q_INVOKABLE double getRightSelvedgeWinderVfdAlarm() const { return m_rightSelvedgeWinderVfdAlarm; }
    void setRightSelvedgeWinderVfdAlarm(double value)
    {
        if (m_rightSelvedgeWinderVfdAlarm == value)
            return;
        m_rightSelvedgeWinderVfdAlarm = value;
        emit rightSelvedgeWinderVfdAlarmChanged(m_rightSelvedgeWinderVfdAlarm);
    }

    Q_INVOKABLE double getWebAlignerVfdFreqAlarm() const { return m_webAlignerVfdFreqAlarm; }
    void setWebAlignerVfdFreqAlarm(double value)
    {
        if (m_webAlignerVfdFreqAlarm == value)
            return;
        m_webAlignerVfdFreqAlarm = value;
        emit webAlignerVfdFreqAlarmChanged(m_webAlignerVfdFreqAlarm);
    }

    Q_INVOKABLE double getUnwinderPowerLoss() const { return m_unwinderPowerLoss; }
    void setUnwinderPowerLoss(double value)
    {
        if (m_unwinderPowerLoss == value)
            return;
        m_unwinderPowerLoss = value;
        emit unwinderPowerLossChanged(m_unwinderPowerLoss);
    }
    Q_INVOKABLE double getMainDrivePowerLoss() const { return m_mainDrivePowerLoss; }
    void setMainDrivePowerLoss(double value)
    {
        if (m_mainDrivePowerLoss == value)
            return;
        m_mainDrivePowerLoss = value;
        emit mainDrivePowerLossChanged(m_mainDrivePowerLoss);
    }

    Q_INVOKABLE double getSmallWinderPowerLoss() const { return m_smallWinderPowerLoss; }
    void setSmallWinderPowerLoss(double value)
    {
        if (m_smallWinderPowerLoss == value)
            return;
        m_smallWinderPowerLoss = value;
        emit smallWinderPowerLossChanged(m_smallWinderPowerLoss);
    }

    Q_INVOKABLE double getLargeWinderPowerLoss() const { return m_largeWinderPowerLoss; }
    void setLargeWinderPowerLoss(double value)
    {
        if (m_largeWinderPowerLoss == value)
            return;
        m_largeWinderPowerLoss = value;
        emit largeWinderPowerLossChanged(m_largeWinderPowerLoss);
    }

    Q_INVOKABLE int getUnwinderVfdFreqAlarmLight() const { return m_unwinderVfdFreqAlarmLight; }
    void setUnwinderVfdFreqAlarmLight(int value)
    {
        if (m_unwinderVfdFreqAlarmLight != value)
            m_unwinderVfdFreqAlarmLight = value;
        emit unwinderVfdFreqAlarmLightChanged(m_unwinderVfdFreqAlarmLight);
    }
    Q_INVOKABLE int getMainDriveVfdFreqAlarmLight() const { return m_mainDriveVfdFreqAlarmLight; }
    void setMainDriveVfdFreqAlarmLight(int value)
    {
        if (m_mainDriveVfdFreqAlarmLight != value)
            m_mainDriveVfdFreqAlarmLight = value;
        emit mainDriveVfdFreqAlarmLightChanged(m_mainDriveVfdFreqAlarmLight);
    }
    Q_INVOKABLE int getSmallWinderVfdFreqAlarmLight() const { return m_smallWinderVfdFreqAlarmLight; }
    void setSmallWinderVfdFreqAlarmLight(int value)
    {
        if (m_smallWinderVfdFreqAlarmLight != value)
            m_smallWinderVfdFreqAlarmLight = value;
        emit smallWinderVfdFreqAlarmLightChanged(m_smallWinderVfdFreqAlarmLight);
    }
    Q_INVOKABLE int getLargeWinderVfdFreqAlarmLight() const { return m_largeWinderVfdFreqAlarmLight; }
    void setLargeWinderVfdFreqAlarmLight(int value)
    {
        if (m_largeWinderVfdFreqAlarmLight != value)
            m_largeWinderVfdFreqAlarmLight = value;
        emit largeWinderVfdFreqAlarmLightChanged(m_largeWinderVfdFreqAlarmLight);
    }
    Q_INVOKABLE int getSmallCutterVfdFreqAlarmLight() const { return m_smallCutterVfdFreqAlarmLight; }
    void setSmallCutterVfdFreqAlarmLight(int value)
    {
        if (m_smallCutterVfdFreqAlarmLight != value)
            m_smallCutterVfdFreqAlarmLight = value;
        emit smallCutterVfdFreqAlarmLightChanged(m_smallCutterVfdFreqAlarmLight);
    }
    Q_INVOKABLE int getSelvedgeFanVfdFreqAlarmLight() const { return m_selvedgeFanVfdFreqAlarmLight; }
    void setSelvedgeFanVfdFreqAlarmLight(int value)
    {
        if (m_selvedgeFanVfdFreqAlarmLight != value)
            m_selvedgeFanVfdFreqAlarmLight = value;
        emit smallCutterVfdFreqAlarmLightChanged(m_selvedgeFanVfdFreqAlarmLight);
    }
    Q_INVOKABLE int getLeftFanOverloadAlarmLight() const { return m_leftFanOverloadAlarmLight; }
    void setLeftFanOverloadAlarmLight(int value)
    {
        if (m_leftFanOverloadAlarmLight != value)
            m_leftFanOverloadAlarmLight = value;
        emit leftFanOverloadAlarmLightChanged(m_leftFanOverloadAlarmLight);
    }
    Q_INVOKABLE int getRightFanOverloadAlarmLight() const { return m_rightFanOverloadAlarmLight; }
    void setRightFanOverloadAlarmLight(int value)
    {
        if (m_rightFanOverloadAlarmLight != value)
            m_rightFanOverloadAlarmLight = value;
        emit rightFanOverloadAlarmLightChanged(m_rightFanOverloadAlarmLight);
    }
    Q_INVOKABLE int getLargeCutterVfdFreqAlarmLight() const { return m_largeCutterVfdFreqAlarmLight; }
    void setLargeCutterVfdFreqAlarmLight(int value)
    {
        if (m_largeCutterVfdFreqAlarmLight != value)
            m_largeCutterVfdFreqAlarmLight = value;
        emit largeCutterVfdFreqAlarmLightChanged(m_largeCutterVfdFreqAlarmLight);
    }
    Q_INVOKABLE int getLeftSelvedgeWinderVfdAlarmLight() const { return m_leftSelvedgeWinderVfdAlarmLight; }
    void setLeftSelvedgeWinderVfdAlarmLight(int value)
    {
        if (m_leftSelvedgeWinderVfdAlarmLight != value)
            m_leftSelvedgeWinderVfdAlarmLight = value;
        emit leftSelvedgeWinderVfdAlarmLightChanged(m_leftSelvedgeWinderVfdAlarmLight);
    }
    Q_INVOKABLE int getRightSelvedgeWinderVfdAlarmLight() const { return m_rightSelvedgeWinderVfdAlarmLight; }
    void setRightSelvedgeWinderVfdAlarmLight(int value)
    {
        if (m_rightSelvedgeWinderVfdAlarmLight != value)
            m_rightSelvedgeWinderVfdAlarmLight = value;
        emit rightSelvedgeWinderVfdAlarmLightChanged(m_rightSelvedgeWinderVfdAlarmLight);
    }
    Q_INVOKABLE int getWebAlignerVfdFreqAlarmLight() const { return m_webAlignerVfdFreqAlarmLight; }
    void setWebAlignerVfdFreqAlarmLight(int value)
    {
        if (m_webAlignerVfdFreqAlarmLight != value)
            m_webAlignerVfdFreqAlarmLight = value;
        emit webAlignerVfdFreqAlarmLightChanged(m_webAlignerVfdFreqAlarmLight);
    }
    Q_INVOKABLE int getUnwinderPowerLossLight() const { return m_unwinderPowerLossLight; }
    void setUnwinderPowerLossLight(int value)
    {
        if (m_unwinderPowerLossLight != value)
            m_unwinderPowerLossLight = value;
        emit unwinderPowerLossLightChanged(m_unwinderPowerLossLight);
    }
    Q_INVOKABLE int getMainDrivePowerLossLight() const { return m_mainDrivePowerLossLight; }
    void setMainDrivePowerLossLight(int value)
    {
        if (m_mainDrivePowerLossLight != value)
            m_mainDrivePowerLossLight = value;
        emit mainDrivePowerLossLightChanged(m_mainDrivePowerLossLight);
    }
    Q_INVOKABLE int getSmallWinderPowerLossLight() const { return m_smallWinderPowerLossLight; }
    void setSmallWinderPowerLossLight(int value)
    {
        if (m_smallWinderPowerLossLight != value)
            m_smallWinderPowerLossLight = value;
        emit smallWinderPowerLossLightChanged(m_smallWinderPowerLossLight);
    }
    Q_INVOKABLE int getLargeWinderPowerLossLight() const { return m_largeWinderPowerLossLight; }
    void setLargeWinderPowerLossLight(int value)
    {
        if (m_largeWinderPowerLossLight != value)
            m_largeWinderPowerLossLight = value;
        emit largeWinderPowerLossLightChanged(m_largeWinderPowerLossLight);
    }
    //===== INPUT-2 : Power Loss =====
    Q_INVOKABLE double getSmallCutterPowerLoss() const { return m_smallCutterPowerLoss; }
    void setSmallCutterPowerLoss(double value)
    {
        if (m_smallCutterPowerLoss == value)
            return;
        m_smallCutterPowerLoss = value;
        emit smallCutterPowerLossChanged(m_smallCutterPowerLoss);
    }

    Q_INVOKABLE double getSelvedgeFanPowerLoss() const { return m_selvedgeFanPowerLoss; }
    void setSelvedgeFanPowerLoss(double value)
    {
        if (m_selvedgeFanPowerLoss == value)
            return;
        m_selvedgeFanPowerLoss = value;
        emit selvedgeFanPowerLossChanged(m_selvedgeFanPowerLoss);
    }

    Q_INVOKABLE double getLargeCutterPowerLoss() const { return m_largeCutterPowerLoss; }
    void setLargeCutterPowerLoss(double value)
    {
        if (m_largeCutterPowerLoss == value)
            return;
        m_largeCutterPowerLoss = value;
        emit largeCutterPowerLossChanged(m_largeCutterPowerLoss);
    }

    Q_INVOKABLE double getLeftSelvedgeWinderPowerLoss() const { return m_leftSelvedgeWinderPowerLoss; }
    void setLeftSelvedgeWinderPowerLoss(double value)
    {
        if (m_leftSelvedgeWinderPowerLoss == value)
            return;
        m_leftSelvedgeWinderPowerLoss = value;
        emit leftSelvedgeWinderPowerLossChanged(m_leftSelvedgeWinderPowerLoss);
    }

    Q_INVOKABLE double getRightSelvedgeWinderPowerLoss() const { return m_rightSelvedgeWinderPowerLoss; }
    void setRightSelvedgeWinderPowerLoss(double value)
    {
        if (m_rightSelvedgeWinderPowerLoss == value)
            return;
        m_rightSelvedgeWinderPowerLoss = value;
        emit rightSelvedgeWinderPowerLossChanged(m_rightSelvedgeWinderPowerLoss);
    }

    Q_INVOKABLE double getWebAlignerPowerLoss() const { return m_webAlignerPowerLoss; }
    void setWebAlignerPowerLoss(double value)
    {
        if (m_webAlignerPowerLoss == value)
            return;
        m_webAlignerPowerLoss = value;
        emit webAlignerPowerLossChanged(m_webAlignerPowerLoss);
    }

    Q_INVOKABLE double getUnwinderDisconnect() const { return m_unwinderDisconnect; }
    void setUnwinderDisconnect(double value)
    {
        if (m_unwinderDisconnect == value)
            return;
        m_unwinderDisconnect = value;
        emit unwinderDisconnectChanged(m_unwinderDisconnect);
    }

    Q_INVOKABLE double getMainDriveDisconnect() const { return m_mainDriveDisconnect; }
    void setMainDriveDisconnect(double value)
    {
        if (m_mainDriveDisconnect == value)
            return;
        m_mainDriveDisconnect = value;
        emit mainDriveDisconnectChanged(m_mainDriveDisconnect);
    }

    Q_INVOKABLE double getSmallWinderDisconnect() const { return m_smallWinderDisconnect; }
    void setSmallWinderDisconnect(double value)
    {
        if (m_smallWinderDisconnect == value)
            return;
        m_smallWinderDisconnect = value;
        emit smallWinderDisconnectChanged(m_smallWinderDisconnect);
    }

    Q_INVOKABLE double getLargeWinderDisconnect() const { return m_largeWinderDisconnect; }
    void setLargeWinderDisconnect(double value)
    {
        if (m_largeWinderDisconnect == value)
            return;
        m_largeWinderDisconnect = value;
        emit largeWinderDisconnectChanged(m_largeWinderDisconnect);
    }

    Q_INVOKABLE double getSmallCutterDisconnect() const { return m_smallCutterDisconnect; }
    void setSmallCutterDisconnect(double value)
    {
        if (m_smallCutterDisconnect == value)
            return;
        m_smallCutterDisconnect = value;
        emit smallCutterDisconnectChanged(m_smallCutterDisconnect);
    }
    Q_INVOKABLE double getLeftFanDisconnect() const { return m_leftFanDisconnect; }
    void setLeftFanDisconnect(double value)
    {
        if (m_leftFanDisconnect == value)
            return;
        m_leftFanDisconnect = value;
        emit leftFanDisconnectChanged(m_leftFanDisconnect);
    }

    Q_INVOKABLE double getRightFanDisconnect() const { return m_rightFanDisconnect; }
    void setRightFanDisconnect(double value)
    {
        if (m_rightFanDisconnect == value)
            return;
        m_rightFanDisconnect = value;
        emit rightFanDisconnectChanged(m_rightFanDisconnect);
    }

    Q_INVOKABLE double getLargeCutterDisconnect() const { return m_largeCutterDisconnect; }
    void setLargeCutterDisconnect(double value)
    {
        if (m_largeCutterDisconnect == value)
            return;
        m_largeCutterDisconnect = value;
        emit largeCutterDisconnectChanged(m_largeCutterDisconnect);
    }

    Q_INVOKABLE double getLeftSelvedgeWinderDisconnect() const { return m_leftSelvedgeWinderDisconnect; }
    void setLeftSelvedgeWinderDisconnect(double value)
    {
        if (m_leftSelvedgeWinderDisconnect == value)
            return;
        m_leftSelvedgeWinderDisconnect = value;
        emit leftSelvedgeWinderDisconnectChanged(m_leftSelvedgeWinderDisconnect);
    }

    Q_INVOKABLE double getRightSelvedgeWinderDisconnect() const { return m_rightSelvedgeWinderDisconnect; }
    void setRightSelvedgeWinderDisconnect(double value)
    {
        if (m_rightSelvedgeWinderDisconnect == value)
            return;
        m_rightSelvedgeWinderDisconnect = value;
        emit rightSelvedgeWinderDisconnectChanged(m_rightSelvedgeWinderDisconnect);
    }

    Q_INVOKABLE int getSmallCutterPowerLossLight() const { return m_smallCutterPowerLossLight; }
    void setSmallCutterPowerLossLight(int value)
    {
        if (m_smallCutterPowerLossLight != value)
            m_smallCutterPowerLossLight = value;
        emit smallCutterPowerLossLightChanged(m_smallCutterPowerLossLight);
    }
    Q_INVOKABLE int getSelvedgeFanPowerLossLight() const { return m_selvedgeFanPowerLossLight; }
    void setSelvedgeFanPowerLossLight(int value)
    {
        if (m_selvedgeFanPowerLossLight != value)
            m_selvedgeFanPowerLossLight = value;
        emit selvedgeFanPowerLossLightChanged(m_selvedgeFanPowerLossLight);
    }
    Q_INVOKABLE int getLargeCutterPowerLossLight() const { return m_largeCutterPowerLossLight; }
    void setLargeCutterPowerLossLight(int value)
    {
        if (m_largeCutterPowerLossLight != value)
            m_largeCutterPowerLossLight = value;
        emit largeCutterPowerLossLightChanged(m_largeCutterPowerLossLight);
    }
    Q_INVOKABLE int getLeftSelvedgeWinderPowerLossLight() const { return m_leftSelvedgeWinderPowerLossLight; }
    void setLeftSelvedgeWinderPowerLossLight(int value)
    {
        if (m_leftSelvedgeWinderPowerLossLight != value)
            m_leftSelvedgeWinderPowerLossLight = value;
        emit leftSelvedgeWinderPowerLossLightChanged(m_leftSelvedgeWinderPowerLossLight);
    }
    Q_INVOKABLE int getRightSelvedgeWinderPowerLossLight() const { return m_rightSelvedgeWinderPowerLossLight; }
    void setRightSelvedgeWinderPowerLossLight(int value)
    {
        if (m_rightSelvedgeWinderPowerLossLight != value)
            m_rightSelvedgeWinderPowerLossLight = value;
        emit rightSelvedgeWinderPowerLossLightChanged(m_rightSelvedgeWinderPowerLossLight);
    }
    Q_INVOKABLE int getWebAlignerPowerLossLight() const { return m_webAlignerPowerLossLight; }
    void setWebAlignerPowerLossLight(int value)
    {
        if (m_webAlignerPowerLossLight != value)
            m_webAlignerPowerLossLight = value;
        emit webAlignerPowerLossLightChanged(m_webAlignerPowerLossLight);
    }
    Q_INVOKABLE int getUnwinderDisconnectLight() const { return m_unwinderDisconnectLight; }
    void setUnwinderDisconnectLight(int value)
    {
        if (m_unwinderDisconnectLight != value)
            m_unwinderDisconnectLight = value;
        emit webAlignerPowerLossLightChanged(m_unwinderDisconnectLight);
    }
    Q_INVOKABLE int getMainDriveDisconnectLight() const { return m_mainDriveDisconnectLight; }
    void setMainDriveDisconnectLight(int value)
    {
        if (m_mainDriveDisconnectLight != value)
            m_mainDriveDisconnectLight = value;
        emit mainDriveDisconnectLightChanged(m_mainDriveDisconnectLight);
    }
    Q_INVOKABLE int getSmallWinderDisconnectLight() const { return m_smallWinderDisconnectLight; }
    void setSmallWinderDisconnectLight(int value)
    {
        if (m_smallWinderDisconnectLight != value)
            m_smallWinderDisconnectLight = value;
        emit smallWinderDisconnectLightChanged(m_smallWinderDisconnectLight);
    }
    Q_INVOKABLE int getLargeWinderDisconnectLight() const { return m_largeWinderDisconnectLight; }
    void setLargeWinderDisconnectLight(int value)
    {
        if (m_largeWinderDisconnectLight != value)
            m_largeWinderDisconnectLight = value;
        emit largeWinderDisconnectLightChanged(m_largeWinderDisconnectLight);
    }
    Q_INVOKABLE int getSmallCutterDisconnectLight() const { return m_smallCutterDisconnectLight; }
    void setSmallCutterDisconnectLight(int value)
    {
        if (m_smallCutterDisconnectLight != value)
            m_largeWinderDisconnectLight = value;
        emit smallCutterDisconnectLightChanged(m_smallCutterDisconnectLight);
    }
    Q_INVOKABLE int getLeftFanDisconnectLight() const { return m_leftFanDisconnectLight; }
    void setLeftFanDisconnectLight(int value)
    {
        if (m_leftFanDisconnectLight != value)
            m_leftFanDisconnectLight = value;
        emit leftFanDisconnectLightChanged(m_leftFanDisconnectLight);
    }
    Q_INVOKABLE int getRightFanDisconnectLight() const { return m_rightFanDisconnectLight; }
    void setRightFanDisconnectLight(int value)
    {
        if (m_rightFanDisconnectLight != value)
            m_rightFanDisconnectLight = value;
        emit rightFanDisconnectLightChanged(m_rightFanDisconnectLight);
    }
    Q_INVOKABLE int getLargeCutterDisconnectLight() const { return m_largeCutterDisconnectLight; }
    void setLargeCutterDisconnectLight(int value)
    {
        if (m_largeCutterDisconnectLight != value)
            m_largeCutterDisconnectLight = value;
        emit largeCutterDisconnectLightChanged(m_largeCutterDisconnectLight);
    }
    Q_INVOKABLE int getLeftSelvedgeWinderDisconnectLight() const { return m_leftSelvedgeWinderDisconnectLight; }
    void setLeftSelvedgeWinderDisconnectLight(int value)
    {
        if (m_leftSelvedgeWinderDisconnectLight != value)
            m_leftSelvedgeWinderDisconnectLight = value;
        emit leftSelvedgeWinderDisconnectLightChanged(m_leftSelvedgeWinderDisconnectLight);
    }
    Q_INVOKABLE int getRightSelvedgeWinderDisconnectLight() const { return m_rightSelvedgeWinderDisconnectLight; }
    void setRightSelvedgeWinderDisconnectLight(int value)
    {
        if (m_rightSelvedgeWinderDisconnectLight != value)
            m_rightSelvedgeWinderDisconnectLight = value;
        emit rightSelvedgeWinderDisconnectLightChanged(m_rightSelvedgeWinderDisconnectLight);
    }
    // ===== INPUT-3 =====
    Q_INVOKABLE double getWebAlignerDisconnect() const { return m_webAlignerDisconnect; }
    void setWebAlignerDisconnect(double value)
    {
        if (m_webAlignerDisconnect == value)
            return;
        m_webAlignerDisconnect = value;
        emit webAlignerDisconnectChanged(m_webAlignerDisconnect);
    }

    Q_INVOKABLE double getEmergencyStop1() const { return m_emergencyStop1; }
    void setEmergencyStop1(double value)
    {
        if (m_emergencyStop1 == value)
            return;
        m_emergencyStop1 = value;
        emit emergencyStop1Changed(m_emergencyStop1);
    }

    Q_INVOKABLE double getEmergencyStop2() const { return m_emergencyStop2; }
    void setEmergencyStop2(double value)
    {
        if (m_emergencyStop2 == value)
            return;
        m_emergencyStop2 = value;
        emit emergencyStop2Changed(m_emergencyStop2);
    }

    Q_INVOKABLE double getEmergencyStop3() const { return m_emergencyStop3; }
    void setEmergencyStop3(double value)
    {
        if (m_emergencyStop3 == value)
            return;
        m_emergencyStop3 = value;
        emit emergencyStop3Changed(m_emergencyStop3);
    }

    Q_INVOKABLE double getEmergencyStop4() const { return m_emergencyStop4; }
    void setEmergencyStop4(double value)
    {
        if (m_emergencyStop4 == value)
            return;
        m_emergencyStop4 = value;
        emit emergencyStop4Changed(m_emergencyStop4);
    }

    Q_INVOKABLE double getEmergencyStop5() const { return m_emergencyStop5; }
    void setEmergencyStop5(double value)
    {
        if (m_emergencyStop5 == value)
            return;
        m_emergencyStop5 = value;
        emit emergencyStop5Changed(m_emergencyStop5);
    }

    Q_INVOKABLE double getEmergencyStop6() const { return m_emergencyStop6; }
    void setEmergencyStop6(double value)
    {
        if (m_emergencyStop6 == value)
            return;
        m_emergencyStop6 = value;
        emit emergencyStop6Changed(m_emergencyStop6);
    }

    Q_INVOKABLE double getEmergencyStop7() const { return m_emergencyStop7; }
    void setEmergencyStop7(double value)
    {
        if (m_emergencyStop7 == value)
            return;
        m_emergencyStop7 = value;
        emit emergencyStop7Changed(m_emergencyStop7);
    }

    Q_INVOKABLE double getMainDriveLeftDoor1Open() const { return m_mainDriveLeftDoor1Open; }
    void setMainDriveLeftDoor1Open(double value)
    {
        if (m_mainDriveLeftDoor1Open == value)
            return;
        m_mainDriveLeftDoor1Open = value;
        emit mainDriveLeftDoor1OpenChanged(m_mainDriveLeftDoor1Open);
    }

    Q_INVOKABLE double getMainDriveLeftDoor2Open() const { return m_mainDriveLeftDoor2Open; }
    void setMainDriveLeftDoor2Open(double value)
    {
        if (m_mainDriveLeftDoor2Open == value)
            return;
        m_mainDriveLeftDoor2Open = value;
        emit mainDriveLeftDoor2OpenChanged(m_mainDriveLeftDoor2Open);
    }

    Q_INVOKABLE double getMainDriveRightDoor3Open() const { return m_mainDriveRightDoor3Open; }
    void setMainDriveRightDoor3Open(double value)
    {
        if (m_mainDriveRightDoor3Open == value)
            return;
        m_mainDriveRightDoor3Open = value;
        emit mainDriveRightDoor3OpenChanged(m_mainDriveRightDoor3Open);
    }

    Q_INVOKABLE double getMainDriveRightDoor4Open() const { return m_mainDriveRightDoor4Open; }
    void setMainDriveRightDoor4Open(double value)
    {
        if (m_mainDriveRightDoor4Open == value)
            return;
        m_mainDriveRightDoor4Open = value;
        emit mainDriveRightDoor4OpenChanged(m_mainDriveRightDoor4Open);
    }

    Q_INVOKABLE double getLargeWinderLeftDoor5Open() const { return m_largeWinderLeftDoor5Open; }
    void setLargeWinderLeftDoor5Open(double value)
    {
        if (m_largeWinderLeftDoor5Open == value)
            return;
        m_largeWinderLeftDoor5Open = value;
        emit largeWinderLeftDoor5OpenChanged(m_largeWinderLeftDoor5Open);
    }

    Q_INVOKABLE double getLargeWinderLeftDoor6Open() const { return m_largeWinderLeftDoor6Open; }
    void setLargeWinderLeftDoor6Open(double value)
    {
        if (m_largeWinderLeftDoor6Open == value)
            return;
        m_largeWinderLeftDoor6Open = value;
        emit largeWinderLeftDoor6OpenChanged(m_largeWinderLeftDoor6Open);
    }

    Q_INVOKABLE double getLargeWinderRightDoor7Open() const { return m_largeWinderRightDoor7Open; }
    void setLargeWinderRightDoor7Open(double value)
    {
        if (m_largeWinderRightDoor7Open == value)
            return;
        m_largeWinderRightDoor7Open = value;
        emit largeWinderRightDoor7OpenChanged(m_largeWinderRightDoor7Open);
    }

    Q_INVOKABLE double getLargeWinderRightDoor8Open() const { return m_largeWinderRightDoor8Open; }
    void setLargeWinderRightDoor8Open(double value)
    {
        if (m_largeWinderRightDoor8Open == value)
            return;
        m_largeWinderRightDoor8Open = value;
        emit largeWinderRightDoor8OpenChanged(m_largeWinderRightDoor8Open);
    }


    Q_INVOKABLE int getWebAlignerDisconnectLight() const { return m_webAlignerDisconnectLight; }
    void setWebAlignerDisconnectLight(int value)
    {
        if (m_webAlignerDisconnectLight != value)
            m_webAlignerDisconnectLight = value;
        emit webAlignerDisconnectLightChanged(m_webAlignerDisconnectLight);
    }
    Q_INVOKABLE int getEmergencyStop1Light() const { return m_emergencyStop1Light; }
    void setEmergencyStop1Light(int value)
    {
        if (m_emergencyStop1Light != value)
            m_emergencyStop1Light = value;
        emit emergencyStop1LightChanged(m_emergencyStop1Light);
    }
    Q_INVOKABLE int getEmergencyStop2Light() const { return m_emergencyStop2Light; }
    void setEmergencyStop2Light(int value)
    {
        if (m_emergencyStop2Light != value)
            m_emergencyStop2Light = value;
        emit emergencyStop2LightChanged(m_emergencyStop2Light);
    }
    Q_INVOKABLE int getEmergencyStop3Light() const { return m_emergencyStop3Light; }
    void setEmergencyStop3Light(int value)
    {
        if (m_emergencyStop3Light != value)
            m_emergencyStop3Light = value;
        emit emergencyStop3LightChanged(m_emergencyStop3Light);
    }
    Q_INVOKABLE int getEmergencyStop4Light() const { return m_emergencyStop4Light; }
    void setEmergencyStop4Light(int value)
    {
        if (m_emergencyStop4Light != value)
            m_emergencyStop4Light = value;
        emit emergencyStop4LightChanged(m_emergencyStop4Light);
    }
    Q_INVOKABLE int getEmergencyStop5Light() const { return m_emergencyStop5Light; }
    void setEmergencyStop5Light(int value)
    {
        if (m_emergencyStop5Light != value)
            m_emergencyStop5Light = value;
        emit emergencyStop5LightChanged(m_emergencyStop5Light);
    }
    Q_INVOKABLE int getEmergencyStop6Light() const { return m_emergencyStop6Light; }
    void setEmergencyStop6Light(int value)
    {
        if (m_emergencyStop6Light != value)
            m_emergencyStop6Light = value;
        emit emergencyStop1LightChanged(m_emergencyStop6Light);
    }
    Q_INVOKABLE int getEmergencyStop7Light() const { return m_emergencyStop7Light; }
    void setEmergencyStop7Light(int value)
    {
        if (m_emergencyStop7Light != value)
            m_emergencyStop7Light = value;
        emit emergencyStop1LightChanged(m_emergencyStop7Light);
    }
    Q_INVOKABLE int getMainDriveLeftDoor1OpenLight() const { return m_mainDriveLeftDoor1OpenLight; }
    void setMainDriveLeftDoor1OpenLight(int value)
    {
        if (m_mainDriveLeftDoor1OpenLight != value)
            m_mainDriveLeftDoor1OpenLight = value;
        emit mainDriveLeftDoor1OpenLightChanged(m_mainDriveLeftDoor1OpenLight);
    }
    Q_INVOKABLE int getMainDriveLeftDoor2OpenLight() const { return m_mainDriveLeftDoor2OpenLight; }
    void setMainDriveLeftDoor2OpenLight(int value)
    {
        if (m_mainDriveLeftDoor2OpenLight != value)
            m_mainDriveLeftDoor2OpenLight = value;
        emit mainDriveLeftDoor2OpenLightChanged(m_mainDriveLeftDoor2OpenLight);
    }
    Q_INVOKABLE int getMainDriveRightDoor3OpenLight() const { return m_mainDriveRightDoor3OpenLight; }
    void setMainDriveRightDoor3OpenLight(int value)
    {
        if (m_mainDriveRightDoor3OpenLight != value)
            m_mainDriveRightDoor3OpenLight = value;
        emit mainDriveRightDoor3OpenLightChanged(m_mainDriveRightDoor3OpenLight);
    }
    Q_INVOKABLE int getMainDriveRightDoor4OpenLight() const { return m_mainDriveRightDoor4OpenLight; }
    void setMainDriveRightDoor4OpenLight(int value)
    {
        if (m_mainDriveRightDoor4OpenLight != value)
            m_mainDriveRightDoor4OpenLight = value;
        emit mainDriveRightDoor4OpenLightChanged(m_mainDriveRightDoor4OpenLight);
    }
    Q_INVOKABLE int getLargeWinderLeftDoor5OpenLight() const { return m_largeWinderLeftDoor5OpenLight; }
    void setLargeWinderLeftDoor5OpenLight(int value)
    {
        if (m_largeWinderLeftDoor5OpenLight != value)
            m_largeWinderLeftDoor5OpenLight = value;
        emit largeWinderLeftDoor5OpenLightChanged(m_largeWinderLeftDoor5OpenLight);
    }
    Q_INVOKABLE int getLargeWinderLeftDoor6OpenLight() const { return m_largeWinderLeftDoor6OpenLight; }
    void setLargeWinderLeftDoor6OpenLight(int value)
    {
        if (m_largeWinderLeftDoor6OpenLight != value)
            m_largeWinderLeftDoor6OpenLight = value;
        emit largeWinderLeftDoor6OpenLightChanged(m_largeWinderLeftDoor6OpenLight);
    }
    Q_INVOKABLE int getLargeWinderRightDoor7OpenLight() const { return m_largeWinderRightDoor7OpenLight; }
    void setLargeWinderRightDoor7OpenLight(int value)
    {
        if (m_largeWinderRightDoor7OpenLight != value)
            m_largeWinderRightDoor7OpenLight = value;
        emit largeWinderRightDoor7OpenLightChanged(m_largeWinderRightDoor7OpenLight);
    }
    Q_INVOKABLE int getLargeWinderRightDoor8OpenLight() const { return m_largeWinderRightDoor8OpenLight; }
    void setLargeWinderRightDoor8OpenLight(int value)
    {
        if (m_largeWinderRightDoor8OpenLight != value)
            m_largeWinderRightDoor8OpenLight = value;
        emit largeWinderRightDoor8OpenLightChanged(m_largeWinderRightDoor8OpenLight);
    }
    // =====INPUT-4 Fence Detect =====
    Q_INVOKABLE double getUnwindingFenceDetect1() const { return m_unwindingFenceDetect1; }
    void setUnwindingFenceDetect1(double value)
    {
        if (m_unwindingFenceDetect1 == value)
            return;
        m_unwindingFenceDetect1 = value;
        emit unwindingFenceDetect1Changed(m_unwindingFenceDetect1);
    }
    Q_INVOKABLE double getUnwindingFenceDetect2() const { return m_unwindingFenceDetect2; }
    void setUnwindingFenceDetect2(double value)
    {
        if (m_unwindingFenceDetect2 == value)
            return;
        m_unwindingFenceDetect2 = value;
        emit unwindingFenceDetect2Changed(m_unwindingFenceDetect2);
    }

    Q_INVOKABLE double getLargeWinderFenceDetect3() const { return m_largeWinderFenceDetect3; }
    void setLargeWinderFenceDetect3(double value)
    {
        if (m_largeWinderFenceDetect3 == value)
            return;
        m_largeWinderFenceDetect3 = value;
        emit largeWinderFenceDetect3Changed(m_largeWinderFenceDetect3);
    }

    Q_INVOKABLE double getLargeWinderFenceDetect4() const { return m_largeWinderFenceDetect4; }
    void setLargeWinderFenceDetect4(double value)
    {
        if (m_largeWinderFenceDetect4 == value)
            return;
        m_largeWinderFenceDetect4 = value;
        emit largeWinderFenceDetect4Changed(m_largeWinderFenceDetect4);
    }

    Q_INVOKABLE int getUnwindingFenceDetect1Light() const { return m_unwindingFenceDetect1Light; }
    void setUnwindingFenceDetect1Light(int value)
    {
        if (m_unwindingFenceDetect1Light != value)
            m_unwindingFenceDetect1Light = value;
        emit unwindingFenceDetect1LightChanged(m_unwindingFenceDetect1Light);
    }
    Q_INVOKABLE int getUnwindingFenceDetect2Light() const { return m_unwindingFenceDetect2Light; }
    void setUnwindingFenceDetect2Light(int value)
    {
        if (m_unwindingFenceDetect2Light != value)
            m_unwindingFenceDetect2Light = value;
        emit unwindingFenceDetect2LightChanged(m_unwindingFenceDetect2Light);
    }
    Q_INVOKABLE int getLargeWinderFenceDetect3Light() const { return m_largeWinderFenceDetect3Light; }
    void setLargeWinderFenceDetect3Light(int value)
    {
        if (m_largeWinderFenceDetect3Light != value)
            m_largeWinderFenceDetect3Light = value;
        emit largeWinderFenceDetect3LightChanged(m_largeWinderFenceDetect3Light);
    }
    Q_INVOKABLE int getLargeWinderFenceDetect4Light() const { return m_largeWinderFenceDetect4Light; }
    void setLargeWinderFenceDetect4Light(int value)
    {
        if (m_largeWinderFenceDetect4Light != value)
            m_largeWinderFenceDetect4Light = value;
        emit largeWinderFenceDetect4LightChanged(m_largeWinderFenceDetect4Light);
    }
    // =====INPUT-4 Safety Light Curtain =====
    Q_INVOKABLE double getUnwindingSafetyLightCurtainAlarm() const { return m_unwindingSafetyLightCurtainAlarm; }
    void setUnwindingSafetyLightCurtainAlarm(double value)
    {
        if (m_unwindingSafetyLightCurtainAlarm == value)
            return;
        m_unwindingSafetyLightCurtainAlarm = value;
        emit unwindingSafetyLightCurtainAlarmChanged(m_unwindingSafetyLightCurtainAlarm);
    }

    Q_INVOKABLE double getInspectionSafetyLightCurtainAlarm() const { return m_inspectionSafetyLightCurtainAlarm; }
    void setInspectionSafetyLightCurtainAlarm(double value)
    {
        if (m_inspectionSafetyLightCurtainAlarm == value)
            return;
        m_inspectionSafetyLightCurtainAlarm = value;
        emit inspectionSafetyLightCurtainAlarmChanged(m_inspectionSafetyLightCurtainAlarm);
    }

    Q_INVOKABLE double getLargeWinderSafetyLightCurtainAlarm() const { return m_largeWinderSafetyLightCurtainAlarm; }
    void setLargeWinderSafetyLightCurtainAlarm(double value)
    {
        if (m_largeWinderSafetyLightCurtainAlarm == value)
            return;
        m_largeWinderSafetyLightCurtainAlarm = value;
        emit largeWinderSafetyLightCurtainAlarmChanged(m_largeWinderSafetyLightCurtainAlarm);
    }

    Q_INVOKABLE int getUnwindingSafetyLightCurtainAlarmLight() const { return m_unwindingSafetyLightCurtainAlarmLight; }
    void setUnwindingSafetyLightCurtainAlarmLight(int value)
    {
        if (m_unwindingSafetyLightCurtainAlarmLight != value)
            m_unwindingSafetyLightCurtainAlarmLight = value;
        emit unwindingSafetyLightCurtainAlarmLightChanged(m_unwindingSafetyLightCurtainAlarmLight);
    }
    Q_INVOKABLE int getInspectionSafetyLightCurtainAlarmLight() const { return m_inspectionSafetyLightCurtainAlarmLight; }
    void setInspectionSafetyLightCurtainAlarmLight(int value)
    {
        if (m_inspectionSafetyLightCurtainAlarmLight != value)
            m_inspectionSafetyLightCurtainAlarmLight = value;
        emit inspectionSafetyLightCurtainAlarmLightChanged(m_inspectionSafetyLightCurtainAlarmLight);
    }
    Q_INVOKABLE int getLargeWinderSafetyLightCurtainAlarmLight() const { return m_largeWinderSafetyLightCurtainAlarmLight; }
    void setLargeWinderSafetyLightCurtainAlarmLight(int value)
    {
        if (m_largeWinderSafetyLightCurtainAlarmLight != value)
            m_largeWinderSafetyLightCurtainAlarmLight = value;
        emit largeWinderSafetyLightCurtainAlarmLightChanged(m_largeWinderSafetyLightCurtainAlarmLight);
    }
    // =====INPUT-4 Zero Speed Detect =====
    Q_INVOKABLE double getSmallWinderZeroSpeedDetect() const { return m_smallWinderZeroSpeedDetect; }
    void setSmallWinderZeroSpeedDetect(double value)
    {
        if (m_smallWinderZeroSpeedDetect == value)
            return;
        m_smallWinderZeroSpeedDetect = value;
        emit smallWinderZeroSpeedDetectChanged(m_smallWinderZeroSpeedDetect);
    }

    Q_INVOKABLE double getLargeWinderZeroSpeedDetect() const { return m_largeWinderZeroSpeedDetect; }
    void setLargeWinderZeroSpeedDetect(double value)
    {
        if (m_largeWinderZeroSpeedDetect == value)
            return;
        m_largeWinderZeroSpeedDetect = value;
        emit largeWinderZeroSpeedDetectChanged(m_largeWinderZeroSpeedDetect);
    }

    Q_INVOKABLE int getSmallWinderZeroSpeedDetectLight() const { return m_smallWinderZeroSpeedDetectLight; }
    void setSmallWinderZeroSpeedDetectLight(int value)
    {
        if (m_smallWinderZeroSpeedDetectLight != value)
            m_smallWinderZeroSpeedDetectLight = value;
        emit smallWinderZeroSpeedDetectLightChanged(m_smallWinderZeroSpeedDetectLight);
    }
    Q_INVOKABLE int getLargeWinderZeroSpeedDetectLight() const { return m_largeWinderZeroSpeedDetectLight; }
    void setLargeWinderZeroSpeedDetectLight(int value)
    {
        if (m_largeWinderZeroSpeedDetectLight != value)
            m_largeWinderZeroSpeedDetectLight = value;
        emit largeWinderZeroSpeedDetectLightChanged(m_largeWinderZeroSpeedDetectLight);
    }
    // =====INPUT-4 Tension Over =====
    Q_INVOKABLE double getUnwindingTensionOver() const { return m_unwindingTensionOver; }
    void setUnwindingTensionOver(double value)
    {
        if (m_unwindingTensionOver == value)
            return;
        m_unwindingTensionOver = value;
        emit unwindingTensionOverChanged(m_unwindingTensionOver);
    }

    Q_INVOKABLE double getSmallWinderTensionOver() const { return m_smallWinderTensionOver; }
    void setSmallWinderTensionOver(double value)
    {
        if (m_smallWinderTensionOver == value)
            return;
        m_smallWinderTensionOver = value;
        emit smallWinderTensionOverChanged(m_smallWinderTensionOver);
    }

    Q_INVOKABLE double getLargeWinderTensionOver() const { return m_largeWinderTensionOver; }
    void setLargeWinderTensionOver(double value)
    {
        if (m_largeWinderTensionOver == value)
            return;
        m_largeWinderTensionOver = value;
        emit largeWinderTensionOverChanged(m_largeWinderTensionOver);
    }

    Q_INVOKABLE int getUnwindingTensionOverLight() const { return m_unwindingTensionOverLight; }
    void setUnwindingTensionOverLight(int value)
    {
        if (m_unwindingTensionOverLight != value)
            m_unwindingTensionOverLight = value;
        emit unwindingTensionOverLightChanged(m_unwindingTensionOverLight);
    }
    Q_INVOKABLE int getSmallWinderTensionOverLight() const { return m_smallWinderTensionOverLight; }
    void setSmallWinderTensionOverLight(int value)
    {
        if (m_smallWinderTensionOverLight != value)
            m_smallWinderTensionOverLight = value;
        emit unwindingTensionOverLightChanged(m_smallWinderTensionOverLight);
    }
    Q_INVOKABLE int getLargeWinderTensionOverLight() const { return m_largeWinderTensionOverLight; }
    void setLargeWinderTensionOverLight(int value)
    {
        if (m_largeWinderTensionOverLight != value)
            m_largeWinderTensionOverLight = value;
        emit largeWinderTensionOverLightChanged(m_largeWinderTensionOverLight);
    }
    // =====INPUT-4 Angle Alarm =====
    Q_INVOKABLE double getLeftSelvedgeWinderAngleAlarm() const { return m_leftSelvedgeWinderAngleAlarm; }
    void setLeftSelvedgeWinderAngleAlarm(double value)
    {
        if (m_leftSelvedgeWinderAngleAlarm == value)
            return;
        m_leftSelvedgeWinderAngleAlarm = value;
        emit leftSelvedgeWinderAngleAlarmChanged(m_leftSelvedgeWinderAngleAlarm);
    }

    Q_INVOKABLE double getRightSelvedgeWinderAngleAlarm() const { return m_rightSelvedgeWinderAngleAlarm; }
    void setRightSelvedgeWinderAngleAlarm(double value)
    {
        if (m_rightSelvedgeWinderAngleAlarm == value)
            return;
        m_rightSelvedgeWinderAngleAlarm = value;
        emit rightSelvedgeWinderAngleAlarmChanged(m_rightSelvedgeWinderAngleAlarm);
    }

    Q_INVOKABLE int getLeftSelvedgeWinderAngleAlarmLight() const { return m_leftSelvedgeWinderAngleAlarmLight; }
    void setLeftSelvedgeWinderAngleAlarmLight(int value)
    {
        if (m_leftSelvedgeWinderAngleAlarmLight != value)
            m_leftSelvedgeWinderAngleAlarmLight = value;
        emit leftSelvedgeWinderAngleAlarmLightChanged(m_leftSelvedgeWinderAngleAlarmLight);
    }
    Q_INVOKABLE int getRightSelvedgeWinderAngleAlarmLight() const { return m_rightSelvedgeWinderAngleAlarmLight; }
    void setRightSelvedgeWinderAngleAlarmLight(int value)
    {
        if (m_rightSelvedgeWinderAngleAlarmLight != value)
            m_rightSelvedgeWinderAngleAlarmLight = value;
        emit rightSelvedgeWinderAngleAlarmLightChanged(m_rightSelvedgeWinderAngleAlarmLight);
    }
    //===== OUTPUT-1 READ =====
    // =====OUTPUT-1 Alarm Reset =====
    Q_INVOKABLE double getVfdAlarmReset() const { return m_vfdAlarmReset; }
    void setVfdAlarmReset(double value)
    {
        if (m_vfdAlarmReset != value)
            m_vfdAlarmReset = value;

        emit vfdAlarmResetChanged(m_vfdAlarmReset);
    }
    // =====OUTPUT-1 Alarm Reset Switch=====
    Q_INVOKABLE int getVfdAlarmResetSwitch() const { return m_vfdAlarmResetSwitch; }
    void setVfdAlarmResetSwitch(int value)
    {
        if (m_vfdAlarmResetSwitch != value)
            m_vfdAlarmResetSwitch = value;

        emit vfdAlarmResetSwitchChanged(m_vfdAlarmResetSwitch);
    }

    // =====OUTPUT-1 Unwinder =====
    Q_INVOKABLE double getUnwinderForward() const { return m_unwinderForward; }
    void setUnwinderForward(double value)
    {
        if (m_unwinderForward != value)
            m_unwinderForward = value;

        emit unwinderForwardChanged(m_unwinderForward);
    }

    // =====OUTPUT-1 Unwinder switch=====
    Q_INVOKABLE int getUnwinderForwardSwitch() const { return m_unwinderForwardSwitch; }
    void setUnwinderForwardSwitch(int value)
    {
        if (m_unwinderForwardSwitch != value)
            m_unwinderForwardSwitch = value;
        
            emit unwinderForwardSwitchChanged(m_unwinderForwardSwitch);
    }

    Q_INVOKABLE double getUnwinderReverse() const { return m_unwinderReverse; }
    void setUnwinderReverse(double value)
    {
        if (m_unwinderReverse != value)
            m_unwinderReverse = value;

        emit unwinderReverseChanged(m_unwinderReverse);
    }

    Q_INVOKABLE int getUnwinderReverseSwitch() const { return m_unwinderReverseSwitch; }
    void setUnwinderReverseSwitch(int value)
    {
        if (m_unwinderReverseSwitch != value)
            m_unwinderReverseSwitch = value;

        emit unwinderReverseSwitchChanged(m_unwinderReverseSwitch);
    }

    // =====OUTPUT-1 Main Drive =====
    Q_INVOKABLE double getMainDriveForward() const { return m_mainDriveForward; }
    void setMainDriveForward(double value)
    {
        if (m_mainDriveForward != value)
            m_mainDriveForward = value;

        emit mainDriveForwardChanged(m_mainDriveForward);
    }

    // =====OUTPUT-1 Main Drive Switch=====
    Q_INVOKABLE int getMainDriveForwardSwitch() const { return m_mainDriveForwardSwitch; }
    void setMainDriveForwardSwitch(int value)
    {
        if (m_mainDriveForwardSwitch != value)
            m_mainDriveForwardSwitch = value;

        emit mainDriveForwardSwitchChanged(m_mainDriveForwardSwitch);
    }

    Q_INVOKABLE double getMainDriveReverse() const { return m_mainDriveReverse; }
    void setMainDriveReverse(double value)
    {
        if (m_mainDriveReverse != value)
            m_mainDriveReverse = value;

        emit mainDriveReverseChanged(m_mainDriveReverse);
    }

    //switch
    Q_INVOKABLE int getMainDriveReverseSwitch() const { return m_mainDriveReverseSwitch; }
    void setMainDriveReverseSwitch(int value)
    {
        if (m_mainDriveReverseSwitch != value)
            m_mainDriveReverseSwitch = value;

        emit mainDriveReverseSwitchChanged(m_mainDriveReverseSwitch);
    }

    // =====OUTPUT-1 Small Winder =====
    Q_INVOKABLE double getSmallWinderForward() const { return m_smallWinderForward; }
    void setSmallWinderForward(double value)
    {
        if (m_smallWinderForward != value)
            m_smallWinderForward = value;
        emit smallWinderForwardChanged(m_smallWinderForward);
    }

    // =====OUTPUT-1 Small Winder Switch=====
    Q_INVOKABLE int getSmallWinderForwardSwitch() const { return m_smallWinderForwardSwitch; }
    void setSmallWinderForwardSwitch(int value)
    {
        if (m_smallWinderForwardSwitch != value)
            m_smallWinderForwardSwitch = value;

        emit smallWinderForwardSwitchChanged(m_smallWinderForwardSwitch);
    }

    Q_INVOKABLE double getSmallWinderReverse() const { return m_smallWinderReverse; }
    void setSmallWinderReverse(double value)
    {
        if (m_smallWinderReverse != value)
            m_smallWinderReverse = value;
        emit smallWinderReverseChanged(m_smallWinderReverse);
    }
    // =====OUTPUT-1 Small Winder Switch=====
    Q_INVOKABLE int getSmallWinderReverseSwitch() const { return m_smallWinderReverseSwitch; }
    void setSmallWinderReverseSwitch(int value)
    {
        if (m_smallWinderReverseSwitch != value)
            m_smallWinderReverseSwitch = value;

        emit smallWinderReverseSwitchChanged(m_smallWinderReverseSwitch);
    }


    // =====OUTPUT-1 Large Winder =====
    Q_INVOKABLE double getLargeWinderForward() const { return m_largeWinderForward; }
    void setLargeWinderForward(double value)
    {
        if (m_largeWinderForward != value)
            m_largeWinderForward = value;
        emit largeWinderForwardChanged(m_largeWinderForward);
    }
    // =====OUTPUT-1 Large Winder Switch=====
    Q_INVOKABLE int getLargeWinderForwardSwitch() const { return m_largeWinderForwardSwitch; }
    void setLargeWinderForwardSwitch(int value)
    {
        if (m_largeWinderForwardSwitch != value)
            m_largeWinderForwardSwitch = value;

        emit largeWinderForwardSwitchChanged(m_largeWinderForwardSwitch);
    }

    Q_INVOKABLE double getLargeWinderReverse() const { return m_largeWinderReverse; }
    void setLargeWinderReverse(double value)
    {
        if (m_largeWinderReverse != value)
            m_largeWinderReverse = value;

        emit largeWinderReverseChanged(m_largeWinderReverse);
    }
    //switch
    Q_INVOKABLE int getLargeWinderReverseSwitch() const { return m_largeWinderReverseSwitch; }
    void setLargeWinderReverseSwitch(int value)
    {
        if (m_largeWinderReverseSwitch != value)
            m_largeWinderReverseSwitch = value;

        emit largeWinderReverseSwitchChanged(m_largeWinderReverseSwitch);
    }


    // =====OUTPUT-1 Cutter / Fan =====
    Q_INVOKABLE double getSmallCutterStart() const { return m_smallCutterStart; }
    void setSmallCutterStart(double value)
    {
        if (m_smallCutterStart != value)
            m_smallCutterStart = value;
        emit smallCutterStartChanged(m_smallCutterStart);
    }
    //! ===OUTPUT-1 Cutter / Fan Switch=====
    Q_INVOKABLE int getSmallCutterStartSwitch() const { return m_smallCutterStartSwitch; }
    void setSmallCutterStartSwitch(int value)
    {
        if (m_smallCutterStartSwitch != value)
            m_smallCutterStartSwitch = value;

        emit smallCutterStartSwitchChanged(m_smallCutterStartSwitch);
    }

    Q_INVOKABLE double getSelvedgeFanStart() const { return m_selvedgeFanStart; }
    void setSelvedgeFanStart(double value)
    {
        if (m_selvedgeFanStart != value)
            m_selvedgeFanStart = value;
        emit selvedgeFanStartChanged(m_selvedgeFanStart);
    }
    Q_INVOKABLE int getSelvedgeFanStartSwitch() const { return m_selvedgeFanStartSwitch; }
    void setSelvedgeFanStartSwitch(int value)
    {
        if (m_selvedgeFanStartSwitch != value)
            m_selvedgeFanStartSwitch = value;

        emit selvedgeFanStartSwitchChanged(m_selvedgeFanStartSwitch);
    }

    Q_INVOKABLE double getLargeCutterStart() const { return m_largeCutterStart; }
    void setLargeCutterStart(double value)
    {
        if (m_largeCutterStart != value)
            m_largeCutterStart = value;
        emit largeCutterStartChanged(m_largeCutterStart);
    }
    Q_INVOKABLE int getLargeCutterStartSwitch() const { return m_largeCutterStartSwitch; }
    void setLargeCutterStartSwitch(int value)
    {
        if (m_largeCutterStartSwitch != value)
            m_largeCutterStartSwitch = value;

        emit largeCutterStartSwitchChanged(m_largeCutterStartSwitch);
    }

    // =====OUTPUT-1 Selvedge Winder =====
    Q_INVOKABLE double getLeftSelvedgeWinderForward() const { return m_leftSelvedgeWinderForward; }
    void setLeftSelvedgeWinderForward(double value)
    {
        if (m_leftSelvedgeWinderForward != value)
            m_leftSelvedgeWinderForward = value;

        emit leftSelvedgeWinderForwardChanged(m_leftSelvedgeWinderForward);
    }

    // =====OUTPUT-1 Selvedge Winder Switch=====
    Q_INVOKABLE int getLeftSelvedgeWinderForwardSwitch() const { return m_leftSelvedgeWinderForwardSwitch; }
    void setLeftSelvedgeWinderForwardSwitch(int value)
    {
        if (m_leftSelvedgeWinderForwardSwitch != value)
            m_leftSelvedgeWinderForwardSwitch = value;

        emit leftSelvedgeWinderForwardSwitchChanged(m_leftSelvedgeWinderForwardSwitch);
    }

    Q_INVOKABLE double getLeftSelvedgeWinderReverse() const { return m_leftSelvedgeWinderReverse; }
    void setLeftSelvedgeWinderReverse(double value)
    {
        if (m_leftSelvedgeWinderReverse != value)
            m_leftSelvedgeWinderReverse = value;

        emit leftSelvedgeWinderReverseChanged(m_leftSelvedgeWinderReverse);
    }

    Q_INVOKABLE int getLeftSelvedgeWinderReverseSwitch() const { return m_leftSelvedgeWinderReverseSwitch; }
    void setLeftSelvedgeWinderReverseSwitch(int value)
    {
        if (m_leftSelvedgeWinderReverseSwitch != value)
            m_leftSelvedgeWinderReverseSwitch = value;
        emit leftSelvedgeWinderReverseSwitchChanged(m_leftSelvedgeWinderReverseSwitch);
    }

    Q_INVOKABLE double getRightSelvedgeWinderForward() const { return m_rightSelvedgeWinderForward; }
    void setRightSelvedgeWinderForward(double value)
    {
        if (m_rightSelvedgeWinderForward != value)
            m_rightSelvedgeWinderForward = value;

        emit rightSelvedgeWinderForwardChanged(m_rightSelvedgeWinderForward);
    }

    Q_INVOKABLE int getRightSelvedgeWinderForwardSwitch() const { return m_rightSelvedgeWinderForwardSwitch; }
    void setRightSelvedgeWinderForwardSwitch(int value)
    {
        if (m_rightSelvedgeWinderForwardSwitch != value)
            m_rightSelvedgeWinderForwardSwitch = value;
        emit rightSelvedgeWinderForwardSwitchChanged(m_rightSelvedgeWinderForwardSwitch);
    }

    Q_INVOKABLE double getRightSelvedgeWinderReverse() const { return m_rightSelvedgeWinderReverse; }
    void setRightSelvedgeWinderReverse(double value)
    {
        if (m_rightSelvedgeWinderReverse != value)
            m_rightSelvedgeWinderReverse = value;

        emit rightSelvedgeWinderReverseChanged(m_rightSelvedgeWinderReverse);
    }
    Q_INVOKABLE int getRightSelvedgeWinderReverseSwitch() const { return m_rightSelvedgeWinderReverseSwitch; }
    void setRightSelvedgeWinderReverseSwitch(int value)
    {
        if (m_rightSelvedgeWinderReverseSwitch != value)
            m_rightSelvedgeWinderReverseSwitch = value;

        emit rightSelvedgeWinderReverseSwitchChanged(m_rightSelvedgeWinderReverseSwitch);
    }

    // =====OUTPUT2 Web Aligner / Unwinding =====
    Q_INVOKABLE double getWebAlignerStart() const { return m_webAlignerStart; }
    void setWebAlignerStart(double value)
    {
        if (m_webAlignerStart != value)
            m_webAlignerStart = value;
        emit webAlignerStartChanged(m_webAlignerStart);
    }

    // =====OUTPUT2 Web Aligner / Unwinding Switch=====
    Q_INVOKABLE int getWebAlignerStartSwitch() const { return m_webAlignerStartSwitch; }
    void setWebAlignerStartSwitch(int value)
    {
        if (m_webAlignerStartSwitch != value)
            m_webAlignerStartSwitch = value;

        emit webAlignerStartSwitchChanged(m_webAlignerStartSwitch);
    }

    Q_INVOKABLE double getUnwindingTensionAuto() const { return m_unwindingTensionAuto; }
    void setUnwindingTensionAuto(double value)
    {
        if (m_unwindingTensionAuto != value)
            m_unwindingTensionAuto = value;
        emit unwindingTensionAutoChanged(m_unwindingTensionAuto);
    }
    //switch
    Q_INVOKABLE int getUnwindingTensionAutoSwitch() const { return m_unwindingTensionAutoSwitch; }
    void setUnwindingTensionAutoSwitch(int value)
    {
        if (m_unwindingTensionAutoSwitch != value)
            m_unwindingTensionAutoSwitch = value;

        emit unwindingTensionAutoSwitchChanged(m_unwindingTensionAuto);
    }

    Q_INVOKABLE double getUnwindingDiameterReset() const { return m_unwindingDiameterReset; }
    void setUnwindingDiameterReset(double value)
    {
        if (m_unwindingDiameterReset != value)
            m_unwindingDiameterReset = value;
        emit unwindingDiameterResetChanged(m_unwindingDiameterReset);
    }
    //switch
    Q_INVOKABLE int getUnwindingDiameterResetSwitch() const { return m_unwindingDiameterResetSwitch; }
    void setUnwindingDiameterResetSwitch(int value)
    {
        if (m_unwindingDiameterResetSwitch != value)
            m_unwindingDiameterResetSwitch = value;
        emit unwindingDiameterResetSwitchChanged(m_unwindingDiameterResetSwitch);
    }

    // =====OUTPUT2 Small Winder =====
    Q_INVOKABLE double getSmallWinderTensionAuto() const { return m_smallWinderTensionAuto; }
    void setSmallWinderTensionAuto(double value)
    {
        if (m_smallWinderTensionAuto != value)
            m_smallWinderTensionAuto = value;
        emit smallWinderTensionAutoChanged(m_smallWinderTensionAuto);
    }
    // =====OUTPUT2 Small Winder switch=====
    Q_INVOKABLE int getSmallWinderTensionAutoSwitch() const { return m_smallWinderTensionAutoSwitch; }
    void setSmallWinderTensionAutoSwitch(int value)
    {
        if (m_smallWinderTensionAutoSwitch != value)
            m_smallWinderTensionAutoSwitch = value;
        emit smallWinderTensionAutoSwitchChanged(m_smallWinderTensionAutoSwitch);
    }

    Q_INVOKABLE double getSmallWinderDiameterReset() const { return m_smallWinderDiameterReset; }
    void setSmallWinderDiameterReset(double value)
    {
        if (m_smallWinderDiameterReset != value)
            m_smallWinderDiameterReset = value;
        emit smallWinderDiameterResetChanged(m_smallWinderDiameterReset);
    }
    //switch
    Q_INVOKABLE int getSmallWinderDiameterResetSwitch() const { return m_smallWinderDiameterResetSwitch; }
    void setSmallWinderDiameterResetSwitch(int value)
    {
        if (m_smallWinderDiameterResetSwitch != value)
            m_smallWinderDiameterResetSwitch = value;
        emit smallWinderDiameterResetSwitchChanged(m_smallWinderDiameterResetSwitch);
    }

    // =====OUTPUT2 Large Winder =====
    Q_INVOKABLE double getLargeWinderTensionAuto() const { return m_largeWinderTensionAuto; }
    void setLargeWinderTensionAuto(double value)
    {
        if (m_largeWinderTensionAuto != value)
            m_largeWinderTensionAuto = value;
        emit largeWinderTensionAutoChanged(m_largeWinderTensionAuto);
    }
    // =====OUTPUT2 Large Winder switch=====
    Q_INVOKABLE int getLargeWinderTensionAutoSwitch() const { return m_largeWinderTensionAutoSwitch; }
    void setLargeWinderTensionAutoSwitch(int value)
    {
        if (m_largeWinderTensionAutoSwitch != value)
            m_largeWinderTensionAutoSwitch = value;
        emit largeWinderTensionAutoSwitchChanged(m_largeWinderTensionAutoSwitch);
    }

    Q_INVOKABLE double getLargeWinderDiameterReset() const { return m_largeWinderDiameterReset; }
    void setLargeWinderDiameterReset(double value)
    {
        if (m_largeWinderDiameterReset != value)
            m_largeWinderDiameterReset = value;
        emit largeWinderDiameterResetChanged(m_largeWinderDiameterReset);
    }

    //switch
    Q_INVOKABLE int getLargeWinderDiameterResetSwitch() const { return m_largeWinderDiameterResetSwitch; }
    void setLargeWinderDiameterResetSwitch(int value)
    {
        if (m_largeWinderDiameterResetSwitch != value)
            m_largeWinderDiameterResetSwitch = value;
        emit largeWinderDiameterResetSwitchChanged(m_largeWinderDiameterResetSwitch);
    }

    // =====OUTPUT2 Selvedge Winder =====
    Q_INVOKABLE double getLeftSelvedgeWinderAuto() const { return m_leftSelvedgeWinderAuto; }
    void setLeftSelvedgeWinderAuto(double value)
    {
        if (m_leftSelvedgeWinderAuto != value)
            m_leftSelvedgeWinderAuto = value;
        emit leftSelvedgeWinderAutoChanged(m_leftSelvedgeWinderAuto);
    }
    // =====OUTPUT2 Selvedge Winder Switch=====
    Q_INVOKABLE int getLeftSelvedgeWinderAutoSwitch() const { return m_leftSelvedgeWinderAutoSwitch; }
    void setLeftSelvedgeWinderAutoSwitch(int value)
    {
        if (m_leftSelvedgeWinderAutoSwitch != value)
            m_leftSelvedgeWinderAutoSwitch = value;
        emit leftSelvedgeWinderAutoSwitchChanged(m_leftSelvedgeWinderAutoSwitch);
    }

    Q_INVOKABLE double getRightSelvedgeWinderAuto() const { return m_rightSelvedgeWinderAuto; }
    void setRightSelvedgeWinderAuto(double value)
    {
        if (m_rightSelvedgeWinderAuto != value)
            m_rightSelvedgeWinderAuto = value;
        emit rightSelvedgeWinderAutoChanged(m_rightSelvedgeWinderAuto);
    }

    //switch
    Q_INVOKABLE int getRightSelvedgeWinderAutoSwitch() const { return m_rightSelvedgeWinderAutoSwitch; }
    void setRightSelvedgeWinderAutoSwitch(int value)
    {
        if (m_rightSelvedgeWinderAutoSwitch != value)
            m_rightSelvedgeWinderAutoSwitch = value;

        emit rightSelvedgeWinderAutoSwitchChanged(m_rightSelvedgeWinderAutoSwitch);
    }


    // =====OUTPUT2 Nip Roll =====
    Q_INVOKABLE double getNipRollUp() const { return m_nipRollUp; }
    void setNipRollUp(double value)
    {
        if (m_nipRollUp != value)
            m_nipRollUp = value;
        emit nipRollUpChanged(m_nipRollUp);
    }
    // =====OUTPUT2 Nip Roll Switch=====
    Q_INVOKABLE int getNipRollUpSwitch() const { return m_nipRollUpSwitch; }
    void setNipRollUpSwitch(int value)
    {
        if (m_nipRollUpSwitch != value)
            m_nipRollUpSwitch = value;
        emit nipRollUpSwitchChanged(m_nipRollUpSwitch);
    }

    Q_INVOKABLE double getNipRollDown() const { return m_nipRollDown; }
    void setNipRollDown(double value)
    {
        if (m_nipRollDown != value)
            m_nipRollDown = value;
        emit nipRollDownChanged(m_nipRollDown);
    }
    //switch
    Q_INVOKABLE int getNipRollDownSwitch() const { return m_nipRollDownSwitch; }
    void setNipRollDownSwitch(int value)
    {
        if (m_nipRollDownSwitch != value)
            m_nipRollDownSwitch = value;
        emit nipRollDownSwitchChanged(m_nipRollDownSwitch);
    }

    // =====OUTPUT2 Press Plate =====
    Q_INVOKABLE double getLeftPressPlateForward() const { return m_leftPressPlateForward; }
    void setLeftPressPlateForward(double value)
    {
        if (m_leftPressPlateForward != value)
            m_leftPressPlateForward = value;
        emit leftPressPlateForwardChanged(m_leftPressPlateForward);
    }
    // =====OUTPUT2 Press Plate Switch=====
    Q_INVOKABLE int getLeftPressPlateForwardSwitch() const { return m_leftPressPlateForwardSwitch; }
    void setLeftPressPlateForwardSwitch(int value)
    {
        if (m_leftPressPlateForwardSwitch != value)
            m_leftPressPlateForwardSwitch = value;
        emit leftPressPlateForwardSwitchChanged(m_leftPressPlateForwardSwitch);
    }

    Q_INVOKABLE double getLeftPressPlateBackward() const { return m_leftPressPlateBackward; }
    void setLeftPressPlateBackward(double value)
    {
        if (m_leftPressPlateBackward != value)
            m_leftPressPlateBackward = value;
        emit leftPressPlateBackwardChanged(m_leftPressPlateBackward);
    }
    //switch
    Q_INVOKABLE int getLeftPressPlateBackwardSwitch() const { return m_leftPressPlateBackwardSwitch; }
    void setLeftPressPlateBackwardSwitch(int value)
    {
        if (m_leftPressPlateBackwardSwitch != value)
            m_leftPressPlateBackwardSwitch = value;
        emit leftPressPlateBackwardSwitchChanged(m_leftPressPlateBackwardSwitch);
    }

    Q_INVOKABLE double getRightPressPlateForward() const { return m_rightPressPlateForward; }
    void setRightPressPlateForward(double value)
    {
        if (m_rightPressPlateForward != value)
            m_rightPressPlateForward = value;
        emit rightPressPlateForwardChanged(m_rightPressPlateForward);
    }
    //switch
    Q_INVOKABLE int getRightPressPlateForwardSwitch() const { return m_rightPressPlateForwardSwitch; }
    void setRightPressPlateForwardSwitch(int value)
    {
        if (m_rightPressPlateForwardSwitch != value)
            m_rightPressPlateForwardSwitch = value;
        emit rightPressPlateForwardSwitchChanged(m_rightPressPlateForwardSwitch);
    }

    Q_INVOKABLE double getRightPressPlateBackward() const { return m_rightPressPlateBackward; }
    void setRightPressPlateBackward(double value)
    {
        if (m_rightPressPlateBackward != value)
            m_rightPressPlateBackward = value;
        emit rightPressPlateBackwardChanged(m_rightPressPlateBackward);
    }
    //switch
    Q_INVOKABLE int getRightPressPlateBackwardSwitch() const { return m_rightPressPlateBackwardSwitch; }
    void setRightPressPlateBackwardSwitch(int value)
    {
        if (m_rightPressPlateBackwardSwitch != value)
            m_rightPressPlateBackwardSwitch = value;
        emit rightPressPlateBackwardSwitchChanged(m_rightPressPlateBackwardSwitch);
    }

    // =====OUTPUT2 Cutter =====
    Q_INVOKABLE double getSmallCutterIn() const { return m_smallCutterIn; }
    void setSmallCutterIn(double value)
    {
        if (m_smallCutterIn != value)
            m_smallCutterIn = value;
        emit smallCutterInChanged(m_smallCutterIn);
    }
    // =====OUTPUT2 Cutter switch=====
    Q_INVOKABLE int getSmallCutterInSwitch() const { return m_smallCutterInSwitch; }
    void setSmallCutterInSwitch(int value)
    {
        if (m_smallCutterInSwitch != value)
            m_smallCutterInSwitch = value;
        emit smallCutterInSwitchChanged(m_smallCutterInSwitch);
    }

    // =====OUTPUT3 Cutter / Mode =====
    Q_INVOKABLE double getLargeCutterIn() const { return m_largeCutterIn; }
    void setLargeCutterIn(double value)
     {
         if (m_largeCutterIn != value)
            m_largeCutterIn = value;
         emit largeCutterInChanged(m_largeCutterIn);
     }
    // =====OUTPUT3 Cutter / Mode Switch=====
    Q_INVOKABLE int getLargeCutterInSwitch() const { return m_largeCutterInSwitch; }
    void setLargeCutterInSwitch(int value)
    {
         if (m_largeCutterInSwitch != value)
            m_largeCutterInSwitch = value;
         emit largeCutterInSwitchChanged(m_largeCutterInSwitch);
    }

    Q_INVOKABLE double getModeSelect() const { return m_modeSelect; }
    void setModeSelect(double value)
    {
        if (m_modeSelect != value)
            m_modeSelect = value;
        emit modeSelectChanged(m_modeSelect);
    }
    //switch
    Q_INVOKABLE int getModeSelectSwitch() const { return m_modeSelectSwitch; }
    void setModeSelectSwitch(int value)
    {
        if (m_modeSelectSwitch != value)
            m_modeSelectSwitch = value;
        emit modeSelectSwitchChanged(m_modeSelectSwitch);
    }

    // =====OUTPUT3 Indicator =====
    Q_INVOKABLE double getRunIndicator() const { return m_runIndicator; }
    void setRunIndicator(double value)
    {
        if (m_runIndicator != value)
            m_runIndicator = value;
        emit runIndicatorChanged(m_runIndicator);
    }
    // =====OUTPUT3 Indicator switch =====
    Q_INVOKABLE int getRunIndicatorSwitch() const { return m_runIndicatorSwitch; }
    void setRunIndicatorSwitch(int value)
    {
        if (m_runIndicatorSwitch != value)
                m_runIndicatorSwitch = value;
        emit runIndicatorSwitchChanged(m_runIndicatorSwitch);
    }

    Q_INVOKABLE double getAlarmIndicator() const { return m_alarmIndicator; }
    void setAlarmIndicator(double value)
    {
        if (m_alarmIndicator != value)
            m_alarmIndicator = value;
        emit alarmIndicatorChanged(m_alarmIndicator);
    }
    //switch
    Q_INVOKABLE int getAlarmIndicatorSwitch() const { return m_alarmIndicatorSwitch; }
    void setAlarmIndicatorSwitch(int value)
    {
        if (m_alarmIndicatorSwitch != value)
            m_alarmIndicatorSwitch = value;
        emit alarmIndicatorSwitchChanged(m_alarmIndicatorSwitch);
    }

    Q_INVOKABLE double getStopIndicator() const { return m_stopIndicator; }
    void setStopIndicator(double value)
     {
         if (m_stopIndicator != value)
            m_stopIndicator = value;
         emit stopIndicatorChanged(m_stopIndicator);
     }
    //switch
    Q_INVOKABLE int getStopIndicatorSwitch() const { return m_stopIndicatorSwitch; }
    void setStopIndicatorSwitch(int value)
     {
         if (m_stopIndicatorSwitch != value)
             m_stopIndicatorSwitch = value;
         emit stopIndicatorChanged(m_stopIndicatorSwitch);
     }

    // =====OUTPUT3 Buzzer / Mode Select =====
    Q_INVOKABLE double getBuzzer() const { return m_buzzer; }
    void setBuzzer(double value)
    {
        if (m_buzzer != value)
            m_buzzer = value;
        emit buzzerChanged(m_buzzer);
    }
    // =====OUTPUT3 Buzzer / Mode Select switch=====
    Q_INVOKABLE int getBuzzerSwitch() const { return m_buzzerSwitch; }
    void setBuzzerSwitch(int value)
    {
        if (m_buzzerSwitch != value)
            m_buzzerSwitch = value;
        emit buzzerSwitchChanged(m_buzzerSwitch);
    }

    Q_INVOKABLE double getSmallRollModeSelect() const { return m_smallRollModeSelect; }
    void setSmallRollModeSelect(double value)
    {
        if (m_smallRollModeSelect != value)
            m_smallRollModeSelect = value;
        emit smallRollModeSelectChanged(m_smallRollModeSelect);
    }
    //switch
    Q_INVOKABLE int getSmallRollModeSelectSwitch() const { return m_smallRollModeSelectSwitch; }
    void setSmallRollModeSelectSwitch(int value)
    {
        if (m_smallRollModeSelectSwitch != value)
            m_smallRollModeSelectSwitch = value;
        emit smallRollModeSelectSwitchChanged(m_smallRollModeSelectSwitch);
    }
    //8
    Q_INVOKABLE double getOutput8() const { return m_output8; }
    void setOutput8(double value)
    {
        if (m_output8 != value)
            m_output8 = value;
        emit output8Changed(m_output8);
    }
    //8switch
    Q_INVOKABLE int getOutput8Switch() const { return output8Switch; }
    void setOutput8Switch(int value)
    {
        if (output8Switch != value)
            output8Switch = value;
        emit output8SwitchChanged(output8Switch);
    }

    //9
    Q_INVOKABLE double getOutput9() const { return m_output9; }
    void setOutput9(double value)
    {
        if (m_output9 != value)
            m_output9 = value;
        emit output9Changed(m_output9);
    }
    //9switch
    Q_INVOKABLE int getOutput9Switch() const { return output9Switch; }
    void setOutput9Switch(int value)
    {
        if (output9Switch != value)
            output9Switch = value;
        emit output9SwitchChanged(output9Switch);
    }
    //10
    Q_INVOKABLE double getOutput10() const { return m_output10; }
    void setOutput10(double value)
    {
        if (m_output10 != value)
            m_output10 = value;
        emit output10Changed(m_output10);
    }
    //10switch
    Q_INVOKABLE int getOutput10Switch() const { return output10Switch; }
    void setOutput10Switch(int value)
    {
        if (output10Switch != value)
            output10Switch = value;
        emit output10SwitchChanged(output10Switch);
    }
    //11
    Q_INVOKABLE double getOutput11() const { return m_output11; }
    void setOutput11(double value)
    {
        if (m_output11 != value)
            m_output11 = value;
        emit output11Changed(m_output11);
    }
    //11switch
    Q_INVOKABLE int getOutput11Switch() const { return output11Switch; }
    void setOutput11Switch(int value)
    {
        if (output11Switch != value)
            output11Switch = value;
        emit output11SwitchChanged(output11Switch);
    }
    //12
    Q_INVOKABLE double getOutput12() const { return m_output12; }
    void setOutput12(double value)
    {
        if (m_output12 != value)
            m_output12 = value;
        emit output12Changed(m_output12);
    }
    //12switch
    Q_INVOKABLE int getOutput12Switch() const { return output12Switch; }
    void setOutput12Switch(int value)
    {
        if (output12Switch != value)
            output12Switch = value;
        emit output12SwitchChanged(output12Switch);
    }
    //13
    Q_INVOKABLE double getOutput13() const { return m_output13; }
    void setOutput13(double value)
    {
        if (m_output13 != value)
            m_output13 = value;
        emit output13Changed(m_output13);
    }
    //13switch
    Q_INVOKABLE int getOutput13Switch() const { return output13Switch; }
    void setOutput13Switch(int value)
    {
        if (output13Switch != value)
            output13Switch = value;
        emit output13SwitchChanged(output13Switch);
    }
    //14
    Q_INVOKABLE double getOutput14() const { return m_output14; }
    void setOutput14(double value)
    {
        if (m_output14 != value)
            m_output14 = value;
        emit output14Changed(m_output14);
    }
    //14switch
    Q_INVOKABLE int getOutput14Switch() const { return output14Switch; }
    void setOutput14Switch(int value)
    {
        if (output14Switch != value)
            output14Switch = value;
        emit output14SwitchChanged(output14Switch);
    }
    //15
    Q_INVOKABLE double getOutput15() const { return m_output15; }
    void setOutput15(double value)
    {
        if (m_output15 != value)
            m_output15 = value;
        emit output15Changed(m_output15);
    }
    //15switch
    Q_INVOKABLE int getOutput15Switch() const { return output15Switch; }
    void setOutput15Switch(int value)
    {
        if (output15Switch != value)
            output15Switch = value;
        emit output15SwitchChanged(output15Switch);
    }
    //16
    Q_INVOKABLE double getOutput16() const { return m_output16; }
    void setOutput16(double value)
    {
        if (m_output16 != value)
            m_output16 = value;
        emit output16Changed(m_output16);
    }
    //16switch
    Q_INVOKABLE int getOutput16Switch() const { return output16Switch; }
    void setOutput16Switch(int value)
    {
        if (output16Switch != value)
            output16Switch = value;
        emit output16SwitchChanged(output16Switch);
    }
    //17
    Q_INVOKABLE double getOutput17() const { return m_output17; }
    void setOutput17(double value)
    {
        if (m_output17 != value)
            m_output17 = value;
        emit output17Changed(m_output17);
    }
    //17switch
    Q_INVOKABLE int getOutput17Switch() const { return output17Switch; }
    void setOutput17Switch(int value)
    {
        if (output17Switch != value)
            output17Switch = value;
        emit output17SwitchChanged(output17Switch);
    }

     
    // ===== ANALOG OUTPUT READ =====
    Q_INVOKABLE double getAnalogOutUnwinderMainDrive() const{ return m_analogOutUnwinderMainDrive;}
    void setAnalogOutUnwinderMainDrive(double value)
    {
        if (m_analogOutUnwinderMainDrive != value)
            m_analogOutUnwinderMainDrive = value;
        emit analogOutUnwinderMainDriveChanged(m_analogOutUnwinderMainDrive);
    }

    //%
    Q_INVOKABLE double getAnalogOutUnwinderMainDrivePc() const{ return m_analogOutUnwinderMainDrivePc;}
    void setAnalogOutUnwinderMainDrivePc(double value){m_analogOutUnwinderMainDrivePc = value;emit analogOutUnwinderMainDrivePcChanged(m_analogOutUnwinderMainDrivePc);}

    // ===== ANALOG OUTPUT READ switch=====
    Q_INVOKABLE int getAnalogOutUnwinderMainDriveSwitch() const{ return m_analogOutUnwinderMainDriveSwitch;}
    void setAnalogOutUnwinderMainDriveSwitch(int value)
    {
        if (m_analogOutUnwinderMainDriveSwitch != value)
            m_analogOutUnwinderMainDriveSwitch = value;
        emit analogOutUnwinderMainDriveSwitchChanged(m_analogOutUnwinderMainDriveSwitch);
    }

    Q_INVOKABLE double getAnalogOutWinder() const{ return m_analogOutWinder;}
    void setAnalogOutWinder(double value)
    {
        if (m_analogOutWinder != value)
            m_analogOutWinder = value;
        emit analogOutWinderChanged(m_analogOutWinder);
    }

    //%
    Q_INVOKABLE double getAnalogOutWinderPc() const{ return m_analogOutWinderPc;}
    void setAnalogOutWinderPc(double value){m_analogOutWinderPc = value;emit analogOutWinderPcChanged(m_analogOutWinderPc);}


    Q_INVOKABLE int getAnalogOutWinderSwitch() const{ return m_analogOutWinderSwitch;}
    void setAnalogOutWinderSwitch(int value)
    {
        if (m_analogOutWinderSwitch != value)
            m_analogOutWinderSwitch = value;
        emit analogOutWinderSwitchChanged(m_analogOutWinderSwitch);
    }

    Q_INVOKABLE double getAnalogOutCutter() const { return m_analogOutCutter;}
    void setAnalogOutCutter(double value)
    {
        if (m_analogOutCutter != value)
            m_analogOutCutter = value;
        emit analogOutCutterChanged(m_analogOutCutter);
    }
    //%
    Q_INVOKABLE double getAnalogOutCutterPc() const{ return m_analogOutCutterPc;}
    void setAnalogOutCutterPc(double value){m_analogOutCutterPc = value;emit analogOutCutterPcChanged(m_analogOutCutterPc);}

    //switch
    Q_INVOKABLE int getAnalogOutCutterSwitch() const { return m_analogOutCutterSwitch;}
    void setAnalogOutCutterSwitch(int value)
    {
        if (m_analogOutCutterSwitch != value)
            m_analogOutCutterSwitch = value;
        emit analogOutCutterSwitchChanged(m_analogOutCutterSwitch);
    }

    Q_INVOKABLE double getAnalogOutSelvedgeWinder() const{ return m_analogOutSelvedgeWinder;}
    void setAnalogOutSelvedgeWinder(double value)
    {
        if (m_analogOutSelvedgeWinder != value)
            m_analogOutSelvedgeWinder = value;
        emit analogOutSelvedgeWinderChanged(m_analogOutSelvedgeWinder);
    }

    //%
    Q_INVOKABLE double getAnalogOutSelvedgeWinderPc() const{ return m_analogOutSelvedgeWinderPc;}
    void setAnalogOutSelvedgeWinderPc(double value){ m_analogOutSelvedgeWinderPc = value;emit analogOutSelvedgeWinderPcChanged(m_analogOutSelvedgeWinderPc);}

    //switch
    Q_INVOKABLE int getAnalogOutSelvedgeWinderSwitch() const{ return m_analogOutSelvedgeWinderSwitch;}
    void setAnalogOutSelvedgeWinderSwitch(int value)
    {
        if (m_analogOutSelvedgeWinderSwitch != value)
            m_analogOutSelvedgeWinderSwitch = value;
        emit analogOutSelvedgeWinderSwitchChanged(m_analogOutSelvedgeWinderSwitch);
    }

    Q_INVOKABLE double getModifyAnalogOutUnwinderMainDrive() const { return m_modifyAnalogOutUnwinderMainDrive; }
    void setModifyAnalogOutUnwinderMainDrive(double value)
    {
        if (m_modifyAnalogOutUnwinderMainDrive != value)
            m_modifyAnalogOutUnwinderMainDrive = value;
        emit modifyAnalogOutUnwinderMainDriveChanged(m_modifyAnalogOutUnwinderMainDrive);
    }
    //switch
    Q_INVOKABLE int getModifyAnalogOutUnwinderMainDriveSwitch() const { return m_modifyAnalogOutUnwinderMainDriveSwitch; }
    void setModifyAnalogOutUnwinderMainDriveSwitch(int value)
    {
        if (m_modifyAnalogOutUnwinderMainDriveSwitch != value)
            m_modifyAnalogOutUnwinderMainDriveSwitch = value;
        emit modifyAnalogOutUnwinderMainDriveSwitchChanged(m_modifyAnalogOutUnwinderMainDriveSwitch);
    }

    Q_INVOKABLE double getModifyAnalogOutWinder() const { return m_modifyAnalogOutWinder; }
    void setModifyAnalogOutWinder(double value)
    {
        if (m_modifyAnalogOutWinder != value)
            m_modifyAnalogOutWinder = value;
        emit modifyAnalogOutWinderChanged(m_modifyAnalogOutWinder);
    }
    //switch
    Q_INVOKABLE int getModifyAnalogOutWinderSwitch() const { return m_modifyAnalogOutWinderSwitch; }
    void setModifyAnalogOutWinderSwitch(int value)
    {
        if (m_modifyAnalogOutWinderSwitch != value)
            m_modifyAnalogOutWinderSwitch = value;
        emit modifyAnalogOutWinderSwitchChanged(m_modifyAnalogOutWinderSwitch);
    }

    Q_INVOKABLE double getModifyAnalogOutCutter() const { return m_modifyAnalogOutCutter; }
    void setModifyAnalogOutCutter(double value)
    {
        if (m_modifyAnalogOutCutter != value)
            m_modifyAnalogOutCutter = value;
        emit modifyAnalogOutCutterChanged(m_modifyAnalogOutCutter);
    }
    //switch
    Q_INVOKABLE int getModifyAnalogOutCutterSwitch() const { return m_modifyAnalogOutCutterSwitch; }
    void setModifyAnalogOutCutterSwitch(int value)
    {
        if (m_modifyAnalogOutCutterSwitch != value)
            m_modifyAnalogOutCutterSwitch = value;
        emit modifyAnalogOutCutterSwitchChanged(m_modifyAnalogOutCutterSwitch);
    }

    Q_INVOKABLE double getModifyAnalogOutSelvedgeWinder() const { return m_modifyAnalogOutSelvedgeWinder;}
    void setModifyAnalogOutSelvedgeWinder(double value)
    {
        if (m_modifyAnalogOutSelvedgeWinder != value)
            m_modifyAnalogOutSelvedgeWinder = value;
        emit modifyAnalogOutSelvedgeWinderChanged(m_modifyAnalogOutSelvedgeWinder);
        qDebug()<<"get setModifyAnalogOutSelvedgeWinder"<<m_modifyAnalogOutSelvedgeWinder;
    }
    //switch
    Q_INVOKABLE int getModifyAnalogOutSelvedgeWinderSwitch() const { return m_modifyAnalogOutSelvedgeWinderSwitch;}
    void setModifyAnalogOutSelvedgeWinderSwitch(int value)
    {
        if (m_modifyAnalogOutSelvedgeWinderSwitch != value)
            m_modifyAnalogOutSelvedgeWinderSwitch = value;
        emit modifyAnalogOutSelvedgeWinderSwitchChanged(m_modifyAnalogOutSelvedgeWinderSwitch);
    }

    // ===== IPC INPUT WRITE =====
    Q_INVOKABLE double getIpcStart() const { return m_ipcStart; }
    Q_INVOKABLE double getIpcStop() const { return m_ipcStop; }
    Q_INVOKABLE double getIpcAlarmReset() const { return m_ipcAlarmReset; }

    Q_INVOKABLE double getMainJogForward() const { return m_mainJogForward; }
    Q_INVOKABLE double getMainJogReverse() const { return m_mainJogReverse; }

    Q_INVOKABLE double getSmallWinderJogForward() const { return m_smallWinderJogForward; }
    Q_INVOKABLE double getSmallWinderJogReverse() const { return m_smallWinderJogReverse; }

    Q_INVOKABLE double getUnwinderJogReverseSelect() const { return m_unwinderJogReverseSelect; }
    Q_INVOKABLE double getUnwinderJogStart() const { return m_unwinderJogStart; }

    Q_INVOKABLE double getWinderJogReverseSelect() const { return m_winderJogReverseSelect; }
    Q_INVOKABLE double getWinderJogStart() const { return m_winderJogStart; }

    Q_INVOKABLE double getLeftSelvedgeWinderSelect() const { return m_leftSelvedgeWinderSelect; }
    Q_INVOKABLE double getRightSelvedgeWinderSelect() const { return m_rightSelvedgeWinderSelect; }

     // ===== IPC INPUT WRITE Light=====
    Q_INVOKABLE int getIpcStartLight() const { return m_ipcStartLight; }
    Q_INVOKABLE int getIpcStopLight() const { return m_ipcStopLight; }
    Q_INVOKABLE int getIpcAlarmResetLight() const { return m_ipcAlarmResetLight; }

    Q_INVOKABLE int getMainJogForwardLight() const { return m_mainJogForwardLight; }
    Q_INVOKABLE int getMainJogReverseLight() const { return m_mainJogReverseLight; }

    Q_INVOKABLE int getSmallWinderJogForwardLight() const { return m_smallWinderJogForwardLight; }
    Q_INVOKABLE int getSmallWinderJogReverseLight() const { return m_smallWinderJogReverseLight; }

    Q_INVOKABLE int getUnwinderJogReverseSelectLight() const { return m_unwinderJogReverseSelectLight; }
    Q_INVOKABLE int getUnwinderJogStartLight() const { return m_unwinderJogStartLight; }

    Q_INVOKABLE int getWinderJogReverseSelectLight() const { return m_winderJogReverseSelectLight; }
    Q_INVOKABLE int getWinderJogStartLight() const { return m_winderJogStartLight; }

    Q_INVOKABLE int getLeftSelvedgeWinderSelectLight() const { return m_leftSelvedgeWinderSelectLight; }
    Q_INVOKABLE int getRightSelvedgeWinderSelectLight() const { return m_rightSelvedgeWinderSelectLight; }

    // =====控制介面 Motor Control =====
    Q_INVOKABLE double getSmallRollMotor() const { return m_smallRollMotor; }
    void setSmallRollMotor(double value)
    {
        if (m_smallRollMotor != value)
            m_smallRollMotor = value;
        emit smallRollMotorChanged(m_smallRollMotor);
    }
    //switch
    Q_INVOKABLE int getSmallRollMotorSwitch() const { return m_smallRollMotorSwitch; }
    void setSmallRollMotorSwitch(int value)
    {
        if (m_smallRollMotorSwitch != value)
            m_smallRollMotorSwitch = value;
        emit smallRollMotorSwitchChanged(m_smallRollMotorSwitch);
    }
    

    Q_INVOKABLE double getMainDriveMotor() const { return m_mainDriveMotor; }
    void setMainDriveMotor(double value)
    {
        if (m_mainDriveMotor != value)
            m_mainDriveMotor = value;
        emit mainDriveMotorChanged(m_mainDriveMotor);
    }
    //switch
    Q_INVOKABLE int getMainDriveMotorSwitch() const { return m_mainDriveMotorSwitch; }
    void setMainDriveMotorSwitch(int value)
    {
        if (m_mainDriveMotorSwitch != value)
            m_mainDriveMotorSwitch = value;
        emit mainDriveMotorSwitchChanged(m_mainDriveMotorSwitch);
    }

    Q_INVOKABLE double getLargeRollMotor() const { return m_largeRollMotor; }
    void setLargeRollMotor(double value)
    {
        if (m_largeRollMotor != value)
            m_largeRollMotor = value;
        emit largeRollMotorChanged(m_largeRollMotor);
    }
    //switch
    Q_INVOKABLE int getLargeRollMotorSwitch() const { return m_largeRollMotorSwitch; }
    void setLargeRollMotorSwitch(int value)
    {
        if (m_largeRollMotorSwitch != value)
            m_largeRollMotorSwitch = value;
        emit largeRollMotorSwitchChanged(m_largeRollMotorSwitch);
    }

    Q_INVOKABLE double getWasteRollMotorB() const { return m_wasteRollMotorB; }
    void setWasteRollMotorB(double value)
    {
        if (m_wasteRollMotorB != value)
            m_wasteRollMotorB = value;
        emit wasteRollMotorBChanged(m_wasteRollMotorB);
    }
    //switch
    Q_INVOKABLE int getWasteRollMotorBSwitch() const { return m_wasteRollMotorBSwitch; }
    void setWasteRollMotorBSwitch(int value)
    {
        if (m_wasteRollMotorBSwitch != value)
            m_wasteRollMotorBSwitch = value;
        emit wasteRollMotorBSwitchChanged(m_wasteRollMotorBSwitch);
    }

    Q_INVOKABLE double getUnwindingMotor() const { return m_unwindingMotor; }
    void setUnwindingMotor(double value)
    {
        if (m_unwindingMotor != value)
            m_unwindingMotor = value;
        emit unwindingMotorChanged(m_unwindingMotor);
    }
    //switch
    Q_INVOKABLE int getUnwindingMotorSwitch() const { return m_unwindingMotorSwitch; }
    void setUnwindingMotorSwitch(int value)
    {
        if (m_unwindingMotorSwitch != value)
            m_unwindingMotorSwitch = value;
        emit unwindingMotorSwitchChanged(m_unwindingMotorSwitch);
    }

    Q_INVOKABLE double getEdgeAlignMotor() const { return m_edgeAlignMotor; }
    void setEdgeAlignMotor(double value)
    {
        if (m_edgeAlignMotor != value)
            m_edgeAlignMotor = value;
        emit edgeAlignMotorChanged(m_edgeAlignMotor);
    }
    Q_INVOKABLE int getEdgeAlignMotorSwitch() const { return m_edgeAlignMotorSwitch; }
    void setEdgeAlignMotorSwitch(int value)
    {
        if (m_edgeAlignMotorSwitch != value)
            m_edgeAlignMotorSwitch = value;
        emit edgeAlignMotorSwitchChanged(m_edgeAlignMotorSwitch);
    }

    Q_INVOKABLE double getCutterWheelMotor() const { return m_cutterWheelMotor; }
    void setCutterWheelMotor(double value)
    {
        if (m_cutterWheelMotor != value)
            m_cutterWheelMotor = value;
        emit cutterWheelMotorChanged(m_cutterWheelMotor);
    }
    //switch
    Q_INVOKABLE int getCutterWheelMotorSwitch() const { return m_cutterWheelMotorSwitch; }
    void setCutterWheelMotorSwitch(int value)
    {
        if (m_cutterWheelMotorSwitch != value)
            m_cutterWheelMotorSwitch = value;
        emit cutterWheelMotorSwitchChanged(m_cutterWheelMotorSwitch);
    }

    Q_INVOKABLE double getWasteRollMotorA() const { return m_wasteRollMotorA; }
    void setWasteRollMotorA(double value)
    {
        if (m_wasteRollMotorA != value)
            m_wasteRollMotorA = value;
        emit wasteRollMotorAChanged(m_wasteRollMotorA);
    }
    //switch
    Q_INVOKABLE int getWasteRollMotorASwitch() const { return m_wasteRollMotorASwitch; }
    void setWasteRollMotorASwitch(int value)
    {
        if (m_wasteRollMotorASwitch != value)
            m_wasteRollMotorASwitch = value;
        emit wasteRollMotorASwitchChanged(m_wasteRollMotorASwitch);
    }

    // =====控制介面 Tension Control =====
    Q_INVOKABLE double getUnwindingTension() const { return m_unwindingTension; }
    void setUnwindingTension(double value)
    {
        if (m_unwindingTension != value)
            m_unwindingTension = value;
        emit unwindingTensionChanged(m_unwindingTension);
    }
    //switch
    Q_INVOKABLE int getUnwindingTensionSwitch() const { return m_unwindingTensionSwitch; }
    void setUnwindingTensionSwitch(int value)
    {
        if (m_unwindingTensionSwitch != value)
            m_unwindingTensionSwitch = value;
        emit unwindingTensionSwitchChanged(m_unwindingTensionSwitch);
    }

    Q_INVOKABLE double getSmallRollTension() const { return m_smallRollTension; }
    void setSmallRollTension(double value)
    {
        if (m_smallRollTension != value)
            m_smallRollTension = value;
        emit smallRollTensionChanged(m_smallRollTension);
    }
    //switch
    Q_INVOKABLE int getSmallRollTensionSwitch() const { return m_smallRollTensionSwitch; }
    void setSmallRollTensionSwitch(int value)
    {
        if (m_smallRollTensionSwitch != value)
            m_smallRollTensionSwitch = value;
        emit smallRollTensionSwitchChanged(m_smallRollTensionSwitch);
    }

    Q_INVOKABLE double getLargeRollTension() const { return m_largeRollTension; }
    void setLargeRollTension(double value)
    {
        if (m_largeRollTension != value)
            m_largeRollTension = value;
        emit largeRollTensionChanged(m_largeRollTension);
    }
    //switch
    Q_INVOKABLE int getLargeRollTensionSwitch() const { return m_largeRollTensionSwitch; }
    void setLargeRollTensionSwitch(int value)
    {
        if (m_largeRollTensionSwitch != value)
            m_largeRollTensionSwitch = value;
        emit largeRollTensionSwitchChanged(m_largeRollTensionSwitch);
    }

    // ===== cutter=====
    Q_INVOKABLE int getSmallRollCutter1() const { return m_smallRollCutter1; }
    void setSmallRollCutter1(int value)
    {
        if (m_smallRollCutter1 != value)
            m_smallRollCutter1 = value;
        emit smallRollCutter1Changed(m_smallRollCutter1);
    }

    Q_INVOKABLE int getSmallRollCutter2() const { return m_smallRollCutter2; }
    void setSmallRollCutter2(int value)
    {
        if (m_smallRollCutter2 != value)
            m_smallRollCutter2 = value;
        emit smallRollCutter2Changed(m_smallRollCutter2);
    }
    Q_INVOKABLE int getSmallRollCutter3() const { return m_smallRollCutter3; }
    void setSmallRollCutter3(int value)
    {
        if (m_smallRollCutter3 != value)
            m_smallRollCutter3 = value;
        emit smallRollCutter3Changed(m_smallRollCutter3);
    }
    Q_INVOKABLE int getSmallRollCutter4() const { return m_smallRollCutter4; }
    void setSmallRollCutter4(int value)
    {
        if (m_smallRollCutter4 != value)
            m_smallRollCutter4 = value;
        emit smallRollCutter4Changed(m_smallRollCutter4);
    }
    Q_INVOKABLE int getSmallRollCutter5() const { return m_smallRollCutter5; }
    void setSmallRollCutter5(int value)
    {
        if (m_smallRollCutter5 != value)
            m_smallRollCutter5 = value;
        emit smallRollCutter5Changed(m_smallRollCutter5);
    }
    Q_INVOKABLE int getBigRollCutter() const { return m_bigRollCutter; }
    void setBigRollCutter(int value)
    {
        if (m_bigRollCutter != value)
            m_bigRollCutter = value;
        emit bigRollCutterChanged(m_bigRollCutter);
    }

    // ===== Single Action Mode=====
    Q_INVOKABLE int getSingleActionMode() const { return m_singleActionMode; }
    void setSingleActionMode(int value)
    {
        if (m_singleActionMode != value)
            m_singleActionMode = value;
        emit singleActionModeChanged(m_singleActionMode);
    }
    signals:

    void bigRollModeChanged(int value);
    void smallRollModeChanged(int value);
    void restBtnChanged(int value);

    void metalDetectorChanged(int value);
    void gratingDetectionChanged(int value);
    void oppositeSideChanged(int value);

    void doorASignalChanged(int value);
    void doorBSignalChanged(int value);
    void doorCSignalChanged(int value);
    void doorDSignalChanged(int value);
    void doorESignalChanged(int value);
    void doorFSignalChanged(int value);
    void doorGSignalChanged(int value);
    void doorHSignalChanged(int value);
    void doorISignalChanged(int value);

    void uvLightChanged(int value);
    void whiteLightChanged(int value);
    void bottomLightChanged(int value);

    void currentLengthChanged(double value);
    void speedChanged(double value);
    void brakingDistanceChanged(double value);

    void modifyCurrentLengthChanged(int value);
    void modifySpeedChanged(int value);
    void modifyBrakingDistanceChanged(double value);

    void modifyUnwindingTensionChanged(double value);
    void modifySmallWinderTensionOverChanged(double value);
    void modifyLargeWinderTensionOverChanged(double value);


    // INPUT-1
    void unwinderVfdFreqAlarmChanged(double value);
    void mainDriveVfdFreqAlarmChanged(double value);
    void smallWinderVfdFreqAlarmChanged(double value);
    void largeWinderVfdFreqAlarmChanged(double value);
    void smallCutterVfdFreqAlarmChanged(double value);
    void selvedgeFanVfdFreqAlarmChanged(double value);

    void leftFanOverloadAlarmChanged(double value);
    void rightFanOverloadAlarmChanged(double value);

    void largeCutterVfdFreqAlarmChanged(double value);
    void leftSelvedgeWinderVfdAlarmChanged(double value);
    void rightSelvedgeWinderVfdAlarmChanged(double value);

    void webAlignerVfdFreqAlarmChanged(double value);

    void unwinderPowerLossChanged(double value);
    void mainDrivePowerLossChanged(double value);
    void smallWinderPowerLossChanged(double value);
    void largeWinderPowerLossChanged(double value);

    //INPUT-1 信號燈
    void unwinderVfdFreqAlarmLightChanged(int value);
    void mainDriveVfdFreqAlarmLightChanged(int value);
    void smallWinderVfdFreqAlarmLightChanged(int value);
    void largeWinderVfdFreqAlarmLightChanged(int value);
    void smallCutterVfdFreqAlarmLightChanged(int value);
    void selvedgeFanVfdFreqAlarmLightChanged(int value);
    
    void leftFanOverloadAlarmLightChanged(int value);
    void rightFanOverloadAlarmLightChanged(int value);

    void largeCutterVfdFreqAlarmLightChanged(int value);
    void leftSelvedgeWinderVfdAlarmLightChanged(int value);
    void rightSelvedgeWinderVfdAlarmLightChanged(int value);
    void webAlignerVfdFreqAlarmLightChanged(int value);

    void unwinderPowerLossLightChanged(int value);
    void mainDrivePowerLossLightChanged(int value);
    void smallWinderPowerLossLightChanged(int value);
    void largeWinderPowerLossLightChanged(int value);

    // ===== INPUT-2 Power Loss =====
    void smallCutterPowerLossChanged(double value);
    void selvedgeFanPowerLossChanged(double value);
    void largeCutterPowerLossChanged(double value);
    void leftSelvedgeWinderPowerLossChanged(double value);
    void rightSelvedgeWinderPowerLossChanged(double value);
    void webAlignerPowerLossChanged(double value);

    void unwinderDisconnectChanged(double value);
    void mainDriveDisconnectChanged(double value);
    void smallWinderDisconnectChanged(double value);
    void largeWinderDisconnectChanged(double value);
    void smallCutterDisconnectChanged(double value);
    void leftFanDisconnectChanged(double value);
    void rightFanDisconnectChanged(double value);
    void largeCutterDisconnectChanged(double value);
    void leftSelvedgeWinderDisconnectChanged(double value);
    void rightSelvedgeWinderDisconnectChanged(double value);

    // ===== INPUT-2 light =====
    void smallCutterPowerLossLightChanged(int value);
    void selvedgeFanPowerLossLightChanged(int value);
    void largeCutterPowerLossLightChanged(int value);
    void leftSelvedgeWinderPowerLossLightChanged(int value);
    void rightSelvedgeWinderPowerLossLightChanged(int value);
    void webAlignerPowerLossLightChanged(int value);

    void unwinderDisconnectLightChanged(int value);
    void mainDriveDisconnectLightChanged(int value);
    void smallWinderDisconnectLightChanged(int value);
    void largeWinderDisconnectLightChanged(int value);
    void smallCutterDisconnectLightChanged(int value);
    void leftFanDisconnectLightChanged(int value);
    void rightFanDisconnectLightChanged(int value);
    void largeCutterDisconnectLightChanged(int value);
    void leftSelvedgeWinderDisconnectLightChanged(int value);
    void rightSelvedgeWinderDisconnectLightChanged(int value);

    //===== INPUT-3 =====
    void webAlignerDisconnectChanged(double value);
    void emergencyStop1Changed(double value);
    void emergencyStop2Changed(double value);
    void emergencyStop3Changed(double value);
    void emergencyStop4Changed(double value);
    void emergencyStop5Changed(double value);
    void emergencyStop6Changed(double value);
    void emergencyStop7Changed(double value);

    void mainDriveLeftDoor1OpenChanged(double value);
    void mainDriveLeftDoor2OpenChanged(double value);
    void mainDriveRightDoor3OpenChanged(double value);
    void mainDriveRightDoor4OpenChanged(double value);

    void largeWinderLeftDoor5OpenChanged(double value);
    void largeWinderLeftDoor6OpenChanged(double value);
    void largeWinderRightDoor7OpenChanged(double value);
    void largeWinderRightDoor8OpenChanged(double value);

    //===== INPUT-3 Light=====
    void webAlignerDisconnectLightChanged(int value);
    void emergencyStop1LightChanged(int value);
    void emergencyStop2LightChanged(int value);
    void emergencyStop3LightChanged(int value);
    void emergencyStop4LightChanged(int value);
    void emergencyStop5LightChanged(int value);
    void emergencyStop6LightChanged(int value);
    void emergencyStop7LightChanged(int value);

    void mainDriveLeftDoor1OpenLightChanged(int value);
    void mainDriveLeftDoor2OpenLightChanged(int value);
    void mainDriveRightDoor3OpenLightChanged(int value);
    void mainDriveRightDoor4OpenLightChanged(int value);

    void largeWinderLeftDoor5OpenLightChanged(int value);
    void largeWinderLeftDoor6OpenLightChanged(int value);
    void largeWinderRightDoor7OpenLightChanged(int value);
    void largeWinderRightDoor8OpenLightChanged(int value);

    //===== INPUT-4 =====
    void unwindingFenceDetect1Changed(double value);
    void unwindingFenceDetect2Changed(double value);
    void largeWinderFenceDetect3Changed(double value);
    void largeWinderFenceDetect4Changed(double value);

    void unwindingSafetyLightCurtainAlarmChanged(double value);
    void inspectionSafetyLightCurtainAlarmChanged(double value);
    void largeWinderSafetyLightCurtainAlarmChanged(double value);

    void smallWinderZeroSpeedDetectChanged(double value);
    void largeWinderZeroSpeedDetectChanged(double value);

    void unwindingTensionOverChanged(double value);
    void smallWinderTensionOverChanged(double value);
    void largeWinderTensionOverChanged(double value);

    void leftSelvedgeWinderAngleAlarmChanged(double value);
    void rightSelvedgeWinderAngleAlarmChanged(double value);

    //===== INPUT-4 LIGHT=====
    void unwindingFenceDetect1LightChanged(int value);
    void unwindingFenceDetect2LightChanged(int value);
    void largeWinderFenceDetect3LightChanged(int value);
    void largeWinderFenceDetect4LightChanged(int value);

    void unwindingSafetyLightCurtainAlarmLightChanged(int value);
    void inspectionSafetyLightCurtainAlarmLightChanged(int value);
    void largeWinderSafetyLightCurtainAlarmLightChanged(int value);

    void smallWinderZeroSpeedDetectLightChanged(int value);
    void largeWinderZeroSpeedDetectLightChanged(int value);

    void unwindingTensionOverLightChanged(int value);
    void smallWinderTensionOverLightChanged(int value);
    void largeWinderTensionOverLightChanged(int value);

    void leftSelvedgeWinderAngleAlarmLightChanged(int value);
    void rightSelvedgeWinderAngleAlarmLightChanged(int value);

    //===== OUTPUT-1 =====
    void vfdAlarmResetChanged(double value);

    void unwinderForwardChanged(double value);
    void unwinderReverseChanged(double value);

    void mainDriveForwardChanged(double value);
    void mainDriveReverseChanged(double value);

    void smallWinderForwardChanged(double value);
    void smallWinderReverseChanged(double value);

    void largeWinderForwardChanged(double value);
    void largeWinderReverseChanged(double value);

    void smallCutterStartChanged(double value);
    void selvedgeFanStartChanged(double value);
    void largeCutterStartChanged(double value);

    void leftSelvedgeWinderForwardChanged(double value);
    void leftSelvedgeWinderReverseChanged(double value);

    void rightSelvedgeWinderForwardChanged(double value);
    void rightSelvedgeWinderReverseChanged(double value);
    //===== OUTPUT-1 Switch=====
    void vfdAlarmResetSwitchChanged(int value);

    void unwinderForwardSwitchChanged(int value);
    void unwinderReverseSwitchChanged(int value);

    void mainDriveForwardSwitchChanged(int value);
    void mainDriveReverseSwitchChanged(int value);

    void smallWinderForwardSwitchChanged(int value);
    void smallWinderReverseSwitchChanged(int value);

    void largeWinderForwardSwitchChanged(int value);
    void largeWinderReverseSwitchChanged(int value);

    void smallCutterStartSwitchChanged(int value);
    void selvedgeFanStartSwitchChanged(int value);
    void largeCutterStartSwitchChanged(int value);

    void leftSelvedgeWinderForwardSwitchChanged(int value);
    void leftSelvedgeWinderReverseSwitchChanged(int value);

    void rightSelvedgeWinderForwardSwitchChanged(int value);
    void rightSelvedgeWinderReverseSwitchChanged(int value);

    //===== OUTPUT-2 =====
    void webAlignerStartChanged(double value);
    void unwindingTensionAutoChanged(double value);
    void unwindingDiameterResetChanged(double value);

    void smallWinderTensionAutoChanged(double value);
    void smallWinderDiameterResetChanged(double value);

    void largeWinderTensionAutoChanged(double value);
    void largeWinderDiameterResetChanged(double value);

    void leftSelvedgeWinderAutoChanged(double value);
    void rightSelvedgeWinderAutoChanged(double value);

    void nipRollUpChanged(double value);
    void nipRollDownChanged(double value);

    void leftPressPlateForwardChanged(double value);
    void leftPressPlateBackwardChanged(double value);

    void rightPressPlateForwardChanged(double value);
    void rightPressPlateBackwardChanged(double value);

    void smallCutterInChanged(double value);

    //===== OUTPUT-2 Switch=====
    void webAlignerStartSwitchChanged(int value);
    void unwindingTensionAutoSwitchChanged(int value);
    void unwindingDiameterResetSwitchChanged(int value);

    void smallWinderTensionAutoSwitchChanged(int value);
    void smallWinderDiameterResetSwitchChanged(int value);

    void largeWinderTensionAutoSwitchChanged(int value);
    void largeWinderDiameterResetSwitchChanged(int value);

    void leftSelvedgeWinderAutoSwitchChanged(int value);
    void rightSelvedgeWinderAutoSwitchChanged(int value);

    void nipRollUpSwitchChanged(int value);
    void nipRollDownSwitchChanged(int value);

    void leftPressPlateForwardSwitchChanged(int value);
    void leftPressPlateBackwardSwitchChanged(int value);

    void rightPressPlateForwardSwitchChanged(int value);
    void rightPressPlateBackwardSwitchChanged(int value);
    void smallCutterInSwitchChanged(int value);

    //===== OUTPUT-3 =====
    void largeCutterInChanged(double value);
    void modeSelectChanged(double value);

    void runIndicatorChanged(double value);
    void alarmIndicatorChanged(double value);
    void stopIndicatorChanged(double value);

    void buzzerChanged(double value);
    void smallRollModeSelectChanged(double value);

    void output8Changed(double value);
    void output9Changed(double value);
    void output10Changed(double value);
    void output11Changed(double value);
    void output12Changed(double value);
    void output13Changed(double value);
    void output14Changed(double value);
    void output15Changed(double value);
    void output16Changed(double value);
    void output17Changed(double value);

    //===== OUTPUT-3 switch=====
    void largeCutterInSwitchChanged(int value);
    void modeSelectSwitchChanged(int value);

    void runIndicatorSwitchChanged(int value);
    void alarmIndicatorSwitchChanged(int value);
    void stopIndicatorSwitchChanged(int value);

    void buzzerSwitchChanged(int value);
    void smallRollModeSelectSwitchChanged(int value);

    void output8SwitchChanged(int value);
    void output9SwitchChanged(int value);
    void output10SwitchChanged(int value);
    void output11SwitchChanged(int value);
    void output12SwitchChanged(int value);
    void output13SwitchChanged(int value);
    void output14SwitchChanged(int value);
    void output15SwitchChanged(int value);
    void output16SwitchChanged(int value);
    void output17SwitchChanged(int value);


    //===== ANALOG OUTPUT =====
    void analogOutUnwinderMainDriveChanged(double value);
    void analogOutWinderChanged(double value);
    void analogOutCutterChanged(double value);
    void analogOutSelvedgeWinderChanged(double value);

    //%
    void analogOutUnwinderMainDrivePcChanged(double value);
    void analogOutWinderPcChanged(double value);
    void analogOutCutterPcChanged(double value);
    void analogOutSelvedgeWinderPcChanged(double value);

    void modifyAnalogOutUnwinderMainDriveChanged(double value);
    void modifyAnalogOutWinderChanged(double value);
    void modifyAnalogOutCutterChanged(double value);
    void modifyAnalogOutSelvedgeWinderChanged(double value);
    //===== ANALOG OUTPUT switch=====
    void analogOutUnwinderMainDriveSwitchChanged(int value);
    void analogOutWinderSwitchChanged(int value);
    void analogOutCutterSwitchChanged(int value);
    void analogOutSelvedgeWinderSwitchChanged(int value);

    void modifyAnalogOutUnwinderMainDriveSwitchChanged(int value);
    void modifyAnalogOutWinderSwitchChanged(int value);
    void modifyAnalogOutCutterSwitchChanged(int value);
    void modifyAnalogOutSelvedgeWinderSwitchChanged(int value);

    //===== IPC-INPUT =====
    void ipcStartChanged(double value);
    void ipcStopChanged(double value);
    void ipcAlarmResetChanged(double value);

    void mainJogForwardChanged(double value);
    void mainJogReverseChanged(double value);

    void smallWinderJogForwardChanged(double value);
    void smallWinderJogReverseChanged(double value);

    void unwinderJogReverseSelectChanged(double value);
    void unwinderJogStartChanged(double value);

    void winderJogReverseSelectChanged(double value);
    void winderJogStartChanged(double value);

    void leftSelvedgeWinderSelectChanged(double value);
    void rightSelvedgeWinderSelectChanged(double value);
    //===== IPC-INPUT Light=====
    void ipcStartLightChanged(int value);
    void ipcStopLightChanged(int value);
    void ipcAlarmResetLightChanged(int value);

    void mainJogForwardLightChanged(int value);
    void mainJogReverseLightChanged(int value);

    void smallWinderJogForwardLightChanged(int value);
    void smallWinderJogReverseLightChanged(int value);

    void unwinderJogReverseSelectLightChanged(int value);
    void unwinderJogStartLightChanged(int value);

    void winderJogReverseSelectLightChanged(int value);
    void winderJogStartLightChanged(int value);

    void leftSelvedgeWinderSelectLightChanged(int value);
    void rightSelvedgeWinderSelectLightChanged(int value);

    // =====控制介面 Motor =====
    void smallRollMotorChanged(double value);
    void mainDriveMotorChanged(double value);
    void largeRollMotorChanged(double value);
    void wasteRollMotorBChanged(double value);
    void unwindingMotorChanged(double value);
    void edgeAlignMotorChanged(double value);
    void cutterWheelMotorChanged(double value);
    void wasteRollMotorAChanged(double value);

    void unwindingTensionChanged(double value);
    void smallRollTensionChanged(double value);
    void largeRollTensionChanged(double value);

    void pressurePlateChanged(int value);
    void pressureRollerChanged(int value);
    void pressurePlateBackChanged(int value);
    void pressureRollerDownChanged(int value);
    // =====控制介面 Motor switch=====
    void smallRollMotorSwitchChanged(int value);
    void mainDriveMotorSwitchChanged(int value);
    void largeRollMotorSwitchChanged(int value);
    void wasteRollMotorBSwitchChanged(int value);
    void unwindingMotorSwitchChanged(int value);
    void edgeAlignMotorSwitchChanged(int value);
    void cutterWheelMotorSwitchChanged(int value);
    void wasteRollMotorASwitchChanged(int value);

    void unwindingTensionSwitchChanged(int value);
    void smallRollTensionSwitchChanged(int value);
    void largeRollTensionSwitchChanged(int value);



    // ===== cutter=====
    void smallRollCutter1Changed(int value);
    void smallRollCutter2Changed(int value);
    void smallRollCutter3Changed(int value);
    void smallRollCutter4Changed(int value);
    void smallRollCutter5Changed(int value);
    void bigRollCutterChanged(int value);

    // ===== Single Action Mode=====
    void singleActionModeChanged(int value);

private:
    int m_bigRollMode = 1;//默認大捲模式(1大捲模式,0小捲模式)
    int m_restBtn = 0;//主畫面長度reset btn

    int m_metalDetector = 0;
    int m_gratingDetection = 0;
    int m_OppositeSideSignal = 0;

    int m_doorASignal = 0;
    int m_doorBSignal = 0;
    int m_doorCSignal = 0;
    int m_doorDSignal = 0;
    int m_doorESignal = 0;
    int m_doorFSignal = 0;
    int m_doorGSignal = 0;
    int m_doorHSignal = 0;
    int m_doorISignal = 0;

    int m_uvLight = 0;
    int m_whiteLight = 0;
    int m_bottomLight = 0;

    double m_currentLength = 0;
    double m_speed = 0;
    double m_brakingDistance = 0;

    int m_modifycurrentLength = 0;
    int m_modifyspeed = 0;
    double m_modifybrakingDistance = 0;

    double m_modifyUnwindingTension = 0.0;
    double m_modifySmallWinderTensionOver = 0.0;
    double m_modifyLargeWinderTensionOver = 0.0;

    // ===== cutter=====
    int m_smallRollCutter1 = 0;
    int m_smallRollCutter2 = 0;
    int m_smallRollCutter3 = 0;
    int m_smallRollCutter4 = 0;
    int m_smallRollCutter5 = 0;
    int m_bigRollCutter = 0;

    //=====INPUT-1 READ functions =====
    double m_unwinderVfdFreqAlarm = 0.0;
    double m_mainDriveVfdFreqAlarm = 0.0;
    double m_smallWinderVfdFreqAlarm = 0.0;
    double m_largeWinderVfdFreqAlarm = 0.0;
    double m_smallCutterVfdFreqAlarm = 0.0;
    double m_selvedgeFanVfdFreqAlarm = 0.0;

    double m_leftFanOverloadAlarm = 0.0;
    double m_rightFanOverloadAlarm = 0.0;

    double m_largeCutterVfdFreqAlarm = 0.0;
    double m_leftSelvedgeWinderVfdAlarm = 0.0;
    double m_rightSelvedgeWinderVfdAlarm = 0.0;

    double m_webAlignerVfdFreqAlarm = 0.0;

    double m_unwinderPowerLoss = 0.0;
    double m_mainDrivePowerLoss = 0.0;
    double m_smallWinderPowerLoss = 0.0;
    double m_largeWinderPowerLoss = 0.0;
    //input1 Light
    int m_unwinderVfdFreqAlarmLight = 0;
    int m_mainDriveVfdFreqAlarmLight = 0;
    int m_smallWinderVfdFreqAlarmLight = 0;
    int m_largeWinderVfdFreqAlarmLight = 0;
    int m_smallCutterVfdFreqAlarmLight = 0;
    int m_selvedgeFanVfdFreqAlarmLight = 0;

    int m_leftFanOverloadAlarmLight = 0;
    int m_rightFanOverloadAlarmLight = 0;

    int m_largeCutterVfdFreqAlarmLight = 0;
    int m_leftSelvedgeWinderVfdAlarmLight = 0;
    int m_rightSelvedgeWinderVfdAlarmLight = 0;

    int m_webAlignerVfdFreqAlarmLight = 0;

    int m_unwinderPowerLossLight = 0;
    int m_mainDrivePowerLossLight = 0;
    int m_smallWinderPowerLossLight = 0;
    int m_largeWinderPowerLossLight = 0;
    // ===== INPUT-2 Power Loss =====
    double m_smallCutterPowerLoss = 0.0;
    double m_selvedgeFanPowerLoss = 0.0;
    double m_largeCutterPowerLoss = 0.0;
    double m_leftSelvedgeWinderPowerLoss = 0.0;
    double m_rightSelvedgeWinderPowerLoss = 0.0;
    double m_webAlignerPowerLoss = 0.0;

    double m_unwinderDisconnect = 0.0;
    double m_mainDriveDisconnect = 0.0;
    double m_smallWinderDisconnect = 0.0;
    double m_largeWinderDisconnect = 0.0;
    double m_smallCutterDisconnect = 0.0;
    double m_leftFanDisconnect = 0.0;
    double m_rightFanDisconnect = 0.0;
    double m_largeCutterDisconnect = 0.0;
    double m_leftSelvedgeWinderDisconnect = 0.0;
    double m_rightSelvedgeWinderDisconnect = 0.0;

    // ===== INPUT-2 Power Loss Light=====
    int m_smallCutterPowerLossLight = 0;
    int m_selvedgeFanPowerLossLight = 0;
    int m_largeCutterPowerLossLight = 0;
    int m_leftSelvedgeWinderPowerLossLight = 0;
    int m_rightSelvedgeWinderPowerLossLight = 0;
    int m_webAlignerPowerLossLight = 0;

    int m_unwinderDisconnectLight = 0;
    int m_mainDriveDisconnectLight = 0;
    int m_smallWinderDisconnectLight = 0;
    int m_largeWinderDisconnectLight = 0;
    int m_smallCutterDisconnectLight = 0;
    int m_leftFanDisconnectLight = 0;
    int m_rightFanDisconnectLight = 0;
    int m_largeCutterDisconnectLight = 0;
    int m_leftSelvedgeWinderDisconnectLight = 0;
    int m_rightSelvedgeWinderDisconnectLight = 0;

    // ===== INPUT-3 =====
    double m_webAlignerDisconnect = 0.0;

    double m_emergencyStop1 = 0.0;
    double m_emergencyStop2 = 0.0;
    double m_emergencyStop3 = 0.0;
    double m_emergencyStop4 = 0.0;
    double m_emergencyStop5 = 0.0;
    double m_emergencyStop6 = 0.0;
    double m_emergencyStop7 = 0.0;

    double m_mainDriveLeftDoor1Open = 0.0;
    double m_mainDriveLeftDoor2Open = 0.0;
    double m_mainDriveRightDoor3Open = 0.0;
    double m_mainDriveRightDoor4Open = 0.0;

    double m_largeWinderLeftDoor5Open = 0.0;
    double m_largeWinderLeftDoor6Open = 0.0;
    double m_largeWinderRightDoor7Open = 0.0;
    double m_largeWinderRightDoor8Open = 0.0;
    // ===== INPUT-3 light=====
    int m_webAlignerDisconnectLight = 0;
    int m_emergencyStop1Light = 0;
    int m_emergencyStop2Light = 0;
    int m_emergencyStop3Light = 0;
    int m_emergencyStop4Light = 0;
    int m_emergencyStop5Light = 0;
    int m_emergencyStop6Light = 0;
    int m_emergencyStop7Light = 0;

    int m_mainDriveLeftDoor1OpenLight = 0;
    int m_mainDriveLeftDoor2OpenLight = 0;
    int m_mainDriveRightDoor3OpenLight = 0;
    int m_mainDriveRightDoor4OpenLight = 0;

    int m_largeWinderLeftDoor5OpenLight = 0;
    int m_largeWinderLeftDoor6OpenLight = 0;
    int m_largeWinderRightDoor7OpenLight = 0;
    int m_largeWinderRightDoor8OpenLight = 0;

    // =====INPUT-4 Fence Detect =====
    double m_unwindingFenceDetect1 = 0.0;
    double m_unwindingFenceDetect2 = 0.0;
    double m_largeWinderFenceDetect3 = 0.0;
    double m_largeWinderFenceDetect4 = 0.0;

    int m_unwindingFenceDetect1Light = 0;
    int m_unwindingFenceDetect2Light = 0;
    int m_largeWinderFenceDetect3Light = 0;
    int m_largeWinderFenceDetect4Light = 0;
    // =====INPUT-4 Safety Light Curtain =====
    int m_unwindingSafetyLightCurtainAlarm = 0;
    int m_inspectionSafetyLightCurtainAlarm =0;
    int m_largeWinderSafetyLightCurtainAlarm = 0;

    int m_unwindingSafetyLightCurtainAlarmLight = 0;
    int m_inspectionSafetyLightCurtainAlarmLight = 0;
    int m_largeWinderSafetyLightCurtainAlarmLight = 0;

    // =====INPUT-4 Zero Speed Detect =====
    double m_smallWinderZeroSpeedDetect = 0.0;
    double m_largeWinderZeroSpeedDetect = 0.0;

    int m_smallWinderZeroSpeedDetectLight = 0;
    int m_largeWinderZeroSpeedDetectLight = 0;

    // =====INPUT-4 Tension Over =====
    double m_unwindingTensionOver = 0.0;
    double m_smallWinderTensionOver = 0.0;
    double m_largeWinderTensionOver = 0.0;

    int m_unwindingTensionOverLight = 0;
    int m_smallWinderTensionOverLight = 0;
    int m_largeWinderTensionOverLight = 0;

    // =====INPUT-4 Angle Alarm =====
    double m_leftSelvedgeWinderAngleAlarm = 0.0;
    double m_rightSelvedgeWinderAngleAlarm = 0.0;

    int m_leftSelvedgeWinderAngleAlarmLight = 0;
    int m_rightSelvedgeWinderAngleAlarmLight = 0;
    // =====OUTPUT-1 Angle Alarm =====
    double m_vfdAlarmReset = 0.0;

    double m_unwinderForward = 0.0;
    double m_unwinderReverse = 0.0;

    double m_mainDriveForward = 0.0;
    double m_mainDriveReverse = 0.0;

    double m_smallWinderForward = 0.0;
    double m_smallWinderReverse = 0.0;

    double m_largeWinderForward = 0.0;
    double m_largeWinderReverse = 0.0;

    double m_smallCutterStart = 0.0;
    double m_selvedgeFanStart = 0.0;
    double m_largeCutterStart = 0.0;

    double m_leftSelvedgeWinderForward = 0.0;
    double m_leftSelvedgeWinderReverse = 0.0;

    double m_rightSelvedgeWinderForward = 0.0;
    double m_rightSelvedgeWinderReverse = 0.0;
    // =====OUTPUT-1 Angle Alarm switch=====
    int m_vfdAlarmResetSwitch = 0;
    int m_unwinderForwardSwitch = 0;
    int m_unwinderReverseSwitch = 0;
    int m_mainDriveForwardSwitch = 0;
    int m_mainDriveReverseSwitch = 0;
    int m_smallWinderForwardSwitch = 0;
    int m_smallWinderReverseSwitch = 0;
    int m_largeWinderForwardSwitch = 0;
    int m_largeWinderReverseSwitch = 0;
    int m_smallCutterStartSwitch = 0;
    int m_selvedgeFanStartSwitch = 0;
    int m_largeCutterStartSwitch = 0;
    int m_leftSelvedgeWinderForwardSwitch = 0;
    int m_leftSelvedgeWinderReverseSwitch = 0;
    int m_rightSelvedgeWinderForwardSwitch = 0;
    int m_rightSelvedgeWinderReverseSwitch = 0;

    //=====OUTPUT2=====
    double m_webAlignerStart = 0.0;
    double m_unwindingTensionAuto = 0.0;
    double m_unwindingDiameterReset = 0.0;

    double m_smallWinderTensionAuto = 0.0;
    double m_smallWinderDiameterReset = 0.0;

    double m_largeWinderTensionAuto = 0.0;
    double m_largeWinderDiameterReset = 0.0;

    double m_leftSelvedgeWinderAuto = 0.0;
    double m_rightSelvedgeWinderAuto = 0.0;

    double m_nipRollUp = 0.0;
    double m_nipRollDown = 0.0;

    double m_leftPressPlateForward = 0.0;
    double m_leftPressPlateBackward = 0.0;

    double m_rightPressPlateForward = 0.0;
    double m_rightPressPlateBackward = 0.0;

    double m_smallCutterIn = 0.0;
    //=====OUTPUT2 Switch=====
    int m_webAlignerStartSwitch = 0;
    int m_unwindingTensionAutoSwitch = 0;
    int m_unwindingDiameterResetSwitch = 0;

    int m_smallWinderTensionAutoSwitch = 0;
    int m_smallWinderDiameterResetSwitch = 0;

    int m_largeWinderTensionAutoSwitch = 0;
    int m_largeWinderDiameterResetSwitch = 0;

    int m_leftSelvedgeWinderAutoSwitch = 0;
    int m_rightSelvedgeWinderAutoSwitch = 0;

    int m_nipRollUpSwitch = 0;
    int m_nipRollDownSwitch = 0;

    int m_leftPressPlateForwardSwitch = 0;
    int m_leftPressPlateBackwardSwitch = 0;

    int m_rightPressPlateForwardSwitch = 0;
    int m_rightPressPlateBackwardSwitch = 0;

    int m_smallCutterInSwitch = 0;

    //===OUTPUT3=====
    double m_largeCutterIn = 0.0;
    double m_modeSelect = 0.0;

    double m_runIndicator = 0.0;
    double m_alarmIndicator = 0.0;
    double m_stopIndicator = 0.0;

    double m_buzzer = 0.0;
    double m_smallRollModeSelect = 0.0;

    double m_output8 = 0.0;
    double m_output9 = 0.0;
    double m_output10 = 0.0;
    double m_output11 = 0.0;
    double m_output12 = 0.0;
    double m_output13 = 0.0;
    double m_output14 = 0.0;
    double m_output15 = 0.0;
    double m_output16 = 0.0;
    double m_output17 = 0.0;

    //===OUTPUT3 switch=====
    int m_largeCutterInSwitch = 0;
    int m_modeSelectSwitch = 0;

    int m_runIndicatorSwitch = 0;
    int m_alarmIndicatorSwitch = 0;
    int m_stopIndicatorSwitch = 0;

    int m_buzzerSwitch = 0;
    int m_smallRollModeSelectSwitch = 0;

    int output8Switch = 0;
    int output9Switch = 0;
    int output10Switch = 0;
    int output11Switch = 0;
    int output12Switch = 0;
    int output13Switch = 0;
    int output14Switch = 0;
    int output15Switch = 0;
    int output16Switch = 0;
    int output17Switch = 0;

    // ===== ANALOG OUTPUT =====
    double m_analogOutUnwinderMainDrive = 0.0;
    double m_analogOutWinder = 0.0;
    double m_analogOutCutter = 0.0;
    double m_analogOutSelvedgeWinder = 0.0;

    //%
    double m_analogOutUnwinderMainDrivePc = 1.0;
    double m_analogOutWinderPc = 2.0;
    double m_analogOutCutterPc = 3.0;
    double m_analogOutSelvedgeWinderPc = 4.0;

    double m_modifyAnalogOutUnwinderMainDrive = 0.0;
    double m_modifyAnalogOutWinder = 0.0;
    double m_modifyAnalogOutCutter = 0.0;
    double m_modifyAnalogOutSelvedgeWinder = 0.0;
    // ===== ANALOG OUTPUT switch=====
    int m_analogOutUnwinderMainDriveSwitch = 0;
    int m_analogOutWinderSwitch = 0;
    int m_analogOutCutterSwitch = 0;
    int m_analogOutSelvedgeWinderSwitch = 0;

    int m_modifyAnalogOutUnwinderMainDriveSwitch = 0;
    int m_modifyAnalogOutWinderSwitch = 0;
    int m_modifyAnalogOutCutterSwitch = 0;
    int m_modifyAnalogOutSelvedgeWinderSwitch = 0;


    // ===== IPC INPUT =====
    double m_ipcStart = 0.0;
    double m_ipcStop = 0.0;
    double m_ipcAlarmReset = 0.0;

    double m_mainJogForward = 0.0;
    double m_mainJogReverse = 0.0;

    double m_smallWinderJogForward = 0.0;
    double m_smallWinderJogReverse = 0.0;

    double m_unwinderJogReverseSelect = 0.0;
    double m_unwinderJogStart = 0.0;

    double m_winderJogReverseSelect = 0.0;
    double m_winderJogStart = 0.0;

    double m_leftSelvedgeWinderSelect = 0.0;
    double m_rightSelvedgeWinderSelect = 0.0;
    // ===== IPC INPUT light=====
    int m_ipcStartLight = 0;
    int m_ipcStopLight = 0;
    int m_ipcAlarmResetLight = 0;

    int m_mainJogForwardLight = 0;
    int m_mainJogReverseLight = 0;

    int m_smallWinderJogForwardLight = 0;
    int m_smallWinderJogReverseLight = 0;

    int m_unwinderJogReverseSelectLight = 0;
    int m_unwinderJogStartLight = 0;

    int m_winderJogReverseSelectLight = 0;
    int m_winderJogStartLight = 0;

    int m_leftSelvedgeWinderSelectLight = 0;
    int m_rightSelvedgeWinderSelectLight = 0;

    // ===== 控制介面 =====
    double m_smallRollMotor = 0.0;
    double m_mainDriveMotor = 0.0;
    double m_largeRollMotor = 0.0;
    double m_wasteRollMotorB = 0.0;
    double m_unwindingMotor = 0.0;
    double m_edgeAlignMotor = 0.0;
    double m_cutterWheelMotor = 0.0;
    double m_wasteRollMotorA = 0.0;

    double m_unwindingTension = 0.0;
    double m_smallRollTension = 0.0;
    double m_largeRollTension = 0.0;
    //壓板
    int m_pressurePlate = 0;
    //壓輪
    int m_pressureRoller = 0;
    //壓板
    int m_pressurePlateBack = 0;
    //壓輪
    int m_pressureRollerDown = 0;
    // ===== 控制介面 switch=====
    int m_smallRollMotorSwitch = 0;
    int m_mainDriveMotorSwitch = 0;
    int m_largeRollMotorSwitch = 0;
    int m_wasteRollMotorBSwitch = 0;
    int m_unwindingMotorSwitch = 0;
    int m_edgeAlignMotorSwitch = 0;
    int m_cutterWheelMotorSwitch = 0;
    int m_wasteRollMotorASwitch = 0;

    int m_unwindingTensionSwitch = 0;
    int m_smallRollTensionSwitch = 0;
    int m_largeRollTensionSwitch = 0;

    // ===== Single Action Mode=====
    int m_singleActionMode = 0;

};


