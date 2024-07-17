#ifndef HARDWARESERIAL_9BIT_H
#define HARDWARESERIAL_9BIT_H

#include <QObject>
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

#endif // HARDWARESERIAL_9BIT_H
