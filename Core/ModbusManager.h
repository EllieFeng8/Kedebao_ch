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
    void IpcStop();  //1
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
    bool m_lastRunningStatus = false;
    bool m_lastAlarmStatus = false;
    bool m_lastLightStatus = false;
    bool m_LeftSelvedgeWinderSelect = false;
    bool m_RightSelvedgeWinderSelect = false;
    bool m_WinderJogReverseSelect = false;
    bool m_UnwinderJogReverseSelect = false;
    QVector<double> stopSpeed = { 0,0,0,0 };
    int currentOutput = 0;    // 目前輸出
    int targetOutput = 0;     // 設定的輸出值
    int stepSize = 50;        // 每次增加
    QTimer* rampTimer;
    bool big_Alarm = false;
    bool small_Alarm = false;
    bool hasAlarmFunc(const QVector<quint16> v)
    {
        bool hasAlarm = false;
        small_Alarm = false;
        big_Alarm = false;
        if (v[0] == 1) { 
            emit ErrMsg(QString::fromLocal8Bit("放捲變頻異常"));
            //qDebug() << "alarm 0";
            big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true; }
        if (v[1] == 1) { 
            emit ErrMsg(QString::fromLocal8Bit("主傳變頻異常"));
            //qDebug() << "alarm 1";
            big_Alarm = true;
            small_Alarm = true; 
            hasAlarm = true;}
        if (v[2] == 1) {
            emit ErrMsg(QString::fromLocal8Bit("小收卷變頻異常"));
            //qDebug() << "alarm 2";
            //big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;}
        if (v[3] == 1) { 
            emit ErrMsg(QString::fromLocal8Bit("大收卷變頻異常"));
            big_Alarm = true;
            //small_Alarm = true;
            hasAlarm = true;}
        //qDebug() << "alarm 3";
        if (v[4] == 1) {

            //qDebug() << "alarm 4";
            emit ErrMsg(QString::fromLocal8Bit("小卷切刀輪變頻異常"));
            //big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;}
        if (v[5] == 1) { 
            //qDebug() << "alarm 5";
            emit ErrMsg(QString::fromLocal8Bit("耳料抽風變頻異常"));
            //big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        if (v[6] == 1) { 
            //qDebug() << "alarm 6";
            emit ErrMsg(QString::fromLocal8Bit("左側抽風過載"));
            //big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        if (v[7] == 1) {
            //qDebug() << "alarm 7";
            emit ErrMsg(QString::fromLocal8Bit("右側抽風過載"));
            //big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        if (v[8] == 1) { 
            //qDebug() << "alarm 8";
            emit ErrMsg(QString::fromLocal8Bit("大捲切刀輪變頻異常"));
            big_Alarm = true;
            //small_Alarm = true;
            hasAlarm = true;
        }
        if (v[9] == 1) { 
            //qDebug() << "alarm 9";
            emit ErrMsg(QString::fromLocal8Bit("右側耳料變頻異常"));
            big_Alarm = true;
            //small_Alarm = true;
            hasAlarm = true;
        }
        if (v[10] == 1) { 
            //qDebug() << "alarm 10";
            emit ErrMsg(QString::fromLocal8Bit("左側耳料變頻異常"));
            big_Alarm = true;
            //small_Alarm = true;
            hasAlarm = true;
        }
        if (v[11] == 1) { 
            //qDebug() << "alarm 11";
            emit ErrMsg(QString::fromLocal8Bit("對邊機變頻異常"));
            big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        if (v[12] == 1) {
            //qDebug() << "alarm 12";
            emit ErrMsg(QString::fromLocal8Bit("放捲軸電源檢出"));
            big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        if (v[13] == 1) { 
            //qDebug() << "alarm 13";
            emit ErrMsg(QString::fromLocal8Bit("主傳電源檢出"));
            big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        if (v[14] == 1) { 
            //qDebug() << "alarm 14";
            emit ErrMsg(QString::fromLocal8Bit("小收卷電源檢出"));
            //big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        if (v[15] == 1) { 
            //qDebug() << "alarm 15";
            emit ErrMsg(QString::fromLocal8Bit("大收卷電源檢出"));
            big_Alarm = true;
            //small_Alarm = true;
            hasAlarm = true;
        }
        if (v[16] == 1) { 
            //qDebug() << "alarm 16";
            emit ErrMsg(QString::fromLocal8Bit("小捲切刀輪電源檢出"));
            //big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        if (v[17] == 1) { 
            //qDebug() << "alarm 17";
            emit ErrMsg(QString::fromLocal8Bit("耳料抽風電源檢出"));
            //big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        if (v[18] == 1) { 
            //qDebug() << "alarm 18";
            emit ErrMsg(QString::fromLocal8Bit("大捲切刀輪電源檢出"));
            big_Alarm = true;
            //small_Alarm = true;
            hasAlarm = true;
        }
        if (v[19] == 1) { 
            //qDebug() << "alarm 19";
            emit ErrMsg(QString::fromLocal8Bit("左耳料收卷電源檢出"));
            big_Alarm = true;
            //small_Alarm = true;
            hasAlarm = true;
        }
        if (v[20] == 1) { 
            //qDebug() << "alarm 20";
            emit ErrMsg(QString::fromLocal8Bit("右耳料收卷電源檢出"));
            big_Alarm = true;
            //small_Alarm = true;
            hasAlarm = true;
        }
        if (v[21] == 1) { 
            //qDebug() << "alarm 21";
            emit ErrMsg(QString::fromLocal8Bit("對邊機電源檢出"));
            big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        if (v[22] == 1) { 
            //qDebug() << "alarm 22";
            emit ErrMsg(QString::fromLocal8Bit("放捲軸切斷開關檢出"));
            //big_Alarm = true;
            //small_Alarm = true;
            hasAlarm = true;
        }
        if (v[23] == 1) { 
            //qDebug() << "alarm 23";
            emit ErrMsg(QString::fromLocal8Bit("主傳切斷開關檢出"));
            big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        if (v[24] == 1) { 
            //qDebug() << "alarm 24";
            emit ErrMsg(QString::fromLocal8Bit("小收卷切斷開關檢出"));
            //big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        if (v[25] == 1) { 
            //qDebug() << "alarm 25";
            emit ErrMsg(QString::fromLocal8Bit("大收卷切斷開關檢出"));
            big_Alarm = true;
            //small_Alarm = true;
            hasAlarm = true;
        }
        if (v[26] == 1) 
        {
            //qDebug() << "alarm 26";
            emit ErrMsg(QString::fromLocal8Bit("小卷切刀輪切斷開關檢出"));
            //big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        if (v[27] == 1) {
            //qDebug() << "alarm 27";
            emit ErrMsg(QString::fromLocal8Bit("左側抽風切斷開關檢出"));
            //big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        if (v[28] == 1) { 
            //qDebug() << "alarm 28";
            emit ErrMsg(QString::fromLocal8Bit("右側抽風切斷開關檢出"));
            //big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        if (v[29] == 1) {
            //qDebug() << "alarm 29";
            emit ErrMsg(QString::fromLocal8Bit("大卷切刀輪切斷開關檢出"));
            big_Alarm = true;
            //small_Alarm = true;
            hasAlarm = true;
        }
        if (v[30] == 1) {
            //qDebug() << "alarm 30";
            emit ErrMsg(QString::fromLocal8Bit("左側耳料收卷切斷開關檢出"));
            big_Alarm = true;
            //small_Alarm = true;
            hasAlarm = true;
        }
        if (v[31] == 1) { 
            //qDebug() << "alarm 31";
            emit ErrMsg(QString::fromLocal8Bit("右側耳料收卷切斷開關檢出"));
            big_Alarm = true;
            //small_Alarm = true;
            hasAlarm = true;
        }
        if (v[32] == 1) {
            //qDebug() << "alarm 32";
            emit ErrMsg(QString::fromLocal8Bit("對邊機切斷開關檢出"));
            big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        if (v[33] == 0) { 
            emit ErrMsg(QString::fromLocal8Bit("STOP-1"));
            big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        //if (v[34] == 0) { 
        //    emit ErrMsg(QString::fromLocal8Bit("STOP-2"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[35] == 0) {
        //    emit ErrMsg(QString::fromLocal8Bit("STOP-3"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[36] == 0) { 
        //    emit ErrMsg(QString::fromLocal8Bit("STOP-4"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        if (v[37] == 0) { 
            emit ErrMsg(QString::fromLocal8Bit("STOP-5"));
            big_Alarm = true;
            small_Alarm = true;
            hasAlarm = true;
        }
        //if (v[38] == 0) {
        //    emit ErrMsg(QString::fromLocal8Bit("STOP-6"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[39] == 0) {
        //    emit ErrMsg(QString::fromLocal8Bit("STOP-7"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[40] == 1) {
        //    emit ErrMsg(QString::fromLocal8Bit("門1"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[41] == 1) { 
        //    emit ErrMsg(QString::fromLocal8Bit("門2"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[42] == 1) { 
        //    emit ErrMsg(QString::fromLocal8Bit("門3"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[43] == 1) { 
        //    emit ErrMsg(QString::fromLocal8Bit("門4"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[44] == 1) { 
        //    emit ErrMsg(QString::fromLocal8Bit("門5"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[45] == 1) { 
        //    emit ErrMsg(QString::fromLocal8Bit("門6"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[46] == 1) { 
        //    emit ErrMsg(QString::fromLocal8Bit("門7"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[47] == 1) { 
        //    emit ErrMsg(QString::fromLocal8Bit("門8"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[48] == 0) { 
        //    emit ErrMsg(QString::fromLocal8Bit("放捲圍籬-1"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[49] == 0) {
        //    emit ErrMsg(QString::fromLocal8Bit("放捲圍籬-2"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[50] == 0) { 
        //    emit ErrMsg(QString::fromLocal8Bit("大捲圍籬-3"));
        //    big_Alarm = true;
        //    //small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[51] == 0) {
        //    emit ErrMsg(QString::fromLocal8Bit("大捲圍籬-4"));
        //    big_Alarm = true;
        //    //small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[52] == 0) { 
        //    emit ErrMsg(QString::fromLocal8Bit("放捲光柵"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[53] == 0) { 
        //    emit ErrMsg(QString::fromLocal8Bit("小卷光柵"));
        //    //big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[54] == 0) { 
        //    emit ErrMsg(QString::fromLocal8Bit("大捲光柵"));
        //    big_Alarm = true;
        //    //small_Alarm = true;
        //    hasAlarm = true;
        //}
        if (v[55] == 1) { 
            emit ErrMsg(QString::fromLocal8Bit("小收卷零速檢出"));
            //big_Alarm = true;
            //small_Alarm = true;
            //hasAlarm = true;
        }
        if (v[56] == 1) {
            emit ErrMsg(QString::fromLocal8Bit("大收卷零速檢出"));
            //big_Alarm = true;
            //small_Alarm = true;
            //hasAlarm = true;
        }
        //if (v[57] == 1) { 
        //    emit ErrMsg(QString::fromLocal8Bit("放捲張力過大"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[58] == 1) { 
        //    emit ErrMsg(QString::fromLocal8Bit("小捲張力過大"));
        //    //big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        //if (v[59] == 1) {
        //    emit ErrMsg(QString::fromLocal8Bit("大捲張力過大"));
        //    big_Alarm = true;
        //    hasAlarm = true;
        //}
        if (v[60] == 1) {
            emit ErrMsg(QString::fromLocal8Bit("左耳料角度異常"));
            big_Alarm = true;
            hasAlarm = true;
        }
        if (v[61] == 1) { 
            emit ErrMsg(QString::fromLocal8Bit("右耳料角度異常"));
            big_Alarm = true;
            hasAlarm = true;
        }
        //if (v[62] == 1) {
        //    emit ErrMsg(QString::fromLocal8Bit("62"));
        //    big_Alarm = true;
        //    small_Alarm = true;
        //    hasAlarm = true;
        //}
        return hasAlarm;
    }
    bool isRunning(const QVector<quint16> v)
    {
        // 安全檢查：確保向量長度至少達到索引 80 (即 size 至少為 81)
        if (v.size() <= 80) {
            return false;
        }

        // 判斷 v[65] 到 v[80] 是否有任一數值不為 0
        for (int i = 65; i <= 80; ++i) {
            if (v[i] != 0) {
                return true; // 只要發現一個是 true (非 0)，就回傳運轉中
            }
        }

        return false; // 全部都是 0，代表停止
    }
};