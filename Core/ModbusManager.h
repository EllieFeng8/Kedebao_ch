#pragma once
#include <QObject>
#include <QMap>
#include <QThread>
#include "ModbusWorker.h"

class ModbusManager : public QObject
{
    Q_OBJECT
public:
    explicit ModbusManager(QObject* parent = nullptr);
    ~ModbusManager();

    void createWorker(const QString& ip, int port);
    void startAll();
    void stopAll();
    void writeSingleCoil( int address, bool value);
    void writeCoils(int startAddress, const QVector<bool>& values);
    void writeRegisters(int startAddress, const QVector<quint16>& values);
    void readRegisters(int startAddress, int count);
signals:
    void workerData(QVector<quint16> v);
    void workerError(QString msg);
    void holdingRegisterReady(QVector<quint16> values);
    void workerWriteDone( int address, bool ok, QString msg);

private:

        QThread* m_thread;
        ModbusWorker* m_worker;

};