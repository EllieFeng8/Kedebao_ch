#pragma once
#include <QObject>
#include <QModbusTcpClient>
#include <QModbusReply>
#include <QTimer>

class ModbusWorker : public QObject
{
    Q_OBJECT
public:
    ModbusWorker(int id, const QString& ip, int port, QObject* parent = nullptr);
    ~ModbusWorker() override = default;

public slots:
    void startWork();
    void stopWork();

private slots:
    void onStateChanged(QModbusDevice::State state);
    void onErrorOccurred(QModbusDevice::Error error);
    void poll();
    void onReply();
public slots:
    void writeCoils(int startAddress, const QVector<bool>& values);
    void writeSingleCoil(int address, bool value);
    void writeRegisters(int startAddress, QVector<quint16> values);
    void readRegisters(int startAddress, int count);

signals:
    void writeDone(int address, bool ok, QString msg);
    void dataReady(QVector<quint16> values);   // Manager 會包裝 workerId
    void errorOccurred(QString msg);           // Manager 會包裝 workerId
    void holdingRegisterReady( QVector<quint16> values);
private:
    int m_workerId;
    QString m_ip;
    int m_port;

    QModbusTcpClient* m_client = nullptr;
    QTimer* m_pollTimer = nullptr;
    QTimer* m_reconnectTimer = nullptr;

    bool m_running = false;
};