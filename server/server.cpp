#include "server.h"

Server::Server(QObject *parent, MainWindow *mainWindow) : QTcpServer(parent) , mainWindow(mainWindow)
{
    if (mainWindow == nullptr) {
        // Handle the case where mainWindow pointer is null
        // For example, you might throw an exception or log an error
        throw std::invalid_argument("mainWindow pointer cannot be null");
    }
}

void Server::startServer()
{
    if (!(mainWindow == nullptr)) {
        qDebug() << "MW EXISTS";
    }

    if (!this->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Could not start server";
    }
    else {
        qDebug() << "Server started on PORT 1234";
    }

    if (!mainWindow) {
        qDebug() << "Error: Null pointer received for mainWindow in Server::startServer()";
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

    int index = clientSockets.indexOf(clientSocket);
    if (index == -1) {
        qDebug() << "Error: Socket not found in the clientSockets array";
        return;
    }
    index+=1;
    // qDebug() << "INDEX" << index;

    QByteArray data = clientSocket->readAll();
    qDebug() << clientSocket->socketDescriptor() << "Data in: " << data;


    QString signal = data.left(9);
    if (signal == "newSprite"){
        qDebug() << "NEW SPRITE SPAWNED";

        data.remove(0, 10);

        QString X; // Store characters until the comma
        QString Y; // Store characters after the comma
        bool commaFound = false; // Flag to track if comma is found

        qDebug() << "data:" << data;
        // Iterate through each character in the input string
        for (const QChar& ch : data) {
            // Check if the character is a comma
            if (ch == ',') {
                // Set the flag to true if comma is found
                commaFound = true;
                continue; // Skip appending comma to the first part
            }

            // Append the character to the appropriate part
            if (!commaFound) {
                X.append(ch);
            } else {
                Y.append(ch);
            }
        }
        qDebug() << "X:" << X;
        qDebug() << "Y:" << Y;

        int intX = X.toInt();
        int intY = Y.toInt();

        qDebug() << "newX:" << intX;
        qDebug() << "newY:" << intY;

        QString indexString = QString::number(index);
        QByteArray msg = indexString.toUtf8();
        clientSocket->write(msg);

        mainWindow->spawnSprite(index, intX, intY);
    }

    else if (signal == "movSprite"){
        qDebug() << "MOVED SPRITE";
        data.remove(0, 9);

        QString spriteID = data.left(1);
        qDebug() << "SPRITE_ID:" << spriteID;
        data.remove(0, 2);

        QString X;
        QString Y;
        bool commaFound = false;
        qDebug() << "data:" << data;

        for (const QChar& ch : data) {
            if (ch == ',') {
                commaFound = true;
                continue;
            }
            if (!commaFound) {
                X.append(ch);
            } else {
                Y.append(ch);
            }
        }
        qDebug() << "X:" << X;
        qDebug() << "Y:" << Y;

        int intX = X.toInt();
        int intY = Y.toInt();

        qDebug() << "newX:" << intX;
        qDebug() << "newY:" << intY;

        int intID = spriteID.toInt();
        // mainWindow->moveSprite(intID, intX, intY);
        mainWindow->moveSprite(intX, intY);
    }

    else if (signal == "delSprite"){
        qDebug() << "REMOVED SPAWNED";

        mainWindow->delSprite();
    }

    // Echo back to the client
    // clientSocket->write(data);

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
    // clientSockets.removeOne(clientSocket); // Remove the client socket from the list
}

void Server::sendToAllClients(const QByteArray &data)
{
    for (QTcpSocket *socket : clientSockets) {
        socket->write(data);
    }
}

