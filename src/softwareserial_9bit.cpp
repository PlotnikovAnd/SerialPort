#include <QElapsedTimer>
#include <QThread>
#include "softwareserial_9bit.h"



SoftwareSerial_9bit::SoftwareSerial_9bit(QSerialPort *port, QObject *parent):
    SerialBase_9bit(port, parent)
{
    //
}

SoftwareSerial_9bit::~SoftwareSerial_9bit()
{
    //
}

bool SoftwareSerial_9bit::writeData(const char *data, const size_t size)
{
    std::size_t totalWrittenBytes = 0;
    std::size_t writtenBytes = 0;
    char        ch = 0;

    while(true) {
        if(!updateParityMode(ch))
            break;

        ch = data[totalWrittenBytes];

        writtenBytes = m_pPort->write(&ch, 1);

        if(-1 == writtenBytes)
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

bool SoftwareSerial_9bit::tests()
{
    Q_ASSERT(SoftwareSerial_9bit::setBitsCount(0x00) == 0);
    Q_ASSERT(SoftwareSerial_9bit::setBitsCount(0x01) == 1);
    Q_ASSERT(SoftwareSerial_9bit::setBitsCount(0x03) == 2);
    Q_ASSERT(SoftwareSerial_9bit::setBitsCount(0x07) == 3);
    Q_ASSERT(SoftwareSerial_9bit::setBitsCount(0x0F) == 4);
    Q_ASSERT(SoftwareSerial_9bit::setBitsCount(0x1F) == 5);
    Q_ASSERT(SoftwareSerial_9bit::setBitsCount(0x3F) == 6);
    Q_ASSERT(SoftwareSerial_9bit::setBitsCount(0x7F) == 7);
    Q_ASSERT(SoftwareSerial_9bit::setBitsCount(0xFF) == 8);

    return true;
}

short int SoftwareSerial_9bit::setBitsCount(const unsigned char value)
{
    unsigned char   t = value;
    short int       ret = 0;

    while(t > 0) {
        if (t & 0x01)
            ret++;

        t >>= 1;
    }

    return ret;
}

QSerialPort::Parity SoftwareSerial_9bit::needfulParity(const char ch) const
{
    if(!markedTransmissionMode())
        return defaultTransmissionMode();

    QSerialPort::Parity parity = QSerialPort::NoParity;
    
    if((SoftwareSerial_9bit::setBitsCount(ch) % 2) != 0) {
        parity = QSerialPort::EvenParity;
    } else {
        parity = QSerialPort::OddParity;
    }

    return parity;
}

bool SoftwareSerial_9bit::updateParityMode(const char ch)
{
    QSerialPort::Parity parity = this->needfulParity(ch);

    if(m_pPort->parity() == parity)
        return true;

    qDebug() << "updating parity";
    return m_pPort->setParity(parity);
}

