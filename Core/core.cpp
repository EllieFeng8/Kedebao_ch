
#include "core.h"
#include "ModbusManager.h"
#include <qsettings>

QMutex Core::m_mutex;

Core::Core(QObject* parent)
    : QObject(parent)
{
}
Core::~Core()
{

    stopAll(); 

    dioWorker->stop();
    if (threadDIO) {
        threadDIO->quit();
        threadDIO->wait();
    }


    if (threadTension) {
        threadTension->quit();
        threadTension->wait();
        qDebug() << "threadTension is quit";
    }
    if (threadMS300) {
        threadMS300->quit();
        threadMS300->wait();
        qDebug() << "threadMS300 is quit";

    }
    qDebug() << "Core destroyed: Resources cleaned up.";
}

Core& Core::instance()
{
    static Core inst;
    return inst;
}


void Core::addModbusServer( QString ip, int port)
{
    m_manager->createWorker();
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
    if (DataValues == values) {
        return;
    }

    if(values[102]==1)
    {
        m_mode = true;
    }
    else
    {
        m_mode = false;
    }

    for (int i = 0; i < values.size(); ++i) {
        
        if (DataValues[i] != values[i]) {
            qDebug() << "value" << i << " = " << values[i];
            DataValues[i] = values[i];
            updateProxyProperty(i, values[i]);
        }
    }
    
    //
    // INPUT 0~61
    // 
    //m_proxy->setUnwinderVfdFreqAlarm(DataValues[0]);
    //m_proxy->setMainDriveVfdFreqAlarm(DataValues[1]);
    //m_proxy->setSmallWinderVfdFreqAlarm(DataValues[2]);
    //m_proxy->setLargeWinderVfdFreqAlarm(DataValues[3]);
    //m_proxy->setSmallCutterVfdFreqAlarm(DataValues[4]);
    //m_proxy->setSelvedgeFanVfdFreqAlarm(DataValues[5]);
    //m_proxy->setLeftFanOverloadAlarm(DataValues[6]);
    //m_proxy->setRightFanOverloadAlarm(DataValues[7]);
    //m_proxy->setLargeCutterVfdFreqAlarm(DataValues[8]);
    //m_proxy->setLeftSelvedgeWinderVfdAlarm(DataValues[9]);
    //m_proxy->setRightSelvedgeWinderVfdAlarm(DataValues[10]);
    //m_proxy->setWebAlignerVfdFreqAlarm(DataValues[11]);
    //m_proxy->setUnwinderPowerLoss(DataValues[12]);
    //m_proxy->setMainDrivePowerLoss(DataValues[13]);
    //m_proxy->setSmallWinderPowerLoss(DataValues[14]);
    //m_proxy->setLargeWinderPowerLoss(DataValues[15]);
    //m_proxy->setSmallCutterPowerLoss(DataValues[16]);
    //m_proxy->setSelvedgeFanPowerLoss(DataValues[17]);
    //m_proxy->setLargeCutterPowerLoss(DataValues[18]);
    //m_proxy->setLeftSelvedgeWinderPowerLoss(DataValues[19]);
    //m_proxy->setRightSelvedgeWinderPowerLoss(DataValues[20]);
    //m_proxy->setWebAlignerPowerLoss(DataValues[21]);
    //m_proxy->setUnwinderDisconnect(DataValues[22]);
    //m_proxy->setMainDriveDisconnect(DataValues[23]);
    //m_proxy->setSmallWinderDisconnect(DataValues[24]);
    //m_proxy->setLargeWinderDisconnect(DataValues[25]);
    //m_proxy->setSmallCutterDisconnect(DataValues[26]);
    //m_proxy->setLeftFanDisconnect(DataValues[27]);
    //m_proxy->setRightFanDisconnect(DataValues[28]);
    //m_proxy->setLargeCutterDisconnect(DataValues[29]);
    //m_proxy->setLeftSelvedgeWinderDisconnect(DataValues[30]);
    //m_proxy->setRightSelvedgeWinderDisconnect(DataValues[31]);
    //m_proxy->setWebAlignerDisconnect(DataValues[32]);
    //m_proxy->setEmergencyStop1(DataValues[33]);
    //m_proxy->setEmergencyStop2(DataValues[34]);
    //m_proxy->setEmergencyStop3(DataValues[35]);
    //m_proxy->setEmergencyStop4(DataValues[36]);
    //m_proxy->setEmergencyStop5(DataValues[37]);
    //m_proxy->setEmergencyStop6(DataValues[38]);
    //m_proxy->setEmergencyStop7(DataValues[39]);
    //m_proxy->setMainDriveLeftDoor1Open(DataValues[40]);
    //m_proxy->setMainDriveLeftDoor2Open(DataValues[41]);
    //m_proxy->setMainDriveRightDoor3Open(DataValues[42]);
    //m_proxy->setMainDriveRightDoor4Open(DataValues[43]);
    //m_proxy->setLargeWinderLeftDoor5Open(DataValues[44]);
    //m_proxy->setLargeWinderLeftDoor6Open(DataValues[45]);
    //m_proxy->setLargeWinderRightDoor7Open(DataValues[46]);
    //m_proxy->setLargeWinderRightDoor8Open(DataValues[47]);
    //m_proxy->setUnwindingFenceDetect1(DataValues[48]);
    //m_proxy->setUnwindingFenceDetect2(DataValues[49]);
    //m_proxy->setLargeWinderFenceDetect3(DataValues[50]);
    //m_proxy->setLargeWinderFenceDetect4(DataValues[51]);
    //m_proxy->setUnwindingSafetyLightCurtainAlarm(DataValues[52]);
    //m_proxy->setInspectionSafetyLightCurtainAlarm(DataValues[53]);
    //m_proxy->setLargeWinderSafetyLightCurtainAlarm(DataValues[54]);
    //m_proxy->setSmallWinderZeroSpeedDetect(DataValues[55]);
    //m_proxy->setLargeWinderZeroSpeedDetect(DataValues[56]);
    //m_proxy->setUnwindingTensionOver(DataValues[57]);
    //m_proxy->setSmallWinderTensionOver(DataValues[58]);
    //m_proxy->setLargeWinderTensionOver(DataValues[59]);
    //m_proxy->setLeftSelvedgeWinderAngleAlarm(DataValues[60]);
    //m_proxy->setRightSelvedgeWinderAngleAlarm(DataValues[61]);
    ////
    //// OUTPUT 64~102
    ////
    //m_proxy->setVfdAlarmReset(DataValues[64]);
    //m_proxy->setUnwinderForward(DataValues[65]);
    //m_proxy->setUnwinderReverse(DataValues[66]);
    //m_proxy->setMainDriveForward(DataValues[67]);
    //m_proxy->setMainDriveReverse(DataValues[68]);
    //m_proxy->setSmallWinderForward(DataValues[69]);
    //m_proxy->setSmallWinderReverse(DataValues[70]);
    //m_proxy->setLargeWinderForward(DataValues[71]);
    //m_proxy->setLargeWinderReverse(DataValues[72]);
    //m_proxy->setSmallCutterStart(DataValues[73]);
    //m_proxy->setSelvedgeFanStart(DataValues[74]);
    //m_proxy->setLargeCutterStart(DataValues[75]);
    //m_proxy->setLeftSelvedgeWinderForward(DataValues[76]);
    //m_proxy->setLeftSelvedgeWinderReverse(DataValues[77]);
    //m_proxy->setRightSelvedgeWinderForward(DataValues[78]);
    //m_proxy->setRightSelvedgeWinderReverse(DataValues[79]);
    //m_proxy->setWebAlignerStart(DataValues[80]);
    //m_proxy->setUnwindingTensionAuto(DataValues[81]);
    //m_proxy->setUnwindingDiameterReset(DataValues[82]);
    //m_proxy->setSmallWinderTensionAuto(DataValues[83]);
    //m_proxy->setSmallWinderDiameterReset(DataValues[84]);
    //m_proxy->setLargeWinderTensionAuto(DataValues[85]);
    //m_proxy->setLargeWinderDiameterReset(DataValues[86]);
    //m_proxy->setLeftSelvedgeWinderAuto(DataValues[87]);
    //m_proxy->setRightSelvedgeWinderAuto(DataValues[88]);
    //m_proxy->setNipRollUp(DataValues[89]);
    //m_proxy->setNipRollDown(DataValues[90]);
    //m_proxy->setLeftPressPlateForward(DataValues[91]);
    //m_proxy->setLeftPressPlateBackward(DataValues[92]);
    //m_proxy->setRightPressPlateForward(DataValues[93]);
    //m_proxy->setRightPressPlateBackward(DataValues[94]);
    //m_proxy->setSmallCutterIn(DataValues[95]);
    //m_proxy->setLargeCutterIn(DataValues[96]);
    //m_proxy->setModeSelect(DataValues[97]);
    //m_proxy->setRunIndicator(DataValues[98]);
    //m_proxy->setAlarmIndicator(DataValues[99]);
    //m_proxy->setStopIndicator(DataValues[100]);
    //m_proxy->setBuzzer(DataValues[101]);
    //m_proxy->setSmallRollModeSelect(DataValues[102]);
}
void Core::onWorkerData2(QVector<quint16> values)
{
    if (DataValues2 == values) {
        return;
    }
    DataValues2 = values;
    qDebug() << "W2=" << DataValues2[0];
    m_proxy->setSmallRollCutter1(DataValues2[0]);
}

void Core::onWorkerError( QString msg)
{
    qDebug() << "worker error :" << msg;
}

void Core::on485Data(int id, double PV, double tqo)
{
    //emit newTensionData(id,PV,tqo);
    if (id == 1)
    {
        m_proxy->setUnwindingTension(PV);
    }
    else if (id == 2)
    {
        m_proxy->setSmallRollTension(PV);
    }
    else if (id == 3)
    {
        m_proxy->setLargeRollTension(PV);
    }
}

void Core::onholdingRegisterReady( QVector<quint16> values)
{
    double v1 = values[0] /409.5;
    double v2 = values[1] /409.5;
    double v3 = values[2] /409.5;

    double v4 = values[3] /409.5;

    //emit holdingRegisterReady( values);
    m_proxy->setAnalogOutUnwinderMainDrive(v1);
    m_proxy->setAnalogOutWinder(v2);
    m_proxy->setAnalogOutCutter(v3);
    m_proxy->setAnalogOutSelvedgeWinder(v4);
}

void Core::writeSingleCoil(int address, double value)
{
    //qDebug() << " CORE : write single coil" << address <<" = " <<value ;
    m_manager->writeSingleCoil( address, value);
}

void Core::writeCoils( int startAddress, const QVector<bool>& values)
{
    m_manager->writeCoils( startAddress, values);   
}

void Core::writeRegister(int startAddr, const quint16 &value)
{
    //m_manager->writeRegister( value);

}

void Core::readRegisters( int startAddress, int count)
{
    m_manager->readRegisters( startAddress, count);
}

//void Core::initDIO()
//{
//    DIOModule::instance().initialize();
//}

//void Core::readDIO()
//{
//    uint8_t p0 = 0, p1 = 0, out = 0;
//
//    bool ok1 = DIOModule::instance().readInputs(p0, p1);
//    bool ok2 = DIOModule::instance().readOutputs(out);
//    if (ok1) {
//        qDebug() << "MOS-1110Y DI:"
//            << "Port0 =" << p0
//            << "Port1 =" << p1;
//
//        // 逐 bit 顯示
//        qDebug() << "DI bits (0~7):";
//        for (int i = 0; i < 8; i++)
//            qDebug() << " DI" << i << ":" << ((p0 >> i) & 1);
//
//        qDebug() << "DI bits (8~15):";
//        for (int i = 0; i < 8; i++)
//            qDebug() << " DI" << (i + 8) << ":" << ((p1 >> i) & 1);
//    }
//    else {
//        qDebug() << "DI read failed.";
//    }
//
//    if (ok2) {
//        qDebug() << "MOS-1110Y DO =" << out;
//
//        for (int i = 0; i < 8; i++)
//            qDebug() << " DO" << i << ":" << ((out >> i) & 1);
//    }
//    else {
//        qDebug() << "DO read failed.";
//    }
//    //emit dioUpdated(p0, p1, out);
//}
//
//
//void Core::setOutputBit(int bit, bool high)
//{
//
//    DIOModule::instance().setOutput(bit, high);
//}

void Core::read485(int id)
{
    m_tension->readPV(id);
}

void Core::write485(int id, double value)
{
    m_tension->setTargetTension(id, value);
   
}

void Core::setFreq(int id , double value)
{
    m_ms300->updateFreqCache(id, value);
}
void Core::setMS300Run(int id, int mode) {
    quint16 cmd = 0x0001; // 預設停止
    if (mode == 1) cmd = 0x0012;      // 正轉
    else if (mode == 2) cmd = 0x0022; // 反轉
    qDebug()<< "ID=" << id << "run mode =" << mode;
    m_ms300->updateControlCache(id, cmd);
}

void Core::onMS300Data(int id, double v)
{
    m_proxy->setSpeed(v);
}

void Core::resetMS300(int id)
{
    // 根據手冊 2002H 的 bit 1 為 Reset 指令，故寫入數值 2
    qDebug() << "ID=" << id << " Trigger Reset";
    m_ms300->updateResetCache(id, 2);
}

void Core::loadSavedData() 
{
    //QSettings settings("config.ini", QSettings::IniFormat);

    //for (int id = 1; id <= 5; ++id) {
    //    settings.beginGroup(QString("Device_%1").arg(id));

    //    // 讀取數值，若沒紀錄過則預設 0.0
    //    double savedPV = settings.value("LastPV", 0.0).toDouble();
    //    double savedTQO = settings.value("LastTQO", 0.0).toDouble();

    //    settings.endGroup();

    //    // 讀取後，主動發一次訊號給 UI 顯示
    //    emit (id, savedPV, savedTQO);
    //}
}

void Core::onZeroSpeed01()
{
    qDebug() << "Error Zero Speed SmallWinderZeroSpeedDetect";
    m_proxy->setUnwindingTensionAuto(false);
    m_proxy->setSmallWinderTensionAuto(false);
    m_proxy->setLargeWinderTensionAuto(false);
    m_proxy->setLeftSelvedgeWinderAuto(false);
    m_proxy->setRightSelvedgeWinderAuto(false);
}
void Core::onZeroSpeed02()
{
    qDebug() << "Error Zero Speed LargeWinderZeroSpeedDetect";
    m_proxy->setUnwindingTensionAuto(false);
    m_proxy->setSmallWinderTensionAuto(false);
    m_proxy->setLargeWinderTensionAuto(false);
    m_proxy->setLeftSelvedgeWinderAuto(false);
    m_proxy->setRightSelvedgeWinderAuto(false);
}

void Core::setTensionSV_1(double v)
{
    QMetaObject::invokeMethod(m_tension, [this,v]() {m_tension->setTargetTension(1, v); },
        Qt::QueuedConnection);
}

void Core::setTensionSV_2(double v)
{
    QMetaObject::invokeMethod(m_tension, [this,v]() {m_tension->setTargetTension(2, v); },
        Qt::QueuedConnection);
}

void Core::setTensionSV_3(double v)
{
    QMetaObject::invokeMethod(m_tension, [this,v]() {m_tension->setTargetTension(3, v); },
        Qt::QueuedConnection);
}

void Core::updateProxyProperty(int index, quint16 value)
{
    
    if (!m_proxy) return;
    //m_proxy->blockSignals(true);
    switch (index) {
        // INPUT 0 ~ 61
    case 0:  m_proxy->setUnwinderVfdFreqAlarm(value); 
        m_proxy->setUnwinderVfdFreqAlarmLight(value); break;
    case 1:  m_proxy->setMainDriveVfdFreqAlarm(value); 
        m_proxy->setMainDriveVfdFreqAlarmLight(value); break;
    case 2:  m_proxy->setSmallWinderVfdFreqAlarm(value);
        m_proxy->setSmallWinderVfdFreqAlarmLight(value); break;
    case 3:  m_proxy->setLargeWinderVfdFreqAlarm(value);
        m_proxy->setLargeWinderVfdFreqAlarmLight(value); break;
    case 4:  m_proxy->setSmallCutterVfdFreqAlarm(value);
        m_proxy->setSmallCutterVfdFreqAlarmLight(value); break;
    case 5:  m_proxy->setSelvedgeFanVfdFreqAlarm(value);
        m_proxy->setSelvedgeFanVfdFreqAlarmLight(value); break;
    case 6:  m_proxy->setLeftFanOverloadAlarm(value);
        m_proxy->setLeftFanOverloadAlarmLight(value); break;
    case 7:  m_proxy->setRightFanOverloadAlarm(value);
        m_proxy->setRightFanOverloadAlarmLight(value); break;
    case 8:  m_proxy->setLargeCutterVfdFreqAlarm(value);
        m_proxy->setLargeCutterVfdFreqAlarmLight(value); break;
    case 9:  m_proxy->setLeftSelvedgeWinderVfdAlarm(value);
        m_proxy->setLeftSelvedgeWinderVfdAlarmLight(value); break;
    case 10: m_proxy->setRightSelvedgeWinderVfdAlarm(value);
        m_proxy->setRightSelvedgeWinderVfdAlarmLight(value); break;
    case 11: m_proxy->setWebAlignerVfdFreqAlarm(value);
        m_proxy->setWebAlignerVfdFreqAlarmLight(value); break;
    case 12: m_proxy->setUnwinderPowerLoss(value);
        m_proxy->setUnwinderPowerLossLight(value); break;
    case 13: m_proxy->setMainDrivePowerLoss(value);
        m_proxy->setMainDrivePowerLossLight(value); break;
    case 14: m_proxy->setSmallWinderPowerLoss(value);
        m_proxy->setSmallWinderPowerLossLight(value); break;
    case 15: m_proxy->setLargeWinderPowerLoss(value);
        m_proxy->setLargeWinderPowerLossLight(value); break;
    case 16: m_proxy->setSmallCutterPowerLoss(value);
        m_proxy->setSmallCutterPowerLossLight(value); break;
    case 17: m_proxy->setSelvedgeFanPowerLoss(value);
        m_proxy->setSelvedgeFanPowerLossLight(value); break;
    case 18: m_proxy->setLargeCutterPowerLoss(value);
        m_proxy->setLargeCutterPowerLossLight(value); break;
    case 19: m_proxy->setLeftSelvedgeWinderPowerLoss(value);
        m_proxy->setLeftSelvedgeWinderPowerLossLight(value); break;
    case 20: m_proxy->setRightSelvedgeWinderPowerLoss(value);
        m_proxy->setRightSelvedgeWinderPowerLossLight(value); break;
    case 21: m_proxy->setWebAlignerPowerLoss(value);
        m_proxy->setWebAlignerPowerLossLight(value); break;
    case 22: m_proxy->setUnwinderDisconnect(value);
        m_proxy->setUnwinderDisconnectLight(value); break;
    case 23: m_proxy->setMainDriveDisconnect(value);
        m_proxy->setMainDriveDisconnectLight(value); break;
    case 24: m_proxy->setSmallWinderDisconnect(value);
        m_proxy->setSmallWinderDisconnectLight(value); break;
    case 25: m_proxy->setLargeWinderDisconnect(value);
        m_proxy->setLargeWinderDisconnectLight(value); break;
    case 26: m_proxy->setSmallCutterDisconnect(value); 
        m_proxy->setSmallCutterDisconnectLight(value); break;
    case 27: m_proxy->setLeftFanDisconnect(value);
        m_proxy->setLeftFanDisconnectLight(value); break;
    case 28: m_proxy->setRightFanDisconnect(value); 
        m_proxy->setRightFanDisconnectLight(value); break;
    case 29: m_proxy->setLargeCutterDisconnect(value);
        m_proxy->setLargeCutterDisconnectLight(value); break;
    case 30: m_proxy->setLeftSelvedgeWinderDisconnect(value);
        m_proxy->setLeftSelvedgeWinderDisconnectLight(value); break;
    case 31: m_proxy->setRightSelvedgeWinderDisconnect(value);
        m_proxy->setRightSelvedgeWinderDisconnectLight(value); break;
    case 32: m_proxy->setWebAlignerDisconnect(value);
        m_proxy->setWebAlignerDisconnectLight(value); break;
    case 33: m_proxy->setEmergencyStop1(value);
        m_proxy->setEmergencyStop1Light(value); break;
    case 34: m_proxy->setEmergencyStop2(value);
        m_proxy->setEmergencyStop2Light(value); break;
    case 35: m_proxy->setEmergencyStop3(value);
        m_proxy->setEmergencyStop3Light(value); break;
    case 36: m_proxy->setEmergencyStop4(value);
        m_proxy->setEmergencyStop4Light(value); break;
    case 37: m_proxy->setEmergencyStop5(value);
        m_proxy->setEmergencyStop5Light(value); break;
    case 38: m_proxy->setEmergencyStop6(value);
        m_proxy->setEmergencyStop6Light(value); break;
    case 39: m_proxy->setEmergencyStop7(value);
        m_proxy->setEmergencyStop7Light(value); break;
    case 40: m_proxy->setMainDriveLeftDoor1Open(value);
        m_proxy->setMainDriveLeftDoor1OpenLight(value); break;
    case 41: m_proxy->setMainDriveLeftDoor2Open(value);
        m_proxy->setMainDriveLeftDoor2OpenLight(value); break;
    case 42: m_proxy->setMainDriveRightDoor3Open(value);
        m_proxy->setMainDriveRightDoor3OpenLight(value); break;
    case 43: m_proxy->setMainDriveRightDoor4Open(value);
        m_proxy->setMainDriveRightDoor4OpenLight(value); break;
    case 44: m_proxy->setLargeWinderLeftDoor5Open(value);
        m_proxy->setLargeWinderLeftDoor5OpenLight(value); break;
    case 45: m_proxy->setLargeWinderLeftDoor6Open(value);
        m_proxy->setLargeWinderLeftDoor6OpenLight(value); break;
    case 46: m_proxy->setLargeWinderRightDoor7Open(value);
        m_proxy->setLargeWinderRightDoor7OpenLight(value); break;
    case 47: m_proxy->setLargeWinderRightDoor8Open(value);
        m_proxy->setLargeWinderRightDoor8OpenLight(value); break;
    case 48: m_proxy->setUnwindingFenceDetect1(value);
        m_proxy->setUnwindingFenceDetect1Light(value); break;
    case 49: m_proxy->setUnwindingFenceDetect2(value);
        m_proxy->setUnwindingFenceDetect2Light(value); break;
    case 50: m_proxy->setLargeWinderFenceDetect3(value);
        m_proxy->setLargeWinderFenceDetect3Light(value); break;
    case 51: m_proxy->setLargeWinderFenceDetect4(value);
        m_proxy->setLargeWinderFenceDetect4Light(value); break;
    case 52: m_proxy->setUnwindingSafetyLightCurtainAlarm(value);
        m_proxy->setUnwindingSafetyLightCurtainAlarmLight(value); break;
    case 53: m_proxy->setInspectionSafetyLightCurtainAlarm(value);
        m_proxy->setInspectionSafetyLightCurtainAlarmLight(value); break;
    case 54: m_proxy->setLargeWinderSafetyLightCurtainAlarm(value);
        m_proxy->setLargeWinderSafetyLightCurtainAlarmLight(value); break;
    case 55: m_proxy->setSmallWinderZeroSpeedDetect(value);
        m_proxy->setSmallWinderZeroSpeedDetectLight(value); break;
    case 56: m_proxy->setLargeWinderZeroSpeedDetect(value);
        m_proxy->setLargeWinderZeroSpeedDetectLight(value); break;
    case 57: m_proxy->setUnwindingTensionOver(value);
        m_proxy->setUnwindingTensionOverLight(value); break;
    case 58: m_proxy->setSmallWinderTensionOver(value);
        m_proxy->setSmallWinderTensionOverLight(value); break;
    case 59: m_proxy->setLargeWinderTensionOver(value);
        m_proxy->setLargeWinderTensionOverLight(value); break;
    case 60: m_proxy->setLeftSelvedgeWinderAngleAlarm(value);
        m_proxy->setLeftSelvedgeWinderAngleAlarmLight(value); break;
    case 61: m_proxy->setRightSelvedgeWinderAngleAlarm(value);
        m_proxy->setRightSelvedgeWinderAngleAlarmLight(value); break;

        // OUTPUT 64 ~ 102
    case 64: m_proxy->setVfdAlarmReset(value); break;
    case 65: m_proxy->setUnwinderForward(value); break;
    case 66: m_proxy->setUnwinderReverse(value); break;
    case 67: m_proxy->setMainDriveForward(value); break;
    case 68: m_proxy->setMainDriveReverse(value); break;
    case 69: m_proxy->setSmallWinderForward(value); break;
    case 70: m_proxy->setSmallWinderReverse(value); break;
    case 71: m_proxy->setLargeWinderForward(value); break;
    case 72: m_proxy->setLargeWinderReverse(value); break;
    case 73: m_proxy->setSmallCutterStart(value); break;
    case 74: m_proxy->setSelvedgeFanStart(value); break;
    case 75: m_proxy->setLargeCutterStart(value); break;
    case 76: m_proxy->setLeftSelvedgeWinderForward(value); break;
    case 77: m_proxy->setLeftSelvedgeWinderReverse(value); break;
    case 78: m_proxy->setRightSelvedgeWinderForward(value); break;
    case 79: m_proxy->setRightSelvedgeWinderReverse(value); break;
    case 80: m_proxy->setWebAlignerStart(value); break;
    case 81: m_proxy->setUnwindingTensionAuto(value); break;
    case 82: m_proxy->setUnwindingDiameterReset(value); break;
    case 83: m_proxy->setSmallWinderTensionAuto(value); break;
    case 84: m_proxy->setSmallWinderDiameterReset(value); break;
    case 85: m_proxy->setLargeWinderTensionAuto(value); break;
    case 86: m_proxy->setLargeWinderDiameterReset(value); break;
    case 87: m_proxy->setLeftSelvedgeWinderAuto(value); break;
    case 88: m_proxy->setRightSelvedgeWinderAuto(value); break;
    case 89: m_proxy->setNipRollUp(value); break;
    case 90: m_proxy->setNipRollDown(value); break;
    case 91: m_proxy->setLeftPressPlateForward(value); break;
    case 92: m_proxy->setLeftPressPlateBackward(value); break;
    case 93: m_proxy->setRightPressPlateForward(value); break;
    case 94: m_proxy->setRightPressPlateBackward(value); break;
    case 95: m_proxy->setSmallCutterIn(value); break;
    case 96: m_proxy->setLargeCutterIn(value); break;
    case 97: m_proxy->setModeSelect(value); break;
    case 98: m_proxy->setRunIndicator(value); break;
    case 99: m_proxy->setAlarmIndicator(value); break;
    case 100: m_proxy->setStopIndicator(value); break;
    case 101: m_proxy->setBuzzer(value); break;
    case 102: m_proxy->setSmallRollModeSelect(value); break;

    default: break;
    }
    //m_proxy->blockSignals(false);
}

//void Core::updateProxyProperty2(int index, quint16 value)
//{
//    if (!m_proxy) return;
//
//    switch (index) {
//
//    case 0:  m_proxy->setSmallRollCutter1(value); break;
//    case 1:  m_proxy->setMainDriveVfdFreqAlarm(value); break;
//    case 2:  m_proxy->setSmallWinderVfdFreqAlarm(value); break;
//    case 3:  m_proxy->setLargeWinderVfdFreqAlarm(value); break;
//    case 4:  m_proxy->setSmallCutterVfdFreqAlarm(value); break;
//    case 5:  m_proxy->setSelvedgeFanVfdFreqAlarm(value); break;
//    case 6:  m_proxy->setLeftFanOverloadAlarm(value); break;
//    case 7:  m_proxy->setRightFanOverloadAlarm(value); break;
//    case 8:  m_proxy->setLargeCutterVfdFreqAlarm(value); break;
//    case 9:  m_proxy->setLeftSelvedgeWinderVfdAlarm(value); break;
//    case 10: m_proxy->setRightSelvedgeWinderVfdAlarm(value); break;
//    case 11: m_proxy->setWebAlignerVfdFreqAlarm(value); break;
//    case 12: m_proxy->setUnwinderPowerLoss(value); break;
//    case 13: m_proxy->setMainDrivePowerLoss(value); break;
//    case 14: m_proxy->setSmallWinderPowerLoss(value); break;
//    case 15: m_proxy->setLargeWinderPowerLoss(value); break;
//    case 16: m_proxy->setSmallCutterPowerLoss(value); break;
//    default: break;
//    }
//}
void Core::handleDIOSignal(int bitIndex, bool state)
{
    if (!m_proxy) return;

    // 將布林狀態轉為 double，以符合您 Proxy 函數的參數形態
    double val = state ? 1.0 : 0.0;

    switch (bitIndex) {
    case 0:
        m_proxy->setIpcStart(val);
        if (state)
        {
        m_manager->IpcStart(state);//動作  

         qDebug() << "DI Bit 0 changed" << state;//Log 
        }
        break;
    case 1:
        m_proxy->setIpcStop(val);
        if (state)
        {
            m_manager->IpcStop(state);//動作  
        }
        qDebug() << "DI Bit 1 changed" << state ;//Log 
        break;
    case 2:
        m_proxy->setIpcAlarmReset(val);
        writeSingleCoil(64, state);//動作  
        qDebug() << "DI Bit 2 changed" << state << ")";//Log 
        break;
    case 3:
        m_proxy->setMainJogForward(val);
        writeSingleCoil(67, state);//動作  
        qDebug() << "DI Bit 3 changed" << state << ")";//Log 
        break;
    case 4:
        m_proxy->setMainJogReverse(val);
        writeSingleCoil(68, state);//動作  
        qDebug() << "DI Bit 4 changed" << state << ")";//Log 
        break;
    case 5:
        m_proxy->setSmallWinderJogForward(val);
        writeSingleCoil(69, state);//動作  
        qDebug() << "DI Bit 5 changed" << state << ")";//Log 
        break;
    case 6:
        m_proxy->setSmallWinderJogReverse(val);
        writeSingleCoil(70, state);//動作  
        qDebug() << "DI Bit 6 changed" << state << ")";//Log 
        break;
    case 7:
        m_proxy->setUnwinderJogReverseSelect(val);
        if (state)
        {
            m_UnwinderJogReverseSelect = true;
            qDebug() << "DI Bit 7 changed" << state << ")";//Log 
        }
        else
        {
            m_UnwinderJogReverseSelect = false;
            qDebug() << "DI Bit 7 changed" << state << ")";//Log 
        }
        break;
    case 8:
        m_proxy->setUnwinderJogStart(val);
        if (state) // 按下時：根據目前選擇的方向啟動
        {
            if (m_UnwinderJogReverseSelect)
                writeSingleCoil(66, state);
            else
                writeSingleCoil(65, state);
        }
        else // 放開時：不管之前是哪個方向，通通關掉！
        {
            writeSingleCoil(65, 0.0);
            writeSingleCoil(66, 0.0);
        }
        qDebug() << "DI Bit 8 changed" << state << ")";//Log 

        break;
    case 9:
        m_proxy->setWinderJogReverseSelect(val);
        if (state)
        {
            m_WinderJogReverseSelect = true;
            qDebug() << "DI Bit 9 changed" << state << ")";//Log 
        }
        else
        {
            m_WinderJogReverseSelect = false;
            qDebug() << "DI Bit 9 changed" << state << ")";//Log 
        }
        break;
    case 10:

        m_proxy->setWinderJogStart(val);

        if (m_LeftSelvedgeWinderSelect && m_RightSelvedgeWinderSelect)
        {
            targetWinder = Winder2;
        }
        else if (!m_LeftSelvedgeWinderSelect && m_RightSelvedgeWinderSelect) 
        {
            targetWinder = Winder3;
        }
        else if (m_LeftSelvedgeWinderSelect && !m_RightSelvedgeWinderSelect)
        {
            targetWinder = Winder4;
        }
        else 
        {
            targetWinder = Winder1;
        }
        // 決定方向位址 (69 正轉 / 70 反轉)
        targetAddr = m_WinderJogReverseSelect ? 70 : 69;

        if (state) {
            // 按下時：送出啟動訊號
            writeCoils(targetAddr, targetWinder);
            qDebug() << "Winder Jog START (" << (m_WinderJogReverseSelect ? "Reverse" : "Forward") << ")";
        }
        else {
            // 放開時：送出全 0 向量強制停止 

            writeCoils(69, StopWinderJog);
            qDebug() << "Winder Jog STOP";
        }

        break;
    case 11:
        m_proxy->setLeftSelvedgeWinderSelect(val);    
        if (state)
        {
            m_LeftSelvedgeWinderSelect = true;
            qDebug() << "DI Bit 11 changed" << state << ")";//Log 
        }
        else
        {
            m_LeftSelvedgeWinderSelect = false;
            qDebug() << "DI Bit 11 changed" << state << ")";//Log 
        }
        break;
    case 12:
        m_proxy->setRightSelvedgeWinderSelect(val);  
        if (state)
        {
            m_RightSelvedgeWinderSelect = true;
            qDebug() << "DI Bit 12 changed" << state << ")";//Log 
        }
        else
        {
            m_RightSelvedgeWinderSelect = false;
            qDebug() << "DI Bit 12 changed" << state << ")";//Log 
        }
        break;

        // 如果還有剩下的 13, 14, 15 位元，可以在此擴充
    case 13:
        // 預留位置
        break;
    case 14:
        // 預留位置
        break;

    default:
        break;
    }
}