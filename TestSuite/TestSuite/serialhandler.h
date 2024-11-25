#pragma once

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QVector>

class SerialHandler : public QObject
{
    Q_OBJECT
public:
    explicit SerialHandler(QObject *parent = nullptr);
    ~SerialHandler();

    // Enumerate available serial ports
    QList<QSerialPortInfo> availablePorts() const;

    // Open a serial port with specified settings
    bool openPort(const QString &portName, qint32 baudRate = 115200,
                  QSerialPort::DataBits dataBits = QSerialPort::Data8,
                  QSerialPort::Parity parity = QSerialPort::NoParity,
                  QSerialPort::StopBits stopBits = QSerialPort::OneStop,
                  QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl);

    // Close the currently open port
    void closePort();

    // Check if the port is open
    bool isOpen() const;

signals:
    // Emitted when new data is received
    void newDataReceived(const QByteArray &data);

    // Emitted when an error occurs
    void errorOccurred(const QString &errorString);

private slots:
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort *serial;
    QByteArray buffer;
};
