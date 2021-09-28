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

    m_dbData = QSqlDatabase::addDatabase("QSQLITE");
    m_dbData.setDatabaseName(strAppDataLocation + "/data.dat");
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
    QSqlQuery sqlQuery;
    QString strSql = "CREATE TABLE nav (\
            ID INTEGER PRIMARY KEY AUTOINCREMENT,\
            FID INTEGER  NOT NULL default 0,\
            TYPE INTEGER  NOT NULL, NAME TEXT NOT NULL);";

    sqlQuery.prepare(strSql);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create table." << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }

    strSql = "CREATE TABLE noteinfo (\
                        ID INTEGER PRIMARY KEY AUTOINCREMENT,\
                        FID INTEGER  NOT NULL default 0,\
                        TITLE TEXT NOT NULL,\
                        CONTENT TEXT,\
                        CONTENT_SRC TEXT,\
                        DELETEED INTEGER default 0,\
                        FAVORITES INTEGER default 0,\
                        TIME  DATETIME DEFAULT (  datetime( 'now', 'localtime' ))\
                    );";

    sqlQuery.prepare(strSql);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create table." << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }

    // 触发器
    strSql = "CREATE TRIGGER noteinfo_md AFTER UPDATE OF TITLE, CONTENT \
            ON noteinfo \
            BEGIN \
               UPDATE noteinfo SET TIME = datetime( 'now', 'localtime' ) WHERE ID = new.ID; \
            END;";

    sqlQuery.prepare(strSql);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create table." << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "触发器 created!";
    }
}

QList<TUserCustomItem> DataMgr::GetUserCustomItem()
{
    QList<TUserCustomItem> list;

    QSqlQuery sqlQuery;
    QString select_sql = "select ID, NAME from nav where FID == 0;";
    if(!sqlQuery.exec(select_sql))
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {

        while(sqlQuery.next())
        {
            TUserCustomItem tItem = {0};
            tItem.nId = sqlQuery.value(0).toInt();
            tItem.strName = sqlQuery.value(1).toString();

            list.append(tItem);
        }
    }

    return list;
}

QList<TUserCustomItem> DataMgr::GetUserCustomChildItem(int nFId)
{
    QList<TUserCustomItem> list;

    QSqlQuery sqlQuery;
    QString select_sql = QString("select ID, NAME from nav where FID == %1;").arg(nFId);
    qDebug() << select_sql;
    if(!sqlQuery.exec(select_sql))
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {

        while(sqlQuery.next())
        {
            TUserCustomItem tItem = {0};
            tItem.nId = sqlQuery.value(0).toInt();
            tItem.strName = sqlQuery.value(1).toString();

            list.append(tItem);
        }
    }

    return list;
}

QList<TNoteItem> DataMgr::GetUserCustomChildNote(int nFId)
{
    QList<TNoteItem> list;

    QSqlQuery sqlQuery;
    QString select_sql = QString("select ID, TITLE, TIME, FAVORITES from noteinfo where DELETEED == 0 and FID == %1 ORDER BY TIME DESC;").arg(nFId);
    if(!sqlQuery.exec(select_sql))
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {

        while(sqlQuery.next())
        {
            TNoteItem tItem = {0};
            tItem.nId = sqlQuery.value(0).toInt();
            tItem.strTitle = sqlQuery.value(1).toString();
            tItem.strTime = sqlQuery.value(2).toString();
            tItem.bFavorited = sqlQuery.value(3).toBool();

            list.append(tItem);
        }
    }

    return list;
}

QList<TNoteItem> DataMgr::GetRecent()
{
    QList<TNoteItem> list;

    QSqlQuery sqlQuery;
    QString select_sql = QString("select ID, TITLE, TIME, FAVORITES from noteinfo where DELETEED == 0  ORDER BY TIME DESC limit 10;");
    if(!sqlQuery.exec(select_sql))
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {

        while(sqlQuery.next())
        {
            TNoteItem tItem = {0};
            tItem.nId = sqlQuery.value(0).toInt();
            tItem.strTitle = sqlQuery.value(1).toString();
            tItem.strTime = sqlQuery.value(2).toString();
            tItem.bFavorited = sqlQuery.value(3).toBool();
            list.append(tItem);
        }
    }

    return list;
}

QList<TNoteItem> DataMgr::GetFavorites()
{
    QList<TNoteItem> list;

    QSqlQuery sqlQuery;
    QString select_sql = QString("select ID, TITLE, TIME, FAVORITES from noteinfo where FAVORITES > 0 and DELETEED == 0 ORDER BY TIME DESC;");
    if(!sqlQuery.exec(select_sql))
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {

        while(sqlQuery.next())
        {
            TNoteItem tItem = {0};
            tItem.nId = sqlQuery.value(0).toInt();
            tItem.strTitle = sqlQuery.value(1).toString();
            tItem.strTime = sqlQuery.value(2).toString();
            tItem.bFavorited = sqlQuery.value(3).toBool();
            list.append(tItem);
        }
    }

    return list;
}

QList<TNoteItem> DataMgr::GetDeleted()
{
    QList<TNoteItem> list;

    QSqlQuery sqlQuery;
    QString select_sql = QString("select ID, TITLE, TIME, FAVORITES from noteinfo where DELETEED > 0 ORDER BY TIME DESC;");
    if(!sqlQuery.exec(select_sql))
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {

        while(sqlQuery.next())
        {
            TNoteItem tItem = {0};
            tItem.nId = sqlQuery.value(0).toInt();
            tItem.strTitle = sqlQuery.value(1).toString();
            tItem.strTime = sqlQuery.value(2).toString();
            tItem.bFavorited = sqlQuery.value(3).toBool();
            list.append(tItem);
        }
    }

    return list;
}

QList<TNoteItem> DataMgr::Search(QString strKey)
{
    QList<TNoteItem> list;

    QSqlQuery sqlQuery;
    QString update_sql = QString("SELECT ID, TITLE, TIME, FAVORITES FROM noteinfo WHERE DELETEED == 0 and TITLE  LIKE '%%1%' or CONTENT_SRC LIKE '%%1%' ORDER BY TIME DESC;").arg(strKey);
    sqlQuery.prepare(update_sql);

    qDebug() << update_sql;

    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {

        while(sqlQuery.next())
        {
            TNoteItem tItem = {0};
            tItem.nId = sqlQuery.value(0).toInt();
            tItem.strTitle = sqlQuery.value(1).toString();
            tItem.strTime = sqlQuery.value(2).toString();
            tItem.bFavorited = sqlQuery.value(3).toBool();
            list.append(tItem);
        }
    }

    return list;
}

TNoteItem DataMgr::GetNote(int nId)
{
    TNoteItem tItem = {0};

    QSqlQuery sqlQuery;
    QString select_sql = QString("select ID, TITLE, CONTENT, TIME from noteinfo where ID == %1;").arg(nId);
    if(!sqlQuery.exec(select_sql))
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            tItem.nId = sqlQuery.value(0).toInt();
            tItem.strTitle = sqlQuery.value(1).toString();
            tItem.strContent = sqlQuery.value(2).toString();
            tItem.strTime = sqlQuery.value(3).toString();

            break;
        }
    }

    return tItem;
}

int DataMgr::GetGroupFId(int nId)
{
    QSqlQuery sqlQuery;
    QString select_sql = QString("select FID from nav where ID == %1;").arg(nId);
    qDebug() << select_sql;
    if(!sqlQuery.exec(select_sql))
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            return sqlQuery.value(0).toInt();
        }
    }

    return 0;
}

bool DataMgr::SaveNote(TNoteItem tItem)
{
    QSqlQuery sqlQuery;
    QString update_sql = "update noteinfo set TITLE = :TITLE, CONTENT = :CONTENT, CONTENT_SRC = :CONTENT_SRC where ID = :ID";

    sqlQuery.prepare(update_sql);
    sqlQuery.bindValue(":TITLE", tItem.strTitle);
    sqlQuery.bindValue(":CONTENT", tItem.strContent);
    sqlQuery.bindValue(":CONTENT_SRC", tItem.strContentSrc);
    sqlQuery.bindValue(":ID", tItem.nId);
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"updated!";
    }

    return true;
}

bool DataMgr::NewNote(TNoteItem tItem)
{
    QSqlQuery sqlQuery;
    QString update_sql = "INSERT INTO noteinfo (FID, TITLE, CONTENT) VALUES (:FID, :TITLE, :CONTENT);";

    sqlQuery.prepare(update_sql);
    sqlQuery.bindValue(":TITLE", tItem.strTitle);
    sqlQuery.bindValue(":CONTENT", tItem.strContent);
    sqlQuery.bindValue(":FID", tItem.nFId);
    if (!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"updated!";
    }

    return true;
}

bool DataMgr::RemoveNote(int nId, bool bDeleted)
{
    QSqlQuery sqlQuery;
    QString update_sql = QString("UPDATE noteinfo SET DELETEED = %2  WHERE ID = %1").arg(nId).arg(bDeleted);
    sqlQuery.prepare(update_sql);

    qDebug() << update_sql;

    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
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
    QSqlQuery sqlQuery;
    QString update_sql = QString("DELETE from noteinfo WHERE ID = %1;").arg(nId);

    sqlQuery.prepare(update_sql);

    qDebug() << update_sql;
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
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
    QSqlQuery sqlQuery;
    QString update_sql = QString("UPDATE noteinfo SET FAVORITES = %1 WHERE ID = %2;").arg(bFavorite).arg(nId);

    sqlQuery.prepare(update_sql);

    qDebug() << update_sql;
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"updated!";
    }

    return true;
}

bool DataMgr::NewFolder(int nFId, QString strName)
{
    QSqlQuery sqlQuery;
    QString update_sql = "INSERT INTO nav (FID, TYPE, NAME) VALUES (:FID, :TYPE, :NAME);";

    sqlQuery.prepare(update_sql);
    sqlQuery.bindValue(":TYPE", 1);
    sqlQuery.bindValue(":NAME", strName);
    sqlQuery.bindValue(":FID", nFId);
    if (!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"updated!";
    }

    emit SignalNoteListChange();
    return true;
}

bool DataMgr::DelFolder(int nId)
{
    {
        QSqlQuery sqlQuery;
        QString update_sql = QString("DELETE from noteinfo WHERE FID = %1;").arg(nId);

        sqlQuery.prepare(update_sql);

        qDebug() << update_sql;
        if(!sqlQuery.exec())
        {
            qDebug()<<sqlQuery.lastError();
        }
        else
        {
            qDebug()<<"updated!";
        }

    }

    {
        QSqlQuery sqlQuery;
        QString update_sql = QString("DELETE from nav WHERE ID = %1;").arg(nId);

        sqlQuery.prepare(update_sql);

        qDebug() << update_sql;
        if(!sqlQuery.exec())
        {
            qDebug()<<sqlQuery.lastError();
        }
        else
        {
            qDebug()<<"updated!";
        }

    }

    emit SignalNoteListChange();

    return true;
}
