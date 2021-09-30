#include "about.h"

About::About(QWidget *parent) :
    QDialog(parent)
{
    m_widgetMain = NULL;
    m_labelLogo = NULL;
    m_labelVersion = NULL;
    m_btnOk = NULL;

    setWindowFlags(windowFlags() | (Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::Dialog));
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式

    GLOBAL_FUNC_RUN
}

About::~About()
{

}

void About::CreateAllChildWnd()
{
    NEW_OBJECT(m_widgetMain, QWidget);
    NEW_OBJECT(m_labelLogo, QLabel);
    NEW_OBJECT(m_labelVersion, QLabel);
    NEW_OBJECT(m_btnOk, QPushButton);
}

void About::InitCtrl()
{
    setFixedSize(400, 250);
    m_widgetMain->setProperty("form", "About");

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(38, 78, 119));
    shadow_effect->setBlurRadius(10);
    m_widgetMain->setGraphicsEffect(shadow_effect);

    m_labelLogo->setFixedSize(50, 50);
    m_labelVersion->setAlignment(Qt::AlignCenter);

    m_btnOk->setFixedSize(100, 30);
    m_btnOk->setText(tr("确认"));
    m_btnOk->setProperty("default_btn", true);

    QImage img(":/img/img/logo.png");
    m_labelLogo->setPixmap(QPixmap::fromImage(img.scaled(m_labelLogo->size(),
                                                         Qt::IgnoreAspectRatio,
                                                         Qt::SmoothTransformation)));
    m_labelVersion->setText(QString(tr("简笔记 %1 \n designed by %3(%2)\n 邮箱: %4").arg(VERSION).arg(__DATE__).arg(AUTHOR).arg(MAIL)));
}

void About::InitSolts()
{
    connect(m_btnOk, &QPushButton::clicked, [=]()
    {
        close();
    });
}

void About::Relayout()
{
    QHBoxLayout *logoHLayout = new QHBoxLayout();
    logoHLayout->addStretch();
    logoHLayout->addWidget(m_labelLogo);
    logoHLayout->addStretch();

    QHBoxLayout *btnHLayout = new QHBoxLayout();
    btnHLayout->addStretch();
    btnHLayout->addWidget(m_btnOk);
    btnHLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(logoHLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(m_labelVersion);
    mainLayout->addStretch();
    mainLayout->addLayout(btnHLayout);
    mainLayout->setMargin(10);

    QHBoxLayout *mainHLayout = new QHBoxLayout(m_widgetMain);
    mainHLayout->addStretch();
    mainHLayout->addLayout(mainLayout);
    mainHLayout->addStretch();

    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(m_widgetMain);
    layoutMain->setMargin(30);
    setLayout(layoutMain);
}
