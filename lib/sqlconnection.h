#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

/*
 * class to handle connection to sqlite
 */

class sqlConnection : public QObject
{
    Q_OBJECT
public:
    explicit sqlConnection(const QString DB_NAME, QObject *parent = nullptr);

    ~sqlConnection();

    //!
    //! \brief init
    //! \return true if connect success
    //!
    bool init();

    //!
    //! \brief execQuery
    //! \param queryStr
    //! \return all record get from DB
    //!
    QVector<QSqlRecord> execQuery(const QString queryStr);

private:

    //!
    //! \brief m_db
    //!
    QSqlDatabase *m_db;

    //!
    //! \brief m_dbStatus
    //!
    bool m_dbStatus;

    //!
    //! \brief m_query
    //!
    QSqlQuery *m_query;

    //!
    //! \brief DB_TYPE
    //!
    const QString DB_NAME;

    //!
    //! \brief DB_TYPE
    //!
    const QString DB_TYPE;

    //!
    //! \brief DB_TYPE
    //!
    const QString CONNECTION_NAME;

signals:

};

#endif // SQLCONNECTION_H
