#include <QModbusReply>
#include <QStringList>
#include "MS300.h"

MS300::MS300(QObject* parent) : QObject(parent) {}

void MS300::reportCommunicationError(QString& lastError, int id, const QString& operation, const QString& error)
{
    const QString detail = error.isEmpty() ? QStringLiteral("unknown error") : error;
    const QString message = QString("MS300 COM4 %1%2: %3")
        .arg(operation)
        .arg(id > 0 ? QString(" (ID %1)").arg(id) : QString())
        .arg(detail);
    if (lastError == message) {
        return;
    }

    lastError = message;
    qWarning() << message;
    emit errorOccurred(id, message);
}

void MS300::reportFaultStatus(int id, quint16 status)
{
    if (id < 1 || id > 10 || (m_hasFaultStatus[id] && m_lastFaultStatus[id] == status)) {
        return;
    }

    m_hasFaultStatus[id] = true;
    m_lastFaultStatus[id] = status;

    const quint8 faultCode = static_cast<quint8>(status & 0x00FF);
    const quint8 warningCode = static_cast<quint8>((status >> 8) & 0x00FF);
    if (faultCode == 0 && warningCode == 0) {
        return;
    }

    QStringList codes;
    if (faultCode != 0) {
        codes << QString("fault code 0x%1 (%2)")
                     .arg(QString::number(faultCode, 16).rightJustified(2, QChar('0')).toUpper())
                     .arg(static_cast<int>(faultCode));
    }
    if (warningCode != 0) {
        codes << QString("warning code 0x%1 (%2)")
                     .arg(QString::number(warningCode, 16).rightJustified(2, QChar('0')).toUpper())
                     .arg(static_cast<int>(warningCode));
    }

    const QString message = QString("MS300 ID %1: %2").arg(id).arg(codes.join(", "));
    qWarning() << message;
    emit errorOccurred(id, message);
}

void MS300::initPort()
{
    m_modbus = new QModbusRtuSerialClient(this);
    m_modbus->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM4");
    m_modbus->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
    m_modbus->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    m_modbus->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    m_modbus->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    m_modbus->setTimeout(200);
    m_modbus->setNumberOfRetries(3);

    connect(m_modbus, &QModbusDevice::errorOccurred, this,
        [this](QModbusDevice::Error error) {
            if (error != QModbusDevice::NoError) {
                reportCommunicationError(m_lastConnectionError, 0, "connection", m_modbus->errorString());
            }
        });

    if (m_modbus->connectDevice()) {
        m_lastConnectionError.clear();
        qDebug() << "COM4 connected";
        m_pollTimer = new QTimer(this);
        connect(m_pollTimer, &QTimer::timeout, this, &MS300::onPollTimeout);
        m_pollTimer->start(50);
    }
    else {
        reportCommunicationError(m_lastConnectionError, 0, "connection", m_modbus->errorString());
    }
}

void MS300::onPollTimeout()
{
    if (!m_modbus || m_modbus->state() != QModbusDevice::ConnectedState) {
        const QString error = m_modbus ? m_modbus->errorString() : QStringLiteral("Modbus client is unavailable");
        reportCommunicationError(m_lastConnectionError, 0, "connection", error);
        return;
    }

    const bool scanAdditionalDrive = (m_pollSlot++ % 3) == 2;
    const int id = scanAdditionalDrive ? m_faultScanIndex : m_primaryIndex;
    if (scanAdditionalDrive) {
        ++m_faultScanIndex;
        if (m_faultScanIndex > 10) {
            m_faultScanIndex = 3;
        }
    }
    else {
        m_primaryIndex = (m_primaryIndex == 1) ? 2 : 1;
    }

    if (m_needWriteID2) {
        QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 0x2001, 1);
        writeUnit.setValue(0, static_cast<quint16>(m_targetHz * 100));

        if (auto* reply = m_modbus->sendWriteRequest(writeUnit, 2)) {
            connect(reply, &QModbusReply::finished, this, [this, reply]() {
                if (reply->error() == QModbusDevice::NoError) {
                    m_needWriteID2 = false;
                    m_lastWriteError.clear();
                    qDebug() << "ID 2 Frequency updated to:" << m_targetHz;
                }
                else {
                    reportCommunicationError(m_lastWriteError, 2, "write", reply->errorString());
                }
                reply->deleteLater();
            });
        }
        else {
            reportCommunicationError(m_lastWriteError, 2, "write", m_modbus->errorString());
        }
    }

    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 0x2100, 4);
    if (auto* reply = m_modbus->sendReadRequest(readUnit, id)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply, id]() {
                if (reply->error() == QModbusDevice::NoError) {
                    const QModbusDataUnit res = reply->result();
                    m_lastConnectionError.clear();
                    m_lastReadErrors[id].clear();
                    reportFaultStatus(id, res.value(0));

                    if (id == 1) {
                        const double hz = static_cast<double>(res.value(3)) / 100.0;
                        emit dataUpdated(id, hz);
                    }
                    else if (id == 2) {
                        const double rawValue = static_cast<double>(res.value(3));
                        const double lineSpeed = rawValue * (130.0 / 6000.0);
                        emit dataUpdated(id, lineSpeed);
                    }
                }
                else {
                    reportCommunicationError(m_lastReadErrors[id], id, "read", reply->errorString());
                }
                reply->deleteLater();
            });
        }
        else {
            if (reply->error() != QModbusDevice::NoError) {
                reportCommunicationError(m_lastReadErrors[id], id, "read", reply->errorString());
            }
            reply->deleteLater();
        }
    }
    else {
        reportCommunicationError(m_lastReadErrors[id], id, "read", m_modbus->errorString());
    }


}