#ifndef TCPSERVERSIMPLE_H
#define TCPSERVERSIMPLE_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "packet.h"

class TcpServerSimple : public QObject
{
    Q_OBJECT
public:
    explicit TcpServerSimple(QObject *parent = nullptr);
    bool startServer(int port, QHostAddress addr = QHostAddress::Any);
    void stopServer();
    bool sendData(const QByteArray &data);
    QString errorString();
    Packet *packet();
    bool usePacket() const;
    void setUsePacket(bool usePacket);
    bool isClientConnected();
    QString getConnectedClientIp();
    bool isServerRunning();

signals:
    void dataRx(const QByteArray &data);
    void connectionChanged(bool connected, QString address);

public slots:
    void newTcpConnection();
    void tcpInputDisconnected();
    void tcpInputDataAvailable();
    void tcpInputError(QAbstractSocket::SocketError socketError);
    void dataToSend(QByteArray &data);

private:
    QTcpServer *mTcpServer;
    QTcpSocket *mTcpSocket;
    Packet *mPacket;
    bool mUsePacket;
};

#endif // TCPSERVERSIMPLE_H
