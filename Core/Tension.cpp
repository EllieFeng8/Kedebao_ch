#include "Tension.h"
#include <QModbusReply>
Modbus485::Modbus485(QObject* parent) : QObject(parent) {}

void Modbus485::initPort() {
    m_modbus = new QModbusRtuSerialClient();
    m_modbus->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM3");
    m_modbus->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud19200);
    m_modbus->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    m_modbus->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    m_modbus->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    m_modbus->setTimeout(100);
    m_modbus->setNumberOfRetries(1);

    // [優化] 監聽執行時期的錯誤
    connect(m_modbus, &QModbusDevice::errorOccurred, this, [this](QModbusDevice::Error error) {
        if (error != QModbusDevice::NoError) {
            emit connectionFailed(m_modbus->errorString());
        }
        });


    if (m_modbus->connectDevice()) {
        qDebug() << "COM3 connect success";
        m_pollTimer = new QTimer(this);
        //connect(m_pollTimer, &QTimer::timeout, this, &Modbus485::onPollTimeout);
        //m_pollTimer->start(50);
        QTimer::singleShot(60, this, &Modbus485::onPollTimeout);
    }
    else {
        QString err = "connect COM3 fail: " + m_modbus->errorString();
        qDebug() << err;

        // --- 關鍵修改：發出訊號 ---
        emit connectionFailed(err);
    }
    //m_modbus2 = new QModbusRtuSerialClient();
    //m_modbus2->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM1");
    //m_modbus2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud19200);
    //m_modbus2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    //m_modbus2->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    //m_modbus2->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    //m_modbus2->setTimeout(100);
    //m_modbus2->setNumberOfRetries(1);

    //// [優化] 監聽執行時期的錯誤
    //connect(m_modbus2, &QModbusDevice::errorOccurred, this, [this](QModbusDevice::Error error) {
    //    if (error != QModbusDevice::NoError) {
    //        emit connectionFailed(m_modbus2->errorString());
    //    }
    //    });

    //if (m_modbus2->connectDevice()) {
    //    qDebug() << "COM1 connect success";
    //    //m_pollTimer2 = new QTimer(this);
    //    //connect(m_pollTimer, &QTimer::timeout, this, &Modbus485::onPollTimeout);
    //    //m_pollTimer->start(50);
    //    QTimer::singleShot(20, this, &Modbus485::onPollTimeout);

    //}
    //else {
    //    QString err = "connect COM1 fail: " + m_modbus2->errorString();
    //    qDebug() << err;

    //    // --- 關鍵修改：發出訊號 ---
    //    emit connectionFailed(err);
    //}
}

void Modbus485::readPV(int slaveId) {
    if (m_modbus->state() != QModbusDevice::ConnectedState) return;

    // 位址 0x02F8 (760), 讀取 1 個長度
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 514, 2);


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

//void Modbus485::onPollTimeout() {
//
//    //qDebug() << "Timer Tick..."; // <--- 加入這一行偵測
//    if (!m_modbus || m_modbus->state() != QModbusDevice::ConnectedState) {
//        qDebug() << "Device not connected, state:" << (m_modbus ? m_modbus->state() : -1);
//        QTimer::singleShot(1000, this, &Modbus485::onPollTimeout);  
//        return;
//    }
//
//    if (!m_writeQueue.isEmpty()) {
//        WriteTask task = m_writeQueue.dequeue();
//        QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, task.address, 1);
//        writeUnit.setValue(0, task.value);
//
//        if (auto* reply = m_modbus->sendWriteRequest(writeUnit, task.id)) {
//            connect(reply, &QModbusReply::finished, this, [this, reply]() {
//                reply->deleteLater();
//                // 寫入完成後，稍等 20ms 觸發下一次動作
//                QTimer::singleShot(20, this, &Modbus485::onPollTimeout);
//                });
//        }
//        return; // 發送寫入後立即返回，等待 finished 信號
//    }
//
//
//       //int id = m_slaveIds[m_currentIndex];
//       int id = m_slaveIds[m_currentIndex];
//
//    // 一次讀取 PV, SV, TQO (雖然不完全連續，但說明書建議區塊讀取)
//    // 這裡示範讀取 02F0H 開始的 10 個暫存器
//    QModbusDataUnit readUnit;
//    if (id <= 3) {
//        // 處理 TC-3050 (ID 1, 2, 3)
//        readUnit = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 752, 6);
//    }
//
//
//    if (auto* reply = m_modbus->sendReadRequest(readUnit, id)) {
//        if (!reply->isFinished()) {
//            connect(reply, &QModbusReply::finished, this, [this, reply, id]() {
//                if (reply->error() == QModbusDevice::NoError) {
//                    const QModbusDataUnit res = reply->result();
//
//                    if (id <= 3) {
//                        // --- TC-3050  ---
//                        double tqo = res.value(0) / 40.95; // 02F0H
//                        double pv = res.value(4) / 10.0;  // 02F4H
//                        //qDebug() << "TC-3050 ID:" << id << "PV:" << pv ;
//                        emit dataUpdated(id, pv, tqo);
//                    }
//                }   
//                else
//                {
//                    qDebug() << ">>>COM3 Error  ID:" << id << "    :" << reply->errorString();
//                    emit connectionFailed(reply->errorString());
//                }
//                reply->deleteLater();
//                m_currentIndex = (m_currentIndex + 1) % m_slaveIds.size();
//                QTimer::singleShot(20, this, &Modbus485::onPollTimeout);
//
//                });
//        }
//        else 
//        {
//            delete reply; 
//            QTimer::singleShot(20, this, &Modbus485::onPollTimeout);
//        }
//    }
//
//}

void Modbus485::onPollTimeout() {
    if (!m_modbus || m_modbus->state() != QModbusDevice::ConnectedState) {
        QTimer::singleShot(1000, this, &Modbus485::onPollTimeout);
        return;
    }

    // 優先權 1：處理寫入
    if (!m_writeQueue.isEmpty()) {
        WriteTask task = m_writeQueue.dequeue();

            QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, task.address, 1);
            writeUnit.setValue(0, task.value);

            auto* reply = m_modbus->sendWriteRequest(writeUnit, task.id);
            if (reply) {
                connect(reply, &QModbusReply::finished, this, [this, reply, task]() {
                    if (reply->error() != QModbusDevice::NoError) {
                        qDebug() << "Write Fail! ID:" << task.id
                            << "Addr:" << task.address
                            << "Error:" << reply->errorString();
                    }
                    else {

                        qDebug() << "Write Success! ID:" << task.id;
                    }
                    reply->deleteLater();
                    QTimer::singleShot(50, this, &Modbus485::onPollTimeout);
                    });
            }
            else {
                QTimer::singleShot(50, this, &Modbus485::onPollTimeout);
            }
            return;
    }
    //QModbusDataUnit readpid(QModbusDataUnit::HoldingRegisters, 570, 1);

    //auto* replypid = m_modbus->sendReadRequest(readpid, 1);
    //if (replypid) {
    //    connect(replypid, &QModbusReply::finished, this, [this, replypid]() {
    //        if (replypid->error() == QModbusDevice::NoError) {
    //            const QModbusDataUnit res = replypid->result();
    //            for (uint i = 0; i < res.valueCount(); ++i) {
    //                int addr = res.startAddress() + i;
    //                quint16 value = res.value(i);

    //                qDebug() <<addr <<"&&:"
    //                    << value;
    //            }
    //        }
    //        else {
    //            qDebug() << "Com Error ID:" << 1 << replypid->errorString();
    //        }
    //        replypid->deleteLater();
    //        }
    //    );
    //}
    // 優先權 2：處理輪詢讀取
    //if (m_slaveIds.isEmpty()) return;
    int id = m_slaveIds[m_currentIndex];

        QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 758, 1);

        auto* reply = m_modbus->sendReadRequest(readUnit, id);
        if (reply) {
            connect(reply, &QModbusReply::finished, this, [this, reply, id]() {
                if (reply->error() == QModbusDevice::NoError) {
                    const QModbusDataUnit res = reply->result();
                    if (id <= 3) {
                        double tqo = res.value(0) / 40.95;
                        double pv = res.value(0) / 10.0;
                        emit dataUpdated(id, pv, tqo);
                    }
                }
                else {
                    qDebug() << "Com Error ID:" << id << reply->errorString();
                }
                reply->deleteLater();

                // 指標移向下一台
                m_currentIndex = (m_currentIndex + 1) % m_slaveIds.size();
                QTimer::singleShot(30, this, &Modbus485::onPollTimeout);
                });
        }
        else {
            // 發送失敗也要跳下一個 ID，否則輪詢會卡死在同一台
            m_currentIndex = (m_currentIndex + 1) % m_slaveIds.size();
            QTimer::singleShot(30, this, &Modbus485::onPollTimeout);
        }
}

void Modbus485::setTargetTension(int id, double kg) 
{
    // 根據手冊，SV 位址為 0x0202 
    // 通常張力解析度為 0.1，故數值需乘以 10 
    
        WriteTask task;
        task.id = id;
        task.address = 0x0202; // SV 位址
        task.value = static_cast<quint16>(kg * 10);

        m_writeQueue.enqueue(task);
        qDebug() << "Queueing SV set:" << kg << "kg for Slave" << id;
    
    //quint16 sendVal = static_cast<quint16>(kg * 10);

    //QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 0x0202, 1);
    //writeUnit.setValue(0, sendVal);

    //if (m_modbus && m_modbus->state() == QModbusDevice::ConnectedState) {
    //    m_modbus->sendWriteRequest(writeUnit, id);
    //    qDebug() << "Slave" << id << "set  SV :" << sendVal ;
    //}
}

