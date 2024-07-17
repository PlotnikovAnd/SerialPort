#include "hardwareserial_9bit.h"


HardwareSerial_9Bit::HardwareSerial_9Bit(QSerialPort* port, QObject *parent)
    : SerialBase_9bit(port, parent)
{
    //
}

HardwareSerial_9Bit::~HardwareSerial_9Bit()
{
    //
}

bool HardwareSerial_9Bit::setMarkingEnabled(const bool value)
{
    if(!SerialBase_9bit::setMarkingEnabled(value))
        return false;

#ifdef Q_OS_WIN32
    if(m_MarkingEnabled) {
        if(!m_Port->setParity(m_MarkParity))
            return false;
    } else {
        if(!m_Port->setParity(m_DefaultParity))
            return false;
    }
#endif

    return true;
}

bool HardwareSerial_9Bit::writeData(const char *data, const size_t size)
{
    std::size_t totalWrittenBytes = 0;
    std::size_t writtenBytes = 0;

    while(true) {
        writtenBytes = m_pPort->write(data + totalWrittenBytes, size - totalWrittenBytes);

        if(std::size_t{-1} == writtenBytes)
            return false;

        totalWrittenBytes += writtenBytes;

        Q_ASSERT(totalWrittenBytes <= size);

        if(size == totalWrittenBytes)
            break;
    }

    Q_ASSERT(size == totalWrittenBytes);

    qDebug() << "TX:" << QString(QLatin1String(QByteArray(data, size).toHex()));

    return true;
}
