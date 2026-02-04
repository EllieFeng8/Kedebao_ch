#pragma once

#include <QObject>
#include <QModbusRtuSerialMaster>
#include <QModbusDataUnit>
#include <QTimer>
#include <QDebug>
#include <qvariant>
#include <QModbusClient>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QModbusRtuSerialClient>
#include <qthread>

// 定義說明書中的暫存器位址 (轉換為 10 進制)
enum TC3050_Addr {
    ADDR_PV = 0x02F8,      // 760: 現在張力 (顯示值)
    ADDR_SV = 0x0202,      // 514: 設定張力
    ADDR_TQO = 0x02F0,     // 752: 輸出百分比 (對應 YTMC-5318 的強度)
    ADDR_CONTROL = 0x02D0, // 720: 運轉控制位元 (Bit0=Run)
    ADDR_STATUS = 0x02E0   // 736: 狀態位元 (Bit0=Run, Bit1=Auto)
};




class Modbus485 : public QObject {
    Q_OBJECT

public:
    explicit Modbus485(QObject* parent = nullptr);

    //static Modbus485* instance() {
    //    static Modbus485 _instance;
    //    return &_instance;
    //}
    Modbus485(const Modbus485&) = delete;
    Modbus485& operator=(const Modbus485&) = delete;

    void readPV(int slaveId);
signals:
    void dataUpdated(int id,double pv,double tqo);


    void errorOccurred(int id, QString error);

public slots:
    void initPort();
    void setTargetTension(int id, double kg);
    void cleanup() {
        if (m_pollTimer) {
            m_pollTimer->stop();
            m_pollTimer->deleteLater();
            m_pollTimer = nullptr;
        }
        if (m_modbus) {
            m_modbus->disconnectDevice();
            m_modbus->deleteLater();
            m_modbus = nullptr;
        }
        QThread::currentThread()->quit();
        qDebug() << "MS300 resources cleaned up.";
    }

private slots:
    void onPollTimeout();



private:
    double sv;
    QModbusRtuSerialClient* m_modbus = nullptr; 

    QTimer* m_pollTimer = nullptr;

    QList<int> m_slaveIds = { 1,2,3,4,5}; 
    int m_currentIndex = 0;
};