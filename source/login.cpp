#include "login.h"
#include "mainwnd.h"
#include "datamgr.h"


Login::Login(QWidget *parent) : QDialog(parent)
{
    m_widgetMain = NULL;
    m_editPwd = NULL;
    m_btnOk = NULL;
    m_btnCancel = NULL;
    m_labelTitle = NULL;
    m_labelLogo = NULL;
    m_labelLogoName = NULL;

    setWindowFlags(windowFlags() | (Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::Dialog));
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式

    GLOBAL_FUNC_RUN
    CANMOVE
}


void Login::CreateAllChildWnd()
{
    NEW_OBJECT(m_widgetMain, QWidget);
    NEW_OBJECT(m_labelLogo, QLabel);
    NEW_OBJECT(m_editPwd, QLineEdit);
    NEW_OBJECT(m_btnOk, QPushButton);
    NEW_OBJECT(m_btnCancel, QPushButton);
    NEW_OBJECT(m_labelTitle, QLabel);
    NEW_OBJECT(m_labelLogoName, QLabel);
}

void Login::InitCtrl()
{
    setFixedSize(420, 220);
    m_widgetMain->setProperty("form", "About");

    m_labelLogo->setFixedSize(80, 80);
    QImage img(":/img/img/logo.png");
    m_labelLogo->setPixmap(QPixmap::fromImage(img.scaled(m_labelLogo->size(),
                                                         Qt::IgnoreAspectRatio,
                                                         Qt::SmoothTransformation)));

    m_labelLogoName->setText(tr("简笔记"));
    m_labelLogoName->setAlignment(Qt::AlignCenter);

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(38, 78, 119));
    shadow_effect->setBlurRadius(10);
    m_widgetMain->setGraphicsEffect(shadow_effect);

    m_labelTitle->setText(tr("登录密码"));
    m_editPwd->setPlaceholderText(tr("请输入密码"));
    m_editPwd->setEchoMode(QLineEdit::Password);

    m_btnCancel->setFixedSize(100, 30);
    m_btnCancel->setText(tr("取消"));
    m_btnCancel->setProperty("default_btn", true);

    m_btnOk->setFixedSize(100, 30);
    m_btnOk->setText(tr("确认"));
    m_btnOk->setProperty("default_btn", true);

    m_btnOk->setDefault(true);
}

void Login::InitSolts()
{
    connect(m_btnOk, &QPushButton::clicked, [=]()
    {
        QByteArray value;
        value = QCryptographicHash::hash(m_editPwd->text().toLocal8Bit(),QCryptographicHash::Md5);

        if (DATAMGR->CheckPwd(QString(value.toHex())))
            accept();
        else
        {
            MessageBoxTip(tr("密码错误！"));
        }
    });

    connect(m_btnCancel, &QPushButton::clicked, [=]()
    {
        exit(0);
    });
}

void Login::Relayout()
{
    QVBoxLayout *logoHLayout = new QVBoxLayout();
    logoHLayout->addStretch();
    logoHLayout->addWidget(m_labelLogo);
    logoHLayout->addWidget(m_labelLogoName);
    logoHLayout->addStretch();
    logoHLayout->setSpacing(6);

    QHBoxLayout *btnHLayout = new QHBoxLayout();
    btnHLayout->addStretch();
    btnHLayout->addWidget(m_btnCancel);
    btnHLayout->addWidget(m_btnOk);


    QVBoxLayout *mainHLayout = new QVBoxLayout();
    mainHLayout->addStretch();
    mainHLayout->addWidget(m_labelTitle);
    mainHLayout->addWidget(m_editPwd);
    mainHLayout->addStretch();
    mainHLayout->addLayout(btnHLayout);
    mainHLayout->setSpacing(8);

    QHBoxLayout *mainLayout1 = new QHBoxLayout(m_widgetMain);
    mainLayout1->addLayout(logoHLayout);
    mainLayout1->addLayout(mainHLayout);
    mainLayout1->setSpacing(20);
    mainLayout1->setMargin(20);

    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(m_widgetMain);
    layoutMain->setMargin(30);
    setLayout(layoutMain);
}
