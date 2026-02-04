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
    QVector<quint16> DataValues ;
    QVector<quint16> DataValues2;

    KdbProxy* m_proxy=nullptr;
    
    MS300* m_ms300 = nullptr;
    QThread* threadMS300 = nullptr;

    Modbus485* m_tension = nullptr;
    QThread* threadTension=nullptr;
    
    QThread* threadDIO = nullptr;
    DIOModule* dioWorker = nullptr;

    static Core& instance();  // Singleton entry

    void addModbusServer(QString ip, int port);
    void startAll();
    void stopAll();
    //void writeSingleCoil(int address, bool value);

    void writeCoils(int startAddress, const QVector<bool>& values);
    void writeRegister(int startAddr, const quint16 &value);
    void readRegisters(int startAddress, int count);

    void init() {
        m_proxy = new KdbProxy(this);
        m_manager = new ModbusManager(this);

        threadDIO = new QThread(this);
        dioWorker = new DIOModule(); // 注意不要給父類別，否則無法 moveToThread

        // 2. 移動到執行緒
        dioWorker->moveToThread(threadDIO);

        // 3. 建立連線
        // 當執行緒啟動時，先初始化硬體，再開始循環
        connect(threadDIO, &QThread::started, [this]() {
            if (dioWorker->initialize()) {
                dioWorker->process();
            }
            else {
                qDebug() << "DIO Initialization Failed!";
            }
            });
        connect(dioWorker, &DIOModule::bitChanged, this, &Core::handleDIOSignal);

        threadDIO->start();

        //threadTension = new QThread(this);
        //Modbus485::instance()->moveToThread(threadTension);
        //connect(threadTension, &QThread::started, Modbus485::instance(), &Modbus485::initPort);
 
        //threadTension->start();

        m_tension = new Modbus485(); // 注意：不要給 parent (this)，否則不能 moveToThread
        threadTension = new QThread(this);
        m_tension->moveToThread(threadTension);

        // 啟動連線
        connect(threadTension, &QThread::started, m_tension, &Modbus485::initPort);

        // 銷毀連線：當 thread 停止時，自動在 thread 內呼叫 deleteLater 釋放 m_tension
        connect(threadTension, &QThread::finished, m_tension, &QObject::deleteLater);

        threadTension->start();
      /*  threadMS300 = new QThread(this);
        MS300::instance()->moveToThread(threadMS300);
        connect(threadMS300, &QThread::started, MS300::instance(), &MS300::initPort);
        connect(MS300::instance(), &MS300::dataUpdated, this, &Core::onMS300Data);

        threadMS300->start();*/
        m_ms300 = new MS300(); // 不要給 Parent，因為要 moveToThread
        threadMS300 = new QThread(this);
        m_ms300->moveToThread(threadMS300);

        // 連接銷毀訊號：執行緒結束時，自動刪除物件
        connect(threadMS300, &QThread::finished, m_ms300, &QObject::deleteLater);
        connect(threadMS300, &QThread::started, m_ms300, &MS300::initPort);
        connect(m_ms300, &MS300::dataUpdated, this, &Core::onMS300Data);

        threadMS300->start();
    

        connect(m_tension, &Modbus485::dataUpdated,
            this, &Core::on485Data);

        connect(m_manager, &ModbusManager::workerData,
            this, &Core::onWorkerData);
        connect(m_manager, &ModbusManager::workerData2,
            this, &Core::onWorkerData2);

        connect(m_manager, &ModbusManager::workerError,
            this, &Core::onWorkerError);

        connect(m_manager, &ModbusManager::holdingRegisterReady,
            this, &Core::onholdingRegisterReady);
        connect(m_manager, &ModbusManager::Zerospeed01,
            this, &Core::onZeroSpeed01);
        connect(m_manager, &ModbusManager::Zerospeed02,
            this, &Core::onZeroSpeed02);


        DataValues.resize(112);
//目前開啟程式預設開啟Auto 所以預設Auto的幾個位置=1
        //DataValues[81] = 1;
        //DataValues[83] = 1;
        //DataValues[85] = 1;
        //DataValues[87] = 1;
        //DataValues[88] = 1;
        //
        DataValues2.resize(16);


        onWorkerData(DataValues);

        m_manager->createWorker();




        coreConnect();

 

    }

    void initDIO();
    void readDIO();
    void write485(int id, double velue);
    void read485(int id);
    void setOutputBit(int bit, bool high);
    void setFreq(int id, double value);
    void setMS300Run(int id, int mode);
    void resetMS300(int id);
    void loadSavedData();
    void writeRegisters(double v)
    {
        QVector<double> values;
        values.resize(4);
        values.fill(v);
        m_manager->writeRegisters(values);
    }
    void updateProxyProperty(int index, quint16 value);
    void handleDIOSignal(int bitIndex, bool state);

    void coreConnect()
    {
        //ADAM-5000  5056SO Output
        QObject::connect(m_proxy, &KdbProxy::vfdAlarmResetChanged, m_manager, &ModbusManager::VfdAlarmReset);
        QObject::connect(m_proxy, &KdbProxy::unwinderForwardChanged, m_manager, &ModbusManager::UnwinderForward);
        QObject::connect(m_proxy, &KdbProxy::unwinderReverseChanged, m_manager, &ModbusManager::UnwinderReverse);
        QObject::connect(m_proxy, &KdbProxy::mainDriveForwardChanged, m_manager, &ModbusManager::MainDriveForward);
        QObject::connect(m_proxy, &KdbProxy::mainDriveReverseChanged, m_manager, &ModbusManager::MainDriveReverse);
        QObject::connect(m_proxy, &KdbProxy::smallWinderForwardChanged, m_manager, &ModbusManager::SmallWinderForward);
        QObject::connect(m_proxy, &KdbProxy::smallWinderReverseChanged, m_manager, &ModbusManager::SmallWinderReverse);
        QObject::connect(m_proxy, &KdbProxy::largeWinderForwardChanged, m_manager, &ModbusManager::LargeWinderForward);
        QObject::connect(m_proxy, &KdbProxy::largeWinderReverseChanged, m_manager, &ModbusManager::LargeWinderReverse);
        QObject::connect(m_proxy, &KdbProxy::smallCutterStartChanged, m_manager, &ModbusManager::SmallCutterStart);
        QObject::connect(m_proxy, &KdbProxy::selvedgeFanStartChanged, m_manager, &ModbusManager::SelvedgeFanStart);
        QObject::connect(m_proxy, &KdbProxy::largeCutterStartChanged, m_manager, &ModbusManager::LargeCutterStart);
        QObject::connect(m_proxy, &KdbProxy::leftSelvedgeWinderForwardChanged, m_manager, &ModbusManager::LeftSelvedgeWinderForward);
        QObject::connect(m_proxy, &KdbProxy::leftSelvedgeWinderReverseChanged, m_manager, &ModbusManager::LeftSelvedgeWinderReverse);
        QObject::connect(m_proxy, &KdbProxy::rightSelvedgeWinderForwardChanged, m_manager, &ModbusManager::RightSelvedgeWinderForward);
        QObject::connect(m_proxy, &KdbProxy::rightSelvedgeWinderReverseChanged, m_manager, &ModbusManager::RightSelvedgeWinderReverse);
        QObject::connect(m_proxy, &KdbProxy::webAlignerStartChanged, m_manager, &ModbusManager::WebAlignerStart);
        QObject::connect(m_proxy, &KdbProxy::unwindingTensionAutoChanged, m_manager, &ModbusManager::UnwindingTensionAuto);
        QObject::connect(m_proxy, &KdbProxy::unwindingDiameterResetChanged, m_manager, &ModbusManager::UnwindingDiameterRe);
        QObject::connect(m_proxy, &KdbProxy::smallWinderTensionAutoChanged, m_manager, &ModbusManager::SmallWinderTensionAuto);
        QObject::connect(m_proxy, &KdbProxy::smallWinderDiameterResetChanged, m_manager, &ModbusManager::SmallWinderDiameterRe);
        QObject::connect(m_proxy, &KdbProxy::largeWinderTensionAutoChanged, m_manager, &ModbusManager::LargeWinderTensionAuto);
        QObject::connect(m_proxy, &KdbProxy::largeWinderDiameterResetChanged, m_manager, &ModbusManager::LargeWinderDiameterRe);
        QObject::connect(m_proxy, &KdbProxy::leftSelvedgeWinderAutoChanged, m_manager, &ModbusManager::LeftSelvedgeWinderAuto);
        QObject::connect(m_proxy, &KdbProxy::rightSelvedgeWinderAutoChanged, m_manager, &ModbusManager::RightSelvedgeWinderAuto);
        QObject::connect(m_proxy, &KdbProxy::nipRollUpChanged, m_manager, &ModbusManager::NipRollUp);
        QObject::connect(m_proxy, &KdbProxy::nipRollDownChanged, m_manager, &ModbusManager::NipRollDown);
        QObject::connect(m_proxy, &KdbProxy::leftPressPlateForwardChanged, m_manager, &ModbusManager::LeftPressPlateForward);
        QObject::connect(m_proxy, &KdbProxy::leftPressPlateBackwardChanged, m_manager, &ModbusManager::LeftPressPlateBackward);
        QObject::connect(m_proxy, &KdbProxy::rightPressPlateForwardChanged, m_manager, &ModbusManager::RightPressPlateForward);
        QObject::connect(m_proxy, &KdbProxy::rightPressPlateBackwardChanged, m_manager, &ModbusManager::RightPressPlateBackward);
        QObject::connect(m_proxy, &KdbProxy::smallCutterInChanged, m_manager, &ModbusManager::SmallCutterIn);
        QObject::connect(m_proxy, &KdbProxy::largeCutterInChanged, m_manager, &ModbusManager::LargeCutterIn);
        QObject::connect(m_proxy, &KdbProxy::modeSelectChanged, m_manager, &ModbusManager::ModeSelect);
        QObject::connect(m_proxy, &KdbProxy::runIndicatorChanged, this, &Core::ontest);
        QObject::connect(m_proxy, &KdbProxy::alarmIndicatorChanged, m_manager, &ModbusManager::AlarmIndicator);
        QObject::connect(m_proxy, &KdbProxy::stopIndicatorChanged, this, &Core::ontest2);
        QObject::connect(m_proxy, &KdbProxy::buzzerChanged, m_manager, &ModbusManager::Buzzer);
        QObject::connect(m_proxy, &KdbProxy::smallRollModeSelectChanged, m_manager, &ModbusManager::SmallRollModeSelect);
        
        //UI主畫面 設定張力值
        QObject::connect(m_proxy, &KdbProxy::modifyUnwindingTensionChanged, this, &Core::setTensionSV_1);
        QObject::connect(m_proxy, &KdbProxy::modifySmallWinderTensionOverChanged, this, &Core::setTensionSV_2);
        QObject::connect(m_proxy, &KdbProxy::modifyLargeWinderTensionOverChanged, this, &Core::setTensionSV_3);
        QObject::connect(m_proxy, &KdbProxy::modifySpeedChanged, this,&Core::writeRegisters);

        //ADAM-5000  5024 Analog Output  

        QObject::connect(m_proxy, &KdbProxy::modifyAnalogOutUnwinderMainDriveChanged, m_manager, &ModbusManager::writeRegister56);
        QObject::connect(m_proxy, &KdbProxy::modifyAnalogOutWinderChanged, m_manager, &ModbusManager::writeRegister57);
        QObject::connect(m_proxy, &KdbProxy::modifyAnalogOutCutterChanged, m_manager, &ModbusManager::writeRegister58);
        QObject::connect(m_proxy, &KdbProxy::modifyAnalogOutSelvedgeWinderChanged, m_manager, &ModbusManager::writeRegister59);


    }
public slots:
    void writeSingleCoil(int address, double value);
    void setTensionSV_1(double v);
    void setTensionSV_2(double v);
    void setTensionSV_3(double v);
    void ontest(bool v) 
    {
        handleDIOSignal(0, v);
    }
    void ontest2(bool v)
    {
        handleDIOSignal(1, v);
    }
signals:
    void holdingRegisterReady(QVector<quint16> values);
    //void newDataReady( QVector<quint16> values);
    //void WorkerError( QString message);
    //void newTensionData(int id, double PV, double tqo);
    //void newMS300Data(int id, double v);
    //void dioUpdated(uint8_t port0, uint8_t port1, uint8_t output);

private slots:
    // 來自 ModbusManager
    void onholdingRegisterReady(QVector<quint16> values);
    void onWorkerData(QVector<quint16> values);
    void onWorkerData2(QVector<quint16> values);

    void onWorkerError(QString msg);
    void onZeroSpeed01();
    void onZeroSpeed02();
    void on485Data(int id, double pv, double tqo);
    void onMS300Data(int id, double v);
private:
    explicit Core(QObject* parent = nullptr);
    ~Core();
    static Core* m_instance;
    static QMutex m_mutex;

    ModbusManager* m_manager{ nullptr };
    bool m_UnwinderJogReverseSelect = false;
    bool m_WinderJogReverseSelect = false;
    bool m_LeftSelvedgeWinderSelect = false;
    bool m_RightSelvedgeWinderSelect = false;
    bool m_mode = false;
    int targetAddr;
    QVector<bool> targetWinder;
    QVector<bool> Winder1 = { 1,0,1 };
    QVector<bool> Winder2 = { 1,0,1,0,0,0,0,1,0,1 };
    QVector<bool> Winder3 = { 1,0,1,0,0,0,0,0,0,1 };
    QVector<bool> Winder4 = { 1,0,1,0,0,0,0,1,0,0 };
    
    QVector<bool> StopWinderJog = { 0,0,0,0,0,0,0,0,0,0,0 };



};