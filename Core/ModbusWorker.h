#pragma once
#include <QObject>
#include <QModbusTcpClient>
#include <QModbusReply>
#include <QTimer>
#include <QMutex>
#include <qdebug>
class ModbusWorker : public QObject
{
    Q_OBJECT
public:
    ModbusWorker(QObject* parent = nullptr);
    ~ModbusWorker()
    {
        qDebug() << "quit woker thread";
        m_running = false;

        if (m_pollTimer && m_pollTimer->isActive())
            m_pollTimer->stop();

        if (m_reconnectTimer && m_reconnectTimer->isActive())
            m_reconnectTimer->stop();


        if (m_client && m_client->state() != QModbusDevice::UnconnectedState)
            m_client->disconnectDevice();

        if (m_client2 && m_client2->state() != QModbusDevice::UnconnectedState)
            m_client2->disconnectDevice();
    }
    void initFlag()
    {
         flag_vfdAlarmReset = false;               //64

         flag_unwinderForward = false;             //65
         flag_unwinderReverse = false;             //66

         flag_mainDriveForward = false;            //67
         flag_mainDriveReverse = false;            //68

         flag_smallWinderForward = false;          //69
         flag_smallWinderReverse = false;          //70

         flag_largeWinderForward = false;          //71
         flag_largeWinderReverse = false;          //72

         flag_smallCutterStart = false;            //73
         flag_selvedgeFanStart = false;            //74
         flag_largeCutterStart = false;            //75

         flag_leftSelvedgeWinderForward = false;   //76
         flag_leftSelvedgeWinderReverse = false;   //77

         flag_rightSelvedgeWinderForward = false;  //78
         flag_rightSelvedgeWinderReverse = false;  //79

        //=====OUTPUT2=====
         flag_webAlignerStart = false;             //80
         flag_unwindingTensionAuto = false;        //81
         flag_unwindingDiameterReset = false;      //82

         flag_smallWinderTensionAuto = false;      //83
         flag_smallWinderDiameterReset = false;    //84

         flag_largeWinderTensionAuto = false;      //85
         flag_largeWinderDiameterReset = false;    //86

         flag_leftSelvedgeWinderAuto = false;  //87
         flag_rightSelvedgeWinderAuto = false; //88

         flag_nipRollUp = false;               //89
         flag_nipRollDown = false;             //90

         flag_leftPressPlateForward = false;   //91
         flag_leftPressPlateBackward = false;  //92

         flag_rightPressPlateForward = false;  //93
         flag_rightPressPlateBackward = false; //94

         flag_IO95 = false;       //95

        //===OUTPUT3=====
         flag_IO96 = false;       //96
         flag_IO97 = false;       //97

         flag_IO98 = false;       //98
         flag_IO99 = false;       //99
         flag_IO100 = false;      //100

         flag_IO101 = false;      //101
         flag_IO102 = false;      //102
    }
    //Output flag 
    bool flag_vfdAlarmReset = false;               //64

    bool flag_unwinderForward = false;             //65
    bool flag_unwinderReverse = false;             //66

    bool flag_mainDriveForward = false;            //67
    bool flag_mainDriveReverse = false;            //68

    bool flag_smallWinderForward = false;          //69
    bool flag_smallWinderReverse = false;          //70

    bool flag_largeWinderForward = false;          //71
    bool flag_largeWinderReverse = false;          //72

    bool flag_smallCutterStart = false;            //73
    bool flag_selvedgeFanStart = false;            //74
    bool flag_largeCutterStart = false;            //75

    bool flag_leftSelvedgeWinderForward = false;   //76
    bool flag_leftSelvedgeWinderReverse = false;   //77

    bool flag_rightSelvedgeWinderForward = false;  //78
    bool flag_rightSelvedgeWinderReverse = false;  //79

    //=====OUTPUT2=====
    bool flag_webAlignerStart = false;             //80
    bool flag_unwindingTensionAuto = false;        //81
    bool flag_unwindingDiameterReset = false;      //82

    bool flag_smallWinderTensionAuto = false;      //83
    bool flag_smallWinderDiameterReset = false;    //84

    bool flag_largeWinderTensionAuto = false;      //85
    bool flag_largeWinderDiameterReset = false;    //86

    bool flag_leftSelvedgeWinderAuto = false;  //87
    bool flag_rightSelvedgeWinderAuto = false; //88

    bool flag_nipRollUp = false;               //89
    bool flag_nipRollDown = false;             //90

    bool flag_leftPressPlateForward = false;   //91
    bool flag_leftPressPlateBackward = false;  //92

    bool flag_rightPressPlateForward = false;  //93
    bool flag_rightPressPlateBackward = false; //94

    bool flag_IO95 = false;        //95

    //===OUTPUT3=====
    bool flag_IO96 = false;        //96
    bool flag_IO97 = false;        //97

    bool flag_IO98 = false;        //98
    bool flag_IO99 = false;        //99
    bool flag_IO100 = false;       //100

    bool flag_IO101 = false;       //101
    bool flag_IO102 = false;       //102
    bool flag_IO103 = false;
    bool flag_IO104 = false;
    bool flag_IO105 = false;
    bool flag_IO106 = false;
    bool flag_IO107 = false;
    bool flag_IO108 = false;
    bool flag_IO109 = false;
    bool flag_IO110 = false;
    bool flag_IO111 = false;
    bool flag_IO112 = false;

    //OUTPUT Value 
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

    double m_IO95 = 0.0;

    //===OUTPUT3=====
    double m_IO96 = 0.0;
    double m_IO97 = 0.0;

    double m_IO98 = 0.0;
    double m_IO99 = 0.0;
    double m_IO100 = 0.0;

    double m_IO101 = 0.0;
    double m_IO102 = 0.0;

    double m_IO103 = 0.0;
    double m_IO104 = 0.0;
    double m_IO105 = 0.0;
    double m_IO106 = 0.0;
    double m_IO107 = 0.0;
    double m_IO108 = 0.0;
    double m_IO109 = 0.0;
    double m_IO110 = 0.0;
    double m_IO111 = 0.0;
    double m_IO112 = 0.0;

    QVector<bool> startAuto = { 1,0,1,0,1,0,1,1 };
    QVector<bool> stopAuto = { 0,0,0,0,0,0,0,0 };


public slots:
    void startWork();
    void stopWork();
    void StartAuto();
    void StopAuto();

private slots:
    void onStateChanged(QModbusDevice::State state);
    void onErrorOccurred(QModbusDevice::Error error);
    void poll();
    void onReply(QModbusReply* reply);
    void onReply2(QModbusReply* reply);

public slots:
    void writeCoils(int startAddress, const QVector<bool>& values);
    void writeSingleCoil(int address, bool value);
    void writeRegister(int startAddress, double values);
    void writeRegisters(int startAddress, QVector<double> values);

    void readRegisters(int startAddress, int count);

    void set_VfdAlarmReset(double value);
    void set_UnwinderForward(double value);
    void set_UnwinderReverse(double value);
    void set_MainDriveForward(double value);
    void set_MainDriveReverse(double value);
    void set_SmallWinderForward(double value);
    void set_SmallWinderReverse(double value);
    void set_LargeWinderForward(double value);
    void set_LargeWinderReverse(double value);
    void set_SmallCutterStart(double value);
    void set_SelvedgeFanStart(double value);
    void set_LargeCutterStart(double value);
    void set_LeftSelvedgeWinderForward(double value);
    void set_LeftSelvedgeWinderReverse(double value);
    void set_RightSelvedgeWinderForward(double value);
    void set_RightSelvedgeWinderReverse(double value);
    void set_WebAlignerStart(double value);
    void set_UnwindingTensionAuto(double value);
    void set_UnwindingDiameterReset_(double value);
    void set_SmallWinderTensionAuto(double value);
    void set_SmallWinderDiameterReset_(double value);
    void set_LargeWinderTensionAuto(double value);
    void set_LargeWinderDiameterReset_(double value);
    void set_LeftSelvedgeWinderAuto(double value);
    void set_RightSelvedgeWinderAuto(double value);
    void set_NipRollUp(double value);
    void set_NipRollDown(double value);
    void set_LeftPressPlateForward(double value);
    void set_LeftPressPlateBackward(double value);
    void set_RightPressPlateForward(double value);
    void set_RightPressPlateBackward(double value);
    void set_IO95(double value);
    void set_IO96(double value);
    void set_IO97(double value);
    void set_IO98(double value);
    void set_IO99(double value);
    void set_IO100(double value);
    void set_IO101(double value);
    void set_IO102(double value);
    void set_IO103(double);
    void set_IO104(double);
    void set_IO105(double);
    void set_IO106(double);
    void set_IO107(double);
    void set_IO108(double);
    void set_IO109(double);
    void set_IO110(double);
    void set_IO111(double);
    void set_IO112(double);

signals:
    void writeDone(int address, bool ok, QString msg);
    void dataReady(QVector<quint16> values);  
    void dataReady2(QVector<quint16> values);   
    void isWorking();
    void errorOccurred(QString msg);           
    void holdingRegisterReady( QVector<quint16> values);
private:
    int m_workerId;
    QString m_ip;
    int m_port;


    QModbusTcpClient* m_client = nullptr;
    QModbusTcpClient* m_client2 = nullptr;
    QTimer* m_pollTimer = nullptr;
    QTimer* m_reconnectTimer = nullptr;

    bool m_running = false;

    QMutex m_lock64;

};