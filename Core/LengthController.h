#pragma once

#include <QObject>
#include <QModbusRtuSerialClient>
#include <QModbusDataUnit>
#include <QTimer>
#include <QDebug>

class LengthController : public QObject {
    Q_OBJECT

public:
    explicit LengthController(QObject* parent = nullptr);
    ~LengthController();

signals:
    // 當長度更新時發送此訊號
    void lengthUpdated(double val);
    void errorOccurred(QString error);

public slots:
    void initPort();            // 初始化 COM2
    void lengthReset();         // ID 6 歸零功能
    void stopPolling();         // 停止輪詢

private slots:
    void onPollTimeout();       // 定時讀取資料

private:
    QModbusRtuSerialClient* m_modbus = nullptr;
    QTimer* m_pollTimer = nullptr;
    const int m_slaveId = 6;    // 固定處理 ID 6
    bool reset = false;
};