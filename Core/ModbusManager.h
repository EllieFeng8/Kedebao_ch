#pragma once
#include <QObject>
#include <QMap>
#include <QThread>
#include "ModbusWorker.h"
#include <set>
class ModbusManager : public QObject
{
    Q_OBJECT
public:
    explicit ModbusManager(QObject* parent = nullptr);
    ~ModbusManager();

    void createWorker();
    void startAll();
    void stopAll();
    void writeSingleCoil(int address, bool value);
    void writeCoils(int startAddress, const QVector<bool>& values);
    void writeRegister56(const double& value);
    void writeRegister57(const double& value);
    void writeRegister58(const double& value);
    void writeRegister59(const double& value);
    void writeRegisters(const QVector<double>& values);


    void readRegisters(int startAddress, int count);

    bool m_alarmActive = false;
    bool m_ModeSelet = false;


    bool hasAlarmFunc(const QVector<quint16> v)
    {
        if ( /*v[0]==1|| v[1] == 1 || v[2] == 1 || v[3] == 1 || v[4] == 1 ||
            v[5] == 1 || v[6] == 1 || v[7] == 1 || v[8] == 1 || v[9] == 1 ||
            v[10] == 1 || v[11] == 1 || v[12] == 1 || v[13] == 1 || v[14] == 1 ||
            v[15] == 1 || v[16] == 1 || v[17] == 1 || v[18] == 1 || v[19] == 1 ||
            v[20] == 1 || v[21] == 1 || v[22] == 1 || v[23] == 1 || v[24] == 1 ||
            v[25] == 1 || v[26] == 1 || v[27] == 1 || v[28] == 1 || v[29] == 1 ||
            v[30] == 1 || v[31] == 1 || v[32] == 1 || v[33] == 0 || v[34] == 1 ||
            v[35] == 1 || v[36] == 1 || v[37] == 0 || v[38] == 1 || v[39] == 1 ||
            v[40] == 1 || v[41] == 1 || v[42] == 1 || v[43] == 1 || v[44] == 1 ||
            v[45] == 1 || v[46] == 1 || v[47] == 1 || v[48] == 1 || v[49] == 1 ||
            v[50] == 1 || v[51] == 1 || v[52] == 1 || v[53] == 1 || v[54] == 1 ||
            v[55] == 1 || v[56] == 1 || v[57] == 1 || v[58] == 1 || v[59] == 1 ||
            v[60] == 1 || v[61] == 1 )*/
            v[33]==0||v[37]==0||v[57]==0||v[58]==0||v[59]==0)
        {
            return true;
        }

        // 3. 只有當 34 ~ 40 全部都為 1 (或大於 0) 時，才視為正常
        return false;
    }

public slots:
    //void startAuto();
    //void stopAuto();

    void VfdAlarmReset(double value);//64
    void UnwinderForward(double value);//65 
    void UnwinderReverse(double value);//66 
    void MainDriveForward(double value);//67  
    void MainDriveReverse(double value);//68 
    void SmallWinderForward(double value);//69 
    void SmallWinderReverse(double value);//70 
    void LargeWinderForward(double value);//71 
    void LargeWinderReverse(double value);//72 
    void SmallCutterStart(double value);//73 
    void SelvedgeFanStart(double value);//74 
    void LargeCutterStart(double value);//75 
    void LeftSelvedgeWinderForward(double value);//76
    void LeftSelvedgeWinderReverse(double value);//77 
    void RightSelvedgeWinderForward(double value);//78 
    void RightSelvedgeWinderReverse(double value);//79
    void WebAlignerStart(double value);//80
    void UnwindingTensionAuto(double value);//81
    void UnwindingDiameterRe(double value);//82
    void SmallWinderTensionAuto(double value);//83
    void SmallWinderDiameterRe(double value);//84
    void LargeWinderTensionAuto(double value);//85
    void LargeWinderDiameterRe(double value);//86
    void LeftSelvedgeWinderAuto(double value);//87
    void RightSelvedgeWinderAuto(double value);//88/
    void NipRollUp(double value);//89
    void NipRollDown(double value);//90
    void LeftPressPlateForward(double value);//91
    void LeftPressPlateBackward(double value);//92
    void RightPressPlateForward(double value);//93
    void RightPressPlateBackward(double value);//94
    void SmallCutterIn(double value);//95
    void SmallCutter2(double value);//96
    void SmallCutter3(double value);//97
    void SmallCutter4(double value);//98
    void SmallCutter5(double value);//99

    void LargeCutterIn(double value);//100
    void RunIndicator(double value);//101
    void AlarmIndicator(double value);//102
    void StopIndicator(double value);//103
    void Buzzer(double value);//104
    void ModeSelect(double value);//105

    //void SmallRollModeSelect(double value);//105
    //void io103(double value); //106
    //void io104(double value); //107
    //void io105(double value); //108
    void io106(double value); //109
    void io107(double value); //110
    void io108(double value); //111
    void io109(double value); //112
    void io110(double value); //110
    void io111(double value); //111
    void io112(double value); //112
    void PressRoll(double v);
    void PressRollDown(double v);
    void PressPlate(double v);
    void PressPlateBack(double v);
    //IPC DIO
    void IpcStart(bool v); //0
    void IpcStop(double val,bool v);  //1
    //void IpcAlarmRe(bool v);    //2
    //void MainJogForward(bool v);   //3
    //void MainJogReverse(bool v);   //4
    //void SmallWinderJogForward(bool v);    //5
    //void SmallWinderJogReverse(bool v);    //6
    //void UnwinderJogReverseSelect(bool v); //7
    //void UnwinderJogStart(bool v);         //8
    //void WinderJogReverseSelect(bool v);   //9
    //void WinderJogStart(bool v);           //10
    //void LeftSelvedgeWinderSelect(bool v); //11
    //void RightSelvedgeWinderSelect(bool v);//12


signals:
    void workerData(QVector<quint16> v);
    void workerData2(QVector<quint16> v);
    void isWorking();
    void workerError(QString msg);
    void holdingRegisterReady(QVector<quint16> values);
    void workerWriteDone( int address, bool ok, QString msg);
    void Zerospeed01();
    void Zerospeed02();
    void ErrMsg(QString msg);
private:

    QThread* m_thread;
    ModbusWorker* m_worker = nullptr;

    bool m_LeftSelvedgeWinderSelect = false;
    bool m_RightSelvedgeWinderSelect = false;
    bool m_WinderJogReverseSelect = false;
    bool m_UnwinderJogReverseSelect = false;
    QVector<double> stopSpeed = { 0,0,0,0 };
    int currentOutput = 0;    // 目前輸出
    int targetOutput = 0;     // 設定的輸出值
    int stepSize = 50;        // 每次增加
    QTimer* rampTimer;
   /* bool hasAlarmFunc2(const QVector<quint16> v)
    {
        if (v[1] == 1) { emit ErrMsg("放捲變頻異常"); }
        if (v[2] == 1) { emit ErrMsg("2"); }
        if (v[3] == 1) { emit ErrMsg("3"); }
        if (v[4] == 1) { emit ErrMsg("4"); }
        if (v[5] == 1) { emit ErrMsg("5"); }
        if (v[6] == 1) { emit ErrMsg("6"); }
        if (v[7] == 1) { emit ErrMsg("7"); }
        if (v[8] == 1) { emit ErrMsg("8"); }
        if (v[9] == 1) { emit ErrMsg("9"); }
        if (v[10] == 1) { emit ErrMsg("10"); }
        if (v[11] == 1) { emit ErrMsg("11"); }
        if (v[12] == 1) { emit ErrMsg("12"); }
        if (v[13] == 1) { emit ErrMsg("13"); }
        if (v[14] == 1) { emit ErrMsg("14"); }
        if (v[15] == 1) { emit ErrMsg("15"); }
        if (v[16] == 1) { emit ErrMsg("16"); }
        if (v[17] == 1) { emit ErrMsg("17"); }
        if (v[18] == 1) { emit ErrMsg("18"); }
        if (v[19] == 1) { emit ErrMsg("19"); }
        if (v[20] == 1) { emit ErrMsg("20"); }
        if (v[21] == 1) { emit ErrMsg("21"); }
        if (v[22] == 1) { emit ErrMsg("22"); }
        if (v[23] == 1) { emit ErrMsg("23"); }
        if (v[24] == 1) { emit ErrMsg("24"); }
        if (v[25] == 1) { emit ErrMsg("25"); }
        if (v[26] == 1) { emit ErrMsg("26"); }
        if (v[27] == 1) { emit ErrMsg("27"); }
        if (v[28] == 1) { emit ErrMsg("28"); }
        if (v[29] == 1) { emit ErrMsg("29"); }
        if (v[30] == 1) { emit ErrMsg("30"); }
        if (v[31] == 1) { emit ErrMsg("31"); }
        if (v[32] == 1) { emit ErrMsg("32"); }
        if (v[33] == 0) { emit ErrMsg("STOP-1"); }
        if (v[34] == 0) { emit ErrMsg("STOP-2"); }
        if (v[35] == 0) { emit ErrMsg("STOP-3"); }
        if (v[36] == 0) { emit ErrMsg("STOP-4"); }
        if (v[37] == 0) { emit ErrMsg("STOP-5"); }
        if (v[38] == 0) { emit ErrMsg("STOP-6"); }
        if (v[39] == 0) { emit ErrMsg("STOP-7"); }
        if (v[40] == 1) { emit ErrMsg("40"); }
        if (v[41] == 1) { emit ErrMsg("41"); }
        if (v[42] == 1) { emit ErrMsg("42"); }
        if (v[43] == 1) { emit ErrMsg("43"); }
        if (v[44] == 1) { emit ErrMsg("44"); }
        if (v[45] == 1) { emit ErrMsg("45"); }
        if (v[46] == 1) { emit ErrMsg("46"); }
        if (v[47] == 1) { emit ErrMsg("47"); }
        if (v[48] == 0) { emit ErrMsg("48"); }
        if (v[49] == 0) { emit ErrMsg("49"); }
        if (v[50] == 0) { emit ErrMsg("50"); }
        if (v[51] == 0) { emit ErrMsg("51"); }
        if (v[52] == 0) { emit ErrMsg("52"); }
        if (v[53] == 0) { emit ErrMsg("53"); }
        if (v[54] == 0) { emit ErrMsg("54"); }
        if (v[55] == 1) { emit ErrMsg("55"); }
        if (v[56] == 1) { emit ErrMsg("56"); }
        if (v[57] == 1) { emit ErrMsg("57"); }
        if (v[58] == 1) { emit ErrMsg("58"); }
        if (v[59] == 1) { emit ErrMsg("59"); }
        if (v[60] == 1) { emit ErrMsg("60"); }
        if (v[61] == 1) { emit ErrMsg("61"); }
        if (v[62] == 1) { emit ErrMsg("62"); }

    }*/
};