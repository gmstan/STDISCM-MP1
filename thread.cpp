#include "thread.h"

Thread::Thread(int id, QObject *parent)
    : QThread{parent}
{
    this->socketDescriptor = id;
}

void Thread::run()
{
    // thread starts here
    qDebug() << socketDescriptor << " Starting thread";
    socket = new QTcpSocket();

    if (!socket->setSocketDescriptor(this->socketDescriptor)) {
        qDebug() << "socket error";
        emit error(socket->error());
        return;
    }

    QObject::connect(socket, &QTcpSocket::readyRead, this, &Thread::readyRead);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &Thread::disconnected);

    qDebug() << socketDescriptor << " Client connected";

    exec();
}

void Thread::readyRead()
{
    QByteArray Data = socket->readAll();

    qDebug() << socketDescriptor << "Data in: " << Data;
    socket->write(Data);

}

void Thread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}
