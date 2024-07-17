#ifndef SERIALBASE_9BIT_H
#define SERIALBASE_9BIT_H

#include <QObject>
#include <QtSerialPort/QtSerialPort>

class SerialBase_9bit : public QObject
{
    Q_OBJECT
public:
    SerialBase_9bit(QSerialPort* port = nullptr, QObject *parent = nullptr);
    virtual ~SerialBase_9bit();

    //! attaches port to processor
    virtual void setPort(QSerialPort* port);

    //! returns attached port
    QSerialPort* port() const;

    //! sets default (non-marked) transmission mode
    virtual void setDefaultTransmissionMode(const QSerialPort::Parity value);

    //! returns marked transmission mode
    QSerialPort::Parity defaultTransmissionMode() const;

    //! enables/disables marking
    virtual bool setMarkingEnabled(const bool value);

    //! returns marked transmission parity
    QSerialPort::Parity markedTransmissionMode() const;

    //! sets marked transmission parity
    virtual void setMarkedTransmissionMode(const QSerialPort::Parity value);

    //! writes data to attached port
    virtual bool writeData(const char* data, const size_t size) = 0;

    /*!
     * \brief readData reads data from port
     * \param size needful data size
     * \param maxMSecs max wait time (in msecs)
     * \param ok pointer where will be status of operation (can be NULL), when operations succeded here will be true, otherwise false
     * \return read data
     */
    virtual QByteArray readData(const size_t size, const int maxMSecs, bool *ok = Q_NULLPTR);

protected:
    mutable QSerialPort         *m_pPort;
    QSerialPort::Parity         m_markParity = QSerialPort::MarkParity;
    QSerialPort::Parity         m_defaultParity = QSerialPort::SpaceParity;
    bool                        m_markingEnabled = false;

    void setBool(bool *ptr, const bool value);
};

#endif // SERIALBASE_9BIT_H
