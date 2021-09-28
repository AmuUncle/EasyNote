#include "addfolder.h"

AddFolder::AddFolder(QWidget *parent) : QDialog(parent)
{
    m_widgetMain = NULL;
    m_editName = NULL;
    m_btnOk = NULL;
    m_btnCancel = NULL;
    m_labelTitle = NULL;

    setWindowFlags(windowFlags() | (Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::Dialog));
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式

    GLOBAL_FUNC_RUN
}


void AddFolder::CreateAllChildWnd()
{
    NEW_OBJECT(m_widgetMain, QWidget);
    NEW_OBJECT(m_editName, QLineEdit);
    NEW_OBJECT(m_btnOk, QPushButton);
    NEW_OBJECT(m_btnCancel, QPushButton);
    NEW_OBJECT(m_labelTitle, QLabel);
}

void AddFolder::InitCtrl()
{
    setFixedSize(330, 180);
    m_widgetMain->setProperty("form", "About");

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(38, 78, 119));
    shadow_effect->setBlurRadius(10);
    m_widgetMain->setGraphicsEffect(shadow_effect);

    m_labelTitle->setText(tr("新建文件夹"));

    m_btnCancel->setFixedSize(100, 30);
    m_btnCancel->setText(tr("取消"));
    m_btnCancel->setProperty("default_btn", true);

    m_btnOk->setFixedSize(100, 30);
    m_btnOk->setText(tr("确认"));
    m_btnOk->setProperty("default_btn", true);

    m_btnOk->setDefault(true);
}

void AddFolder::InitSolts()
{
    connect(m_btnOk, &QPushButton::clicked, [=]()
    {
        m_strName = m_editName->text();
        if (m_strName.length() > 0)
           accept();
        else
           reject();
    });

    connect(m_btnCancel, &QPushButton::clicked, [=]()
    {
        reject();
    });
}

void AddFolder::Relayout()
{
    QHBoxLayout *btnHLayout = new QHBoxLayout();
    btnHLayout->addStretch();
    btnHLayout->addWidget(m_btnCancel);
    btnHLayout->addWidget(m_btnOk);

    QVBoxLayout *mainHLayout = new QVBoxLayout(m_widgetMain);
    mainHLayout->addWidget(m_labelTitle);
    mainHLayout->addWidget(m_editName);
    mainHLayout->addLayout(btnHLayout);
    mainHLayout->setSpacing(8);

    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(m_widgetMain);
    layoutMain->setMargin(30);
    setLayout(layoutMain);
}
