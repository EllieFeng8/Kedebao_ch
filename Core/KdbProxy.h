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

    Q_PROPERTY(int uvLight READ getUvLight NOTIFY uvLightChanged)
    Q_PROPERTY(int whiteLight READ getWhiteLight NOTIFY whiteLightChanged)
    Q_PROPERTY(int bottomLight READ getBottomLight NOTIFY bottomLightChanged)

    Q_PROPERTY(double currentLength READ getCurrentLength NOTIFY currentLengthChanged)
    Q_PROPERTY(double speed READ getSpeed NOTIFY speedChanged)
    Q_PROPERTY(double brakingDistance READ getBrakingDistance NOTIFY brakingDistanceChanged)

    Q_PROPERTY(double modifyCurrentLength READ getModifyCurrentLength WRITE setModifyCurrentLength NOTIFY modifyCurrentLengthChanged)
    Q_PROPERTY(double modifySpeed READ getModifySpeed WRITE setModifySpeed NOTIFY modifySpeedChanged)
    Q_PROPERTY(double modifyBrakingDistance READ getModifyBrakingDistance WRITE setModifySpeed NOTIFY modifyBrakingDistanceChanged)


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


    // ===== INPUT-4 Fence Detect =====
    Q_PROPERTY(double unwindingFenceDetect1 READ getUnwindingFenceDetect1 NOTIFY unwindingFenceDetect1Changed)
    Q_PROPERTY(double unwindingFenceDetect2 READ getUnwindingFenceDetect2 NOTIFY unwindingFenceDetect2Changed)
    Q_PROPERTY(double largeWinderFenceDetect3 READ getLargeWinderFenceDetect3 NOTIFY largeWinderFenceDetect3Changed)
    Q_PROPERTY(double largeWinderFenceDetect4 READ getLargeWinderFenceDetect4 NOTIFY largeWinderFenceDetect4Changed)


    // ===== INPUT-4 Safety Light Curtain =====
    Q_PROPERTY(double unwindingSafetyLightCurtainAlarm READ getUnwindingSafetyLightCurtainAlarm NOTIFY unwindingSafetyLightCurtainAlarmChanged)
    Q_PROPERTY(double inspectionSafetyLightCurtainAlarm READ getInspectionSafetyLightCurtainAlarm NOTIFY inspectionSafetyLightCurtainAlarmChanged)
    Q_PROPERTY(double largeWinderSafetyLightCurtainAlarm READ getLargeWinderSafetyLightCurtainAlarm NOTIFY largeWinderSafetyLightCurtainAlarmChanged)


    // ===== INPUT-4 Zero Speed Detect =====
    Q_PROPERTY(double smallWinderZeroSpeedDetect READ getSmallWinderZeroSpeedDetect NOTIFY smallWinderZeroSpeedDetectChanged)
    Q_PROPERTY(double largeWinderZeroSpeedDetect READ getLargeWinderZeroSpeedDetect NOTIFY largeWinderZeroSpeedDetectChanged)


    // ===== INPUT-4 Tension Over =====
    Q_PROPERTY(double unwindingTensionOver READ getUnwindingTensionOver NOTIFY unwindingTensionOverChanged)
    Q_PROPERTY(double smallWinderTensionOver READ getSmallWinderTensionOver NOTIFY smallWinderTensionOverChanged)
    Q_PROPERTY(double largeWinderTensionOver READ getLargeWinderTensionOver NOTIFY largeWinderTensionOverChanged)


    // ===== INPUT-4 Angle Alarm =====
    Q_PROPERTY(double leftSelvedgeWinderAngleAlarm READ getLeftSelvedgeWinderAngleAlarm NOTIFY leftSelvedgeWinderAngleAlarmChanged)
    Q_PROPERTY(double rightSelvedgeWinderAngleAlarm READ getRightSelvedgeWinderAngleAlarm NOTIFY rightSelvedgeWinderAngleAlarmChanged)


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


    // ===== OUTPUT-3 Control =====
    Q_PROPERTY(double largeCutterIn READ getLargeCutterIn WRITE setLargeCutterIn NOTIFY largeCutterInChanged)
    Q_PROPERTY(double modeSelect READ getModeSelect WRITE setModeSelect NOTIFY modeSelectChanged)

    Q_PROPERTY(double runIndicator READ getRunIndicator WRITE setRunIndicator NOTIFY runIndicatorChanged)
    Q_PROPERTY(double alarmIndicator READ getAlarmIndicator WRITE setAlarmIndicator NOTIFY alarmIndicatorChanged)
    Q_PROPERTY(double stopIndicator READ getStopIndicator WRITE setStopIndicator NOTIFY stopIndicatorChanged)

    Q_PROPERTY(double buzzer READ getBuzzer WRITE setBuzzer NOTIFY buzzerChanged)
    Q_PROPERTY(double smallRollModeSelect READ getSmallRollModeSelect WRITE setSmallRollModeSelect NOTIFY smallRollModeSelectChanged)


    // ===== ANALOG OUTPUT =====
    Q_PROPERTY(double analogOutUnwinderMainDrive READ getAnalogOutUnwinderMainDrive WRITE setAnalogOutUnwinderMainDrive NOTIFY analogOutUnwinderMainDriveChanged)
    Q_PROPERTY(double analogOutWinder READ getAnalogOutWinder WRITE setAnalogOutWinder NOTIFY analogOutWinderChanged)
    Q_PROPERTY(double analogOutCutter READ getAnalogOutCutter WRITE setAnalogOutCutter NOTIFY analogOutCutterChanged)
    Q_PROPERTY(double analogOutSelvedgeWinder READ getAnalogOutSelvedgeWinder WRITE setAnalogOutSelvedgeWinder NOTIFY analogOutSelvedgeWinderChanged)


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


public:
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
     Q_INVOKABLE int getWhiteLight() const { return m_whiteLight; }
     Q_INVOKABLE int getBottomLight() const { return m_bottomLight; }

     Q_INVOKABLE double getCurrentLength() const { return m_currentLength; }
     Q_INVOKABLE double getSpeed() const { return m_speed; }
     Q_INVOKABLE double getBrakingDistance() const { return m_brakingDistance;}

     Q_INVOKABLE double getModifyCurrentLength() const { return m_modifycurrentLength; }
     Q_INVOKABLE double getModifySpeed() const { return m_modifyspeed; }
     Q_INVOKABLE double getModifyBrakingDistance() const { return m_modifybrakingDistance;}
     void setModifyCurrentLength(double value){m_modifycurrentLength = value; emit modifyCurrentLengthChanged(m_brakingDistance);};
     void setModifySpeed(double value){m_modifyspeed = value; emit modifySpeedChanged(m_modifyspeed);};
     void setModifyBrakingDistance(double value){m_modifybrakingDistance = value; emit modifyBrakingDistanceChanged(m_modifybrakingDistance);};

     //=====INPUT-1 READ functions =====
     Q_INVOKABLE double getUnwinderVfdFreqAlarm() const { return m_unwinderVfdFreqAlarm; }
     Q_INVOKABLE double getMainDriveVfdFreqAlarm() const { return m_mainDriveVfdFreqAlarm; }
     Q_INVOKABLE double getSmallWinderVfdFreqAlarm() const { return m_smallWinderVfdFreqAlarm; }
     Q_INVOKABLE double getLargeWinderVfdFreqAlarm() const { return m_largeWinderVfdFreqAlarm; }
     Q_INVOKABLE double getSmallCutterVfdFreqAlarm() const { return m_smallCutterVfdFreqAlarm; }
     Q_INVOKABLE double getSelvedgeFanVfdFreqAlarm() const { return m_selvedgeFanVfdFreqAlarm; }

     Q_INVOKABLE double getLeftFanOverloadAlarm() const { return m_leftFanOverloadAlarm; }
     Q_INVOKABLE double getRightFanOverloadAlarm() const { return m_rightFanOverloadAlarm; }

     Q_INVOKABLE double getLargeCutterVfdFreqAlarm() const { return m_largeCutterVfdFreqAlarm; }
     Q_INVOKABLE double getLeftSelvedgeWinderVfdAlarm() const { return m_leftSelvedgeWinderVfdAlarm; }
     Q_INVOKABLE double getRightSelvedgeWinderVfdAlarm() const { return m_rightSelvedgeWinderVfdAlarm; }

     Q_INVOKABLE double getWebAlignerVfdFreqAlarm() const { return m_webAlignerVfdFreqAlarm; }

     Q_INVOKABLE double getUnwinderPowerLoss() const { return m_unwinderPowerLoss; }
     Q_INVOKABLE double getMainDrivePowerLoss() const { return m_mainDrivePowerLoss; }
     Q_INVOKABLE double getSmallWinderPowerLoss() const { return m_smallWinderPowerLoss; }
     Q_INVOKABLE double getLargeWinderPowerLoss() const { return m_largeWinderPowerLoss; }

     //===== INPUT-2 : Power Loss =====
     Q_INVOKABLE double getSmallCutterPowerLoss() const { return m_smallCutterPowerLoss; }
     Q_INVOKABLE double getSelvedgeFanPowerLoss() const { return m_selvedgeFanPowerLoss; }
     Q_INVOKABLE double getLargeCutterPowerLoss() const { return m_largeCutterPowerLoss; }
     Q_INVOKABLE double getLeftSelvedgeWinderPowerLoss() const { return m_leftSelvedgeWinderPowerLoss; }
     Q_INVOKABLE double getRightSelvedgeWinderPowerLoss() const { return m_rightSelvedgeWinderPowerLoss; }
     Q_INVOKABLE double getWebAlignerPowerLoss() const { return m_webAlignerPowerLoss; }

    Q_INVOKABLE double getUnwinderDisconnect() const { return m_unwinderDisconnect; }
    Q_INVOKABLE double getMainDriveDisconnect() const { return m_mainDriveDisconnect; }
    Q_INVOKABLE double getSmallWinderDisconnect() const { return m_smallWinderDisconnect; }
    Q_INVOKABLE double getLargeWinderDisconnect() const { return m_largeWinderDisconnect; }
    Q_INVOKABLE double getSmallCutterDisconnect() const { return m_smallCutterDisconnect; }
    Q_INVOKABLE double getLeftFanDisconnect() const { return m_leftFanDisconnect; }
    Q_INVOKABLE double getRightFanDisconnect() const { return m_rightFanDisconnect; }
    Q_INVOKABLE double getLargeCutterDisconnect() const { return m_largeCutterDisconnect; }
    Q_INVOKABLE double getLeftSelvedgeWinderDisconnect() const { return m_leftSelvedgeWinderDisconnect; }
    Q_INVOKABLE double getRightSelvedgeWinderDisconnect() const { return m_rightSelvedgeWinderDisconnect; }

     // ===== INPUT-3 =====
    Q_INVOKABLE double getWebAlignerDisconnect() const { return m_webAlignerDisconnect; }

    Q_INVOKABLE double getEmergencyStop1() const { return m_emergencyStop1; }
    Q_INVOKABLE double getEmergencyStop2() const { return m_emergencyStop2; }
    Q_INVOKABLE double getEmergencyStop3() const { return m_emergencyStop3; }
    Q_INVOKABLE double getEmergencyStop4() const { return m_emergencyStop4; }
    Q_INVOKABLE double getEmergencyStop5() const { return m_emergencyStop5; }
    Q_INVOKABLE double getEmergencyStop6() const { return m_emergencyStop6; }
    Q_INVOKABLE double getEmergencyStop7() const { return m_emergencyStop7; }

    Q_INVOKABLE double getMainDriveLeftDoor1Open() const { return m_mainDriveLeftDoor1Open; }
    Q_INVOKABLE double getMainDriveLeftDoor2Open() const { return m_mainDriveLeftDoor2Open; }
    Q_INVOKABLE double getMainDriveRightDoor3Open() const { return m_mainDriveRightDoor3Open; }
    Q_INVOKABLE double getMainDriveRightDoor4Open() const { return m_mainDriveRightDoor4Open; }

    Q_INVOKABLE double getLargeWinderLeftDoor5Open() const { return m_largeWinderLeftDoor5Open; }
    Q_INVOKABLE double getLargeWinderLeftDoor6Open() const { return m_largeWinderLeftDoor6Open; }
    Q_INVOKABLE double getLargeWinderRightDoor7Open() const { return m_largeWinderRightDoor7Open; }
    Q_INVOKABLE double getLargeWinderRightDoor8Open() const { return m_largeWinderRightDoor8Open; }

    // =====INPUT-4 Fence Detect =====
    Q_INVOKABLE double getUnwindingFenceDetect1() const { return m_unwindingFenceDetect1; }
    Q_INVOKABLE double getUnwindingFenceDetect2() const { return m_unwindingFenceDetect2; }
    Q_INVOKABLE double getLargeWinderFenceDetect3() const { return m_largeWinderFenceDetect3; }
    Q_INVOKABLE double getLargeWinderFenceDetect4() const { return m_largeWinderFenceDetect4; }

    // =====INPUT-4 Safety Light Curtain =====
    Q_INVOKABLE double getUnwindingSafetyLightCurtainAlarm() const { return m_unwindingSafetyLightCurtainAlarm; }
    Q_INVOKABLE double getInspectionSafetyLightCurtainAlarm() const { return m_inspectionSafetyLightCurtainAlarm; }
    Q_INVOKABLE double getLargeWinderSafetyLightCurtainAlarm() const { return m_largeWinderSafetyLightCurtainAlarm; }

    // =====INPUT-4 Zero Speed Detect =====
    Q_INVOKABLE double getSmallWinderZeroSpeedDetect() const { return m_smallWinderZeroSpeedDetect; }
    Q_INVOKABLE double getLargeWinderZeroSpeedDetect() const { return m_largeWinderZeroSpeedDetect; }

    // =====INPUT-4 Tension Over =====
    Q_INVOKABLE double getUnwindingTensionOver() const { return m_unwindingTensionOver; }
    Q_INVOKABLE double getSmallWinderTensionOver() const { return m_smallWinderTensionOver; }
    Q_INVOKABLE double getLargeWinderTensionOver() const { return m_largeWinderTensionOver; }

    // =====INPUT-4 Angle Alarm =====
    Q_INVOKABLE double getLeftSelvedgeWinderAngleAlarm() const { return m_leftSelvedgeWinderAngleAlarm; }
    Q_INVOKABLE double getRightSelvedgeWinderAngleAlarm() const { return m_rightSelvedgeWinderAngleAlarm; }

    //===== OUTPUT-1 READ =====
    // =====OUTPUT-1 Alarm Reset =====
    Q_INVOKABLE double getVfdAlarmReset() const { return m_vfdAlarmReset; }
    void setVfdAlarmReset(double value)
    {
        if (m_vfdAlarmReset == value)
            return;
        m_vfdAlarmReset = value;
        emit vfdAlarmResetChanged(m_vfdAlarmReset);
    }

    // =====OUTPUT-1 Unwinder =====
    Q_INVOKABLE double getUnwinderForward() const { return m_unwinderForward; }
    void setUnwinderForward(double value)
    {
        if (m_unwinderForward == value)
            return;
        m_unwinderForward = value;
        emit unwinderForwardChanged(m_unwinderForward);
    }

    Q_INVOKABLE double getUnwinderReverse() const { return m_unwinderReverse; }
    void setUnwinderReverse(double value)
    {
        if (m_unwinderReverse == value)
            return;
        m_unwinderReverse = value;
        emit unwinderReverseChanged(m_unwinderReverse);
    }

    // =====OUTPUT-1 Main Drive =====
    Q_INVOKABLE double getMainDriveForward() const { return m_mainDriveForward; }
    void setMainDriveForward(double value)
    {
        if (m_mainDriveForward == value)
            return;
        m_mainDriveForward = value;
        emit mainDriveForwardChanged(m_mainDriveForward);
    }

    Q_INVOKABLE double getMainDriveReverse() const { return m_mainDriveReverse; }
    void setMainDriveReverse(double value)
    {
        if (m_mainDriveReverse == value)
            return;
        m_mainDriveReverse = value;
        emit mainDriveReverseChanged(m_mainDriveReverse);
    }

    // =====OUTPUT-1 Small Winder =====
    Q_INVOKABLE double getSmallWinderForward() const { return m_smallWinderForward; }
    void setSmallWinderForward(double value)
    {
        if (m_smallWinderForward == value)
            return;
        m_smallWinderForward = value;
        emit smallWinderForwardChanged(m_smallWinderForward);
    }

    Q_INVOKABLE double getSmallWinderReverse() const { return m_smallWinderReverse; }
    void setSmallWinderReverse(double value)
    {
        if (m_smallWinderReverse == value)
            return;
        m_smallWinderReverse = value;
        emit smallWinderReverseChanged(m_smallWinderReverse);
    }

    // =====OUTPUT-1 Large Winder =====
    Q_INVOKABLE double getLargeWinderForward() const { return m_largeWinderForward; }
    void setLargeWinderForward(double value)
    {
        if (m_largeWinderForward == value)
            return;
        m_largeWinderForward = value;
        emit largeWinderForwardChanged(m_largeWinderForward);
    }

    Q_INVOKABLE double getLargeWinderReverse() const { return m_largeWinderReverse; }
    void setLargeWinderReverse(double value)
    {
        if (m_largeWinderReverse == value)
            return;
        m_largeWinderReverse = value;
        emit largeWinderReverseChanged(m_largeWinderReverse);
    }

    // =====OUTPUT-1 Cutter / Fan =====
    Q_INVOKABLE double getSmallCutterStart() const { return m_smallCutterStart; }
    void setSmallCutterStart(double value)
    {
        if (m_smallCutterStart == value)
            return;
        m_smallCutterStart = value;
        emit smallCutterStartChanged(m_smallCutterStart);
    }

    Q_INVOKABLE double getSelvedgeFanStart() const { return m_selvedgeFanStart; }
    void setSelvedgeFanStart(double value)
    {
        if (m_selvedgeFanStart == value)
            return;
        m_selvedgeFanStart = value;
        emit selvedgeFanStartChanged(m_selvedgeFanStart);
    }

    Q_INVOKABLE double getLargeCutterStart() const { return m_largeCutterStart; }
    void setLargeCutterStart(double value)
    {
        if (m_largeCutterStart == value)
            return;
        m_largeCutterStart = value;
        emit largeCutterStartChanged(m_largeCutterStart);
    }

    // =====OUTPUT-1 Selvedge Winder =====
    Q_INVOKABLE double getLeftSelvedgeWinderForward() const { return m_leftSelvedgeWinderForward; }
    void setLeftSelvedgeWinderForward(double value)
    {
        if (m_leftSelvedgeWinderForward == value)
            return;
        m_leftSelvedgeWinderForward = value;
        emit leftSelvedgeWinderForwardChanged(m_leftSelvedgeWinderForward);
    }

    Q_INVOKABLE double getLeftSelvedgeWinderReverse() const { return m_leftSelvedgeWinderReverse; }
    void setLeftSelvedgeWinderReverse(double value)
    {
        if (m_leftSelvedgeWinderReverse == value)
            return;
        m_leftSelvedgeWinderReverse = value;
        emit leftSelvedgeWinderReverseChanged(m_leftSelvedgeWinderReverse);
    }

    Q_INVOKABLE double getRightSelvedgeWinderForward() const { return m_rightSelvedgeWinderForward; }
    void setRightSelvedgeWinderForward(double value)
    {
        if (m_rightSelvedgeWinderForward == value)
            return;
        m_rightSelvedgeWinderForward = value;
        emit rightSelvedgeWinderForwardChanged(m_rightSelvedgeWinderForward);
    }

    Q_INVOKABLE double getRightSelvedgeWinderReverse() const { return m_rightSelvedgeWinderReverse; }
    void setRightSelvedgeWinderReverse(double value)
    {
        if (m_rightSelvedgeWinderReverse == value)
            return;
        m_rightSelvedgeWinderReverse = value;
        emit rightSelvedgeWinderReverseChanged(m_rightSelvedgeWinderReverse);
    }

    // =====OUTPUT2 Web Aligner / Unwinding =====
    Q_INVOKABLE double getWebAlignerStart() const { return m_webAlignerStart; }
    void setWebAlignerStart(double value)
    {
        if (m_webAlignerStart == value)
            return;
        m_webAlignerStart = value;
        emit webAlignerStartChanged(m_webAlignerStart);
    }

    Q_INVOKABLE double getUnwindingTensionAuto() const { return m_unwindingTensionAuto; }
    void setUnwindingTensionAuto(double value)
    {
        if (m_unwindingTensionAuto == value)
            return;
        m_unwindingTensionAuto = value;
        emit unwindingTensionAutoChanged(m_unwindingTensionAuto);
    }

    Q_INVOKABLE double getUnwindingDiameterReset() const { return m_unwindingDiameterReset; }
    void setUnwindingDiameterReset(double value)
    {
        if (m_unwindingDiameterReset == value)
            return;
        m_unwindingDiameterReset = value;
        emit unwindingDiameterResetChanged(m_unwindingDiameterReset);
    }

    // =====OUTPUT2 Small Winder =====
    Q_INVOKABLE double getSmallWinderTensionAuto() const { return m_smallWinderTensionAuto; }
    void setSmallWinderTensionAuto(double value)
    {
        if (m_smallWinderTensionAuto == value)
            return;
        m_smallWinderTensionAuto = value;
        emit smallWinderTensionAutoChanged(m_smallWinderTensionAuto);
    }

    Q_INVOKABLE double getSmallWinderDiameterReset() const { return m_smallWinderDiameterReset; }
    void setSmallWinderDiameterReset(double value)
    {
        if (m_smallWinderDiameterReset == value)
            return;
        m_smallWinderDiameterReset = value;
        emit smallWinderDiameterResetChanged(m_smallWinderDiameterReset);
    }

    // =====OUTPUT2 Large Winder =====
    Q_INVOKABLE double getLargeWinderTensionAuto() const { return m_largeWinderTensionAuto; }
    void setLargeWinderTensionAuto(double value)
    {
        if (m_largeWinderTensionAuto == value)
            return;
        m_largeWinderTensionAuto = value;
        emit largeWinderTensionAutoChanged(m_largeWinderTensionAuto);
    }

    Q_INVOKABLE double getLargeWinderDiameterReset() const { return m_largeWinderDiameterReset; }
    void setLargeWinderDiameterReset(double value)
    {
        if (m_largeWinderDiameterReset == value)
            return;
        m_largeWinderDiameterReset = value;
        emit largeWinderDiameterResetChanged(m_largeWinderDiameterReset);
    }

    // =====OUTPUT2 Selvedge Winder =====
    Q_INVOKABLE double getLeftSelvedgeWinderAuto() const { return m_leftSelvedgeWinderAuto; }
    void setLeftSelvedgeWinderAuto(double value)
    {
        if (m_leftSelvedgeWinderAuto == value)
            return;
        m_leftSelvedgeWinderAuto = value;
        emit leftSelvedgeWinderAutoChanged(m_leftSelvedgeWinderAuto);
    }

    Q_INVOKABLE double getRightSelvedgeWinderAuto() const { return m_rightSelvedgeWinderAuto; }
    void setRightSelvedgeWinderAuto(double value)
    {
        if (m_rightSelvedgeWinderAuto == value)
            return;
        m_rightSelvedgeWinderAuto = value;
        emit rightSelvedgeWinderAutoChanged(m_rightSelvedgeWinderAuto);
    }

    // =====OUTPUT2 Nip Roll =====
    Q_INVOKABLE double getNipRollUp() const { return m_nipRollUp; }
    void setNipRollUp(double value)
    {
        if (m_nipRollUp == value)
            return;
        m_nipRollUp = value;
        emit nipRollUpChanged(m_nipRollUp);
    }

    Q_INVOKABLE double getNipRollDown() const { return m_nipRollDown; }
    void setNipRollDown(double value)
    {
        if (m_nipRollDown == value)
            return;
        m_nipRollDown = value;
        emit nipRollDownChanged(m_nipRollDown);
    }

    // =====OUTPUT2 Press Plate =====
    Q_INVOKABLE double getLeftPressPlateForward() const { return m_leftPressPlateForward; }
    void setLeftPressPlateForward(double value)
    {
        if (m_leftPressPlateForward == value)
            return;
        m_leftPressPlateForward = value;
        emit leftPressPlateForwardChanged(m_leftPressPlateForward);
    }

    Q_INVOKABLE double getLeftPressPlateBackward() const { return m_leftPressPlateBackward; }
    void setLeftPressPlateBackward(double value)
    {
        if (m_leftPressPlateBackward == value)
            return;
        m_leftPressPlateBackward = value;
        emit leftPressPlateBackwardChanged(m_leftPressPlateBackward);
    }

    Q_INVOKABLE double getRightPressPlateForward() const { return m_rightPressPlateForward; }
    void setRightPressPlateForward(double value)
    {
        if (m_rightPressPlateForward == value)
            return;
        m_rightPressPlateForward = value;
        emit rightPressPlateForwardChanged(m_rightPressPlateForward);
    }

    Q_INVOKABLE double getRightPressPlateBackward() const { return m_rightPressPlateBackward; }
    void setRightPressPlateBackward(double value)
    {
        if (m_rightPressPlateBackward == value)
            return;
        m_rightPressPlateBackward = value;
        emit rightPressPlateBackwardChanged(m_rightPressPlateBackward);
    }

    // =====OUTPUT2 Cutter =====
    Q_INVOKABLE double getSmallCutterIn() const { return m_smallCutterIn; }
    void setSmallCutterIn(double value)
    {
        if (m_smallCutterIn == value)
            return;
        m_smallCutterIn = value;
        emit smallCutterInChanged(m_smallCutterIn);
    }

    // =====OUTPUT3 Cutter / Mode =====
    Q_INVOKABLE double getLargeCutterIn() const { return m_largeCutterIn; }
    void setLargeCutterIn(double value)
     {
         if (m_largeCutterIn == value)
             return;
         m_largeCutterIn = value;
         emit largeCutterInChanged(m_largeCutterIn);
     }

    Q_INVOKABLE double getModeSelect() const { return m_modeSelect; }
    void setModeSelect(double value)
     {
         if (m_modeSelect == value)
             return;
         m_modeSelect = value;
         emit modeSelectChanged(m_modeSelect);
     }

    // =====OUTPUT3 Indicator =====
    Q_INVOKABLE double getRunIndicator() const { return m_runIndicator; }
    void setRunIndicator(double value)
     {
         if (m_runIndicator == value)
             return;
         m_runIndicator = value;
         emit runIndicatorChanged(m_runIndicator);
     }

    Q_INVOKABLE double getAlarmIndicator() const { return m_alarmIndicator; }
    void setAlarmIndicator(double value)
     {
         if (m_alarmIndicator == value)
             return;
         m_alarmIndicator = value;
         emit alarmIndicatorChanged(m_alarmIndicator);
     }

    Q_INVOKABLE double getStopIndicator() const { return m_stopIndicator; }
    void setStopIndicator(double value)
     {
         if (m_stopIndicator == value)
             return;
         m_stopIndicator = value;
         emit stopIndicatorChanged(m_stopIndicator);
     }

    // =====OUTPUT3 Buzzer / Mode Select =====
    Q_INVOKABLE double getBuzzer() const { return m_buzzer; }
    void setBuzzer(double value)
     {
         if (m_buzzer == value)
             return;
         m_buzzer = value;
         emit buzzerChanged(m_buzzer);
     }

    Q_INVOKABLE double getSmallRollModeSelect() const { return m_smallRollModeSelect; }
    void setSmallRollModeSelect(double value)
     {
         if (m_smallRollModeSelect == value)
             return;
         m_smallRollModeSelect = value;
         emit smallRollModeSelectChanged(m_smallRollModeSelect);
     }
     // ===== ANALOG OUTPUT READ =====
    Q_INVOKABLE double getAnalogOutUnwinderMainDrive() const
     {
         return m_analogOutUnwinderMainDrive;
     }
    void setAnalogOutUnwinderMainDrive(double value)
     {
         if (m_analogOutUnwinderMainDrive == value)
             return;
         m_analogOutUnwinderMainDrive = value;
         emit analogOutUnwinderMainDriveChanged(m_analogOutUnwinderMainDrive);
     }

    Q_INVOKABLE double getAnalogOutWinder() const
     {
         return m_analogOutWinder;
     }
    void setAnalogOutWinder(double value)
     {
         if (m_analogOutWinder == value)
             return;
         m_analogOutWinder = value;
         emit analogOutWinderChanged(m_analogOutWinder);
     }

    Q_INVOKABLE double getAnalogOutCutter() const
     {
         return m_analogOutCutter;
     }
    void setAnalogOutCutter(double value)
     {
         if (m_analogOutCutter == value)
             return;
         m_analogOutCutter = value;
         emit analogOutCutterChanged(m_analogOutCutter);
     }

    Q_INVOKABLE double getAnalogOutSelvedgeWinder() const
     {
         return m_analogOutSelvedgeWinder;
     }
    void setAnalogOutSelvedgeWinder(double value)
     {
         if (m_analogOutSelvedgeWinder == value)
             return;
         m_analogOutSelvedgeWinder = value;
         emit analogOutSelvedgeWinderChanged(m_analogOutSelvedgeWinder);
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

    // =====控制介面 Motor Control =====
    Q_INVOKABLE double getSmallRollMotor() const { return m_smallRollMotor; }
    void setSmallRollMotor(double value)
    {
        if (m_smallRollMotor == value)
            return;
        m_smallRollMotor = value;
        emit smallRollMotorChanged(m_smallRollMotor);
    }

    Q_INVOKABLE double getMainDriveMotor() const { return m_mainDriveMotor; }
    void setMainDriveMotor(double value)
    {
        if (m_mainDriveMotor == value)
            return;
        m_mainDriveMotor = value;
        emit mainDriveMotorChanged(m_mainDriveMotor);
    }

    Q_INVOKABLE double getLargeRollMotor() const { return m_largeRollMotor; }
    void setLargeRollMotor(double value)
    {
        if (m_largeRollMotor == value)
            return;
        m_largeRollMotor = value;
        emit largeRollMotorChanged(m_largeRollMotor);
    }

    Q_INVOKABLE double getWasteRollMotorB() const { return m_wasteRollMotorB; }
    void setWasteRollMotorB(double value)
    {
        if (m_wasteRollMotorB == value)
            return;
        m_wasteRollMotorB = value;
        emit wasteRollMotorBChanged(m_wasteRollMotorB);
    }

    Q_INVOKABLE double getUnwindingMotor() const { return m_unwindingMotor; }
    void setUnwindingMotor(double value)
    {
        if (m_unwindingMotor == value)
            return;
        m_unwindingMotor = value;
        emit unwindingMotorChanged(m_unwindingMotor);
    }

    Q_INVOKABLE double getEdgeAlignMotor() const { return m_edgeAlignMotor; }
    void setEdgeAlignMotor(double value)
    {
        if (m_edgeAlignMotor == value)
            return;
        m_edgeAlignMotor = value;
        emit edgeAlignMotorChanged(m_edgeAlignMotor);
    }

    Q_INVOKABLE double getCutterWheelMotor() const { return m_cutterWheelMotor; }
    void setCutterWheelMotor(double value)
    {
        if (m_cutterWheelMotor == value)
            return;
        m_cutterWheelMotor = value;
        emit cutterWheelMotorChanged(m_cutterWheelMotor);
    }

    Q_INVOKABLE double getWasteRollMotorA() const { return m_wasteRollMotorA; }
    void setWasteRollMotorA(double value)
    {
        if (m_wasteRollMotorA == value)
            return;
        m_wasteRollMotorA = value;
        emit wasteRollMotorAChanged(m_wasteRollMotorA);
    }

    // =====控制介面 Tension Control =====
    Q_INVOKABLE double getUnwindingTension() const { return m_unwindingTension; }
    void setUnwindingTension(double value)
    {
        if (m_unwindingTension == value)
            return;
        m_unwindingTension = value;
        emit unwindingTensionChanged(m_unwindingTension);
    }

    Q_INVOKABLE double getSmallRollTension() const { return m_smallRollTension; }
    void setSmallRollTension(double value)
    {
        if (m_smallRollTension == value)
            return;
        m_smallRollTension = value;
        emit smallRollTensionChanged(m_smallRollTension);
    }

    Q_INVOKABLE double getLargeRollTension() const { return m_largeRollTension; }
    void setLargeRollTension(double value)
    {
        if (m_largeRollTension == value)
            return;
        m_largeRollTension = value;
        emit largeRollTensionChanged(m_largeRollTension);
    }



    signals:
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

    void modifyCurrentLengthChanged(double value);
    void modifySpeedChanged(double value);
    void modifyBrakingDistanceChanged(double value);


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

    //===== OUTPUT-3 =====
    void largeCutterInChanged(double value);
    void modeSelectChanged(double value);

    void runIndicatorChanged(double value);
    void alarmIndicatorChanged(double value);
    void stopIndicatorChanged(double value);

    void buzzerChanged(double value);
    void smallRollModeSelectChanged(double value);

    //===== ANALOG OUTPUT =====
    void analogOutUnwinderMainDriveChanged(double value);
    void analogOutWinderChanged(double value);
    void analogOutCutterChanged(double value);
    void analogOutSelvedgeWinderChanged(double value);

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



private:
    int m_metalDetector = 0.0;
    int m_gratingDetection = 0.0;
    int m_OppositeSideSignal = 0.0;

    int m_doorASignal = 0.0;
    int m_doorBSignal = 0.0;
    int m_doorCSignal = 0.0;
    int m_doorDSignal = 0.0;
    int m_doorESignal = 0.0;
    int m_doorFSignal = 0.0;
    int m_doorGSignal = 0.0;
    int m_doorHSignal = 0.0;
    int m_doorISignal = 0.0;

    int m_uvLight = 0.0;
    int m_whiteLight = 0.0;
    int m_bottomLight = 0.0;

    double m_currentLength = 2560;
    double m_speed = 60;
    double m_brakingDistance = 10;

    double m_modifycurrentLength = 2560;
    double m_modifyspeed = 60;
    double m_modifybrakingDistance = 10;


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

    // =====INPUT-4 Fence Detect =====
    double m_unwindingFenceDetect1 = 0.0;
    double m_unwindingFenceDetect2 = 0.0;
    double m_largeWinderFenceDetect3 = 0.0;
    double m_largeWinderFenceDetect4 = 0.0;

    // =====INPUT-4 Safety Light Curtain =====
    double m_unwindingSafetyLightCurtainAlarm = 0.0;
    double m_inspectionSafetyLightCurtainAlarm = 0.0;
    double m_largeWinderSafetyLightCurtainAlarm = 0.0;

    // =====INPUT-4 Zero Speed Detect =====
    double m_smallWinderZeroSpeedDetect = 0.0;
    double m_largeWinderZeroSpeedDetect = 0.0;

    // =====INPUT-4 Tension Over =====
    double m_unwindingTensionOver = 0.0;
    double m_smallWinderTensionOver = 0.0;
    double m_largeWinderTensionOver = 0.0;

    // =====INPUT-4 Angle Alarm =====
    double m_leftSelvedgeWinderAngleAlarm = 0.0;
    double m_rightSelvedgeWinderAngleAlarm = 0.0;

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

    //===OUTPUT3=====
    double m_largeCutterIn = 0.0;
    double m_modeSelect = 0.0;

    double m_runIndicator = 0.0;
    double m_alarmIndicator = 0.0;
    double m_stopIndicator = 0.0;

    double m_buzzer = 0.0;
    double m_smallRollModeSelect = 0.0;

    // ===== ANALOG OUTPUT =====
    double m_analogOutUnwinderMainDrive = 0.0;
    double m_analogOutWinder = 0.0;
    double m_analogOutCutter = 0.0;
    double m_analogOutSelvedgeWinder = 0.0;

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
};


