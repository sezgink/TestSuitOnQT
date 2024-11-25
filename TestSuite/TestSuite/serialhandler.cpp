#include "serialhandler.h"

// Initialize serial port on contruction
SerialHandler::SerialHandler(QObject *parent)
    : QObject(parent),
    serial(new QSerialPort(this))
{
    // Connect the readyRead signal to handle incoming data
    connect(serial, &QSerialPort::readyRead, this, &SerialHandler::handleReadyRead);

    // Connect the errorOccurred signal to handle errors
    connect(serial, &QSerialPort::errorOccurred, this, &SerialHandler::handleError);
}

// Closing serial port on destructor
SerialHandler::~SerialHandler()
{
    if (serial->isOpen()) {
        serial->close();
    }
}

// Enumerate available serial ports
QList<QSerialPortInfo> SerialHandler::availablePorts() const
{
    return QSerialPortInfo::availablePorts();
}

// Open a serial port with specified settings
bool SerialHandler::openPort(const QString &portName, qint32 baudRate,
                             QSerialPort::DataBits dataBits,
                             QSerialPort::Parity parity,
                             QSerialPort::StopBits stopBits,
                             QSerialPort::FlowControl flowControl)
{
    if (serial->isOpen()) {
        serial->close();
    }

    serial->setPortName(portName);
    serial->setBaudRate(baudRate);
    serial->setDataBits(dataBits);
    serial->setParity(parity);
    serial->setStopBits(stopBits);
    serial->setFlowControl(flowControl);

    if (!serial->open(QIODevice::ReadWrite)) {
        emit errorOccurred(QString("Failed to open port %1: %2")
                               .arg(portName, serial->errorString()));
        return false;
    }

    return true;
}

// Close the currently open port
void SerialHandler::closePort()
{
    if (serial->isOpen()) {
        serial->close();
    }
}

// Check if the port is open
bool SerialHandler::isOpen() const
{
    return serial->isOpen();
}

// Handle incoming data when readyRead signal is emitted
void SerialHandler::handleReadyRead()
{
    QByteArray data = serial->readAll();
    if (!data.isEmpty()) {
        buffer.append(data);

        //Data will process here WIP
        preprocessData(buffer);


        emit newDataReceived(buffer);

        lastBuffer = buffer;
        lastBuffer.data();

        buffer.clear();
    }
}

void SerialHandler::preprocessData(QByteArray &data){
    //Preprocess here
}
// Handle errors when errorOccurred signal is emitted
void SerialHandler::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError) {
        return;
    }

    QString errorMessage;

    switch (error) {
    case QSerialPort::DeviceNotFoundError:
        errorMessage = "Device not found.";
        break;
    case QSerialPort::PermissionError:
        errorMessage = "Permission denied.";
        break;
    case QSerialPort::OpenError:
        errorMessage = "Unable to open the port.";
        break;
    case QSerialPort::ReadError:
        errorMessage = "Read error.";
        break;
    case QSerialPort::ResourceError:
        errorMessage = "Resource error.";
        break;
    case QSerialPort::UnsupportedOperationError:
        errorMessage = "Unsupported operation.";
        break;
    case QSerialPort::UnknownError:
    default:
        errorMessage = serial->errorString();
        break;
    }

    emit errorOccurred(errorMessage);

    // Close the port on certain errors
    if (serial->isOpen() && (error == QSerialPort::ResourceError ||
                             error == QSerialPort::UnsupportedOperationError ||
                             error == QSerialPort::DeviceNotFoundError)) {
        serial->close();
    }
}
