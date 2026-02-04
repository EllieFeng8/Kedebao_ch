#include "DIOModule.h"
#include <qthread>


DIOModule::DIOModule(QObject* parent)
    : diCtrl(nullptr), doCtrl(nullptr), currentOutputState(0)
{

}

DIOModule::~DIOModule()
{
    if (diCtrl) {
        diCtrl->Dispose();
      
    }
    if (doCtrl) {
        doCtrl->Dispose();
    
    }
}

bool DIOModule::initialize(const wchar_t* deviceDescription)
{
    diCtrl = InstantDiCtrl::Create();
    if (!diCtrl) {
        qDebug() << "Failed to create InstantDiCtrl";
    }
    doCtrl = InstantDoCtrl::Create();
    if (!doCtrl) {
        qDebug() << "Failed to create InstantDoCtrl";
    }

    Array<DeviceTreeNode>* supportedDevices = diCtrl->getSupportedDevices();
    Array<DeviceTreeNode>* supportedDeviceso = doCtrl->getSupportedDevices();
    for (int i = 0; i < supportedDevices->getCount(); i++) {
        DeviceTreeNode const& node = supportedDevices->getItem(i);
        qDebug("%d, %ls\n", node.DeviceNumber, node.Description);
    }

    DeviceInformation deviceInfo(deviceDescription);
    // DI 初始化

    ErrorCode errorCode = Success;
    errorCode = diCtrl->setSelectedDevice(deviceInfo);
    if (errorCode != Success)
    {
        qDebug() << "Failed to set di selected device"<< errorCode;
        return false;
    }

    // 檢查 DI port 數 (MOS-1110Y 應該是 2 port = 16 DI)
    int diPortCount = diCtrl->getPortCount();
    if (diPortCount < 2) {
        qDebug() << "ERROR: Device DI ports < 2, not 16-DI device!";
        return false;
    }

    // DO 初始化
    errorCode = doCtrl->setSelectedDevice(deviceInfo);
    if (errorCode != Success)
    {
        qDebug() << "Failed to set do selected device"<< errorCode ;
        return false;
    }
    
    // 檢查 DO port 數 (MOS-1110Y 應該是 1 port = 8 DO)
    int doPortCount = doCtrl->getPortCount();
    if (doPortCount < 1) {
        qDebug() << "ERROR: Device DO ports < 1, expecting at least 8 DO";
        return false;
    }
    //m_timer = new QTimer(this);
    //connect(m_timer, &QTimer::timeout, this, &DIOModule::process);
    //m_timer->start(50);
    //// 初始讀取 DO 狀態
    //return doCtrl->Read(0, currentOutputState) == Success;
    bool success = (doCtrl->Read(0, currentOutputState) == Success);

    if (success) {
        // 確保在 return 之前啟動計時器
        m_timer = new QTimer(this);
        connect(m_timer, &QTimer::timeout, this, &DIOModule::process);
        m_timer->start(50);
    }

    return success;
}

bool DIOModule::readInputs(uint8_t& port0, uint8_t& port1)
{
    QMutexLocker locker(&mutex);
    if (!diCtrl) return false;
    ErrorCode err0 = diCtrl->Read(0, port0);
    ErrorCode err1 = diCtrl->Read(1, port1);
    if (err0 == Success && err1 == Success) {
        // 若需要偵錯，請在 return 前執行
        // qDebug() << "DI Read Success - P0:" << port0 << "P1:" << port1; 
        return true;
    }
    else {
        qDebug() << "DI read failed. Error codes:" << err0 << "," << err1;
    }

    //qDebug() << "readInput failed";
    //if (readInputs(port0,port1)) {
    //    qDebug() << "MOS-1110Y DI:";

    //    // 逐 bit 顯示
    //    qDebug() << "DI bits (0~7):";
    //    for (int i = 0; i < 8; i++)
    //    {
    //        qDebug() << " DI" << i << ":" << ((port0 >> i) & 1);
    //        if (i == 0)
    //        {
    //            
    //        }
    //    }
    //    qDebug() << "DI bits (8~15):";
    //    for (int i = 0; i < 8; i++)
    //        qDebug() << " DI" << (i + 8) << ":" << ((port1 >> i) & 1);
    //}
    //else {
    //    qDebug() << "DI read failed.";
    //}
}

bool DIOModule::readOutputs(uint8_t& value)
{
    QMutexLocker locker(&mutex);
    if (!doCtrl) return false;
    ErrorCode ret = doCtrl->Read(0, value);
    if (ret == Success) currentOutputState = value;
    return ret == Success;
}

bool DIOModule::setOutput(int bit, bool high)
{
    if (!doCtrl || bit < 0 || bit > 7) return false;
	QMutexLocker locker(&mutex);
    if (high)
        currentOutputState |= (1 << bit);
    else
        currentOutputState &= ~(1 << bit);
    return doCtrl->Write(0, currentOutputState) == Success;
}

void DIOModule::process() {



    //while (m_running) 
    //{
        uint8_t p0 = 0, p1 = 0;

        if (readInputs(p0, p1)) 
        {
            uint16_t currentState = (static_cast<uint16_t>(p1) << 8) | p0;
            QString binaryStr = QString("%1").arg(currentState, 16, 2, QChar('0'));

            //qDebug() << "Current DI State: [" << binaryStr.mid(0, 8) << "|" << binaryStr.mid(8, 8) << "]";
            uint16_t changed = currentState ^ lastState;

            for (int i = 0; i < 16; ++i) 
            {
                if ((changed >> i) & 1) 
                {   // 只有變動的位元才處理
                    bool state = (currentState >> i) & 1;
                    emit bitChanged(i, state);
                }
            }
            lastState = currentState;
        }
        //QThread::msleep(50);
    //}
}