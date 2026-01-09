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

class MS300 : public QObject {
    Q_OBJECT

public:
    // 取得唯一實例的靜態函式
    static MS300* instance() {
        static MS300 _instance;
        return &_instance;
    }
    MS300(const MS300&) = delete;
    MS300& operator=(const MS300&) = delete;


signals:
    void dataUpdated(int id ,double v);

    void errorOccurred(int id, QString error);

public slots:
    void initPort();
    // UI 呼叫此 Slot 來更新value
    void updateFreqCache(int id, double hz) {
        if (id >= 1 && id <= 10) m_targetFreqs[id] = hz;
    }
    // UI 呼叫此 Slot 來更新運轉狀態
    void updateControlCache(int id, quint16 cmd) {
        if (id >= 1 && id <= 10) m_targetCmds[id] = cmd;
    }
    void updateResetCache(int id, quint16 val) {
        if (id >= 1 && id <= 10) m_targetReset[id] = val;
    }
private slots:
    void onPollTimeout();

private:
    double m_targetFreqs[11]; //  2001H (頻率)
    quint16 m_targetCmds[11]; //  2000H (mode)
    quint16 m_targetReset[11];//  2002H (Reset 指令位址)
    explicit MS300(QObject* parent = nullptr);
    QModbusRtuSerialClient* m_modbus = nullptr; 
    QTimer* m_pollTimer = nullptr;

    int m_currentIndex = 1;
};