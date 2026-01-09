#include <QModbusReply>
#include "MS300.h"

MS300::MS300(QObject* parent) : QObject(parent) {}

void MS300::initPort() {
    m_modbus = new QModbusRtuSerialClient(this);
    m_modbus->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM4");
    m_modbus->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
    m_modbus->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    m_modbus->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    m_modbus->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    m_modbus->setTimeout(200);
    m_modbus->setNumberOfRetries(3);
    if (m_modbus->connectDevice()) {
        qDebug() << "COM4 connet";
        m_pollTimer = new QTimer(this);
        connect(m_pollTimer, &QTimer::timeout, this, &MS300::onPollTimeout);
        m_pollTimer->start(100); // 每輪詢一台，三台共約 0.45秒 更新一次
    }
    else
    {
        qDebug() << "connect COM4 fail";
    }
}
void MS300::onPollTimeout()
{
    //qDebug() << "Timer2 Tick...";
    if (!m_modbus || m_modbus->state() != QModbusDevice::ConnectedState) {
        qDebug() << "Device not connected, state:" << (m_modbus ? m_modbus->state() : -1);
        return;
    }

    int id = m_currentIndex;
    double targetHz = m_targetFreqs[id]; // 抓取 UI 先前存進來的最新值



    // --- 步驟 A: 寫入運轉指令 (2000H) ---
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 0x2000, 2);
    writeUnit.setValue(0, m_targetCmds[id]);
    qDebug() << id << "set mode" << m_targetCmds[id];

    writeUnit.setValue(1, static_cast<quint16>(targetHz * 100));
    qDebug() << id << "set value" << static_cast<quint16>(targetHz * 100);

    writeUnit.setValue(2, m_targetReset[id]);
    
    m_modbus->sendWriteRequest(writeUnit, id);
    m_targetReset[id] = 0;
    // ---讀取
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 0x2103, 1);
    if (auto* reply = m_modbus->sendReadRequest(readUnit, id)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply, id]() {
                if (reply->error() == QModbusDevice::NoError) {
                    const QModbusDataUnit res = reply->result();

                    qDebug() << "COM4 MS300: " << id << " Frequency= " << res.value(0);
                    emit dataUpdated(id,res.value(0));
                }
                else
                {
                    qDebug() << ">>> COM4 Error  ID:" << id << "    :" << reply->errorString();
                }
                reply->deleteLater();
                });
        }
        else { delete reply; }
    }
    m_currentIndex++;
    if (m_currentIndex > 10) {
        m_currentIndex = 1;
    }
}