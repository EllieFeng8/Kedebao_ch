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
#include <QQueue>


struct WriteTask {
    int id;
    int address;
    quint16 value;
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
    void lengthupdate(double val);
    void connectionFailed(const QString& errorMsg);
    void errorOccurred(int id, QString error);

public slots:
    void initPort();
    void setTargetTension(int id, double kg);
    //void executeWriteSync(WriteTask task);
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
    //void lengthReset();
private slots:
    void onPollTimeout();
    //void onPollTimeout2();



private:
    double sv;
    QModbusRtuSerialClient* m_modbus = nullptr; 
    QModbusRtuSerialClient* m_modbus2 = nullptr;
    QModbusRtuSerialClient* m_modbus3 = nullptr;

    QTimer* m_pollTimer = nullptr;
    QTimer* m_pollTimer2 = nullptr;

    QList<int> m_slaveIds = { 1,2,3}; 
    int m_currentIndex = 0;
    QQueue<WriteTask> m_writeQueue;
};