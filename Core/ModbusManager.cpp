#include "ModbusManager.h"
#include <qdebug>
ModbusManager::ModbusManager(QObject* parent)
    : QObject(parent)
{
}

ModbusManager::~ModbusManager()
{
    stopAll();
}

void ModbusManager::createWorker(const QString& ip, int port)
{
    // 1. 安全檢查：如果 worker 已經存在，則不再重複建立
    if (m_worker != nullptr) {
        emit workerError("Worker already exists.");
        return;
    }

    // 2. 建立 Thread 與 Worker 實體
    m_thread = new QThread(this);
    m_worker = new ModbusWorker(0, ip, port); // 固定 ID 為 0

    // 3. 將 Worker 移動到獨立執行緒
    m_worker->moveToThread(m_thread);

    // 4. 設定訊號與槽的連接 (Connections)

    // 當 Thread 啟動時，觸發 Worker 的開始工作函式
    connect(m_thread, &QThread::started,
        m_worker, &ModbusWorker::startWork);

    // 將 Worker 的數據輸出轉發給 Manager 的訊號
    connect(m_worker, &ModbusWorker::dataReady,
        this, [this](QVector<quint16> v) {
            emit workerData(v);
        });

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

    qDebug() << "Single Modbus Worker initialized and started for" << ip << ":" << port;
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
    QMetaObject::invokeMethod(m_worker, [this, address, value] {m_worker->writeSingleCoil(address, value); },
        Qt::QueuedConnection);
}

void ModbusManager::writeCoils(int startAddress, const QVector<bool>& values)
{

    qDebug() << "worker: write Colls";
    QMetaObject::invokeMethod(m_worker, [this, startAddress, values] { m_worker->writeCoils(startAddress, values);},
        Qt::QueuedConnection
    );
}

void ModbusManager::writeRegisters( int startAddress, const QVector<quint16>& values)
{


    QMetaObject::invokeMethod(
        m_worker, [this, startAddress, values] { m_worker->writeRegisters(startAddress, values); },
        Qt::QueuedConnection
    );
}

void ModbusManager::readRegisters(int startAddress, int count)
{

    qDebug() << "worker: read HR";
    QMetaObject::invokeMethod(
        m_worker,[this, startAddress, count] { m_worker->readRegisters(startAddress, count);},
        Qt::QueuedConnection
    );
    connect(m_worker, &ModbusWorker::holdingRegisterReady,
        this, [this]( QVector<quint16> values) {
            emit holdingRegisterReady(values);
        });
}
