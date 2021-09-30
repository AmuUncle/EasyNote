#include "messagebox.h"

QMessageBoxEx::QMessageBoxEx(bool bTipMode, QWidget *parent) : QDialog(parent)
{
    m_widgetMain = NULL;
    m_labelLogo = NULL;
    m_labelTitle = NULL;
    m_btnOk = NULL;
    m_btnCancel = NULL;

    m_bTipMode = bTipMode;

    setWindowFlags(windowFlags() | (Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::Dialog));
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式

    GLOBAL_FUNC_RUN
    CANMOVE
}

void QMessageBoxEx::setText(QString strText)
{
   m_labelTitle->setText(strText);
}


void QMessageBoxEx::CreateAllChildWnd()
{
    NEW_OBJECT(m_widgetMain, QWidget);
    NEW_OBJECT(m_labelLogo, QLabel);
    NEW_OBJECT(m_labelTitle, QLabel);
    NEW_OBJECT(m_btnOk, QPushButton);
    NEW_OBJECT(m_btnCancel, QPushButton);
}

void QMessageBoxEx::InitCtrl()
{
    setFixedSize(400, 250);
    m_widgetMain->setProperty("form", "About");

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(38, 78, 119));
    shadow_effect->setBlurRadius(10);
    m_widgetMain->setGraphicsEffect(shadow_effect);

    m_labelLogo->setFixedSize(64, 64);
    m_labelTitle->setAlignment(Qt::AlignCenter);

    m_btnCancel->setFixedSize(100, 30);
    m_btnCancel->setText(tr("取消"));
    m_btnCancel->setProperty("default_btn", true);

    m_btnOk->setFixedSize(100, 30);
    m_btnOk->setText(tr("确认"));
    m_btnOk->setProperty("default_btn", true);

    QImage img(":/img/img/warning.png");
    m_labelLogo->setPixmap(QPixmap::fromImage(img.scaled(m_labelLogo->size(),
                                                         Qt::IgnoreAspectRatio,
                                                         Qt::SmoothTransformation)));

    m_btnCancel->setVisible(!m_bTipMode);
}

void QMessageBoxEx::InitSolts()
{
    connect(m_btnOk, &QPushButton::clicked, [=]()
    {
        done(QMessageBox::Yes);
    });

    connect(m_btnCancel, &QPushButton::clicked, [=]()
    {
        done(QMessageBox::No);
    });
}

void QMessageBoxEx::Relayout()
{
    QHBoxLayout *logoHLayout = new QHBoxLayout();
    logoHLayout->addStretch();
    logoHLayout->addWidget(m_labelLogo);
    logoHLayout->addStretch();

    QHBoxLayout *btnHLayout = new QHBoxLayout();
    btnHLayout->addStretch();
    btnHLayout->addWidget(m_btnCancel);
    btnHLayout->addWidget(m_btnOk);
    btnHLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(logoHLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(m_labelTitle);
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
