#pragma once
#include <cstdint>
#include <QDebug>
#include <QObject>
#include <QMutex>
#include "bdaqctrl.h"
using namespace Automation::BDaq;

class DIOModule
    : public QObject
{
    Q_OBJECT
public:
    static DIOModule& instance();

    bool initialize(const wchar_t* deviceDescription = L"MOS-1110Y-01,BID#0");

    // DI
    bool readInputs(uint8_t& port0, uint8_t& port1);

    // DO
    bool readOutputs(uint8_t& value);
    bool setOutput(int bit, bool high);

private:
    explicit DIOModule(QObject* parent = nullptr);
    ~DIOModule();
    DIOModule(const DIOModule&) = delete;
    DIOModule& operator=(const DIOModule&) = delete;
    InstantDiCtrl* diCtrl;
    InstantDoCtrl* doCtrl;
    uint8_t currentOutputState;
    QMutex mutex;
};

