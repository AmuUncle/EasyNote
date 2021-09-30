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

    void SetNavItem(NavItem eNavItem) { m_eNavItem = eNavItem; }
    NavItem GetNavItem() { return m_eNavItem; }

    QList<TUserCustomItem> GetUserCustomItem();
    QList<TUserCustomItem> GetUserCustomChildItem(int nFId);
    QList<TNoteItem> GetUserCustomChildNote(int nFId);

    QList<TNoteItem> GetRecent();
    QList<TNoteItem> GetFavorites();
    QList<TNoteItem> GetDeleted();

    QList<TNoteItem> Search(QString strKey);

    TNoteItem GetNote(int nId);
    int GetGroupFId(int nId);

    bool SaveNote(TNoteItem tItem);

    bool NewNote(TNoteItem tItem);
    bool RemoveNote(int nId, bool bDeleted = true);
    bool DelNote(int nId);
    bool FavoriteNote(int nId, bool bFavorite);
    bool ClearDeleted();

    bool NewFolder(int nFId, QString strName);
    bool DelFolder(int nId);

    MenuType GetTheme();
    void SetTheme(MenuType eTheme);

    bool CheckPwd(QString strPwd);
    bool SetPwd(QString strPwd);
    bool HasPwd();

signals:
    void SignalNoteListChange();

private:
    static DataMgr *m_pDataMgr;

    NavItem m_eNavItem;
    QSqlDatabase m_dbData;
};

#define DATAMGR DataMgr::GetInstance()

#endif // DATAMGR_H
