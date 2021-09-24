#ifndef NOTEITEM_H
#define NOTEITEM_H

#include <QWidget>

#include "global.h"
#include "datamgr.h"

class NoteItem : public QWidget
{
    Q_OBJECT
public:
    explicit NoteItem(QWidget *parent = 0);

    enum EItemType
    {
        ITEMTYPE_GROUP = 0,
        ITEMTYPE_NOTE
    };

public:
    void SetParam(TNoteItem tNoteItem);
    void SetParam(TUserCustomItem tItem);

private:
    GLOBAL_FUNC

    void UpdateCtrlText();

    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

private:
    EItemType m_eType;
    bool m_bRestoreMode;
    TNoteItem m_tNoteIte;
    TUserCustomItem m_tGroupItem;

    QLabel *m_labelIcon;
    QLabel *m_labelTitle;
    QLabel *m_labelTime;

    QWidget *m_widgetTools;
    QPushButton *m_btnDel;
    QPushButton *m_btnAdd;
    QPushButton *m_btnFavorite;
    QPushButton *m_btnRestore;
};

#endif // NOTEITEM_H
