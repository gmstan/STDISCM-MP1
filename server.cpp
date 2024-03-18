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
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting...";
    Thread *thread = new Thread(socketDescriptor, this);

    QObject::connect(thread, &Thread::finished, thread, &Thread::deleteLater);

    thread->start();
}
