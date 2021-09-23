#include "datamgr.h"
#include <QDebug>


DataMgr* DataMgr::m_pDataMgr = NULL;

DataMgr::DataMgr(QObject *parent) : QObject(parent)
{

}

DataMgr *DataMgr::GetInstance()
{
    if (NULL == m_pDataMgr)
        m_pDataMgr = new DataMgr();

    return m_pDataMgr;
}

void DataMgr::ExitInstance()
{
    if (m_pDataMgr != NULL)
    {
        delete m_pDataMgr;
        m_pDataMgr = NULL;
    }
}

void DataMgr::Open()
{
    m_dbData = QSqlDatabase::addDatabase("QSQLITE");
    m_dbData.setDatabaseName("MyDataBase.db");
    m_dbData.setUserName("XingYeZhiXia");
    m_dbData.setPassword("123456");

    if (!m_dbData.open())
    {
        qDebug() << "Error: Failed to connect database." << m_dbData.lastError();
    }
    else
    {
        InitDB();
    }
}

void DataMgr::InitDB()
{
    QSqlQuery sql_query;
    QString create_sql = "CREATE TABLE nav (\
            ID INTEGER PRIMARY KEY AUTOINCREMENT,\
            FID INTEGER  NOT NULL default 0,\
            TYPE INTEGER  NOT NULL, NAME TEXT NOT NULL);";

    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }

    create_sql = "CREATE TABLE noteinfo (\
                        ID INTEGER PRIMARY KEY AUTOINCREMENT,\
                        FID INTEGER  NOT NULL default 0,\
                        TITLE TEXT NOT NULL,\
                        CONTENT TEXT,\
                        DELETEED INTEGER default 0,\
                        FAVORITES INTEGER default 0,\
                        TIME  DATETIME DEFAULT (  datetime( 'now', 'localtime' ))\
                    );";

    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}

QList<TUserCustomItem> DataMgr::GetUserCustomItem()
{
    QList<TUserCustomItem> list;

    QSqlQuery sql_query;
    QString select_sql = "select ID, NAME from nav where FID == 0;";
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {

        while(sql_query.next())
        {
            TUserCustomItem tItem = {0};
            tItem.nId = sql_query.value(0).toInt();
            tItem.strName = sql_query.value(1).toString();

            list.append(tItem);
        }
    }

    return list;
}

QList<TUserCustomItem> DataMgr::GetUserCustomChildItem(int nFId)
{
    QList<TUserCustomItem> list;

    QSqlQuery sql_query;
    QString select_sql = QString("select ID, NAME from nav where FID == %1;").arg(nFId);
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {

        while(sql_query.next())
        {
            TUserCustomItem tItem = {0};
            tItem.nId = sql_query.value(0).toInt();
            tItem.strName = sql_query.value(1).toString();

            list.append(tItem);
        }
    }

    return list;
}

QList<TNoteItem> DataMgr::GetUserCustomChildNote(int nFId)
{
    QList<TNoteItem> list;

    QSqlQuery sql_query;
    QString select_sql = QString("select ID, TITLE, TIME from noteinfo where FID == %1;").arg(nFId);
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {

        while(sql_query.next())
        {
            TNoteItem tItem = {0};
            tItem.nId = sql_query.value(0).toInt();
            tItem.strTitle = sql_query.value(1).toString();
            tItem.strTime = sql_query.value(2).toString();
            list.append(tItem);
        }
    }

    return list;
}

QList<TNoteItem> DataMgr::GetRecent()
{
    QList<TNoteItem> list;

    QSqlQuery sql_query;
    QString select_sql = QString("select ID, TITLE, TIME from noteinfo where DELETEED == 0  ORDER BY TIME DESC limit 10;");
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {

        while(sql_query.next())
        {
            TNoteItem tItem = {0};
            tItem.nId = sql_query.value(0).toInt();
            tItem.strTitle = sql_query.value(1).toString();
            tItem.strTime = sql_query.value(2).toString();
            list.append(tItem);
        }
    }

    return list;
}

QList<TNoteItem> DataMgr::GetFavorites()
{
    QList<TNoteItem> list;

    QSqlQuery sql_query;
    QString select_sql = QString("select ID, TITLE, TIME from noteinfo where FAVORITES > 0 and DELETEED == 0;");
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {

        while(sql_query.next())
        {
            TNoteItem tItem = {0};
            tItem.nId = sql_query.value(0).toInt();
            tItem.strTitle = sql_query.value(1).toString();
            tItem.strTime = sql_query.value(2).toString();
            list.append(tItem);
        }
    }

    return list;
}

QList<TNoteItem> DataMgr::GetDeleted()
{
    QList<TNoteItem> list;

    QSqlQuery sql_query;
    QString select_sql = QString("select ID, TITLE, TIME from noteinfo where DELETEED > 0;");
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {

        while(sql_query.next())
        {
            TNoteItem tItem = {0};
            tItem.nId = sql_query.value(0).toInt();
            tItem.strTitle = sql_query.value(1).toString();
            tItem.strTime = sql_query.value(2).toString();
            list.append(tItem);
        }
    }

    return list;
}

TNoteItem DataMgr::GetNote(int nId)
{
    TNoteItem tItem = {0};

    QSqlQuery sql_query;
    QString select_sql = QString("select ID, TITLE, CONTENT, TIME from noteinfo where ID == %1;").arg(nId);
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            tItem.nId = sql_query.value(0).toInt();
            tItem.strTitle = sql_query.value(1).toString();
            tItem.strContent = sql_query.value(2).toString();
            tItem.strTime = sql_query.value(3).toString();

            break;
        }
    }

    return tItem;
}

bool DataMgr::SaveNote(TNoteItem tItem)
{
    QSqlQuery sql_query;
    QString update_sql = "update noteinfo set TITLE = :TITLE, CONTENT = :CONTENT where ID = :ID";

    sql_query.prepare(update_sql);
    sql_query.bindValue(":TITLE", tItem.strTitle);
    sql_query.bindValue(":CONTENT", tItem.strContent);
    sql_query.bindValue(":ID", tItem.nId);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"updated!";
    }

    return true;
}
