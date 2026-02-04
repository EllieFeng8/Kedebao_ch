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
    void writeSingleCoil( int address, bool value);
    void writeCoils(int startAddress, const QVector<bool>& values);
    void writeRegister56(const double &value);
    void writeRegister57(const double & value);
    void writeRegister58(const double & value);
    void writeRegister59(const double & value);
    void writeRegisters( const QVector<double>& values);


    void readRegisters(int startAddress, int count);

    bool m_alarmActive = false;
    bool m_ModeSelet = false;

    
    bool hasAlarmFunc(const QVector<quint16> v)
    {
        // 不檢查的 input

        static const std::set<int> ignoreBits = { 55, 56, 57, 58, 59};
        bool hasAlarm =false;
        for (int i = 0; i < 64; ++i)
        {
            if (ignoreBits.count(i))
                continue;   // 跳過這些點
            if (v[i])
            {
                hasAlarm = true;
            }
        }
        return hasAlarm;
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
    void LargeCutterIn(double value);//96
    void ModeSelect(double value);//97
    void RunIndicator(double value);//98
    void AlarmIndicator(double value);//99
    void StopIndicator(double value);//100
    void Buzzer(double value);//101
    void SmallRollModeSelect(double value);//102

    //IPC DIO
    void IpcStart(bool v); //0
    void IpcStop(bool v);  //1
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

    void workerError(QString msg);
    void holdingRegisterReady(QVector<quint16> values);
    void workerWriteDone( int address, bool ok, QString msg);
    void Zerospeed01();
    void Zerospeed02();

private:

        QThread* m_thread;
        ModbusWorker* m_worker = nullptr;
        
        bool m_LeftSelvedgeWinderSelect = false;
        bool m_RightSelvedgeWinderSelect = false;
        bool m_WinderJogReverseSelect = false;
        bool m_UnwinderJogReverseSelect = false;

        int currentOutput = 0;    // 目前輸出
        int targetOutput = 0;     // 設定的輸出值
        int stepSize = 50;        // 每次增加
        QTimer* rampTimer;
};