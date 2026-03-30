#include "ModbusWorker.h"
#include <QDebug>
#include <Qvariant>
#include <qeventloop>
ModbusWorker::ModbusWorker( QObject* parent)
    : QObject(parent),
    m_workerId(0),
    m_ip("192.168.1.201"),
    m_port(502)
{
    qDebug() << "created worker ";
    // 只建立 QModbusTcpClient，**不要**在建構子建立 QTimer（以免在主線程）
    m_client = new QModbusTcpClient(this);

    // 監聽 client 的狀態與錯誤（safe: client 在 worker 被 moveToThread 前可以 connect）
    connect(m_client, &QModbusTcpClient::stateChanged,
        this, &ModbusWorker::onStateChanged);
    connect(m_client, &QModbusTcpClient::errorOccurred,
        this, &ModbusWorker::onErrorOccurred);

    m_client2 = new QModbusTcpClient(this);

    // 監聽 client 的狀態與錯誤（safe: client 在 worker 被 moveToThread 前可以 connect）
    connect(m_client2, &QModbusTcpClient::stateChanged,
        this, &ModbusWorker::onStateChanged);
    connect(m_client2, &QModbusTcpClient::errorOccurred,
        this, &ModbusWorker::onErrorOccurred);
}

void ModbusWorker::startWork()
{
    if (m_running)
        return;
    m_running = true;


    if (!m_pollTimer) {

        m_pollTimer = new QTimer(this);
        m_pollTimer->setInterval(30);
        connect(m_pollTimer, &QTimer::timeout, this, &ModbusWorker::poll, Qt::DirectConnection);
        // DirectConnection 因為 timer 與 this 在同一 thread (保障)
    }

    if (!m_reconnectTimer) {
        m_reconnectTimer = new QTimer(this);
        m_reconnectTimer->setInterval(1000);
        m_reconnectTimer->setSingleShot(true);
        connect(m_reconnectTimer, &QTimer::timeout, this, &ModbusWorker::startWork, Qt::QueuedConnection);
    }

    // 設定連線參數
    m_client->setConnectionParameter(QModbusDevice::NetworkAddressParameter, m_ip);
    m_client->setConnectionParameter(QModbusDevice::NetworkPortParameter, m_port);
    m_client->setTimeout(100);
    m_client->setNumberOfRetries(1);
    qDebug() << "connecting to" << m_ip << ":" << m_port;
    m_client2->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "192.168.1.202");
    m_client2->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);
    m_client2->setTimeout(100);
    m_client2->setNumberOfRetries(1);
    qDebug() << "connecting to" << "192.168.1.202" << ":" << "502";

    // 非同步嘗試連線；onStateChanged 會處理 Connected/Unconnected
    m_client->connectDevice(); 
    m_client2->connectDevice();
    emit isWorking();
}

void ModbusWorker::stopWork()
{
    // 先標記停止，停止 timers，然後斷線
    m_running = false;

    if (m_pollTimer && m_pollTimer->isActive())
        m_pollTimer->stop();

    if (m_reconnectTimer && m_reconnectTimer->isActive())
        m_reconnectTimer->stop();

    // 斷線（此 call 會導致 stateChanged -> UnconnectedState）
    if (m_client && m_client->state() != QModbusDevice::UnconnectedState)
        m_client->disconnectDevice();

    if (m_client2 && m_client2->state() != QModbusDevice::UnconnectedState)
        m_client2->disconnectDevice();
    // 注意：reply->deleteLater() 與 parent=this 會確保 reply 隨 this 一起清理
}

void ModbusWorker::onStateChanged(QModbusDevice::State state)
{
    if (state == QModbusDevice::ConnectedState) {
        qDebug() << "Worker" << m_workerId << "connected.";

        if (m_pollTimer && !m_pollTimer->isActive())
            m_pollTimer->start();

        //emit isWorking();
        // 用 info-style 訊息也用 errorOccurred（Manager 可另作處理）
        //emit errorOccurred(QString("Connected"));
        //writeCoils(81, startAuto);
    }
    else if (state == QModbusDevice::UnconnectedState) {
        qDebug() << "Worker" << m_workerId << "disconnected.";

        if (m_pollTimer && m_pollTimer->isActive())
            m_pollTimer->stop();

        if (m_running && m_reconnectTimer)
            m_reconnectTimer->start();
    }
}

void ModbusWorker::onErrorOccurred(QModbusDevice::Error /*error*/)
{
    if (!m_client) return;
    if (m_client->error() == QModbusDevice::NoError) return;
    emit errorOccurred(QString("Modbus error: %1").arg(m_client->errorString()));
}

void ModbusWorker::poll()
{

    if (!m_running) {
        qDebug() << "Worker is not Running";
        return;
    }

    if (!m_client || m_client->state() != QModbusDevice::ConnectedState)
    {
        qDebug() << "m_client is not connect";
        return;
    }
    m_pollTimer->stop();

    if(E_Stop)
    {
        QVector<bool> stop(24, false);
        writeCoils(65, stop);
        writeSingleCoil(102, true);
        E_Stop = false;
    }
    //Flag
    bool f_vfdAlarmReset = false;               //64
    bool f_unwinderForward = false;             //65
    bool f_unwinderReverse = false;             //66
    bool f_mainDriveForward = false;            //67
    bool f_mainDriveReverse = false;            //68
    bool f_smallWinderForward = false;          //69
    bool f_smallWinderReverse = false;          //70
    bool f_largeWinderForward = false;          //71
    bool f_largeWinderReverse = false;          //72
    bool f_smallCutterStart = false;            //73
    bool f_selvedgeFanStart = false;            //74
    bool f_largeCutterStart = false;            //75
    bool f_leftSelvedgeWinderForward = false;   //76
    bool f_leftSelvedgeWinderReverse = false;   //77
    bool f_rightSelvedgeWinderForward = false;  //78
    bool f_rightSelvedgeWinderReverse = false;  //79
    //=====OUTPUT2=====
    bool f_webAlignerStart = false;             //80
    bool f_unwindingTensionAuto = false;        //81
    bool f_unwindingDiameterReset = false;      //82
    bool f_smallWinderTensionAuto = false;      //83
    bool f_smallWinderDiameterReset = false;    //84
    bool f_largeWinderTensionAuto = false;      //85
    bool f_largeWinderDiameterReset = false;    //86
    bool f_leftSelvedgeWinderAuto = false;  //87
    bool f_rightSelvedgeWinderAuto = false; //88
    bool f_nipRollUp = false;               //89
    bool f_nipRollDown = false;             //90
    bool f_leftPressPlateForward = false;   //91
    bool f_leftPressPlateBackward = false;  //92
    bool f_rightPressPlateForward = false;  //93
    bool f_rightPressPlateBackward = false; //94
    bool f_IO95 = false;       //95
    //===OUTPUT3=====
    bool f_IO96 = false;       //96
    bool f_IO97 = false;          //97
    bool f_IO98 = false;        //98
    bool f_IO99 = false;      //99
    bool f_IO100 = false;      //100
    bool f_IO101 = false;              //101
    bool f_IO102 = false; //102
    bool f_IO103 = false;
    bool f_IO104 = false;
    bool f_IO105 = false;
    bool f_IO106 = false;
    bool f_IO107 = false;
    bool f_IO108 = false;
    bool f_IO109 = false;
    bool f_IO110 = false;
    bool f_IO111 = false;
    bool f_IO112 = false;
    //Value  
    bool _vfdAlarmReset = false;               //64
    bool _unwinderForward = false;             //65
    bool _unwinderReverse = false;             //66
    bool _mainDriveForward = false;            //67
    bool _mainDriveReverse = false;            //68
    bool _smallWinderForward = false;          //69
    bool _smallWinderReverse = false;          //70
    bool _largeWinderForward = false;          //71
    bool _largeWinderReverse = false;          //72
    bool _smallCutterStart = false;            //73
    bool _selvedgeFanStart = false;            //74
    bool _largeCutterStart = false;            //75
    bool _leftSelvedgeWinderForward = false;   //76
    bool _leftSelvedgeWinderReverse = false;   //77
    bool _rightSelvedgeWinderForward = false;  //78
    bool _rightSelvedgeWinderReverse = false;  //79
    //=====OUTPUT2=====
    bool _webAlignerStart = false;             //80
    bool _unwindingTensionAuto = false;        //81
    bool _unwindingDiameterReset = false;      //82
    bool _smallWinderTensionAuto = false;      //83
    bool _smallWinderDiameterReset = false;    //84
    bool _largeWinderTensionAuto = false;      //85
    bool _largeWinderDiameterReset = false;    //86
    bool _leftSelvedgeWinderAuto = false;  //87
    bool _rightSelvedgeWinderAuto = false; //88
    bool _nipRollUp = false;               //89
    bool _nipRollDown = false;             //90
    bool _leftPressPlateForward = false;   //91
    bool _leftPressPlateBackward = false;  //92
    bool _rightPressPlateForward = false;  //93
    bool _rightPressPlateBackward = false; //94
    bool _IO95 = false;  //95
    //===OUTPUT3=====
    bool _IO96 = false;  //96
    bool _IO97 = false;  //97
    bool _IO98 = false;  //98
    bool _IO99 = false;  //99
    bool _IO100 = false; //100
    bool _IO101 = false; //101
    bool _IO102 = false; //102
    bool _IO103 = false;
    bool _IO104 = false;
    bool _IO105 = false;
    bool _IO106 = false;
    bool _IO107 = false;
    bool _IO108 = false;
    bool _IO109 = false;
    bool _IO110 = false;
    bool _IO111 = false;
    bool _IO112 = false;
    {
        QMutexLocker locker(&m_lock64);
        if(flag_vfdAlarmReset)
        {
            _vfdAlarmReset = (m_vfdAlarmReset >0.0) ?true:false;
            f_vfdAlarmReset = flag_vfdAlarmReset;
            flag_vfdAlarmReset = false;
        }
        if(flag_unwinderForward)
        {
            _unwinderForward = (m_unwinderForward > 0.0) ? true : false;
            f_unwinderForward = flag_unwinderForward;
            flag_unwinderForward = false;
        }
        if(flag_unwinderReverse)
        {
            _unwinderReverse = (m_unwinderReverse > 0.0) ? true : false;
            f_unwinderReverse = flag_unwinderReverse;
            flag_unwinderReverse = false;
        }
        if(flag_mainDriveForward)
        {
            _mainDriveForward = (m_mainDriveForward > 0.0) ? true : false;
            f_mainDriveForward = flag_mainDriveForward;
            flag_mainDriveForward = false;
        }
        if(flag_mainDriveReverse)
        {
            _mainDriveReverse = (m_mainDriveReverse > 0.0) ? true : false;
            f_mainDriveReverse = flag_mainDriveReverse;
            flag_mainDriveReverse = false;
        }
        if(flag_smallWinderForward)
        {
            _smallWinderForward = (m_smallWinderForward > 0.0) ? true : false;
            f_smallWinderForward = flag_smallWinderForward;
            flag_smallWinderForward = false;
        }
        if(flag_smallWinderReverse)
        {
            _smallWinderReverse = (m_smallWinderReverse > 0.0) ? true : false;
            f_smallWinderReverse = flag_smallWinderReverse;
            flag_smallWinderReverse = false;
        }
        if(flag_largeWinderForward)
        {
            _largeWinderForward = (m_largeWinderForward > 0.0) ? true : false;
            f_largeWinderForward = flag_largeWinderForward;
            flag_largeWinderForward = false;
        }
        if(flag_largeWinderReverse)
        {
            _largeWinderReverse = (m_largeWinderReverse > 0.0) ? true : false;
            f_largeWinderReverse = flag_largeWinderReverse;
            flag_largeWinderReverse = false;
        }
        if(flag_smallCutterStart)
        {
            _smallCutterStart = (m_smallCutterStart > 0.0) ? true : false;
            f_smallCutterStart = flag_smallCutterStart;
            flag_smallCutterStart = false;
        }
        if(flag_selvedgeFanStart)
        {
            _selvedgeFanStart = (m_selvedgeFanStart > 0.0) ? true : false;
            f_selvedgeFanStart = flag_selvedgeFanStart;
            flag_selvedgeFanStart = false;
        }
        if(flag_largeCutterStart)
        {
            _largeCutterStart = (m_largeCutterStart > 0.0) ? true : false;
            f_largeCutterStart = flag_largeCutterStart;
            flag_largeCutterStart = false;
        }
        if(flag_leftSelvedgeWinderForward)
        {
            _leftSelvedgeWinderForward = (m_leftSelvedgeWinderForward > 0.0) ? true : false;
            f_leftSelvedgeWinderForward = flag_leftSelvedgeWinderForward;
            flag_leftSelvedgeWinderForward = false;
        }
        if(flag_leftSelvedgeWinderReverse)
        {
            _leftSelvedgeWinderReverse = (m_leftSelvedgeWinderReverse > 0.0) ? true : false;
            f_leftSelvedgeWinderReverse = flag_leftSelvedgeWinderReverse;
            flag_leftSelvedgeWinderReverse = false;
        }
        if(flag_rightSelvedgeWinderForward)
        {
            _rightSelvedgeWinderForward = (m_rightSelvedgeWinderForward > 0.0) ? true : false;
            f_rightSelvedgeWinderForward = flag_rightSelvedgeWinderForward;
            flag_rightSelvedgeWinderForward = false;
        }
        if(flag_rightSelvedgeWinderReverse)
        {
            _rightSelvedgeWinderReverse = (m_rightSelvedgeWinderReverse > 0.0) ? true : false;
            f_rightSelvedgeWinderReverse = flag_rightSelvedgeWinderReverse;
            flag_rightSelvedgeWinderReverse = false;
        }
        if(flag_webAlignerStart)
        {
            _webAlignerStart = (m_webAlignerStart > 0.0) ? true : false;
            f_webAlignerStart = flag_webAlignerStart;
            flag_webAlignerStart = false;
        }
        if(flag_unwindingTensionAuto)
        {
            _unwindingTensionAuto = (m_unwindingTensionAuto > 0.0) ? true : false;
            f_unwindingTensionAuto = flag_unwindingTensionAuto;
            flag_unwindingTensionAuto = false;
        }
        if(flag_unwindingDiameterReset)
        {
            _unwindingDiameterReset = (m_unwindingDiameterReset > 0.0) ? true : false;
            f_unwindingDiameterReset = flag_unwindingDiameterReset;
            flag_unwindingDiameterReset = false;
        }
        if(flag_smallWinderTensionAuto)
        {
            _smallWinderTensionAuto = (m_smallWinderTensionAuto > 0.0) ? true : false;
            f_smallWinderTensionAuto = flag_smallWinderTensionAuto;
            flag_smallWinderTensionAuto = false;
        }
        if(flag_smallWinderDiameterReset)
        {
            _smallWinderDiameterReset = (m_smallWinderDiameterReset > 0.0) ? true : false;
            f_smallWinderDiameterReset = flag_smallWinderDiameterReset;
            flag_smallWinderDiameterReset = false;
        }
        if(flag_largeWinderTensionAuto)
        {
            _largeWinderTensionAuto = (m_largeWinderTensionAuto > 0.0) ? true : false;
            f_largeWinderTensionAuto = flag_largeWinderTensionAuto;
            flag_largeWinderTensionAuto = false;
        }
        if(flag_largeWinderDiameterReset)
        {
            _largeWinderDiameterReset = (m_largeWinderDiameterReset > 0.0) ? true : false;
            f_largeWinderDiameterReset = flag_largeWinderDiameterReset;
            flag_largeWinderDiameterReset = false;
        }
        if(flag_leftSelvedgeWinderAuto)
        {
            _leftSelvedgeWinderAuto = (m_leftSelvedgeWinderAuto > 0.0) ? true : false;
            f_leftSelvedgeWinderAuto = flag_leftSelvedgeWinderAuto;
            flag_leftSelvedgeWinderAuto = false;
        }
        if(flag_rightSelvedgeWinderAuto)
        {
            _rightSelvedgeWinderAuto = (m_rightSelvedgeWinderAuto > 0.0) ? true : false;
            f_rightSelvedgeWinderAuto = flag_rightSelvedgeWinderAuto;
            flag_rightSelvedgeWinderAuto = false;
        }
        if(flag_nipRollUp)
        {
            _nipRollUp = (m_nipRollUp > 0.0) ? true : false;
            f_nipRollUp = flag_nipRollUp;
            flag_nipRollUp = false;
        }
        if(flag_nipRollDown)
        {
            _nipRollDown = (m_nipRollDown > 0.0) ? true : false;
            f_nipRollDown = flag_nipRollDown;
            flag_nipRollDown = false;
        }
        if(flag_leftPressPlateForward)
        {
            _leftPressPlateForward = (m_leftPressPlateForward > 0.0) ? true : false;
            f_leftPressPlateForward = flag_leftPressPlateForward;
            flag_leftPressPlateForward = false;
        }
        if (flag_leftPressPlateBackward)
        {
            _leftPressPlateBackward = (m_leftPressPlateBackward > 0.0) ? true : false;
            f_leftPressPlateBackward = flag_leftPressPlateBackward;
            flag_leftPressPlateBackward = false;
        }
        if(flag_rightPressPlateForward)
        {
            _rightPressPlateForward = (m_rightPressPlateForward > 0.0) ? true : false;
            f_rightPressPlateForward = flag_rightPressPlateForward;
            flag_rightPressPlateForward = false;
        }
        if(flag_rightPressPlateBackward)
        {
            _rightPressPlateBackward = (m_rightPressPlateBackward > 0.0) ? true : false;
            f_rightPressPlateBackward = flag_rightPressPlateBackward;
            flag_rightPressPlateBackward = false;
        }
        if(flag_IO95)
        {
            _IO95 = (m_IO95 > 0.0) ? true : false;
            f_IO95 = flag_IO95;
            flag_IO95 = false;
        }
        if(flag_IO96)
        {
            _IO96 = (m_IO96 > 0.0) ? true : false;
            f_IO96 = flag_IO96;
            flag_IO96 = false;
        }
        if(flag_IO97)
        {
            _IO97 = (m_IO97 > 0.0) ? true : false;
            f_IO97 = flag_IO97;
            flag_IO97 = false;
        }
        if(flag_IO98)
        {
            _IO98 = (m_IO98 > 0.0) ? true : false;
            f_IO98 = flag_IO98;
            flag_IO98 = false;
        }
        if(flag_IO99)
        {
            _IO99 = (m_IO99 > 0.0) ? true : false;
            f_IO99 = flag_IO99;
            flag_IO99 = false;
        }
        if(flag_IO100)
        {
            _IO100 = (m_IO100 > 0.0) ? true : false;
            f_IO100 = flag_IO100;
            flag_IO100 = false;
        }
        if (flag_IO101)
        {
            _IO101 = (m_IO101 > 0.0) ? true : false;
            f_IO101 = flag_IO101;
            flag_IO101 = false;
        }
        if (flag_IO102) 
        {
            _IO102 = (m_IO102 > 0.0) ? true : false;
            f_IO102 = flag_IO102;
            flag_IO102 = false;
        }
        if (flag_IO103)
        {
            _IO103 = (m_IO103 > 0.0) ? true : false;
            f_IO103 = flag_IO103;
            flag_IO103 = false;
        }
        if (flag_IO104)
        {
            _IO104 = (m_IO104 > 0.0) ? true : false;
            f_IO104 = flag_IO104;
            flag_IO104 = false;
        }
        if (flag_IO105)
        {
            _IO105 = (m_IO105 > 0.0) ? true : false;
            f_IO105 = flag_IO105;
            flag_IO105 = false;
        }
        if (flag_IO106)
        {
            _IO106 = (m_IO106 > 0.0) ? true : false;
            f_IO106 = flag_IO106;
            flag_IO106 = false;
        }
        if (flag_IO107)
        {
            _IO107 = (m_IO107 > 0.0) ? true : false;
            f_IO107 = flag_IO107;
            flag_IO107 = false;
        }
        if (flag_IO108)
        {
            _IO108 = (m_IO108 > 0.0) ? true : false;
            f_IO108 = flag_IO108;
            flag_IO108 = false;
        }
        if (flag_IO109)
        {
            _IO109 = (m_IO109 > 0.0) ? true : false;
            f_IO109 = flag_IO109;
            flag_IO109 = false;
        }
        if (flag_IO110)
        {
            _IO110 = (m_IO110 > 0.0) ? true : false;
            f_IO110 = flag_IO110;
            flag_IO110 = false;
        }
        if (flag_IO111)
        {
            _IO111 = (m_IO111 > 0.0) ? true : false;
            f_IO111 = flag_IO111;
            flag_IO111 = false;
        }
        if (flag_IO112)
        {
            _IO112 = (m_IO112 > 0.0) ? true : false;
            f_IO112 = flag_IO112;
            flag_IO112 = false;
        }
    }

    {
        if (f_vfdAlarmReset)
        {
            writeSingleCoil(64, _vfdAlarmReset);
        }
        if (f_unwinderForward)
        {
            writeSingleCoil(65, _unwinderForward);
        }
        if (f_unwinderReverse)
        {
            writeSingleCoil(66, _unwinderReverse);
        }
        if (f_mainDriveForward)
        {
            writeSingleCoil(67, _mainDriveForward);
        }
        if (f_mainDriveReverse)
        {
            writeSingleCoil(68, _mainDriveReverse);
        }
        if (f_smallWinderForward)
        {
            writeSingleCoil(69, _smallWinderForward);
        }
        if (f_smallWinderReverse)
        {
            writeSingleCoil(70, _smallWinderReverse);
        }
        if (f_largeWinderForward)
        {
            writeSingleCoil(71, _largeWinderForward);
        }
        if (f_largeWinderReverse)
        {
            writeSingleCoil(72, _largeWinderReverse);
        }
        if (f_smallCutterStart)
        {
            writeSingleCoil(73, _smallCutterStart);
        }
        if (f_selvedgeFanStart)
        {
            writeSingleCoil(74, _selvedgeFanStart);
        }
        if (f_largeCutterStart)
        {
            writeSingleCoil(75, _largeCutterStart);
        }
        if (f_leftSelvedgeWinderForward)
        {
            writeSingleCoil(76, _leftSelvedgeWinderForward);
        }
        if (f_leftSelvedgeWinderReverse)
        {
            writeSingleCoil(77, _leftSelvedgeWinderReverse);
        }
        if (f_rightSelvedgeWinderForward)
        {
            writeSingleCoil(78, _rightSelvedgeWinderForward);
        }
        if (f_rightSelvedgeWinderReverse)
        {
            writeSingleCoil(79, _rightSelvedgeWinderReverse);
        }
        if (f_webAlignerStart)
        {
            writeSingleCoil(80, _webAlignerStart);
        }
        if (f_unwindingTensionAuto)
        {
            writeSingleCoil(81, _unwindingTensionAuto);
        }
        if (f_unwindingDiameterReset)
        {
            writeSingleCoil(82, _unwindingDiameterReset);
            QTimer::singleShot(1000, this,
                [this]()
                {
                    writeSingleCoil(82, false);
                });
        }
        if (f_smallWinderTensionAuto)
        {
            writeSingleCoil(83, _smallWinderTensionAuto);
        }
        if (f_smallWinderDiameterReset)
        {
            writeSingleCoil(84, _smallWinderDiameterReset);
        }
        if (f_largeWinderTensionAuto)
        {
            writeSingleCoil(85, _largeWinderTensionAuto);
        }
        if (f_largeWinderDiameterReset)
        {
            writeSingleCoil(86, _largeWinderDiameterReset);
        }
        if (f_leftSelvedgeWinderAuto)
        {
            writeSingleCoil(87, _leftSelvedgeWinderAuto);
        }
        if (f_rightSelvedgeWinderAuto)
        {
            writeSingleCoil(88, _rightSelvedgeWinderAuto);
        }
        if (f_nipRollUp)
        {
            writeSingleCoil(89, _nipRollUp);
        }
        if (f_nipRollDown)
        {
            writeSingleCoil(90, _nipRollDown);
        }
        if (f_leftPressPlateForward)
        {
            writeSingleCoil(91, _leftPressPlateForward);
        }
        if (f_leftPressPlateBackward)
        {
            writeSingleCoil(92, _leftPressPlateBackward);
        }
        if (f_rightPressPlateForward)
        {
            writeSingleCoil(93, _rightPressPlateForward);
        }
        if (f_rightPressPlateBackward)
        {
            writeSingleCoil(94, _rightPressPlateBackward);
        }
        if (f_IO95)
        {
            writeSingleCoil(95, _IO95);//小卷切刀
        }
        if (f_IO96)
        {
            writeSingleCoil(96, _IO96);//小卷切刀2
        }
        if (f_IO97)
        {
            writeSingleCoil(97, _IO97);//小卷切刀3
        }
        if (f_IO98)
        {
            writeSingleCoil(98, _IO98);//小卷切刀4
        }
        if (f_IO99)
        {
            writeSingleCoil(99, _IO99);//小卷切刀5
        }
        if (f_IO100)
        {
            writeSingleCoil(100, _IO100);//大捲切刀
        }
        if (f_IO101)
        {
            writeSingleCoil(101, _IO101);//運轉燈
        }
        if (f_IO102)
        {
            writeSingleCoil(102, _IO102);//異常指示燈
        }
        if (f_IO103)
        {
            writeSingleCoil(103, _IO103);//停止指示燈
        }
        if (f_IO104)
        {
            writeSingleCoil(104, _IO104);//蜂鳴器
        }
        if (f_IO105)
        {
            writeSingleCoil(105, _IO105);//模式選擇
        }
        if (f_IO106)
        {
            writeSingleCoil(106, _IO106);//日光燈
        }
        if (f_IO107)
        {
            writeSingleCoil(107, _IO107);//紫光燈
        }
        if (f_IO108)
        {
            writeSingleCoil(108, _IO108);//下方照明燈
        }
        if (f_IO109)
        {
            writeSingleCoil(109, _IO109);//止退壓輪 進
        }
        if (f_IO110)
        {
            writeSingleCoil(110, _IO110);//止退壓輪 出
        }
        if (f_IO111) //STO 
        {
            writeSingleCoil(111, _IO111);
        }
        if (f_IO112)
        {
            //writeSingleCoil(112, true);
            //QTimer::singleShot(1000, this,
            //    [this]()
            //    {
            //        writeSingleCoil(112, false);
            //    });
        }
        initFlag();
    }

    
    //ADAM-5000(192.168.1.201)

// --- 第一台設備讀取 (Coils 0-112) ---
    QModbusDataUnit unit1(QModbusDataUnit::Coils, 0, 112);
    if (auto* reply = m_client->sendReadRequest(unit1, 1)) {
        QEventLoop loop;
        connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
        loop.exec(); // 等待直到讀取完成

        onReply(reply); // 手動呼叫處理函式
        reply->deleteLater();
    }
    
    // --- 第二台設備讀取 (ADAM-5000, Coils 0-16) ---
    QModbusDataUnit unit2(QModbusDataUnit::Coils, 0, 16);
    if (auto* reply2 = m_client2->sendReadRequest(unit2, 1)) {
        QEventLoop loop;
        connect(reply2, &QModbusReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        // 如果 onReply2 邏輯不同，可另寫 processReply2，
        // 如果邏輯一樣，直接共用 processReply
        onReply2(reply2);
        reply2->deleteLater();
    }
    //Analog output READ
    readRegisters(56, 4);
    if (m_running) {
        m_pollTimer->start();
    }
}

void ModbusWorker::onReply(QModbusReply* reply)
{
    //QModbusReply* reply = qobject_cast<QModbusReply*>(sender());
    if (!reply) return;
    
    if (reply->error() == QModbusDevice::NoError) {
        QVector<quint16> values;
        const QModbusDataUnit unit = reply->result();

            for (int i = 0; i < unit.valueCount(); ++i)
                values.append(unit.value(i));

            emit dataReady(values);
        
    }
    else {
        emit errorOccurred(QString("Reply error: %1").arg(reply->errorString()));
    }

    // safe delete
    reply->deleteLater();
}

void ModbusWorker::onReply2(QModbusReply* reply)
{
    //QModbusReply* reply = qobject_cast<QModbusReply*>(sender());
    if (!reply) return;

    if (reply->error() == QModbusDevice::NoError) {
        QVector<quint16> values;
        const QModbusDataUnit unit = reply->result();

        for (int i = 0; i < unit.valueCount(); ++i)
            values.append(unit.value(i));

        emit dataReady2(values);

    }
    else {
        emit errorOccurred(QString("Reply error: %1").arg(reply->errorString()));
    }

    // safe delete
    reply->deleteLater();
}
void ModbusWorker::writeCoils(int startAddress, const QVector<bool>& values)
{
    //qDebug() << "[Modbus]  write coils. Address:" << startAddress << "Count:" << values.size() << "Values:" << values;
    if (!m_running)
        return;

    if (!m_client || m_client->state() != QModbusDevice::ConnectedState)
    {
        emit writeDone(startAddress, false, "Client not connected");
        return;
    }

    if (values.isEmpty())
    {
        emit writeDone(startAddress, false, "Write values is empty");
        return;
    }

    // 建立 DataUnit: Coils, 起始地址 + 數量
    QModbusDataUnit unit(QModbusDataUnit::Coils, startAddress, values.size());

    for (int i = 0; i < values.size(); ++i)
        unit.setValue(i, values[i]);

    // 發送寫入請求 (FC 15)
    QModbusReply* reply = m_client->sendWriteRequest(unit, 1);
    if (!reply)
    {
        emit writeDone(startAddress, false, "sendWriteRequest failed");
        return;
    }

    QEventLoop loop;
    connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // 等待直到讀取完


    if (reply->error() == QModbusDevice::NoError)
        emit writeDone(startAddress, true, "OK");
    else
        emit writeDone(startAddress, false, reply->errorString());

    reply->deleteLater();

}

void ModbusWorker::writeRegister(int startAddress, double values)
{
    if (!m_running || m_client->state() != QModbusDevice::ConnectedState)
    {
        emit errorOccurred("writeRegisters failed: not connected");
        return;
    }

    QModbusDataUnit unit(
        QModbusDataUnit::HoldingRegisters,
        startAddress,
        1
    );

    unit.setValue(0, values);

    QModbusReply* reply = m_client->sendWriteRequest(unit, 1);

    if (!reply)
    {
        emit errorOccurred("writeRegisters send failed");
        return;
    }

    QEventLoop loop;
    connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // 等待直到讀取完

    if (reply->error() != QModbusDevice::NoError)
    {
        emit errorOccurred("writeRegisters reply: " + reply->errorString());
    }
    reply->deleteLater();
}

void ModbusWorker::writeRegisters(int startAddress, QVector<double> values)
{
    if (!m_running || m_client->state() != QModbusDevice::ConnectedState)
    {
        emit errorOccurred("writeRegisters failed: not connected");
        return;
    }

    QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters, startAddress, values.size());

    for (int i = 0; i < values.size(); i++)
        unit.setValue(i, values[i] * 409.5);

    QModbusReply* reply = m_client->sendWriteRequest(unit, 1);

    if (!reply)
    {
        emit errorOccurred("writeRegisters send failed");
        return;
    }
    // 3. 建立區域 EventLoop 確保同步完成
    QEventLoop loop;

    // 確保無論成功或被手動銷毀都能退出 loop
    connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);

    // 啟動迴圈，執行緒會在此等待直到 Modbus Server 回應
    loop.exec();

    if (reply->error() != QModbusDevice::NoError)
    {
        emit errorOccurred("writeRegisters reply: " + reply->errorString());
    }
    reply->deleteLater();

}

void ModbusWorker::readRegisters(int startAddress, int count)
{
    if (!m_running || m_client->state() != QModbusDevice::ConnectedState) {
        emit errorOccurred("readRegisters failed: not connected");
        return;
    }

    QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters, startAddress, count);

    QModbusReply* reply = m_client->sendReadRequest(unit, 1);

    if (!reply) {
        emit errorOccurred("readRegisters send failed");
        return;
    }
    // 2. 建立區域 EventLoop
    QEventLoop loop;

    // 3. 連接完成訊號到 EventLoop 的 quit 槽
    // 無論成功或失敗，只要 reply 結束就跳出 loop
    connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);

    // 4. 開始事件循環 (程式碼會在此阻塞，但 thread 不會當死，仍能處理其他事件)
    loop.exec();

    if (reply->error() == QModbusDevice::NoError) {

        QVector<quint16> values;
        const QModbusDataUnit unit = reply->result();
        for (uint i = 0; i < unit.valueCount(); i++)
            values.append(unit.value(i));

        emit holdingRegisterReady(values);

    }
    else {
        emit errorOccurred("readRegisters reply error: " + reply->errorString());
    }
    reply->deleteLater();

}
void ModbusWorker::writeSingleCoil(int address, bool value)
{
    qDebug() << "Worker write single coil @ addr:" << address << " = " << value;

    if (!m_running || m_client->state() != QModbusDevice::ConnectedState)
    {
        //qDebug() << "Worker write single coil @ addr:" << address << " = " << value;
        emit writeDone(address, false, "Client not connected");
        return;
    }

    // 建立 DataUnit: 類型為 Coils, 起始地址為 address, 數量為 1
    QModbusDataUnit unit(QModbusDataUnit::Coils, address, 1);
    unit.setValue(0, value ? 1 : 0); // 設定第一個(也是唯一一個)數值

    // 發送請求
    QModbusReply* reply = m_client->sendWriteRequest(unit, 1); // 1 為 Server ID
    if (!reply)
    {
        emit writeDone(address, false, "sendWriteRequest failed");
        return;
    }

    // 2. 建立區域 EventLoop
    QEventLoop loop;

    // 3. 連接完成訊號到 EventLoop 的 quit 槽
    // 無論成功或失敗，只要 reply 結束就跳出 loop
    connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);

    // 4. 開始事件循環 (程式碼會在此阻塞，但 thread 不會當死，仍能處理其他事件)
    loop.exec();

    // 處理寫入結果

    if (reply->error() == QModbusDevice::NoError) {
        //qDebug() << "Worker" << m_workerId << "write single coil @ addr:" << address << "success";
        emit writeDone(address, true, "OK");
    }
    else {
        qDebug() << "Worker" << m_workerId << "write single coil error:" << address << reply->errorString();
        emit writeDone(address, false, reply->errorString());
    }
    reply->deleteLater();
}


void ModbusWorker::set_VfdAlarmReset(double value)
{
    if (qFuzzyCompare(m_vfdAlarmReset, value)) return;
    flag_vfdAlarmReset = true;
    m_vfdAlarmReset = value;
}
void ModbusWorker::set_UnwinderForward(double value)
{
    if (qFuzzyCompare(m_unwinderForward, value)) return;
    flag_unwinderForward = true;
    m_unwinderForward = value;
}
void ModbusWorker::set_UnwinderReverse(double value)
{
    if (qFuzzyCompare(m_unwinderReverse, value)) return;
    flag_unwinderReverse = true;
    m_unwinderReverse = value;
}
void ModbusWorker::set_MainDriveForward(double value)
{
    if (qFuzzyCompare(m_mainDriveForward, value)) return;
    flag_mainDriveForward = true;
    m_mainDriveForward = value;
}
void ModbusWorker::set_MainDriveReverse(double value)
{
    if (qFuzzyCompare(m_mainDriveReverse, value)) return;
    flag_mainDriveReverse = true;
    m_mainDriveReverse = value;
}
void ModbusWorker::set_SmallWinderForward(double value)
{
    if (qFuzzyCompare(m_smallWinderForward, value)) return;
    flag_smallWinderForward = true;
    m_smallWinderForward = value;
}
void ModbusWorker::set_SmallWinderReverse(double value)
{
    if (qFuzzyCompare(m_smallWinderReverse, value)) return;
    flag_smallWinderReverse = true;
    m_smallWinderReverse = value;
}
void ModbusWorker::set_LargeWinderForward(double value)
{
    if (qFuzzyCompare(m_largeWinderForward, value)) return;
    flag_largeWinderForward = true;
    m_largeWinderForward = value;
}
void ModbusWorker::set_LargeWinderReverse(double value)
{
    if (qFuzzyCompare(m_largeWinderReverse, value)) return;
    flag_largeWinderReverse = true;
    m_largeWinderReverse = value;
}
void ModbusWorker::set_SmallCutterStart(double value)
{
    if (qFuzzyCompare(m_smallCutterStart, value)) return;
    flag_smallCutterStart = true;
    m_smallCutterStart = value;
}
void ModbusWorker::set_SelvedgeFanStart(double value)
{
    if (qFuzzyCompare(m_selvedgeFanStart, value)) return;
    flag_selvedgeFanStart = true;
    m_selvedgeFanStart = value;
}
void ModbusWorker::set_LargeCutterStart(double value)
{
    if (qFuzzyCompare(m_largeCutterStart, value)) return;
    flag_largeCutterStart = true;
    m_largeCutterStart = value;
}
void ModbusWorker::set_LeftSelvedgeWinderForward(double value)
{
    if (qFuzzyCompare(m_leftSelvedgeWinderForward, value)) return;
    flag_leftSelvedgeWinderForward = true;
    m_leftSelvedgeWinderForward = value;
}
void ModbusWorker::set_LeftSelvedgeWinderReverse(double value)
{
    if (qFuzzyCompare(m_leftSelvedgeWinderReverse, value)) return;
    flag_leftSelvedgeWinderReverse = true;
    m_leftSelvedgeWinderReverse = value;
}
void ModbusWorker::set_RightSelvedgeWinderForward(double value)
{
    if (qFuzzyCompare(m_rightSelvedgeWinderForward, value)) return;
    flag_rightSelvedgeWinderForward = true;
    m_rightSelvedgeWinderForward = value;
}
void ModbusWorker::set_RightSelvedgeWinderReverse(double value)
{
    if (qFuzzyCompare(m_rightSelvedgeWinderReverse, value)) return;
    flag_rightSelvedgeWinderReverse = true;
    m_rightSelvedgeWinderReverse = value;
}
void ModbusWorker::set_WebAlignerStart(double value)
{
    if (qFuzzyCompare(m_webAlignerStart, value)) return;
    flag_webAlignerStart = true;
    m_webAlignerStart = value;
}
void ModbusWorker::set_UnwindingTensionAuto(double value)
{
    if (qFuzzyCompare(m_unwindingTensionAuto, value)) return;
    flag_unwindingTensionAuto = true;
    m_unwindingTensionAuto = value;
}
void ModbusWorker::set_UnwindingDiameterReset_(double value)
{
    if (qFuzzyCompare(m_unwindingDiameterReset, value)) return;
    flag_unwindingDiameterReset = true;
    m_unwindingDiameterReset = value;
}
void ModbusWorker::set_SmallWinderTensionAuto(double value)
{
    if (qFuzzyCompare(m_smallWinderTensionAuto, value)) return;
    flag_smallWinderTensionAuto = true;
    m_smallWinderTensionAuto = value;
}
void ModbusWorker::set_SmallWinderDiameterReset_(double value)
{
    if (qFuzzyCompare(m_smallWinderDiameterReset, value)) return;
    flag_smallWinderDiameterReset = true;
    m_smallWinderDiameterReset = value;
}
void ModbusWorker::set_LargeWinderTensionAuto(double value)
{
    if (qFuzzyCompare(m_largeWinderTensionAuto, value)) return;
    flag_largeWinderTensionAuto = true;
    m_largeWinderTensionAuto = value;
}
void ModbusWorker::set_LargeWinderDiameterReset_(double value)
{
    if (qFuzzyCompare(m_largeWinderDiameterReset, value)) return;
    flag_largeWinderDiameterReset = true;
    m_largeWinderDiameterReset = value;
}
void ModbusWorker::set_LeftSelvedgeWinderAuto(double value)
{
    if (qFuzzyCompare(m_leftSelvedgeWinderAuto, value)) return;
    flag_leftSelvedgeWinderAuto = true;
    m_leftSelvedgeWinderAuto = value;
}
void ModbusWorker::set_RightSelvedgeWinderAuto(double value)
{
    if (qFuzzyCompare(m_rightSelvedgeWinderAuto, value)) return;
    flag_rightSelvedgeWinderAuto = true;
    m_rightSelvedgeWinderAuto = value;
}
void ModbusWorker::set_NipRollUp(double value)
{
    if (qFuzzyCompare(m_nipRollUp, value)) return;
    flag_nipRollUp = true;
    m_nipRollUp = value;
}
void ModbusWorker::set_NipRollDown(double value)
{
    if (qFuzzyCompare(m_nipRollDown, value)) return;
    flag_nipRollDown = true;
    m_nipRollDown = value;
}
void ModbusWorker::set_LeftPressPlateForward(double value)
{
    if (qFuzzyCompare(m_leftPressPlateForward, value)) return;
    flag_leftPressPlateForward = true;
    m_leftPressPlateForward = value;
}
void ModbusWorker::set_LeftPressPlateBackward(double value)
{
    if (qFuzzyCompare(m_leftPressPlateBackward, value)) return;
    flag_leftPressPlateBackward = true;
    m_leftPressPlateBackward = value;
}
void ModbusWorker::set_RightPressPlateForward(double value)
{
    if (qFuzzyCompare(m_rightPressPlateForward, value)) return;
    flag_rightPressPlateForward = true;
    m_rightPressPlateForward = value;
}
void ModbusWorker::set_RightPressPlateBackward(double value)
{
    if (qFuzzyCompare(m_rightPressPlateBackward, value)) return;
    flag_rightPressPlateBackward = true;
    m_rightPressPlateBackward = value;
}
void ModbusWorker::set_IO95(double value)
{

    if (qFuzzyCompare(m_IO95, value)) return;
    qDebug() << "I/O 95 change";
    flag_IO95 = true;
    m_IO95 = value;
}
void ModbusWorker::set_IO96(double value)
{

    if (qFuzzyCompare(m_IO96, value)) return;
    qDebug() << "I/O 96 change";

    flag_IO96 = true;
    m_IO96 = value;
}
void ModbusWorker::set_IO97(double value)
{

    if (qFuzzyCompare(m_IO97, value)) return;
    qDebug() << "I/O 97 change";

    flag_IO97 = true;
    m_IO97 = value;
}
void ModbusWorker::set_IO98(double value)
{

    if (qFuzzyCompare(m_IO98, value)) return;
    qDebug() << "I/O 98 change";

    flag_IO98 = true;
    m_IO98 = value;
}
void ModbusWorker::set_IO99(double value)
{

    if (qFuzzyCompare(m_IO99, value)) return;
    qDebug() << "I/O 99 change";

    flag_IO99 = true;
    m_IO99 = value;
}
void ModbusWorker::set_IO100(double value)
{

    if (qFuzzyCompare(m_IO100, value)) return;
    qDebug() << "I/O 100 change";

    flag_IO100 = true;
    m_IO100 = value;
}
void ModbusWorker::set_IO101(double value)
{

    if (qFuzzyCompare(m_IO101, value)) return;
    qDebug() << "I/O 101 change";

    flag_IO101 = true;
    m_IO101 = value;
}
void ModbusWorker::set_IO102(double value)
{

    if (qFuzzyCompare(m_IO102, value)) return;
    qDebug() << "I/O 102 change";

    flag_IO102 = true;
    m_IO102 = value;
}
void ModbusWorker::set_IO103(double value)
{

    if (qFuzzyCompare(m_IO103, value)) return;
    qDebug() << "I/O 103 change";

    flag_IO103 = true;
    m_IO103 = value;
}
void ModbusWorker::set_IO104(double value)
{

    if (qFuzzyCompare(m_IO104, value)) return;
    qDebug() << "I/O 104 change";

    flag_IO104 = true;
    m_IO104 = value;
}
void ModbusWorker::set_IO105(double value)
{

    if (qFuzzyCompare(m_IO105, value)) return;
    qDebug() << "I/O 105 change";

    flag_IO105 = true;
    m_IO105 = value;
}
void ModbusWorker::set_IO106(double value)
{

    if (qFuzzyCompare(m_IO106, value)) return;
    qDebug() << "I/O 106 change";

    flag_IO106 = true;
    m_IO106 = value;
}
void ModbusWorker::set_IO107(double value)
{

    if (qFuzzyCompare(m_IO107, value)) return;
    qDebug() << "I/O 107 change";

    flag_IO107 = true;
    m_IO107 = value;
}
void ModbusWorker::set_IO108(double value)
{

    if (qFuzzyCompare(m_IO108, value)) return;
    qDebug() << "I/O 108 change";

    flag_IO108 = true;
    m_IO108 = value;
}
void ModbusWorker::set_IO109(double value)
{

    if (qFuzzyCompare(m_IO109, value)) return;
    qDebug() << "I/O 109 change";

    flag_IO109 = true;
    m_IO109 = value;
}
void ModbusWorker::set_IO110(double value)
{

    if (qFuzzyCompare(m_IO110, value)) return;
    qDebug() << "I/O 110 change";

    flag_IO110 = true;
    m_IO110 = value;
}
void ModbusWorker::set_IO111(double value)
{

    if (qFuzzyCompare(m_IO111, value)) return;
    qDebug() << "I/O 111 change";

    flag_IO111 = true;
    m_IO111 = value;
}
void ModbusWorker::set_IO112(double value)
{

    if (qFuzzyCompare(m_IO112, value)) return;
    qDebug() << "I/O 112 change";

    flag_IO112 = true;
    m_IO112 = value;
}
void ModbusWorker::set_EStop(bool value)
{
    E_Stop = true;
    qDebug() << "E-STOP";
}
void ModbusWorker::StartAuto()
{
    writeCoils(81, startAuto);
}
void ModbusWorker::StopAuto()
{
    writeCoils(81, stopAuto);
}
