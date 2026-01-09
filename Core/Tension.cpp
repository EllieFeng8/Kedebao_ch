#include "Tension.h"
#include <QModbusReply>
Modbus485::Modbus485(QObject* parent) : QObject(parent) {}

void Modbus485::initPort() {
    m_modbus = new QModbusRtuSerialClient(this);
    m_modbus->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM3");
    m_modbus->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
    m_modbus->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    m_modbus->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    m_modbus->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    m_modbus->setTimeout(500);
    m_modbus->setNumberOfRetries(3);

    if (m_modbus->connectDevice()) {
        qDebug() << "COM3 connet";
        m_pollTimer = new QTimer(this);
        connect(m_pollTimer, &QTimer::timeout, this, &Modbus485::onPollTimeout);
        m_pollTimer->start(500); // 每輪詢一台，三台共約 0.45秒 更新一次
        //Test set SV
        setTargetTension(1, 20);
        setTargetTension(2, 5);
        setTargetTension(3, 3);
    }
    else
    {
        qDebug() << "connect COM3 fail";
    }
}

void Modbus485::readPV(int slaveId) {
    if (m_modbus->state() != QModbusDevice::ConnectedState) return;

    // 位址 0x02F8 (760), 讀取 1 個長度
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 514, 2);

    // 注意：sendReadRequest 用法不變，第二個參數仍是 Slave ID
    if (auto* reply = m_modbus->sendReadRequest(readUnit, slaveId)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply, slaveId]() {
                if (reply->error() == QModbusDevice::NoError) {
                    const QModbusDataUnit res = reply->result();
                    qDebug() << "Slave" << slaveId << "現在張力:" << res.value(0);
                }
                reply->deleteLater();
                });
        }
        else {
            delete reply;
        }
    }
}

void Modbus485::onPollTimeout() {

    //qDebug() << "Timer Tick..."; // <--- 加入這一行偵測
    if (!m_modbus || m_modbus->state() != QModbusDevice::ConnectedState) {
        qDebug() << "Device not connected, state:" << (m_modbus ? m_modbus->state() : -1);
        return;
    }
       //int id = m_slaveIds[m_currentIndex];
       int id = m_slaveIds[m_currentIndex];

    // 一次讀取 PV, SV, TQO (雖然不完全連續，但說明書建議區塊讀取)
    // 這裡示範讀取 02F0H 開始的 10 個暫存器
    QModbusDataUnit readUnit;
    if (id <= 3) {
        // 處理 TC-3050 (ID 1, 2, 3)
        readUnit = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 752, 10);
    }
    else {
        // 處理 YTMC-5318 (ID 4, 5)
        // 假設讀取從 0x0001 開始的 2 個暫存器
        readUnit = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 0x294, 2);
    }

    if (auto* reply = m_modbus->sendReadRequest(readUnit, id)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply, id]() {
                if (reply->error() == QModbusDevice::NoError) {
                    const QModbusDataUnit res = reply->result();

                    if (id <= 3) {
                        // --- TC-3050  ---
                        double tqo = res.value(0) / 40.95; // 02F0H
                        double pv = res.value(6) / 100.0;  // 02F6H
                        qDebug() << "TC-3050 ID:" << id << "PV:" << pv << "TQO:" << tqo;
                        emit dataUpdated(id, pv, tqo);
                    }
                    else {
                        // --- YTMC-5318  ---
                        // 假設 YTMC 的數值就是強度 (0-1000)
                        double val = res.value(0);
                        qDebug() << "YTMC-5318 ID:" << id << "Value:" << val;
                        // 您可以視需求發送不同的信號或共用 dataUpdated
                        emit dataUpdated(id, val, 0);
                    }
                }   
                else
                {
                    qDebug() << ">>>COM3 Error  ID:" << id << "    :" << reply->errorString();
                }
                reply->deleteLater();
                });
        }
        else { delete reply; }
    }
    m_currentIndex = (m_currentIndex + 1) % m_slaveIds.size();
}

void Modbus485::setTargetTension(int id, double kg) {
    // 根據手冊，SV 位址為 0x0202 
    // 通常張力解析度為 0.1，故數值需乘以 10 
    quint16 sendVal = static_cast<quint16>(kg * 10);

    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 0x0202, 1);
    writeUnit.setValue(0, sendVal);

    if (m_modbus && m_modbus->state() == QModbusDevice::ConnectedState) {
        m_modbus->sendWriteRequest(writeUnit, id);
        qDebug() << "Slave" << id << "設定 SV 為:" << sendVal ;
    }
}

