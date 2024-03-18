#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent) {}

void Server::startServer()
{
    if (!this->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Could not start server";
    }
    else {
        qDebug() << "Server started on PORT 1234";
    }

    connect(this, &Server::newConnection, this, &Server::handleNewConnection);
}

void Server::handleNewConnection()
{
    QTcpSocket *clientSocket = this->nextPendingConnection();
    qDebug() << clientSocket->socketDescriptor() << " Connecting...";

    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readData);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::disconnectClient);

    clientSockets.append(clientSocket); // Add the client socket to the list
}

void Server::readData()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket)
        return;

    QByteArray data = clientSocket->readAll();
    qDebug() << clientSocket->socketDescriptor() << "Data in: " << data;

    // Echo back to the client
    clientSocket->write(data);

    // Optionally, you can send data to all clients
    // sendToAllClients(data);
}

void Server::disconnectClient()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket)
        return;

    qDebug() << clientSocket->socketDescriptor() << " Disconnected";

    clientSocket->deleteLater();
    clientSockets.removeOne(clientSocket); // Remove the client socket from the list
}

void Server::sendToAllClients(const QByteArray &data)
{
    for (QTcpSocket *socket : clientSockets) {
        socket->write(data);
    }
}
