#pragma once

#include <QObject>
#include <Qmutex>
#include <Qvector>
#include "ModbusManager.h"
#include "DIOModule.h"
#include "Tension.h"
#include "MS300.h"
#include <QQmlEngine>
#include "KdbProxy.h"

class Core : public QObject
{
    Q_OBJECT
        QML_ELEMENT
public:
    QVector<quint16> DataValues;
    KdbProxy* m_proxy;
    static Core* instance();  // Singleton entry
    void addModbusServer(QString ip, int port);
    void startAll();
    void stopAll();
    void writeSingleCoil(int address, bool value);

    void writeCoils(int startAddress, const QVector<bool>& values);
    void writeRegisters(int startAddr, const QVector<quint16>& values);
    void readRegisters(int startAddress, int count);

    void initDIO();
    void readDIO();
    void write485(int id, double velue);
    void read485(int id);
    void setOutputBit(int bit, bool high);
    void setFreq(int id, double value);
    void setMS300Run(int id, int mode);
    void resetMS300(int id);
    void loadSavedData();

signals:
    void holdingRegisterReady(QVector<quint16> values);
    //void newDataReady( QVector<quint16> values);
    //void WorkerError( QString message);
    //void newTensionData(int id, double PV, double tqo);
    //void newMS300Data(int id, double v);
    //void dioUpdated(uint8_t port0, uint8_t port1, uint8_t output);

private slots:
    // ¨Ó¦Û ModbusManager
    void onholdingRegisterReady(QVector<quint16> values);
    void onWorkerData(QVector<quint16> values);
    void onWorkerError(QString msg);
    void on485Data(int id, double pv, double tqo);
    void onMS300Data(int id, double v);
private:
    explicit Core(QObject* parent = nullptr);
    static Core* m_instance;
    static QMutex m_mutex;

    ModbusManager* m_manager{ nullptr };
};