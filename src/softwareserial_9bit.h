#ifndef SOFTWARESERIAL_9BIT_H
#define SOFTWARESERIAL_9BIT_H

#include <QtSerialPort/QtSerialPort>
#include <QtCore/QtCore>
#include "serialbase_9bit.h"



class HardwareSerial_9Bit: public SerialBase_9bit
{
    Q_OBJECT

public:
    HardwareSerial_9Bit(QSerialPort* port = nullptr, QObject *parent = nullptr);
    ~HardwareSerial_9Bit();

    virtual bool setMarkingEnabled(const bool value) override;
    virtual bool writeData(const char* data, const size_t size) override;
};

class SoftwareSerial_9bit : public SerialBase_9bit
{
    Q_OBJECT

public:
    SoftwareSerial_9bit(QSerialPort* port = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    ~SoftwareSerial_9bit();

    virtual bool writeData(const char* data, const size_t size) override;
    static bool tests();


private:
    static short int setBitsCount(const unsigned char value);

    QSerialPort::Parity needfulParity(const char ch) const;

    bool updateParityMode(const char ch);

};


#endif //SOFTWARESERIAL_9BIT_H
