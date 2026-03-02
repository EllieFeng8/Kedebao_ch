#include "LengthController.h"
#include <QModbusReply>
#include <QSerialPort>
#include <qvariant>
LengthController::LengthController(QObject* parent) : QObject(parent) {}

LengthController::~LengthController() {
    if (m_modbus) {
        m_modbus->disconnectDevice();
        delete m_modbus;
    }
}

void LengthController::initPort() {
    m_modbus = new QModbusRtuSerialClient(this);

    // 設定為 COM2
    m_modbus->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM2");
    m_modbus->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
    m_modbus->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    m_modbus->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    m_modbus->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    m_modbus->setTimeout(500);
    m_modbus->setNumberOfRetries(3);

    if (m_modbus->connectDevice()) {
        qDebug() << "COM2 (Length Controller) Connected";
        m_pollTimer = new QTimer(this);
        connect(m_pollTimer, &QTimer::timeout, this, &LengthController::onPollTimeout);
        m_pollTimer->start(50); // 100ms 輪詢一次
    }
    else {
        qDebug() << "Connect COM2 Fail:" << m_modbus->errorString();
    }
}

void LengthController::onPollTimeout() {
    if (!m_modbus || m_modbus->state() != QModbusDevice::ConnectedState) return;

    // 讀取位址 0 開始的 2 個暫存器 (32-bit)
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 0, 2);

    if (auto* reply = m_modbus->sendReadRequest(readUnit, m_slaveId)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply]() {
                if (reply->error() == QModbusDevice::NoError) {
                    const QModbusDataUnit res = reply->result();

                    quint16 reg0 = res.value(0);
                    quint16 reg1 = res.value(1);

                    // 組合 32 位元整數 (Little-endian: reg1 為高位, reg0 為低位)
                    int32_t pvRaw = (static_cast<int32_t>(reg1) << 16) | (reg0 & 0xFFFF);

                    double pv = static_cast<double>(pvRaw);
                    emit lengthUpdated(pv/100);
                }
                else {
                    qDebug() << "COM2 Read Error:" << reply->errorString();
                }
                reply->deleteLater();
                });
        }
        else {
            delete reply;
        }
    }
}

void LengthController::lengthReset() {
    // 寫入 Coil 0 進行歸零
    QModbusDataUnit writeUnit(QModbusDataUnit::Coils, 0, 1);
    writeUnit.setValue(0, true);

    if (m_modbus && m_modbus->state() == QModbusDevice::ConnectedState) {
        m_modbus->sendWriteRequest(writeUnit, m_slaveId);
        qDebug() << "COM2: Length Reset sent to ID" << m_slaveId;
    }
}

void LengthController::stopPolling() {
    if (m_pollTimer) m_pollTimer->stop();
}