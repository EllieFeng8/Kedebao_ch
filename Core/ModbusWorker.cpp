#include "ModbusWorker.h"
#include <QDebug>
#include <Qvariant>
ModbusWorker::ModbusWorker(int id, const QString& ip, int port, QObject* parent)
    : QObject(parent),
    m_workerId(id),
    m_ip(ip),
    m_port(port)
{
    // 只建立 QModbusTcpClient，**不要**在建構子建立 QTimer（以免在主線程）
    m_client = new QModbusTcpClient(this);

    // 監聽 client 的狀態與錯誤（safe: client 在 worker 被 moveToThread 前可以 connect）
    connect(m_client, &QModbusTcpClient::stateChanged,
        this, &ModbusWorker::onStateChanged);
    connect(m_client, &QModbusTcpClient::errorOccurred,
        this, &ModbusWorker::onErrorOccurred);
}

void ModbusWorker::startWork()
{
    if (m_running)
        return;
    m_running = true;

    // --- 在真正的 worker thread 中建立 timers ---
    if (!m_pollTimer) {
        // 建立時以 this 為 parent，因為 startWork 在 worker thread 執行 (Manager 已 moveToThread)
        m_pollTimer = new QTimer(this);
        m_pollTimer->setInterval(50);
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

    qDebug() << "Worker" << m_workerId << "connecting to" << m_ip << ":" << m_port;

    // 非同步嘗試連線；onStateChanged 會處理 Connected/Unconnected
    m_client->connectDevice();
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

    // 注意：reply->deleteLater() 與 parent=this 會確保 reply 隨 this 一起清理
}

void ModbusWorker::onStateChanged(QModbusDevice::State state)
{
    if (state == QModbusDevice::ConnectedState) {
        qDebug() << "Worker" << m_workerId << "connected.";

        if (m_pollTimer && !m_pollTimer->isActive())
            m_pollTimer->start();

        // 用 info-style 訊息也用 errorOccurred（Manager 可另作處理）
        emit errorOccurred(QString("Connected"));
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
    if (!m_running)
        return;

    if (!m_client || m_client->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit unit(QModbusDataUnit::Coils, 0, 112);
    QModbusReply* reply = m_client->sendReadRequest(unit, 1);

    if (!reply) {
        emit errorOccurred(QString("sendReadRequest failed"));
        return;
    }

    // 將 reply 設為 this 的 child，reply 的信號會在 reply 所屬 thread 發出
    reply->setParent(this);

    // 以 direct connection 或 default 都可 —— reply 與 this 在同一 thread 通常為 direct
    connect(reply, &QModbusReply::finished, this, &ModbusWorker::onReply, Qt::QueuedConnection);
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

void ModbusWorker::writeRegisters(int startAddress, QVector<quint16> values)
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
        unit.setValue(i, values[i]);

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
    if (!m_running || m_client->state() != QModbusDevice::ConnectedState)
    {
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
            qDebug() << "Worker" << m_workerId << "write single coil @ addr:" << address << "success";
            emit writeDone(address, true, "OK");
        }
        else {
            qDebug() << "Worker" << m_workerId << "write single coil error:" << reply->errorString();
            emit writeDone(address, false, reply->errorString());
        }
        reply->deleteLater();
        });
}