#ifndef DATAMGR_H
#define DATAMGR_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "global.h"

class DataMgr : public QObject
{
    Q_OBJECT
public:
    explicit DataMgr(QObject *parent = 0);


public:
    static DataMgr* GetInstance();
    static void ExitInstance();

    void Open();
    void InitDB();

    QList<TUserCustomItem> GetUserCustomItem();
    QList<TUserCustomItem> GetUserCustomChildItem(int nFId);
    QList<TNoteItem> GetUserCustomChildNote(int nFId);

    QList<TNoteItem> GetRecent();
    QList<TNoteItem> GetFavorites();
    QList<TNoteItem> GetDeleted();

    TNoteItem GetNote(int nId);

    bool SaveNote(TNoteItem tItem);

private:
    static DataMgr *m_pDataMgr;

    QSqlDatabase m_dbData;
};

#define DATAMGR DataMgr::GetInstance()

#endif // DATAMGR_H
