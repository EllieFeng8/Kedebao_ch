#include "ModbusWorker.h"
#include <QDebug>
#include <Qvariant>
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
        m_pollTimer->setInterval(100);
        connect(m_pollTimer, &QTimer::timeout, this, &ModbusWorker::poll, Qt::DirectConnection);
        // DirectConnection 因為 timer 與 this 在同一 thread (保障)
    }

    if (!m_reconnectTimer) {
        m_reconnectTimer = new QTimer(this);
        m_reconnectTimer->setInterval(2000);
        m_reconnectTimer->setSingleShot(true);
        connect(m_reconnectTimer, &QTimer::timeout, this, &ModbusWorker::startWork, Qt::QueuedConnection);
    }

    // 設定連線參數
    m_client->setConnectionParameter(QModbusDevice::NetworkAddressParameter, m_ip);
    m_client->setConnectionParameter(QModbusDevice::NetworkPortParameter, m_port);
    m_client->setTimeout(1000);
    m_client->setNumberOfRetries(2);
    qDebug() << "connecting to" << m_ip << ":" << m_port;
    m_client2->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "192.168.1.202");
    m_client2->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);
    m_client2->setTimeout(1000);
    m_client2->setNumberOfRetries(2);
    qDebug() << "connecting to" << "192.168.1.202" << ":" << "502";

    // 非同步嘗試連線；onStateChanged 會處理 Connected/Unconnected
    m_client->connectDevice();
    m_client2->connectDevice();
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
    bool f_smallCutterIn = false;       //95
    //===OUTPUT3=====
    bool f_largeCutterIn = false;       //96
    bool f_modeSelect = false;          //97
    bool f_runIndicator = false;        //98
    bool f_alarmIndicator = false;      //99
    bool f_stopIndicator = false;      //100
    bool f_buzzer = false;              //101
    bool f_smallRollModeSelect = false; //102

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
    bool _smallCutterIn = false;       //95
    //===OUTPUT3=====
    bool _largeCutterIn = false;       //96
    bool _modeSelect = false;          //97
    bool _runIndicator = false;        //98
    bool _alarmIndicator = false;      //99
    bool _stopIndicator = false;      //100
    bool _buzzer = false;              //101
    bool _smallRollModeSelect = false; //102

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
        if(flag_smallCutterIn)
        {
            _smallCutterIn = (m_smallCutterIn > 0.0) ? true : false;
            f_smallCutterIn = flag_smallCutterIn;
            flag_smallCutterIn = false;
        }
        if(flag_largeCutterIn)
        {
            _largeCutterIn = (m_largeCutterIn > 0.0) ? true : false;
            f_largeCutterIn = flag_largeCutterIn;
            flag_largeCutterIn = false;
        }
        if(flag_modeSelect)
        {
            _modeSelect = (m_modeSelect > 0.0) ? true : false;
            f_modeSelect = flag_modeSelect;
            flag_modeSelect = false;
        }
        if(flag_runIndicator)
        {
            _runIndicator = (m_runIndicator > 0.0) ? true : false;
            f_runIndicator = flag_runIndicator;
            flag_runIndicator = false;
        }
        if(flag_alarmIndicator)
        {
            _alarmIndicator = (m_alarmIndicator > 0.0) ? true : false;
            f_alarmIndicator = flag_alarmIndicator;
            flag_alarmIndicator = false;
        }
        if(flag_stopIndicator)
        {
            _stopIndicator = (m_stopIndicator > 0.0) ? true : false;
            f_stopIndicator = flag_stopIndicator;
            flag_stopIndicator = false;
        }
        if (flag_buzzer)
        {
            _buzzer = (m_buzzer > 0.0) ? true : false;
            f_buzzer = flag_buzzer;
            flag_buzzer = false;
        }
        if (flag_smallRollModeSelect) 
        {
            _smallRollModeSelect = (m_smallRollModeSelect > 0.0) ? true : false;
            f_smallRollModeSelect = flag_smallRollModeSelect;
            flag_smallRollModeSelect = false;
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
        if (f_smallCutterIn)
        {
            writeSingleCoil(95, _smallCutterIn);
        }
        if (f_largeCutterIn)
        {
            writeSingleCoil(96, _largeCutterIn);
        }
        if (f_modeSelect)
        {
            writeSingleCoil(97, _modeSelect);
        }
        if (f_runIndicator)
        {
            writeSingleCoil(98, _runIndicator);
        }
        if (f_alarmIndicator)
        {
            writeSingleCoil(99, _alarmIndicator);
        }
        if (f_stopIndicator)
        {
            writeSingleCoil(100, _stopIndicator);
        }
        if (f_buzzer)
        {
            writeSingleCoil(101, _buzzer);
        }
        if (f_smallRollModeSelect)
        {
            writeSingleCoil(102, _smallRollModeSelect);
        }

        initFlag();
    }

    
    //ADAM-5000(192.168.1.201)

    QModbusDataUnit unit(QModbusDataUnit::Coils, 0, 112);
    QModbusReply* reply = m_client->sendReadRequest(unit, 1);

    if (!reply) {
        emit errorOccurred(QString("sendReadRequest failed"));
        return;
    }
    reply->setParent(this);
    connect(reply, &QModbusReply::finished, this, &ModbusWorker::onReply, Qt::QueuedConnection);
    
    //ADAM-5000(192.168.1.202)
    QModbusDataUnit unit2(QModbusDataUnit::Coils, 0, 16);
    QModbusReply* reply2 = m_client2->sendReadRequest(unit2, 1);

    if (!reply2) {
        emit errorOccurred(QString("sendReadRequest failed"));
        return;
    }
    reply2->setParent(this);
    connect(reply2, &QModbusReply::finished, this, &ModbusWorker::onReply2, Qt::QueuedConnection);

    //Analog output READ
    readRegisters(56, 4);
}

void ModbusWorker::onReply()
{
    QModbusReply* reply = qobject_cast<QModbusReply*>(sender());
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

void ModbusWorker::onReply2()
{
    QModbusReply* reply = qobject_cast<QModbusReply*>(sender());
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
    qDebug() << "[Modbus]  write coils. Address:" << startAddress << "Count:" << values.size() << "Values:" << values;
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
    
    reply->setParent(this);

    // 完成 callback
    connect(reply, &QModbusReply::finished, this,
        [this, startAddress, reply]()
        {
            if (reply->error() == QModbusDevice::NoError)
                emit writeDone(startAddress, true, "OK");
            else
                emit writeDone(startAddress, false, reply->errorString());

            reply->deleteLater();
        });
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

    connect(reply, &QModbusReply::finished, this, [this, reply]() {
        if (reply->error() != QModbusDevice::NoError)
        {
            emit errorOccurred("writeRegisters reply: " + reply->errorString());
        }
        reply->deleteLater();
        });
}

void ModbusWorker::writeRegisters(int startAddress, QVector<double> values)
{
    if (!m_running || m_client->state() != QModbusDevice::ConnectedState)
    {
        emit errorOccurred("writeRegisters failed: not connected");
        return;
    }

    QModbusDataUnit unit(
        QModbusDataUnit::HoldingRegisters,
        startAddress,
        values.size()
    );

    for (int i = 0; i < values.size(); i++)
        unit.setValue(i, values[i]*409.5);

    QModbusReply* reply = m_client->sendWriteRequest(unit, 1);

    if (!reply)
    {
        emit errorOccurred("writeRegisters send failed");
        return;
    }

    connect(reply, &QModbusReply::finished, this, [this, reply]() {
        if (reply->error() != QModbusDevice::NoError)
        {
            emit errorOccurred("writeRegisters reply: " + reply->errorString());
        }
        reply->deleteLater();
        });
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

    connect(reply, &QModbusReply::finished, this, [this, reply]() {
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
        });
}
void ModbusWorker::writeSingleCoil(int address, bool value)
{
    qDebug() << "Worker write single coil @ addr:" << address << " = " << value;

    if (!m_running || m_client->state() != QModbusDevice::ConnectedState)
    {
        qDebug() << "Worker write single coil @ addr:" << address << " = " << value;
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

    reply->setParent(this);

    // 處理寫入結果
    connect(reply, &QModbusReply::finished, this, [this, address, reply]() {
        if (reply->error() == QModbusDevice::NoError) {
            //qDebug() << "Worker" << m_workerId << "write single coil @ addr:" << address << "success";
            emit writeDone(address, true, "OK");
        }
        else {
            qDebug() << "Worker" << m_workerId << "write single coil error:" <<address << reply->errorString();
            emit writeDone(address, false, reply->errorString());
        }
        reply->deleteLater();
        });
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
void ModbusWorker::set_SmallCutterIn(double value)
{
    if (qFuzzyCompare(m_smallCutterIn, value)) return;
    flag_smallCutterIn = true;
    m_smallCutterIn = value;
}
void ModbusWorker::set_LargeCutterIn(double value)
{
    if (qFuzzyCompare(m_largeCutterIn, value)) return;
    flag_largeCutterIn = true;
    m_largeCutterIn = value;
}
void ModbusWorker::set_ModeSelect(double value)
{
    if (qFuzzyCompare(m_modeSelect, value)) return;
    flag_modeSelect = true;
    m_modeSelect = value;
}
void ModbusWorker::set_RunIndicator(double value)
{
    if (qFuzzyCompare(m_runIndicator, value)) return;
    flag_runIndicator = true;
    m_runIndicator = value;
}
void ModbusWorker::set_AlarmIndicator(double value)
{
    if (qFuzzyCompare(m_alarmIndicator, value)) return;
    flag_alarmIndicator = true;
    m_alarmIndicator = value;
}
void ModbusWorker::set_StopIndicator(double value)
{
    if (qFuzzyCompare(m_stopIndicator, value)) return;
    flag_stopIndicator = true;
    m_stopIndicator = value;
}
void ModbusWorker::set_Buzzer(double value)
{
    if (qFuzzyCompare(m_buzzer, value)) return;
    flag_buzzer = true;
    m_buzzer = value;
}
void ModbusWorker::set_SmallRollModeSelect(double value)
{
    if (qFuzzyCompare(m_smallRollModeSelect, value)) return;
    flag_smallRollModeSelect = true;
    m_smallRollModeSelect = value;
}
void ModbusWorker::StartAuto()
{
    writeCoils(81, startAuto);
}
void ModbusWorker::StopAuto()
{
    writeCoils(81, stopAuto);
}
