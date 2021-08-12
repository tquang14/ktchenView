#include "sqlconnection.h"
#include <QDebug>

sqlConnection::sqlConnection(const QString DB_NAME, QObject *parent)
    : QObject(parent),
      DB_NAME(DB_NAME),
      DB_TYPE("QSQLITE"),
      CONNECTION_NAME("qt_sql_default_connection")
{
    if (init())
        qDebug() << "sqlite connected";
    else
        qDebug() << "sqlite not connected";
}

bool sqlConnection::init()
{
    m_db = new QSqlDatabase();
    *m_db = QSqlDatabase::addDatabase(DB_TYPE);
    m_db->setDatabaseName(DB_NAME);
    m_dbStatus = m_db->open();
    qDebug() << "db status: " << m_dbStatus;
    m_query = new QSqlQuery();
    return m_dbStatus;
}

QVector<QSqlRecord> sqlConnection::execQuery(const QString queryStr)
{
    QVector<QSqlRecord> records;
    if (m_dbStatus)
    {
        m_query->exec(queryStr);
        while (m_query->next()) {
            records.append(m_query->record());
        }
    }
    return records;
}

sqlConnection::~sqlConnection()
{
    m_db->close();
    delete m_db;
    delete m_query;
    QSqlDatabase::removeDatabase(CONNECTION_NAME);
}
