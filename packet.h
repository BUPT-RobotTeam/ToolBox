#ifndef PACKET_H
#define PACKET_H

#include <QObject>
#include <QTimer>

class Packet : public QObject
{
    Q_OBJECT
public:
    explicit Packet(QObject *parent = 0);
    ~Packet();
    void sendPacket(const QByteArray &data);
    void sendPacketNoProtocol(const QByteArray &data);
    static unsigned short crc16(const unsigned char *buf, unsigned int len);

signals:
    void dataToSend(QByteArray &data);
    void packetReceived(QByteArray &packet);
    void packetReceivedNoProtocol(QByteArray &packet);

public slots:
    void processData(QByteArray data);

private slots:
    void timerSlot();

private:
    QTimer *mTimer;
    int mRxTimer;
    int mByteTimeout;
    unsigned int mRxReadPtr;
    unsigned int mRxWritePtr;
    int mBytesLeft;
    unsigned int mMaxPacketLen;
    unsigned int mBufferLen;
    unsigned char *mRxBuffer;

    int try_decode_packet(unsigned char *buffer, unsigned int in_len,
                          int *bytes_left, QVector<QByteArray> &decodedPackets);
};

#endif // PACKET_H
