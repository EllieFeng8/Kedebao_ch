#pragma once


#include <QObject>
#include <Qmutex>
#include <qsettings>
#include <Qvector>
#include "ModbusManager.h"
#include "DIOModule.h"
#include "Tension.h"
#include "MS300.h"
#include "LengthController.h"
#include <QQmlEngine>
#include "KdbProxy.h"
#include <QTimer>
class Core : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    QVector<double> values;
    QVector<quint16> DataValues ;
    QVector<quint16> DataValues2;
    double nowSpeed = 0;
    KdbProxy* m_proxy=nullptr;
    
    MS300* m_ms300 = nullptr;
    QThread* threadMS300 = nullptr;

    Modbus485* m_tension = nullptr;
    QThread* threadTension=nullptr;
    
    QThread* threadDIO = nullptr;
    DIOModule* dioWorker = nullptr;

    QThread* threadLength = nullptr;
    LengthController* m_Length = nullptr;

    static Core& instance();  // Singleton entry

    void addModbusServer(QString ip, int port);
    void startAll();
    void stopAll();
    //void writeSingleCoil(int address, bool value);

    void writeCoils(int startAddress, const QVector<bool>& values);
    void writeRegister(int startAddr, const quint16 &value);
    void readRegisters(int startAddress, int count);

    void init() {
        m_tensionStableTimer = new QTimer(this);
        m_tensionStableTimer->setSingleShot(true); // 只需要觸發一次

        connect(this, &Core::finishSoftStartSignal, this, &Core::startRealSpeed);
        // 當 Timer 成功跑完 3 秒時觸發
        connect(m_tensionStableTimer, &QTimer::timeout, this, [=]() {
            qDebug() << "Tension Stable , set speed = " << setspeed;
            m_isSoftStarting = false; // 結束緩啟動狀態

            emit finishSoftStartSignal();
            });

        m_tensionStableTimer2 = new QTimer(this);
        m_tensionStableTimer2->setSingleShot(true); // 只需要觸發一次

        connect(this, &Core::waitforPVSignal, this, [this]()
            {
                setMainSpeed(setspeed);
                waitforPV = false;
            });
        // 當 Timer 成功跑完 3 秒時觸發
        connect(m_tensionStableTimer2, &QTimer::timeout, this, [=]() {
            qDebug() << "Tension Stable , set speed = " << setspeed;

            emit waitforPVSignal();
            });

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
    
        m_Length = new LengthController();
        threadLength = new QThread(this);
        m_Length->moveToThread(threadLength);

        connect(threadLength, &QThread::started, m_Length, &LengthController::initPort);

        // 處理接收到的資料 (假設您 UI 有一個 QLabel 或顯示欄位)
        connect(m_Length, &LengthController::lengthUpdated, this,&Core::onlength);

        // 處理錯誤
        
        connect(m_Length, &LengthController::errorOccurred, this, [](QString err) {
            qWarning() << "Length COM2 Error:" << err;
            });

        // 4. 資源回收：當執行緒結束時，刪除 m_Length
        connect(threadLength, &QThread::finished, m_Length, &QObject::deleteLater);

        // 5. 正式啟動
        threadLength->start();


        connect(m_tension, &Modbus485::dataUpdated,
            this, &Core::on485Data);
        connect(m_tension, &Modbus485::connectionFailed, 
            this, &Core::TensionFailed);
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
        connect(m_manager, &ModbusManager::isWorking, this, [this]() {
            loadProductionSettings();
            });


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
    void setMainFreqs(double v);
    void setMainSpeed(double v);

    void setSTOP();
    bool isStop = true;
    bool LowSpeed = false;
    void writeRegisters(double v)
    {
        nowSpeed = v;
        values.resize(4);
        //values.fill(v);
        values[0] = v*m_p1;
        values[1] = v*m_p2;
        values[2] = v*m_p3;
        values[3] = v*m_p4;


        m_manager->writeRegisters(values);
    }
    void updateProxyProperty(int index, quint16 value);
    void handleDIOSignal(int bitIndex, bool state);

    void coreConnect()
    {
        //main Screen
        QObject::connect(m_proxy, &KdbProxy::bigRollModeChanged, this,&Core::modeSelect);
        QObject::connect(m_proxy, &KdbProxy::restBtnChanged,m_Length,&LengthController::lengthReset );

        QObject::connect(m_proxy, &KdbProxy::pressureRollerChanged, m_manager, &ModbusManager::PressRoll);
        QObject::connect(m_proxy, &KdbProxy::pressureRollerDownChanged, m_manager, &ModbusManager::PressRollDown);
        QObject::connect(m_proxy, &KdbProxy::pressurePlateChanged, this, &Core::PressPlate);
        QObject::connect(m_proxy, &KdbProxy::pressurePlateBackChanged, this, &Core::PressPlateBack);

        //ADAM-5000  5056SO Output
        QObject::connect(m_proxy, &KdbProxy::vfdAlarmResetChanged, m_manager, &ModbusManager::VfdAlarmReset);//64
        QObject::connect(m_proxy, &KdbProxy::unwinderForwardChanged, m_manager, &ModbusManager::UnwinderForward);//65
        QObject::connect(m_proxy, &KdbProxy::unwinderReverseChanged, m_manager, &ModbusManager::UnwinderReverse);//66
        QObject::connect(m_proxy, &KdbProxy::mainDriveForwardChanged, m_manager, &ModbusManager::MainDriveForward);//67
        QObject::connect(m_proxy, &KdbProxy::mainDriveReverseChanged, m_manager, &ModbusManager::MainDriveReverse);//68
        QObject::connect(m_proxy, &KdbProxy::smallWinderForwardChanged, m_manager, &ModbusManager::SmallWinderForward);//69
        QObject::connect(m_proxy, &KdbProxy::smallWinderReverseChanged, m_manager, &ModbusManager::SmallWinderReverse);//70
        QObject::connect(m_proxy, &KdbProxy::largeWinderForwardChanged, m_manager, &ModbusManager::LargeWinderForward);//71
        QObject::connect(m_proxy, &KdbProxy::largeWinderReverseChanged, m_manager, &ModbusManager::LargeWinderReverse);//72
        QObject::connect(m_proxy, &KdbProxy::smallCutterStartChanged, m_manager, &ModbusManager::SmallCutterStart);//73
        QObject::connect(m_proxy, &KdbProxy::selvedgeFanStartChanged, m_manager, &ModbusManager::SelvedgeFanStart);//74
        QObject::connect(m_proxy, &KdbProxy::largeCutterStartChanged, m_manager, &ModbusManager::LargeCutterStart);//75
        QObject::connect(m_proxy, &KdbProxy::leftSelvedgeWinderForwardChanged, m_manager, &ModbusManager::LeftSelvedgeWinderForward);//76
        QObject::connect(m_proxy, &KdbProxy::leftSelvedgeWinderReverseChanged, m_manager, &ModbusManager::LeftSelvedgeWinderReverse);//77
        QObject::connect(m_proxy, &KdbProxy::rightSelvedgeWinderForwardChanged, m_manager, &ModbusManager::RightSelvedgeWinderForward);//78
        QObject::connect(m_proxy, &KdbProxy::rightSelvedgeWinderReverseChanged, m_manager, &ModbusManager::RightSelvedgeWinderReverse);//79
        QObject::connect(m_proxy, &KdbProxy::webAlignerStartChanged, m_manager, &ModbusManager::WebAlignerStart);//80
        QObject::connect(m_proxy, &KdbProxy::unwindingTensionAutoChanged, m_manager, &ModbusManager::UnwindingTensionAuto);//81
        QObject::connect(m_proxy, &KdbProxy::unwindingDiameterResetChanged, m_manager, &ModbusManager::UnwindingDiameterRe);//82
        QObject::connect(m_proxy, &KdbProxy::smallWinderTensionAutoChanged, m_manager, &ModbusManager::SmallWinderTensionAuto);//83
        QObject::connect(m_proxy, &KdbProxy::smallWinderDiameterResetChanged, m_manager, &ModbusManager::SmallWinderDiameterRe);//84
        QObject::connect(m_proxy, &KdbProxy::largeWinderTensionAutoChanged, m_manager, &ModbusManager::LargeWinderTensionAuto);//85
        QObject::connect(m_proxy, &KdbProxy::largeWinderDiameterResetChanged, m_manager, &ModbusManager::LargeWinderDiameterRe);//86
        QObject::connect(m_proxy, &KdbProxy::leftSelvedgeWinderAutoChanged, m_manager, &ModbusManager::LeftSelvedgeWinderAuto);//87
        QObject::connect(m_proxy, &KdbProxy::rightSelvedgeWinderAutoChanged, m_manager, &ModbusManager::RightSelvedgeWinderAuto);//88
        QObject::connect(m_proxy, &KdbProxy::nipRollUpChanged, m_manager, &ModbusManager::NipRollUp);//89
        QObject::connect(m_proxy, &KdbProxy::nipRollDownChanged, m_manager, &ModbusManager::NipRollDown);//90
        QObject::connect(m_proxy, &KdbProxy::leftPressPlateForwardChanged, m_manager, &ModbusManager::LeftPressPlateForward);//91
        QObject::connect(m_proxy, &KdbProxy::leftPressPlateBackwardChanged, m_manager, &ModbusManager::LeftPressPlateBackward);//92
        QObject::connect(m_proxy, &KdbProxy::rightPressPlateForwardChanged, m_manager, &ModbusManager::RightPressPlateForward);//93
        QObject::connect(m_proxy, &KdbProxy::rightPressPlateBackwardChanged, m_manager, &ModbusManager::RightPressPlateBackward);//94
        
        // output 95以後 ,因為新增小卷切刀 proxy名稱對不上 以備註名稱為準
        QObject::connect(m_proxy, &KdbProxy::smallCutterInChanged, m_manager, &ModbusManager::SmallCutterIn);//95  小卷切刀一
        QObject::connect(m_proxy, &KdbProxy::smallRollCutter1Changed, m_manager, &ModbusManager::SmallCutterIn);//95 小卷切刀一

        QObject::connect(m_proxy, &KdbProxy::largeCutterInChanged, m_manager, &ModbusManager::SmallCutter2);//96 小卷切刀二
        QObject::connect(m_proxy, &KdbProxy::smallRollCutter2Changed, m_manager, &ModbusManager::SmallCutter2);//96 小卷切刀二

        QObject::connect(m_proxy, &KdbProxy::modeSelectChanged, m_manager, &ModbusManager::SmallCutter3);//97 小卷切刀三
        QObject::connect(m_proxy, &KdbProxy::smallRollCutter3Changed, m_manager, &ModbusManager::SmallCutter3);//97 小卷切刀三

        QObject::connect(m_proxy, &KdbProxy::runIndicatorChanged, m_manager, &ModbusManager::SmallCutter4);//98 小卷切刀四
        QObject::connect(m_proxy, &KdbProxy::smallRollCutter4Changed, m_manager, &ModbusManager::SmallCutter4);//98 小卷切刀四

        QObject::connect(m_proxy, &KdbProxy::alarmIndicatorChanged, m_manager, &ModbusManager::SmallCutter5);//99 小卷切刀五
        QObject::connect(m_proxy, &KdbProxy::smallRollCutter5Changed, m_manager, &ModbusManager::SmallCutter5);//99 小卷切刀五

        QObject::connect(m_proxy, &KdbProxy::stopIndicatorChanged, m_manager, &ModbusManager::LargeCutterIn);//100 大捲切刀
        QObject::connect(m_proxy, &KdbProxy::bigRollCutterChanged, m_manager, &ModbusManager::LargeCutterIn);//100 大捲切刀

        QObject::connect(m_proxy, &KdbProxy::buzzerChanged, m_manager, &ModbusManager::RunIndicator);//101 指示燈 運行
        QObject::connect(m_proxy, &KdbProxy::smallRollModeSelectChanged, m_manager, &ModbusManager::AlarmIndicator);//102 指示燈 異常
        QObject::connect(m_proxy, &KdbProxy::output8Changed, m_manager, &ModbusManager::StopIndicator);//103 指示燈 停止
        QObject::connect(m_proxy, &KdbProxy::output9Changed, m_manager, &ModbusManager::Buzzer);//104 蜂鳴器
        QObject::connect(m_proxy, &KdbProxy::output10Changed, m_manager, &ModbusManager::ModeSelect);//105 模式選擇

        QObject::connect(m_proxy, &KdbProxy::output11Changed, m_manager, &ModbusManager::io106);//106 日光燈
        QObject::connect(m_proxy, &KdbProxy::whiteLightChanged, m_manager, &ModbusManager::io106);

        QObject::connect(m_proxy, &KdbProxy::output12Changed, m_manager, &ModbusManager::io107);//107 紫光燈
        //QObject::connect(m_proxy, &KdbProxy::uvLightChanged, m_manager, &ModbusManager::io107);
        QObject::connect(m_proxy, &KdbProxy::uvLightChanged, this,[this]()
            {
                m_proxy->abnormalRaised("aaa");
            });


        QObject::connect(m_proxy, &KdbProxy::output13Changed, m_manager, &ModbusManager::io108);//108 下方照明燈
        QObject::connect(m_proxy, &KdbProxy::bottomLightChanged, m_manager, &ModbusManager::io108);

        QObject::connect(m_proxy, &KdbProxy::output14Changed, m_manager, &ModbusManager::io109);//109 
        QObject::connect(m_proxy, &KdbProxy::output15Changed, m_manager, &ModbusManager::io110);//110
        QObject::connect(m_proxy, &KdbProxy::output16Changed, m_manager, &ModbusManager::io111);//111
        QObject::connect(m_proxy, &KdbProxy::output17Changed, m_manager, &ModbusManager::io112);//112

        //UI主畫面 設定張力值
        QObject::connect(m_proxy, &KdbProxy::modifyUnwindingTensionChanged, this, &Core::setTensionSV_1);
        QObject::connect(m_proxy, &KdbProxy::modifySmallWinderTensionOverChanged, this, &Core::setTensionSV_2);
        QObject::connect(m_proxy, &KdbProxy::modifyLargeWinderTensionOverChanged, this, &Core::setTensionSV_3);
        QObject::connect(m_proxy, &KdbProxy::modifySpeedChanged, this,&Core::setMainFreqs);
        QObject::connect(m_proxy, &KdbProxy::modifyCurrentLengthChanged, this, &Core::setCurrentLength);
        
        QObject::connect(m_proxy, &KdbProxy::modifyBrakingDistanceChanged, this, &Core::setBrakingDistance);

        //ADAM-5000  5024 Analog Output  

        QObject::connect(m_proxy, &KdbProxy::modifyAnalogOutUnwinderMainDriveChanged, m_manager, &ModbusManager::writeRegister56);
        QObject::connect(m_proxy, &KdbProxy::modifyAnalogOutWinderChanged, m_manager, &ModbusManager::writeRegister57);
        QObject::connect(m_proxy, &KdbProxy::modifyAnalogOutCutterChanged, m_manager, &ModbusManager::writeRegister58);
        QObject::connect(m_proxy, &KdbProxy::modifyAnalogOutSelvedgeWinderChanged, m_manager, &ModbusManager::writeRegister59);

        QObject::connect(m_proxy, &KdbProxy::analogOutUnwinderMainDrivePcChanged, this, [this](double pc)
            {

                m_p1 = pc / 100;
                qDebug() << "p1 set " << m_p1;

            }
        );
        QObject::connect(m_proxy, &KdbProxy::analogOutWinderPcChanged, this, [this](double pc)
            {
                
                m_p2 = pc / 100;
                qDebug() << "p2 set " << m_p2;

            }
        );
        QObject::connect(m_proxy, &KdbProxy::analogOutCutterPcChanged, this, [this](double pc) 
            {
                
                m_p3 = pc / 100;
                qDebug() << "p3 set " << m_p3;

            }
        );
        QObject::connect(m_proxy, &KdbProxy::analogOutSelvedgeWinderPcChanged, this, [this](double pc)
            {

                m_p4 = pc / 100;
                qDebug() << "p4 set " << m_p4;

            }
        );
        QObject::connect(m_proxy, &KdbProxy::modifyUnwindingLimitThresholdChanged, this, [this](int value)
            {
                Unwinding_Threshold = value;
                qDebug() << "UnwindingLimit Threshold =" <<value;

            }
        );

        QObject::connect(m_proxy, &KdbProxy::softStartSpeedChanged, this, [this](int value)
            {
                m_slowStartSpeed = value;
                qDebug() << "m_slowStartSpeed =" << value;

            }
        );

        QObject::connect(m_proxy, &KdbProxy::softStartThresholdChanged, this, [this](int value)
            {
                m_tensionTolerance = value;
                qDebug() << "m_tensionTolerance =" << value;

            }
        );

        QObject::connect(m_proxy, &KdbProxy::tensionTimeChanged, this, [this](int value)
            {
                stableTime = value;
                qDebug() << "stableTime =" << value;

            }
        );

        QObject::connect(m_proxy, &KdbProxy::smallRollMotorChanged, this, [this]()
            {
                qDebug() << "JOG SmallWinder";
                m_manager->SmallWinderReverse(1.0);
                QTimer::singleShot(1000, this,
                    [this]()
                    {
                        m_manager->SmallWinderReverse(0.0);
                    });
            }
        );
        QObject::connect(m_proxy, &KdbProxy::mainDriveMotorChanged, this, [this]()
            {
                qDebug() << "JOG mainDriveMotor";
                m_manager->MainDriveForward(1.0);
                QTimer::singleShot(1000, this,
                    [this]()
                    {
                        m_manager->MainDriveForward(0.0);
                    });
            }
        );
        QObject::connect(m_proxy, &KdbProxy::largeRollMotorChanged, this, [this]()
            {
                qDebug() << "JOG largeRollMotor";
                m_manager-> LargeWinderForward(1.0);
                QTimer::singleShot(1000, this,
                    [this]()
                    {
                        m_manager->LargeWinderForward(0.0);
                    });
            }
        );
        QObject::connect(m_proxy, &KdbProxy::unwindingMotorChanged, this, [this]()
            {
                qDebug() << "JOG unwindingMotor";
                m_manager->UnwinderForward(1.0);
                QTimer::singleShot(1000, this,
                    [this]()
                    {
                        m_manager->UnwinderForward(0.0);
                    });
            }
        );
     };
public slots:
    void writeSingleCoil(int address, double value);
    void setTensionSV_1(double v);
    void setSV_1(double v)
    {
        nowSV1 = v;
        QMetaObject::invokeMethod(m_tension, [this, v]() {m_tension->setTargetTension(1, v); },
            Qt::QueuedConnection);
    }
    void setTensionSV_2(double v);
    void setTensionSV_3(double v);
    void startRealSpeed() {
        qDebug() <<"startRealSpeed() setSpeed" << setspeed;
        //setMainSpeed(setspeed);    // 加速
        setTensionSV_1(Tension1_SV);
        waitforPV = true;
    }
    void ontest() 
    {
        DataValues[80] = 1;
        onWorkerData(DataValues);
        qDebug() << "test";
    }
   

signals:
    void holdingRegisterReady(QVector<quint16> values);
    void finishSoftStartSignal();
    void waitforPVSignal();
    //void newDataReady( QVector<quint16> values);
    //void WorkerError( QString message);
    //void newTensionData(int id, double PV, double tqo);
    //void newMS300Data(int id, double v);
    //void dioUpdated(uint8_t port0, uint8_t port1, uint8_t output);

private slots:
    // 來自 ModbusManager
    void onlength(double v);
    void onholdingRegisterReady(QVector<quint16> values);
    void onWorkerData(QVector<quint16> values);
    void onWorkerData2(QVector<quint16> values);

    void onWorkerError(QString msg);
    void onZeroSpeed01();
    void onZeroSpeed02();
    void on485Data(int id, double pv, double tqo);
    void TensionFailed(const QString& errorMsg);
    void onMS300Data(int id, double v);
    void setCurrentLength(int length);
    void modeSelect(double v)
    {
        bool value = (v != 1.0) ? true : false;
        writeSingleCoil(105, value);
    }
    void setBrakingDistance(double BrakingDistance);
    void PressPlate(double value)
    {
        if (PressIndex2 <= 0)
        {
            PressIndex2++;
        }
        else
        {
            PressIndex2 = 0;
        }
        if (PressIndex2 == 1)
        {
            writeCoils(91, { 0,0,0,1 });
            //QTimer::singleShot(500, this,
            //    [this]()
            //    {
            //        writeCoils(91, { 0, 0, 0, 0 });
            //    });
        }
        else if (PressIndex2 == 0)
        {
            writeCoils(91, { 1,0,1,0 });
            //QTimer::singleShot(500, this,
            //    [this]()
            //    {
            //        writeCoils(91, { 0, 0, 0, 0 });
            //    });
            PressIndex = 0;
            PressIndex2 = 0;
        }
    }
    void PressPlateBack(double value)
    {
        if (PressIndex <= 0) 
        {
            PressIndex++;
        }
        else 
        {
            PressIndex = 0;
        }
        if (PressIndex == 1)
        {
            writeCoils(91, { 0,1,0,0 });
            //QTimer::singleShot(500, this,
            //    [this]()
            //    {
            //        writeCoils(91, { 0, 0, 0, 0 });
            //    });
        }
        else if (PressIndex == 0)
        {
            writeCoils(91, { 1,0,1,0 });
            //QTimer::singleShot(500, this,
            //    [this]()
            //    {
            //        writeCoils(91, { 0, 0, 0, 0 });
            //    });
            PressIndex = 0;
            PressIndex2 = 0;
        }
    }
private:
    explicit Core(QObject* parent = nullptr);
    ~Core();
    static Core* m_instance;
    static QMutex m_mutex;

    ModbusManager* m_manager{ nullptr };
    bool m_isWaitingForStop = false;
    bool m_isBrakingPerformed = false;
    bool m_UnwinderJogReverseSelect = false;
    bool m_WinderJogReverseSelect = false;
    bool m_LeftSelvedgeWinderSelect = false;
    bool m_RightSelvedgeWinderSelect = false;
    bool m_mode = false;
    bool onLength=false;
    int targetAddr;
    int m_length = 0;
    double m_BrakingDistance = 0.0;
    double speed = 0;
    double setspeed = 0;
    double m_p1 = 1.0;//放捲
    double m_p2 = 1.0;//大小收卷
    double m_p3 = 1.0;//大小切刀
    double m_p4 = 1.0;//耳料收卷
    double Tension1_SV = 0.0;
    double nowSV1 = 0.0;
    double slowSV = 6.0;
    double Tension2_SV = 0.0;
    double Tension3_SV = 0.0;
    int stableTime = 800;
    double Unwinding_Threshold = 0.0;
    //緩啟動>>
    bool m_isSoftStarting = false;         // 是否正在進行緩啟動
    bool waitforPV = false;
    QTimer* m_tensionStableTimer = nullptr; // 用於判斷連續 3 秒的定時器
    QTimer* m_tensionStableTimer2 = nullptr; // 用於判斷連續 3 秒的定時器

    // 參數建議 (可根據實際機器調整)
    double m_slowStartSpeed = 5.0;    // 啟動時的初始慢速
    double m_tensionTolerance = 2;  // 張力容許誤差範圍 (PV與SV的差值)
    //<<緩啟動
    int PressIndex = 0;
    int PressIndex2 = 0;
    int setTime = 500;
    QVector<bool> targetWinder;
    QVector<bool> Winder1 = { 1,0,1 };
    QVector<bool> Winder2 = { 1,0,1,0,0,0,0,1,0,1 };
    QVector<bool> Winder3 = { 1,0,1,0,0,0,0,0,0,1 };
    QVector<bool> Winder4 = { 1,0,1,0,0,0,0,1,0,0 };
    
    QVector<bool> StopWinderJog = { 0,0,0,0,0,0,0,0,0,0,0 };


    void loadProductionSettings()
    {
        QSettings settings("production.ini", QSettings::IniFormat);

        // 讀取數值，若檔案不存在則使用預設值 0.0
        setspeed = settings.value("Production/SetSpeed", 0.0).toDouble();
        m_length = settings.value("Production/TargetLength", 0).toInt();
        m_BrakingDistance = settings.value("Production/BrakingDistance", 0.0).toDouble();
        Tension1_SV = settings.value("Production/Tension1_SV", 0.0).toDouble();
        Tension2_SV = settings.value("Production/Tension2_SV", 0.0).toDouble();
        Tension3_SV = settings.value("Production/Tension3_SV", 0.0).toDouble();
        m_slowStartSpeed = settings.value("Production/softstart_speed", 0.0).toDouble();
        m_tensionTolerance = settings.value("Production/softstart_threshold", 0.0).toDouble();
        Unwinding_Threshold = settings.value("Production/Unwinder_threshold", 0.0).toDouble();
        stableTime = settings.value("Production/stable_Time", 0).toInt();

        // 同步更新到 Proxy (UI 層)，確保介面顯示正確
        if (m_proxy) {
            m_proxy->setModifySpeed(setspeed);
            m_proxy->setModifyCurrentLength(m_length);
            m_proxy->setModifyBrakingDistance(m_BrakingDistance);
            m_proxy->setModifyUnwindingTension(Tension1_SV);
            m_proxy->setModifySmallWinderTensionOver(Tension2_SV);
            m_proxy->setModifyLargeWinderTensionOver(Tension3_SV);
            m_proxy->setSoftStartThreshold(m_tensionTolerance);
            m_proxy->setSoftStartSpeed(m_slowStartSpeed);
            m_proxy->setModifyUnwindingLimitThreshold(Unwinding_Threshold);
            m_proxy->setTensionTime(stableTime);
            
            
            m_proxy->setWhiteLight(1);
            m_proxy->setBigRollMode(0);
        }
    }

    void saveProductionSettings()
    {
        QSettings settings("production.ini", QSettings::IniFormat);

        settings.setValue("Production/SetSpeed", setspeed);
        settings.setValue("Production/TargetLength", m_length);
        settings.setValue("Production/BrakingDistance", m_BrakingDistance);
        settings.setValue("Production/Tension1_SV", Tension1_SV);
        settings.setValue("Production/Tension2_SV", Tension2_SV);
        settings.setValue("Production/Tension3_SV", Tension3_SV);
        settings.setValue("Production/stable_Time", stableTime);
        settings.setValue("Production/softstart_speed", m_slowStartSpeed);
        settings.setValue("Production/softstart_threshold", m_tensionTolerance);
        settings.setValue("Production/Unwinder_threshold", Unwinding_Threshold);

        settings.sync(); 
    }
};