#pragma once
#include <cstdint>
#include <QDebug>
#include <QObject>
#include <QMutex>
#include <QTimer>
#include "bdaqctrl.h"
using namespace Automation::BDaq;

class DIOModule
    : public QObject
{
    Q_OBJECT
public:
    explicit DIOModule(QObject* parent = nullptr);
    ~DIOModule();

    bool initialize(const wchar_t* deviceDescription = L"MOS-1110Y-01,BID#0");

    // DI
    bool readInputs(uint8_t& port0, uint8_t& port1);

    // DO
    bool readOutputs(uint8_t& value);
    //bool setOutput(int bit, bool high);
public slots:
    void process();
    bool setOutput(int bit, bool high);
    void stop() { if(m_timer)m_timer->stop(); }
signals:
    void dioUpdated(uint8_t p0, uint8_t p1, uint8_t out);
    void errorOccurred(QString msg);
    void bitChanged(int bitIndex, bool state);
private:
    QTimer* m_timer= nullptr;
    DIOModule(const DIOModule&) = delete;
    DIOModule& operator=(const DIOModule&) = delete;
    InstantDiCtrl* diCtrl;
    InstantDoCtrl* doCtrl;
    uint8_t currentOutputState;
    QMutex mutex;
    bool m_running = true;
    uint16_t lastState = 0;
};

