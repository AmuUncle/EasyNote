#include "datamgr.h"
#include <QDebug>


DataMgr* DataMgr::m_pDataMgr = NULL;

DataMgr::DataMgr(QObject *parent) : QObject(parent)
{
    m_eNavItem = DEFAULT;
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
    QString strAppDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    qDebug() << strAppDataLocation;

    m_dbData = QSqlDatabase::addDatabase("QSQLITE");
    m_dbData.setDatabaseName(strAppDataLocation + "/MyDataBase.db");
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
                        CONTENT_SRC TEXT,\
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
    qDebug() << select_sql;
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
    QString select_sql = QString("select ID, TITLE, TIME, FAVORITES from noteinfo where DELETEED == 0 and FID == %1 ORDER BY TIME DESC;").arg(nFId);
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
            tItem.bFavorited = sql_query.value(3).toBool();

            list.append(tItem);
        }
    }

    return list;
}

QList<TNoteItem> DataMgr::GetRecent()
{
    QList<TNoteItem> list;

    QSqlQuery sql_query;
    QString select_sql = QString("select ID, TITLE, TIME, FAVORITES from noteinfo where DELETEED == 0  ORDER BY TIME DESC limit 10;");
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
            tItem.bFavorited = sql_query.value(3).toBool();
            list.append(tItem);
        }
    }

    return list;
}

QList<TNoteItem> DataMgr::GetFavorites()
{
    QList<TNoteItem> list;

    QSqlQuery sql_query;
    QString select_sql = QString("select ID, TITLE, TIME, FAVORITES from noteinfo where FAVORITES > 0 and DELETEED == 0 ORDER BY TIME DESC;");
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
            tItem.bFavorited = sql_query.value(3).toBool();
            list.append(tItem);
        }
    }

    return list;
}

QList<TNoteItem> DataMgr::GetDeleted()
{
    QList<TNoteItem> list;

    QSqlQuery sql_query;
    QString select_sql = QString("select ID, TITLE, TIME, FAVORITES from noteinfo where DELETEED > 0 ORDER BY TIME DESC;");
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
            tItem.bFavorited = sql_query.value(3).toBool();
            list.append(tItem);
        }
    }

    return list;
}

QList<TNoteItem> DataMgr::Search(QString strKey)
{
    QList<TNoteItem> list;

    QSqlQuery sql_query;
    QString update_sql = QString("SELECT ID, TITLE, TIME, FAVORITES FROM noteinfo WHERE DELETEED == 0 and TITLE  LIKE '%%1%' or CONTENT_SRC LIKE '%%1%' ORDER BY TIME DESC;").arg(strKey);
    sql_query.prepare(update_sql);

    qDebug() << update_sql;

    if(!sql_query.exec())
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
            tItem.bFavorited = sql_query.value(3).toBool();
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

int DataMgr::GetGroupFId(int nId)
{
    QSqlQuery sql_query;
    QString select_sql = QString("select FID from nav where ID == %1;").arg(nId);
    qDebug() << select_sql;
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            return sql_query.value(0).toInt();
        }
    }

    return 0;
}

bool DataMgr::SaveNote(TNoteItem tItem)
{
    QSqlQuery sql_query;
    QString update_sql = "update noteinfo set TITLE = :TITLE, CONTENT = :CONTENT, CONTENT_SRC = :CONTENT_SRC where ID = :ID";

    sql_query.prepare(update_sql);
    sql_query.bindValue(":TITLE", tItem.strTitle);
    sql_query.bindValue(":CONTENT", tItem.strContent);
    sql_query.bindValue(":CONTENT_SRC", tItem.strContentSrc);
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

bool DataMgr::NewNote(TNoteItem tItem)
{
    QSqlQuery sql_query;
    QString update_sql = "INSERT INTO noteinfo (FID, TITLE, CONTENT) VALUES (:FID, :TITLE, :CONTENT);";

    sql_query.prepare(update_sql);
    sql_query.bindValue(":TITLE", tItem.strTitle);
    sql_query.bindValue(":CONTENT", tItem.strContent);
    sql_query.bindValue(":FID", tItem.nFId);
    if (!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"updated!";
    }

    return true;
}

bool DataMgr::RemoveNote(int nId, bool bDeleted)
{
    QSqlQuery sql_query;
    QString update_sql = QString("UPDATE noteinfo SET DELETEED = %2  WHERE ID = %1").arg(nId).arg(bDeleted);
    sql_query.prepare(update_sql);

    qDebug() << update_sql;

    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"DELETE!";
    }

    emit SignalNoteListChange();

    return true;
}

bool DataMgr::DelNote(int nId)
{
    QSqlQuery sql_query;
    QString update_sql = QString("DELETE from noteinfo WHERE ID = %1;").arg(nId);

    sql_query.prepare(update_sql);

    qDebug() << update_sql;
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"updated!";
    }

    emit SignalNoteListChange();

    return true;
}

bool DataMgr::FavoriteNote(int nId, bool bFavorite)
{
    QSqlQuery sql_query;
    QString update_sql = QString("UPDATE noteinfo SET FAVORITES = %1 WHERE ID = %2;").arg(bFavorite).arg(nId);

    sql_query.prepare(update_sql);

    qDebug() << update_sql;
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
