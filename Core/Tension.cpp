#include "Tension.h"
#include <QModbusReply>
Modbus485::Modbus485(QObject* parent) : QObject(parent) {}

void Modbus485::initPort() {
    m_modbus = new QModbusRtuSerialClient();
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
        m_pollTimer->start(100);
        //Test set SV

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
        readUnit = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 752, 6);
    }
    else if (id == 6)
    {
        // 處理 碼輪控制器
      
        readUnit = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 0, 2);
    }

    if (auto* reply = m_modbus->sendReadRequest(readUnit, id)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply, id]() {
                if (reply->error() == QModbusDevice::NoError) {
                    const QModbusDataUnit res = reply->result();

                    if (id <= 3) {
                        // --- TC-3050  ---
                        double tqo = res.value(0) / 40.95; // 02F0H
                        double pv = res.value(4) / 10.0;  // 02F4H
                        //qDebug() << "TC-3050 ID:" << id << "PV:" << pv ;
                        emit dataUpdated(id, pv, tqo);
                    }
                    //else if(id>=4){
                    //    // --- YTMC-5318  ---
                    //    // 假設 YTMC 的數值就是強度 (0-1000)
                    //    double val = res.value(0);
                    //    //qDebug() << "YTMC-5318 ID:" << id << "Value:" << val;
                    //    // 您可以視需求發送不同的信號或共用 dataUpdated
                    //    emit dataUpdated(id, val, 0);
                    //}
                    else if (id == 6) {
                        quint16 reg0 = res.value(0);
                        quint16 reg1 = res.value(1);

                        // 方案 A: 如果 132186112 太大，表示 reg0 是高位且內含資料
                        // 方案 B: 嘗試以 reg1 作為高位，reg0 作為低位 (Little-endian 方式組合)
                        // 根據說明書 PV 範圍，我們使用有號 32 位元整數 (int32_t)
                        int32_t pvRaw = (static_cast<int32_t>(reg1) << 16) | (reg0 & 0xFFFF);

                        // 如果數值還是不對，請換回這行試試：
                        // int32_t pvRaw = (static_cast<int32_t>(reg0) << 16) | (reg1 & 0xFFFF);

                        double pv = static_cast<double>(pvRaw);
                        qDebug() << "Slave 6 PV (32bit):" << pv;                  
                        emit lengthupdate(pv);
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
        qDebug() << "Slave" << id << "set  SV :" << sendVal ;
    }
}

void Modbus485::lengthReset()
{
    QModbusDataUnit writeUnit(QModbusDataUnit::Coils, 0, 1);
    writeUnit.setValue(0, true);

    if (m_modbus && m_modbus->state() == QModbusDevice::ConnectedState) {
        m_modbus->sendWriteRequest(writeUnit, 6);
        qDebug() << "length Reset";
    }
}