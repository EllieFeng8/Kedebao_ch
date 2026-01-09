#include "DIOModule.h"

DIOModule& DIOModule::instance()
{
    static DIOModule instance;
    return instance;
}

DIOModule::DIOModule(QObject* parent)
    : diCtrl(nullptr), doCtrl(nullptr), currentOutputState(0)
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
    
    // 初始讀取 DO 狀態
    return doCtrl->Read(0, currentOutputState) == Success;
}

bool DIOModule::readInputs(uint8_t& port0, uint8_t& port1)
{
    QMutexLocker locker(&mutex);
    if (!diCtrl) return false;
    ErrorCode err0 = diCtrl->Read(0, port0);
    ErrorCode err1 = diCtrl->Read(1, port1);
    return (err0 == Success && err1 == Success);
    qDebug() << "readInput failed";
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