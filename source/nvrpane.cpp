#include "nvrpane.h"
#include "datamgr.h"

NvrPane::NvrPane(QWidget *parent) : QWidget(parent)
{
    m_labelLogo = NULL;
    m_btnNewNote = NULL;
    m_listNav = NULL;

    GLOBAL_FUNC_RUN
}

void NvrPane::OnItemClicked(QListWidgetItem *item)
{
    int nId = item->data(Qt::UserRole).toInt();

    qDebug() << nId;
    emit SignalIDChange(nId);
}

void NvrPane::AddItem(QListWidgetItem *item, QString strName, QChar icon)
{
    QWidget *pItemWidget = new QWidget(m_listNav);
    QLabel *pLabelIcon = new QLabel(pItemWidget);
    QLabel *pLabelTitle = new QLabel(pItemWidget);

    pLabelIcon->setFixedSize(40, 40);
    SetIcon(pLabelIcon, icon, 18);
    pLabelIcon->setProperty("navbtnicon", true);

    pLabelTitle->setText(strName);

    QHBoxLayout *layoutMain = new QHBoxLayout(pItemWidget);
    layoutMain->addWidget(pLabelIcon);
    layoutMain->addWidget(pLabelTitle);
    layoutMain->setContentsMargins(15, 0, 0, 0);
    m_listNav->setItemWidget(item, pItemWidget);
}

void NvrPane::OnBtnNewClicked()
{
    emit SignalNewNote();
}

void NvrPane::CreateAllChildWnd()
{
    NEW_OBJECT(m_labelLogo, QLabel);
    NEW_OBJECT(m_btnNewNote, QPushButton);
    NEW_OBJECT(m_listNav, QListWidget);
}

void NvrPane::InitCtrl()
{
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "NvrPane");
    setFixedWidth(256);

    m_labelLogo->setFixedSize(80, 80);
    QImage img(":/img/img/icon.png");
    m_labelLogo->setPixmap(QPixmap::fromImage(img.scaled(m_labelLogo->size(),
                                                         Qt::IgnoreAspectRatio,
                                                         Qt::SmoothTransformation)));

    m_btnNewNote->setFixedSize(160, 40);
    m_btnNewNote->setText(tr("新文档"));
    m_btnNewNote->setObjectName("m_btnNewNote");

    QListWidgetItem *item1 = new QListWidgetItem();
    item1->setSizeHint(QSize(10, 50));
    item1->setData(Qt::UserRole, RECENT);
    m_listNav->addItem(item1);
    AddItem(item1, tr("最近文档"), QChar(0xe625));

    QListWidgetItem *item2 = new QListWidgetItem();
    item2->setSizeHint(QSize(10, 50));
    item2->setData(Qt::UserRole, DEFAULT);
    m_listNav->addItem(item2);
    AddItem(item2, tr("我的文档"), QChar(0xe61b));

    QListWidgetItem *item3 = new QListWidgetItem();
    item3->setSizeHint(QSize(10, 50));
    item3->setData(Qt::UserRole, FAVORITES);
    m_listNav->addItem(item3);
    AddItem(item3, tr("收藏夹"), QChar(0xe618));

    QListWidgetItem *item4 = new QListWidgetItem();
    item4->setSizeHint(QSize(10, 50));
    item4->setData(Qt::UserRole, DELETED);
    m_listNav->addItem(item4);
    AddItem(item4, tr("回收站"), QChar(0xe724));

    QTimer::singleShot(500, this, [=]()
    {
        m_listNav->setCurrentItem(item2);
        emit SignalIDChange(DEFAULT);
    });

}

void NvrPane::InitSolts()
{
    connect(m_listNav, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(OnItemClicked(QListWidgetItem*)));
    connect(m_btnNewNote, SIGNAL(clicked()), this, SLOT(OnBtnNewClicked()));
}

void NvrPane::Relayout()
{
    QHBoxLayout *layoutLogo = new QHBoxLayout();
    layoutLogo->addStretch();
    layoutLogo->addWidget(m_labelLogo);
    layoutLogo->addStretch();
    layoutLogo->setContentsMargins(0, 0, 0, 20);
    layoutLogo->setSpacing(0);

    QHBoxLayout *layoutNew = new QHBoxLayout();
    layoutNew->addStretch();
    layoutNew->addWidget(m_btnNewNote);
    layoutNew->addStretch();
    layoutNew->setContentsMargins(0, 0, 0, 20);
    layoutNew->setSpacing(0);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(layoutLogo);
    mainLayout->addLayout(layoutNew);
    mainLayout->addWidget(m_listNav);
    mainLayout->setContentsMargins(0, 50, 0, 0);
    mainLayout->setSpacing(10);
    setLayout(mainLayout);
}
