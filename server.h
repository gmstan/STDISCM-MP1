#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    void startServer();

signals:

public slots:
    void handleNewConnection();
    void readData();
    void disconnectClient();
    void sendToAllClients(const QByteArray &data);

private:
    QList<QTcpSocket *> clientSockets; // List to store connected client sockets
};

#endif // SERVER_H
