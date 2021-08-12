#include "socketclient.h"
#include "QDebug"

#define QT_FATAL_WARNINGS 1

SocketClient::SocketClient(QObject *parent)
    : QObject(parent),
      sqlite("../db/datn.db", parent)
{
    m_socket = new QTcpSocket(this);
}

bool SocketClient::connectToServer(QString addr, int port, uint64_t timeout)
{
    m_socket->connectToHost(addr, port);
    if (m_socket->waitForConnected(timeout))
    {
        m_socket->write("hello server");
        m_socket->waitForBytesWritten(1000);
        bool success = connect(m_socket, &QTcpSocket::readyRead, this,
                               &SocketClient::recieveMessageFromServer);
        if (!success)
        {
            qDebug() << "cannot connect to slot";
            return false;
        }
        qDebug() << "connect success";
        return true;
    }
    qDebug() << "not connected";
    return false;
}

void SocketClient::recieveMessageFromServer()
{
    QString message = m_socket->readAll();
    m_recievedMessages.prepend(message);
    qDebug() << m_recievedMessages;
    emit dataChanged();
}

QVariantList SocketClient::getData()
{
    QVariantList list;
    for (const auto &e : qAsConst(m_recievedMessages))
    {
        list << QVariant::fromValue(e);
    }
    return list;
}

bool SocketClient::removeDishFromData(int idx)
{
    if (m_recievedMessages.size() <= 0 || idx >= m_recievedMessages.size())
        return false;
    // remove element at idx from vector data
    m_recievedMessages.erase(m_recievedMessages.begin() + idx);
    emit dataChanged();
    return true;
}



SocketClient::~SocketClient()
{
    disconnect(m_socket, &QTcpSocket::readyRead, this, &SocketClient::recieveMessageFromServer);
    delete m_socket;
    m_socket = nullptr;
}
