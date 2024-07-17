#include "serialbase_9bit.h"


void SerialBase_9bit::setBool(bool *ptr, const bool value)
{
    if(!ptr)
        return;

    *ptr = value;
}

SerialBase_9bit::SerialBase_9bit(QSerialPort *port, QObject *parent) :
    QObject(parent),
    m_pPort(port)
{
    //

}

SerialBase_9bit::~SerialBase_9bit()
{
    // вызывается самый нижний деструктор в иерархии наследования
}

void SerialBase_9bit::setPort(QSerialPort *port)
{
    m_pPort = port;
}

QSerialPort *SerialBase_9bit::port() const
{
    return m_pPort;
}

void SerialBase_9bit::setDefaultTransmissionMode(const QSerialPort::Parity value)
{
    m_defaultParity = value;
}

QSerialPort::Parity SerialBase_9bit::defaultTransmissionMode() const
{
    return m_defaultParity;
}


bool SerialBase_9bit::setMarkingEnabled(const bool value)
{
    if(value == m_markingEnabled)
        return true;

    m_markingEnabled = value;
    return true;
}

QSerialPort::Parity SerialBase_9bit::markedTransmissionMode() const
{
    return m_markParity;
}

void SerialBase_9bit::setMarkedTransmissionMode(const QSerialPort::Parity value)
{
    m_markParity = value;
}

QByteArray SerialBase_9bit::readData(const size_t size, const int maxMSecs, bool *ok)
{
    QElapsedTimer   timer;
    QByteArray      iret;

    setBool(ok, false);

    timer.start();
    if(!m_pPort->bytesAvailable()) {
        if(!m_pPort->waitForReadyRead(maxMSecs))
            return QByteArray();
    }

    if(timer.hasExpired(maxMSecs))
        return QByteArray();

    iret.resize(size);
    iret.fill(0x00);

    int     timeLeft = 0;
    size_t  readBytes = 0;

    while(true) {
        timeLeft = (maxMSecs - timer.elapsed());

        if(!m_pPort->bytesAvailable()) {
            if(!m_pPort->waitForReadyRead(timeLeft))
                return QByteArray(iret.data(), readBytes);
        }

        size_t bytesAvailable = m_pPort->bytesAvailable();
        size_t bytesNeed = (readBytes + bytesAvailable <= size ? bytesAvailable : size - readBytes);

        int delta = m_pPort->read(iret.data() + readBytes, bytesNeed);

        if(-1 == delta)
            return QByteArray(iret.data(), readBytes);

        readBytes += delta;

        Q_ASSERT(readBytes <= size);

        if(readBytes == size)
            break;

        if( (timer.hasExpired(maxMSecs)) && (readBytes < size) )
            return QByteArray(iret.data(), readBytes);
    }

    setBool(ok, (static_cast<size_t>(iret.size()) == size));

    return QByteArray(iret.data(), readBytes);
}
