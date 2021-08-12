#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <QObject>
#include <QTcpSocket>

#include "sqlconnection.h"

class SocketClient : public QObject
{
    Q_OBJECT

    // property hold the data recieved from server
    Q_PROPERTY(QVariantList data READ getData NOTIFY dataChanged)

public slots:
    //!
    //! \brief removeDishFromData
    //! \param idx
    //! \return
    //!
    bool removeDishFromData(int idx);

public:
    //!
    //! \brief SocketClient - constructor
    //! \param parent
    //! \param array - to store recieved message
    //!
    explicit SocketClient(QObject *parent = nullptr);

    //! \brief destructor
    ~SocketClient();

    //!
    //! \brief connectToServer
    //! \param addr
    //! \param port
    //! \param timeout
    //! \return
    //!
    bool connectToServer(QString addr, int port, uint64_t timeout = 3000);
signals:
    //!
    //! \brief dataChanged
    //!
    void dataChanged();
public slots:
    //!
    //! \brief onRecieveMessageFromServer
    //!
    void recieveMessageFromServer();

private:


    //!
    //! \brief getData - convert QVector<QString> to QVariantList
    //! \return
    //!
    QVariantList getData();

    //!
    //! \brief m_socket
    //!
    QTcpSocket *m_socket;

    //!
    //! \brief messages
    //!
    QVector<QString> m_recievedMessages;

    //!
    //! \brief sqlite
    //!
    sqlConnection sqlite;
};

#endif // SOCKETCLIENT_H
