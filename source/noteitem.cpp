#include "noteitem.h"
#include "popconfirm.h"

NoteItem::NoteItem(QWidget *parent) : QWidget(parent)
{
    m_labelIcon = NULL;
    m_labelTitle = NULL;
    m_labelTime = NULL;

    m_widgetTools = NULL;
    m_btnDel = NULL;
    m_btnAdd = NULL;
    m_btnFavorite = NULL;
    m_btnRestore = NULL;

    m_bRestoreMode = DATAMGR->GetNavItem() == DELETED;

    GLOBAL_FUNC_RUN
}

void NoteItem::SetParam(TNoteItem tNoteItem)
{
    m_eType = ITEMTYPE_NOTE;
    m_tNoteIte = tNoteItem;

    UpdateCtrlText();
}

void NoteItem::SetParam(TUserCustomItem tItem)
{
    m_eType = ITEMTYPE_GROUP;
    m_tGroupItem = tItem;

    UpdateCtrlText();
}

void NoteItem::UpdateCtrlText()
{
    if (m_eType != ITEMTYPE_NOTE)
    {
        SetIcon(m_labelIcon, QChar(0xe7b8), 18);
        m_labelTitle->setText(m_tGroupItem.strName);
        m_labelTime->setText("");
    }
    else
    {
        SetIcon(m_labelIcon, QChar(0xe61e), 18);
        m_labelTitle->setText(m_tNoteIte.strTitle);
        m_labelTime->setText(m_tNoteIte.strTime.mid(5, 5));

        if (!m_tNoteIte.bFavorited)
            SetIcon(m_btnFavorite, QChar(0xe616), 16);
        else
            SetIcon(m_btnFavorite, QChar(0xe620), 16);
    }
}

void NoteItem::enterEvent(QEvent *event)
{
    if (m_eType != ITEMTYPE_NOTE)
    {
        m_btnDel->show();
        m_btnAdd->hide();
        m_btnFavorite->hide();
    }
    else
    {
        m_btnDel->show();
        m_btnAdd->hide();


        if (m_bRestoreMode)
        {
            m_btnFavorite->hide();
            m_btnRestore->show();
        }
        else
        {
           m_btnFavorite->show();
           m_btnRestore->hide();
        }
    }
}

void NoteItem::leaveEvent(QEvent *event)
{
    m_btnDel->hide();
    m_btnAdd->hide();
    m_btnFavorite->hide();
    m_btnRestore->hide();
}

void NoteItem::CreateAllChildWnd()
{
    NEW_OBJECT(m_labelIcon, QLabel);
    NEW_OBJECT(m_labelTitle, QLabel);
    NEW_OBJECT(m_labelTime, QLabel);

    NEW_OBJECT(m_widgetTools, QWidget);
    NEW_OBJECT(m_btnDel, QPushButton);
    NEW_OBJECT(m_btnAdd, QPushButton);
    NEW_OBJECT(m_btnFavorite, QPushButton);
    NEW_OBJECT(m_btnRestore, QPushButton);
}

void NoteItem::InitCtrl()
{
    setProperty("form", "NoteItem");
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式

    m_labelIcon->setProperty("navbtnicon", true);
    m_labelTitle->setProperty("navbtntitle", true);
    m_labelTime->setProperty("navbtntime", true);

    m_widgetTools->setFixedSize(40, 20);

    SetIcon(m_btnDel, QChar(0xe61c), 18);
    SetIcon(m_btnAdd, QChar(0xe6cf), 18);
    SetIcon(m_btnFavorite, QChar(0xe618), 16);
    SetIcon(m_btnRestore, QChar(0xe6eb), 16);

    m_btnDel->setToolTip(tr("删除"));
    m_btnAdd->setToolTip(tr("新建文件夹"));
    m_btnFavorite->setToolTip(tr("收藏"));
    m_btnRestore->setToolTip(tr("还原"));

    m_btnDel->hide();
    m_btnAdd->hide();
    m_btnFavorite->hide();
    m_btnRestore->hide();
}

void NoteItem::InitSolts()
{
    connect(m_btnFavorite, &QPushButton::clicked, [=]{
        if (m_tNoteIte.bFavorited)
        {
            DATAMGR->FavoriteNote(m_tNoteIte.nId, !m_tNoteIte.bFavorited);
        }
        else
        {
           DATAMGR->FavoriteNote(m_tNoteIte.nId, !m_tNoteIte.bFavorited);
        }

        m_tNoteIte.bFavorited = !m_tNoteIte.bFavorited;
        UpdateCtrlText();
    });

    connect(m_btnDel, &QPushButton::clicked, [=]{
        if (m_eType == ITEMTYPE_NOTE)
        {
            if (m_bRestoreMode)
            {
                if (QMessageBox::Ok == QMessageBox::warning(this, PRJ_NAME, tr("是否确认删除？"),
                                                    QMessageBox::Ok | QMessageBox::Cancel,
                                                    QMessageBox::Cancel))
                {
                    DATAMGR->DelNote(m_tNoteIte.nId);
                }
            }
            else
            {
                if (QMessageBox::Ok == QMessageBox::warning(this, PRJ_NAME, tr("是否确认删除？"),
                                                    QMessageBox::Ok | QMessageBox::Cancel,
                                                    QMessageBox::Cancel))
                {
                    DATAMGR->RemoveNote(m_tNoteIte.nId);
                }


            }
        }
        else
        {
            if (QMessageBox::Ok == QMessageBox::warning(this, PRJ_NAME, tr("是否确认删除？"),
                                                QMessageBox::Ok | QMessageBox::Cancel,
                                                QMessageBox::Cancel))
            {
                DATAMGR->DelFolder(m_tGroupItem.nId);
            }
        }
    });

    connect(m_btnRestore, &QPushButton::clicked, [=]{
        if (m_eType == ITEMTYPE_NOTE)
        {
            DATAMGR->RemoveNote(m_tNoteIte.nId, false);
        }
        else
        {

        }
    });
}

void NoteItem::Relayout()
{
    QHBoxLayout *ToolsLayout = new QHBoxLayout(m_widgetTools);
    ToolsLayout->addStretch();
    ToolsLayout->addWidget(m_btnDel);
    ToolsLayout->addWidget(m_btnAdd);
    ToolsLayout->addWidget(m_btnFavorite);
    ToolsLayout->addWidget(m_btnRestore);
    ToolsLayout->setMargin(0);
    ToolsLayout->setSpacing(0);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(m_widgetTools);
    rightLayout->addWidget(m_labelTime);
    rightLayout->setMargin(0);
    rightLayout->setSpacing(0);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_labelIcon);
    mainLayout->addWidget(m_labelTitle);
    mainLayout->addStretch();
    mainLayout->addLayout(rightLayout);
    mainLayout->setContentsMargins(0, 0, 5, 0);
    setLayout(mainLayout);
}
