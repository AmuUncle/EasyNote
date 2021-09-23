﻿#include "notelistpane.h"
#include "datamgr.h"


NoteListPane::NoteListPane(QWidget *parent) : QWidget(parent)
{
    m_btnBack = NULL;
    m_editSearch = NULL;
    m_listNoteItems = NULL;

    GLOBAL_FUNC_RUN
}

void NoteListPane::OnIdChange(int nId)
{
    qDebug() << nId;

    m_listNoteItems->clear();

    if (nId < RECENT)
    {
        QList<TUserCustomItem> listDir = DATAMGR->GetUserCustomChildItem(nId);
        QList<TNoteItem> listNote = DATAMGR->GetUserCustomChildNote(nId);

        foreach (TUserCustomItem item, listDir) {

            QListWidgetItem *item1 = new QListWidgetItem();
            item1->setSizeHint(QSize(10, 50));
            item1->setData(Qt::UserRole, GROUPS);
            item1->setData(Qt::UserRole + 1, item.nId);
            m_listNoteItems->addItem(item1);

            AddItem(item1, item.strName, QChar(0xe7b8), "06-17");
        }

        int nCount = m_listNoteItems->count();

        foreach (TNoteItem item, listNote) {
            QListWidgetItem *item1 = new QListWidgetItem();
            item1->setSizeHint(QSize(10, 50));
            item1->setData(Qt::UserRole, NOTE);
            item1->setData(Qt::UserRole + 1, item.nId);
            m_listNoteItems->addItem(item1);

            AddItem(item1, item.strTitle, QChar(0xe61e), item.strTime);
        }

        m_listNoteItems->setCurrentRow(nCount);
    }
    else
    {
        if (nId == RECENT)
        {
            QList<TNoteItem> listDir = DATAMGR->GetRecent();

            foreach (TNoteItem item, listDir) {

                QListWidgetItem *item1 = new QListWidgetItem();
                item1->setSizeHint(QSize(10, 50));
                item1->setData(Qt::UserRole, NOTE);
                item1->setData(Qt::UserRole + 1, item.nId);
                m_listNoteItems->addItem(item1);

                AddItem(item1, item.strTitle, QChar(0xe61e), item.strTime);
            }
        }
        else if (nId == FAVORITES)
        {
            QList<TNoteItem> listDir = DATAMGR->GetFavorites();

            foreach (TNoteItem item, listDir) {

                QListWidgetItem *item1 = new QListWidgetItem();
                item1->setSizeHint(QSize(10, 50));
                item1->setData(Qt::UserRole, NOTE);
                item1->setData(Qt::UserRole + 1, item.nId);
                m_listNoteItems->addItem(item1);

                AddItem(item1, item.strTitle, QChar(0xe61e), item.strTime);
            }
        }
        else if (nId == DELETED)
        {
            QList<TNoteItem> listDir = DATAMGR->GetDeleted();

            foreach (TNoteItem item, listDir) {

                QListWidgetItem *item1 = new QListWidgetItem();
                item1->setSizeHint(QSize(10, 50));
                item1->setData(Qt::UserRole, NOTE);
                item1->setData(Qt::UserRole + 1, item.nId);
                m_listNoteItems->addItem(item1);

                AddItem(item1, item.strTitle, QChar(0xe61e), item.strTime);
            }
        }

        m_listNoteItems->setCurrentRow(0);
    }
}

void NoteListPane::OnCurrentRowChanged(int currentRow)
{
   if (currentRow < 0)
        return;

   QListWidgetItem *item = m_listNoteItems->item(currentRow);
   if (NULL == item)
       return;


   ItemType eType = (ItemType)(item->data(Qt::UserRole).toInt());
   int nId = item->data(Qt::UserRole + 1).toInt();

   if (GROUPS == eType)
   {
        emit SignalSelGroup();
   }
   else
   {
       TNoteItem tItem = DATAMGR->GetNote(nId);

       qDebug() << tItem.nId << tItem.strTitle << tItem.strContent << tItem.strTime << "---------------";
       emit SignalNoteChange(tItem);
   }
}

void NoteListPane::CreateAllChildWnd()
{
    NEW_OBJECT(m_btnBack, QPushButton);
    NEW_OBJECT(m_editSearch, QLineEdit);
    NEW_OBJECT(m_listNoteItems, QListWidget);
}

void NoteListPane::InitCtrl()
{
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "NoteListPane");
    setFixedWidth(260);

    m_btnBack->setFixedSize(38, 38);
    SetIcon(m_btnBack, QChar(0xe6f4));

    m_editSearch->setFixedHeight(38);
    m_editSearch->setPlaceholderText(tr("请输入搜索内容"));
}

void NoteListPane::InitSolts()
{
    connect(m_listNoteItems, SIGNAL(currentRowChanged(int)), this, SLOT(OnCurrentRowChanged(int)));
}

void NoteListPane::Relayout()
{
    QHBoxLayout *layoutSearch = new QHBoxLayout();
    layoutSearch->addWidget(m_btnBack);
    layoutSearch->addWidget(m_editSearch);
    layoutSearch->setMargin(8);
    layoutSearch->setSpacing(0);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(layoutSearch);
    mainLayout->addWidget(m_listNoteItems);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(1);
    setLayout(mainLayout);
}

void NoteListPane::AddItem(QListWidgetItem *item, QString strName, QChar icon, QString strTime)
{
    QWidget *pItemWidget = new QWidget(m_listNoteItems);
    QLabel *pLabelIcon = new QLabel(pItemWidget);
    QLabel *pLabelTitle = new QLabel(pItemWidget);
    QLabel *pLabelTime = new QLabel(pItemWidget);

    SetIcon(pLabelIcon, icon, 18);
    pLabelIcon->setProperty("navbtnicon", true);

    pLabelTitle->setText(strName);

    pLabelTime->setText(strTime.mid(5, 5));
    pLabelTime->setProperty("navbtntime", true);

    QHBoxLayout *layoutMain = new QHBoxLayout(pItemWidget);
    layoutMain->addWidget(pLabelIcon);
    layoutMain->addWidget(pLabelTitle);
    layoutMain->addStretch();
    layoutMain->addWidget(pLabelTime);
    layoutMain->setContentsMargins(0, 0, 10, 0);
    m_listNoteItems->setItemWidget(item, pItemWidget);
}
