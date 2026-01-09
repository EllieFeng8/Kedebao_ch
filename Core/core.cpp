#include "core.h"
#include "modbusmanager.h"
#include <qsettings>
Core* Core::m_instance = nullptr;
QMutex Core::m_mutex;

Core::Core(QObject* parent)
    : QObject(parent)
{
    DataValues.resize(112);
    DataValues.fill(1);
 
    m_proxy = new KdbProxy(this);
    m_manager = new ModbusManager(this);
    DIOModule::instance().initialize();
    QThread* threadTension = new QThread(this);
    Modbus485::instance()->moveToThread(threadTension);
    connect(threadTension, &QThread::started, Modbus485::instance(), &Modbus485::initPort);
    threadTension->start();

    QThread* threadMS300 = new QThread(this);
    MS300::instance()->moveToThread(threadMS300);
    connect(threadMS300, &QThread::started, MS300::instance(), &MS300::initPort);
    connect(MS300::instance(), &MS300::dataUpdated, this, &Core::onMS300Data);

    threadMS300->start();

    connect(Modbus485::instance(), &Modbus485::dataUpdated, this, &Core::on485Data);
    // Manager → Core
    connect(m_manager, &ModbusManager::workerData,
        this, &Core::onWorkerData);
    
    connect(m_manager, &ModbusManager::workerError,
        this, &Core::onWorkerError);

    connect(m_manager, &ModbusManager::holdingRegisterReady,
        this, &Core::onholdingRegisterReady);
    onWorkerData(DataValues);
    
  
}

Core* Core::instance()
{
    // Double-checked locking
    if (!m_instance) {
        QMutexLocker locker(&m_mutex);
        if (!m_instance) {
            m_instance = new Core;
        }
    }
    return m_instance;
}


void Core::addModbusServer( QString ip, int port)
{
    m_manager->createWorker( ip, port);
}


void Core::startAll()
{
    m_manager->startAll();
}


void Core::stopAll()
{
    m_manager->stopAll();
}


void Core::onWorkerData( QVector<quint16> values)
{
    //emit newDataReady( values);
    DataValues = values;
    for (int i = 0; i < 112; ++i)
    {
       qDebug() << DataValues[i];
    }
    
    //
    // INPUT 0~61
    // 
    m_proxy->setUnwinderVfdFreqAlarm(DataValues[0]);
    m_proxy->setMainDriveVfdFreqAlarm(DataValues[1]);
    m_proxy->setSmallWinderVfdFreqAlarm(DataValues[2]);
    m_proxy->setLargeWinderVfdFreqAlarm(DataValues[3]);
    m_proxy->setSmallCutterVfdFreqAlarm(DataValues[4]);
    m_proxy->setSelvedgeFanVfdFreqAlarm(DataValues[5]);
    m_proxy->setLeftFanOverloadAlarm(DataValues[6]);
    m_proxy->setRightFanOverloadAlarm(DataValues[7]);
    m_proxy->setLargeCutterVfdFreqAlarm(DataValues[8]);
    m_proxy->setLeftSelvedgeWinderVfdAlarm(DataValues[9]);
    m_proxy->setRightSelvedgeWinderVfdAlarm(DataValues[10]);
    m_proxy->setWebAlignerVfdFreqAlarm(DataValues[11]);
    m_proxy->setUnwinderPowerLoss(DataValues[12]);
    m_proxy->setMainDrivePowerLoss(DataValues[13]);
    m_proxy->setSmallWinderPowerLoss(DataValues[14]);
    m_proxy->setLargeWinderPowerLoss(DataValues[15]);
    m_proxy->setSmallCutterPowerLoss(DataValues[16]);
    m_proxy->setSelvedgeFanPowerLoss(DataValues[17]);
    m_proxy->setLargeCutterPowerLoss(DataValues[18]);
    m_proxy->setLeftSelvedgeWinderPowerLoss(DataValues[19]);
    m_proxy->setRightSelvedgeWinderPowerLoss(DataValues[20]);
    m_proxy->setWebAlignerPowerLoss(DataValues[21]);
    m_proxy->setUnwinderDisconnect(DataValues[22]);
    m_proxy->setMainDriveDisconnect(DataValues[23]);
    m_proxy->setSmallWinderDisconnect(DataValues[24]);
    m_proxy->setLargeWinderDisconnect(DataValues[25]);
    m_proxy->setSmallCutterDisconnect(DataValues[26]);
    m_proxy->setLeftFanDisconnect(DataValues[27]);
    m_proxy->setRightFanDisconnect(DataValues[28]);
    m_proxy->setLargeCutterDisconnect(DataValues[29]);
    m_proxy->setLeftSelvedgeWinderDisconnect(DataValues[30]);
    m_proxy->setRightSelvedgeWinderDisconnect(DataValues[31]);
    m_proxy->setWebAlignerDisconnect(DataValues[32]);
    m_proxy->setEmergencyStop1(DataValues[33]);
    m_proxy->setEmergencyStop2(DataValues[34]);
    m_proxy->setEmergencyStop3(DataValues[35]);
    m_proxy->setEmergencyStop4(DataValues[36]);
    m_proxy->setEmergencyStop5(DataValues[37]);
    m_proxy->setEmergencyStop6(DataValues[38]);
    m_proxy->setEmergencyStop7(DataValues[39]);
    m_proxy->setMainDriveLeftDoor1Open(DataValues[40]);
    m_proxy->setMainDriveLeftDoor2Open(DataValues[41]);
    m_proxy->setMainDriveRightDoor3Open(DataValues[42]);
    m_proxy->setMainDriveRightDoor4Open(DataValues[43]);
    m_proxy->setLargeWinderLeftDoor5Open(DataValues[44]);
    m_proxy->setLargeWinderLeftDoor6Open(DataValues[45]);
    m_proxy->setLargeWinderRightDoor7Open(DataValues[46]);
    m_proxy->setLargeWinderRightDoor8Open(DataValues[47]);
    m_proxy->setUnwindingFenceDetect1(DataValues[48]);
    m_proxy->setUnwindingFenceDetect2(DataValues[49]);
    m_proxy->setLargeWinderFenceDetect3(DataValues[50]);
    m_proxy->setLargeWinderFenceDetect4(DataValues[51]);
    m_proxy->setUnwindingSafetyLightCurtainAlarm(DataValues[52]);
    m_proxy->setInspectionSafetyLightCurtainAlarm(DataValues[53]);
    m_proxy->setLargeWinderSafetyLightCurtainAlarm(DataValues[54]);
    m_proxy->setSmallWinderZeroSpeedDetect(DataValues[55]);
    m_proxy->setLargeWinderZeroSpeedDetect(DataValues[56]);
    m_proxy->setUnwindingTensionOver(DataValues[57]);
    m_proxy->setSmallWinderTensionOver(DataValues[58]);
    m_proxy->setLargeWinderTensionOver(DataValues[59]);
    m_proxy->setLeftSelvedgeWinderAngleAlarm(DataValues[60]);
    m_proxy->setRightSelvedgeWinderAngleAlarm(DataValues[61]);

    //
    // OUTPUT 64~102
    //
    m_proxy->setVfdAlarmReset(DataValues[64]);
    m_proxy->setUnwinderForward(DataValues[65]);
    m_proxy->setUnwinderReverse(DataValues[66]);
    m_proxy->setMainDriveForward(DataValues[67]);
    m_proxy->setMainDriveReverse(DataValues[68]);
    m_proxy->setSmallWinderForward(DataValues[69]);
    m_proxy->setSmallWinderReverse(DataValues[70]);
    m_proxy->setLargeWinderForward(DataValues[71]);
    m_proxy->setLargeWinderReverse(DataValues[72]);
    m_proxy->setSmallCutterStart(DataValues[73]);
    m_proxy->setSelvedgeFanStart(DataValues[74]);
    m_proxy->setLargeCutterStart(DataValues[75]);
    m_proxy->setLeftSelvedgeWinderForward(DataValues[76]);
    m_proxy->setLeftSelvedgeWinderReverse(DataValues[77]);
    m_proxy->setRightSelvedgeWinderForward(DataValues[78]);
    m_proxy->setRightSelvedgeWinderReverse(DataValues[79]);
    m_proxy->setWebAlignerStart(DataValues[80]);
    m_proxy->setUnwindingTensionAuto(DataValues[81]);
    m_proxy->setUnwindingDiameterReset(DataValues[82]);
    m_proxy->setSmallWinderTensionAuto(DataValues[83]);
    m_proxy->setSmallWinderDiameterReset(DataValues[84]);
    m_proxy->setLargeWinderTensionAuto(DataValues[85]);
    m_proxy->setLargeWinderDiameterReset(DataValues[86]);
    m_proxy->setLeftSelvedgeWinderAuto(DataValues[87]);
    m_proxy->setRightSelvedgeWinderAuto(DataValues[88]);
    m_proxy->setNipRollUp(DataValues[89]);
    m_proxy->setNipRollDown(DataValues[90]);
    m_proxy->setLeftPressPlateForward(DataValues[91]);
    m_proxy->setLeftPressPlateBackward(DataValues[92]);
    m_proxy->setRightPressPlateForward(DataValues[93]);
    m_proxy->setRightPressPlateBackward(DataValues[94]);
    m_proxy->setSmallCutterIn(DataValues[95]);
    m_proxy->setLargeCutterIn(DataValues[96]);
    m_proxy->setModeSelect(DataValues[97]);
    m_proxy->setRunIndicator(DataValues[98]);
    m_proxy->setAlarmIndicator(DataValues[99]);
    m_proxy->setStopIndicator(DataValues[100]);
    m_proxy->setBuzzer(DataValues[101]);
    m_proxy->setSmallRollModeSelect(DataValues[102]);
}


void Core::onWorkerError( QString msg)
{
    //emit WorkerError( msg);
}

void Core::on485Data(int id, double PV, double tqo)
{
    //emit newTensionData(id,PV,tqo);
}

void Core::onholdingRegisterReady( QVector<quint16> values)
{
    //emit holdingRegisterReady( values);
    m_proxy->setAnalogOutUnwinderMainDrive(values[0]);
    m_proxy->setAnalogOutWinder(values[1]);
    m_proxy->setAnalogOutCutter(values[2]);
    m_proxy->setAnalogOutSelvedgeWinder(values[3]);
}

void Core::writeSingleCoil( int address, bool value)
{
    m_manager->writeSingleCoil( address, value);
}

void Core::writeCoils( int startAddress, const QVector<bool>& values)
{
    m_manager->writeCoils( startAddress, values);   
}

void Core::writeRegisters(int startAddr, const QVector<quint16>& values)
{
    m_manager->writeRegisters( startAddr, values);

}

void Core::readRegisters( int startAddress, int count)
{
    m_manager->readRegisters( startAddress, count);
}

void Core::initDIO()
{
    DIOModule::instance().initialize();
}

void Core::readDIO()
{
    uint8_t p0 = 0, p1 = 0, out = 0;

    bool ok1 = DIOModule::instance().readInputs(p0, p1);
    bool ok2 = DIOModule::instance().readOutputs(out);
    if (DIOModule::instance().readInputs(p0, p1)) {
        qDebug() << "MOS-1110Y DI:"
            << "Port0 =" << p0
            << "Port1 =" << p1;

        // 逐 bit 顯示
        qDebug() << "DI bits (0~7):";
        for (int i = 0; i < 8; i++)
            qDebug() << " DI" << i << ":" << ((p0 >> i) & 1);

        qDebug() << "DI bits (8~15):";
        for (int i = 0; i < 8; i++)
            qDebug() << " DI" << (i + 8) << ":" << ((p1 >> i) & 1);
    }
    else {
        qDebug() << "DI read failed.";
    }

    if (DIOModule::instance().readOutputs(out)) {
        qDebug() << "MOS-1110Y DO =" << out;

        for (int i = 0; i < 8; i++)
            qDebug() << " DO" << i << ":" << ((out >> i) & 1);
    }
    else {
        qDebug() << "DO read failed.";
    }
    //emit dioUpdated(p0, p1, out);
}


void Core::setOutputBit(int bit, bool high)
{

    DIOModule::instance().setOutput(bit, high);
}

void Core::read485(int id)
{
    Modbus485::instance()->readPV(id);
}

void Core::write485(int id, double value)
{
    Modbus485::instance()->setTargetTension(id, value);
   
}

void Core::setFreq(int id , double value)
{
    MS300::instance()->updateFreqCache(id, value);
}
void Core::setMS300Run(int id, int mode) {
    quint16 cmd = 0x0001; // 預設停止
    if (mode == 1) cmd = 0x0012;      // 正轉
    else if (mode == 2) cmd = 0x0022; // 反轉
    qDebug()<< "ID=" << id << "run mode =" << mode;
    MS300::instance()->updateControlCache(id, cmd);
}

void Core::onMS300Data(int id, double v)
{
    //emit newMS300Data(id,v);
}

void Core::resetMS300(int id)
{
    // 根據手冊 2002H 的 bit 1 為 Reset 指令，故寫入數值 2
    qDebug() << "ID=" << id << " Trigger Reset";
    MS300::instance()->updateResetCache(id, 2);
}

void Core::loadSavedData() 
{
    QSettings settings("config.ini", QSettings::IniFormat);

    for (int id = 1; id <= 5; ++id) {
        settings.beginGroup(QString("Device_%1").arg(id));

        // 讀取數值，若沒紀錄過則預設 0.0
        double savedPV = settings.value("LastPV", 0.0).toDouble();
        double savedTQO = settings.value("LastTQO", 0.0).toDouble();

        settings.endGroup();

        // 讀取後，主動發一次訊號給 UI 顯示
        emit (id, savedPV, savedTQO);
    }
}

