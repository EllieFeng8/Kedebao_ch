#include "ModbusManager.h"
#include <qdebug>
#include <Qtimer>
ModbusManager::ModbusManager(QObject* parent)
    : QObject(parent)
{
    qDebug() << "manager";

}

ModbusManager::~ModbusManager()
{

    if (m_thread && m_thread->isRunning()) {
        m_thread->quit();        
        m_thread->wait(200);

    }
}

void ModbusManager::createWorker()
{
    // 1. 安全檢查：如果 worker 已經存在，則不再重複建立
    if (m_worker != nullptr) {
        emit workerError("Worker already exists.");
        return;
    }

    // 2. 建立 Thread 與 Worker 實體
    m_thread = new QThread(this);
    m_worker = new ModbusWorker(); // 固定 ID 為 0

    // 3. 將 Worker 移動到獨立執行緒
    m_worker->moveToThread(m_thread);

    // 4. 設定訊號與槽的連接 (Connections)

    // 當 Thread 啟動時，觸發 Worker 的開始工作函式
    connect(m_thread, &QThread::started,
        m_worker, &ModbusWorker::startWork);
    connect(m_thread, &QThread::finished,
        m_worker, &QObject::deleteLater);
    // 將 Worker 的數據輸出轉發給 Manager 的訊號
    connect(m_worker, &ModbusWorker::dataReady,
        this, [this](QVector<quint16> v) {
            emit workerData(v);
            bool hasAlarm = hasAlarmFunc(v);
            if (hasAlarm && !m_alarmActive)
            {
                QMetaObject::invokeMethod(
                    m_worker, [this, v] { m_worker->writeCoils(81, m_worker->stopAuto); },
                    Qt::QueuedConnection
                ); // 直接呼叫
                m_alarmActive = true; // 標記已處理
            }
            else if (!hasAlarm)
            {
                m_alarmActive = false; // alarm 消失，可再次觸發
            }
            // 零速檢出
            if (v[55] == 1)
            {
                //emit Zerospeed01();
            }
            if (v[56] == 1)
            {
                //emit Zerospeed02();
            }
        });
    connect(m_worker, &ModbusWorker::dataReady2,
        this, [this](QVector<quint16> v) {
            emit workerData2(v); });
    // 將 Worker 的錯誤訊息轉發給 Manager 的訊號
    connect(m_worker, &ModbusWorker::errorOccurred,
        this, [this](QString msg) {
            emit workerError(msg);
        });

    // 處理讀取 Holding Registers 的回傳數據
    connect(m_worker, &ModbusWorker::holdingRegisterReady,
        this, [this]( QVector<quint16> values) {
            emit holdingRegisterReady(values);
        });

    // 5. 啟動執行緒
    m_thread->start();

}


void ModbusManager::startAll()
{
    if (m_thread && !m_thread->isRunning()) {
        m_thread->start();
        qDebug() << "Modbus Worker thread started.";
    }
    else {
        qDebug() << "Worker thread is already running or not initialized.";
    }
}

void ModbusManager::stopAll()
{
    if (m_worker && m_thread) {
        // 安全停止 Worker 的工作循環
        QMetaObject::invokeMethod(m_worker, []() { &ModbusWorker::stopWork; }, Qt::QueuedConnection);

        // 停止執行緒並等待結束
        m_thread->quit();
        if (!m_thread->wait(2000)) { // 等待最多 2 秒
            m_thread->terminate();   // 若無法正常停止則強制終止
        }
        qDebug() << "Modbus Worker stopped.";
    }
}
void ModbusManager::writeSingleCoil( int address, bool value)
{
    //qDebug() << " Manager : write single coil" << address << " = " << value;

    QMetaObject::invokeMethod(m_worker, [this, address, value] {m_worker->writeSingleCoil(address, value); },
        Qt::QueuedConnection);
}

void ModbusManager::writeCoils(int startAddress, const QVector<bool>& values)
{

    //qDebug() << "worker: write Colls";
    QMetaObject::invokeMethod(m_worker, [this, startAddress, values] { m_worker->writeCoils(startAddress, values);},
        Qt::QueuedConnection
    );
}

void ModbusManager::writeRegister56( const double & values)//4000
{
    qDebug() << "set Analog Output CH1 = " << values;

    quint16 v = values * 409.5;
    QMetaObject::invokeMethod(
        m_worker, [this, v] { m_worker->writeRegister(56, v); },
        Qt::QueuedConnection
    );
}
void ModbusManager::writeRegister57(const double & values)
{
    qDebug() << "set Analog Output CH2 = " << values;

    double v = values * 409.5;
    QMetaObject::invokeMethod(
        m_worker, [this, v] { m_worker->writeRegister(57, v); },
        Qt::QueuedConnection
    );
}
void ModbusManager::writeRegister58(const double & values)
{
    qDebug() << "set Analog Output CH3 = " << values;
    quint16 v = values * 409.5;
    QMetaObject::invokeMethod(
        m_worker, [this, v] { m_worker->writeRegister(58, v); },
        Qt::QueuedConnection
    );
}
void ModbusManager::writeRegister59(const double & values)
{
    qDebug() << "set Analog Output CH4 = " << values;

    quint16 v = values * 409.5;
    QMetaObject::invokeMethod(
        m_worker, [this, v] { m_worker->writeRegister(59, v); },
        Qt::QueuedConnection
    );
}


void ModbusManager::writeRegisters( const QVector<double>& values)
{
    QVector<double> v;
    v.resize(values.size());
    for (int i = 0; i < values.size(); ++i)
    {
        v[i] = (values[i] / 13);
        qDebug() << "set Analog Output = " << v[i];
    }
    
    QMetaObject::invokeMethod(
        m_worker, [this, v] { m_worker->writeRegisters(56, v); },
        Qt::QueuedConnection
    );
}

void ModbusManager::readRegisters(int startAddress, int count)
{


    QMetaObject::invokeMethod(
        m_worker,[this, startAddress, count] { m_worker->readRegisters(startAddress, count);},
        Qt::QueuedConnection
    );
    connect(m_worker, &ModbusWorker::holdingRegisterReady,
        this, [this]( QVector<quint16> values) {
            emit holdingRegisterReady(values);
        });
}



void ModbusManager::VfdAlarmReset(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "VfdAlarmReset" << v;
    m_worker->set_VfdAlarmReset(value);
}
void ModbusManager::UnwinderForward(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "UnwinderForward" << v;
    m_worker->set_UnwinderForward(value);
}
void ModbusManager::UnwinderReverse(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "UnwinderReverse" << v;
    m_worker->set_UnwinderReverse(value);
}
void ModbusManager::MainDriveForward(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "MainDriveForward" << v;
    m_worker->set_MainDriveForward(value);
}
void ModbusManager::MainDriveReverse(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "MainDriveReverse" << v;
    m_worker->set_MainDriveReverse(value);
}
void ModbusManager::SmallWinderForward(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "SmallWinderForward" << v;
    m_worker->set_SmallWinderForward(value);
}
void ModbusManager::SmallWinderReverse(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "SmallWinderReverse" << v;
    m_worker->set_SmallWinderReverse(value);
}
void ModbusManager::LargeWinderForward(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "LargeWinderForward" << v;
    m_worker->set_LargeWinderForward(value);
}
void ModbusManager::LargeWinderReverse(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "LargeWinderReverse" << v;
    m_worker->set_LargeWinderReverse(value);
}
void ModbusManager::SmallCutterStart(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "SmallCutterStart" << v;
    m_worker->set_SmallCutterStart(value);
}
void ModbusManager::SelvedgeFanStart(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "SelvedgeFanStart" << v;
    m_worker->set_SelvedgeFanStart(value);
}
void ModbusManager::LargeCutterStart(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "LargeCutterStart" << v;
    m_worker->set_LargeCutterStart(value);
}
void ModbusManager::LeftSelvedgeWinderForward(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "LeftSelvedgeWinderForward" << v;
    m_worker->set_LeftSelvedgeWinderForward(value);
}
void ModbusManager::LeftSelvedgeWinderReverse(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "LeftSelvedgeWinderReverse" << v;
    m_worker->set_LeftSelvedgeWinderReverse(value);
}
void ModbusManager::RightSelvedgeWinderForward(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "RightSelvedgeWinderForward" << v;
    m_worker->set_RightSelvedgeWinderForward(value);
}
void ModbusManager::RightSelvedgeWinderReverse(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "RightSelvedgeWinderReverse" << v;
    m_worker->set_RightSelvedgeWinderReverse(value);
}
void ModbusManager::WebAlignerStart(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "WebAlignerStart" << v;
    m_worker->set_WebAlignerStart(value);
}
void ModbusManager::UnwindingTensionAuto(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "UnwindingTensionAuto" << v;
    m_worker->set_UnwindingTensionAuto(value);
}
void ModbusManager::UnwindingDiameterRe(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "UnwindingDiameterRe" << v;
    m_worker->set_UnwindingDiameterReset_(value);
}
void ModbusManager::SmallWinderTensionAuto(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "SmallWinderTensionAuto" << v;
    m_worker->set_SmallWinderTensionAuto(value);
}
void ModbusManager::SmallWinderDiameterRe(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "SmallWinderDiameterRe" << v;
    m_worker->set_SmallWinderDiameterReset_(value);
}
void ModbusManager::LargeWinderTensionAuto(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "LargeWinderTensionAuto" << v;
    m_worker->set_LargeWinderTensionAuto(value);
}
void ModbusManager::LargeWinderDiameterRe(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "LargeWinderDiameterRe" << v;
    m_worker->set_LargeWinderDiameterReset_(value);
}
void ModbusManager::LeftSelvedgeWinderAuto(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "LeftSelvedgeWinderAuto" << v;
    m_worker->set_LeftSelvedgeWinderAuto(value);
}
void ModbusManager::RightSelvedgeWinderAuto(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "RightSelvedgeWinderAuto" << v;
    m_worker->set_RightSelvedgeWinderAuto(value);
}
void ModbusManager::NipRollUp(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "NipRollUp" << v;
    m_worker->set_NipRollUp(value);
}
void ModbusManager::NipRollDown(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "NipRollDown" << v;
    m_worker->set_NipRollDown(value);
}
void ModbusManager::LeftPressPlateForward(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "LeftPressPlateForward" << v;
    m_worker->set_LeftPressPlateForward(value);
}
void ModbusManager::LeftPressPlateBackward(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "LeftPressPlateBackward" << v;
    m_worker->set_LeftPressPlateBackward(value);
}
void ModbusManager::RightPressPlateForward(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "RightPressPlateForward" << v;
    m_worker->set_RightPressPlateForward(value);
}
void ModbusManager::RightPressPlateBackward(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "RightPressPlateBackward" << v;
    m_worker->set_RightPressPlateBackward(value);
}
void ModbusManager::SmallCutterIn(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "SmallCutterIn" << v;
    m_worker->set_SmallCutterIn(value);
}
void ModbusManager::LargeCutterIn(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "LargeCutterIn" << v;
    m_worker->set_LargeCutterIn(value);
}
void ModbusManager::ModeSelect(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "ModeSelect" << v;
    m_worker->set_ModeSelect(value);
}
void ModbusManager::RunIndicator(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "RunIndicator" << v;
    m_worker->set_RunIndicator(value);
}
void ModbusManager::AlarmIndicator(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "AlarmIndicator" << v;
    m_worker->set_AlarmIndicator(value);
}
void ModbusManager::StopIndicator(double value)
{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "StopIndicator" << v;
    m_worker->set_StopIndicator(value);
}
void ModbusManager::Buzzer(double value)

{
    bool v = (value > 0.0) ? true : false;
    qDebug() << "Buzzer" << v;
    m_worker->set_Buzzer(value);
}
void ModbusManager::SmallRollModeSelect(double value)
{

    bool v = (value > 0.0) ? true : false;
    m_ModeSelet = v;
    qDebug() << "SmallRollModeSelect" << v;
    m_worker->set_SmallRollModeSelect(value);
}

void ModbusManager::IpcStart(bool v)
{
    //writeCoils(81, m_worker->startAuto);
    
    if (m_ModeSelet)
    {
        writeCoils(65, {1,0,1,0,0,1,0,0,1,1,0,0,0,0,0,0,1,0,1,0,1,0,1,1}); //小卷模式 正轉啟動
    }
    else
    {
        writeCoils(65, {1,0,1,0,0,0,1,0,0,0,1,1,0,1,0,0,1,0,1,0,1,0,1,1});//大捲模式 正轉啟動
    }
}
void ModbusManager::IpcStop(bool v)
{
    qDebug() << "IpcStop";
    QVector<bool> stop(24, false);

    writeCoils(65, stop);
}