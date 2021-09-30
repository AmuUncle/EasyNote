#include "setpwddlg.h"
#include "datamgr.h"


SetPwdDlg::SetPwdDlg(QWidget *parent) : QDialog(parent)
{
    m_widgetMain = NULL;
    m_labelTitle = NULL;
    m_editPwd = NULL;
    m_btnOk = NULL;
    m_btnCancel = NULL;
    m_labelPwd = NULL;
    m_labelPwd2 = NULL;
    m_editPwd2 = NULL;
    m_btnClear = NULL;

    setWindowFlags(windowFlags() | (Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::Dialog));
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式

    GLOBAL_FUNC_RUN
}


void SetPwdDlg::CreateAllChildWnd()
{
    NEW_OBJECT(m_widgetMain, QWidget);
    NEW_OBJECT(m_labelTitle, QLabel);
    NEW_OBJECT(m_editPwd, QLineEdit);
    NEW_OBJECT(m_btnOk, QPushButton);
    NEW_OBJECT(m_btnClear, QPushButton);
    NEW_OBJECT(m_btnCancel, QPushButton);
    NEW_OBJECT(m_labelPwd, QLabel);
    NEW_OBJECT(m_editPwd2, QLineEdit);
    NEW_OBJECT(m_labelPwd2, QLabel);
}

void SetPwdDlg::InitCtrl()
{
    m_widgetMain->setFixedSize(360, 150);
    m_widgetMain->setProperty("form", "About");

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(38, 78, 119));
    shadow_effect->setBlurRadius(10);
    m_widgetMain->setGraphicsEffect(shadow_effect);

    m_labelTitle->setText(tr("设置登录密码"));
    m_labelPwd->setText(tr("输入密码"));
    m_editPwd->setPlaceholderText(tr("请输入密码"));
    m_editPwd->setEchoMode(QLineEdit::Password);

    m_labelPwd2->setText(tr("确认密码"));
    m_editPwd2->setPlaceholderText(tr("请再次输入密码"));
    m_editPwd2->setEchoMode(QLineEdit::Password);

    m_btnCancel->setFixedSize(100, 30);
    m_btnCancel->setText(tr("取消"));
    m_btnCancel->setProperty("default_btn", true);

    m_btnOk->setFixedSize(100, 30);
    m_btnOk->setText(tr("确认"));
    m_btnOk->setProperty("default_btn", true);

    m_btnClear->setFixedSize(100, 30);
    m_btnClear->setText(tr("清除密码"));
    m_btnClear->setProperty("default_btn", true);

    m_btnOk->setDefault(true);
}

void SetPwdDlg::InitSolts()
{
    connect(m_btnOk, &QPushButton::clicked, [=]()
    {
        if (m_editPwd->text().length() <= 0 || m_editPwd2->text().length() <= 0)
        {
            MessageBoxTip(tr("请输入密码！"));
        }
        else if (m_editPwd->text() != m_editPwd2->text())
        {
            MessageBoxTip(tr("两次输入密码不一致！"));
        }
        else
        {
            if (QMessageBox::Yes != MessageBoxExt(tr("密码设置成功后，每次启动程序都需要输入密码进行验证，请牢记密码，遗失将无法打开本程序！")))
                return;

            QByteArray value;
            value = QCryptographicHash::hash(m_editPwd->text().toLocal8Bit(),QCryptographicHash::Md5);

            if (DATAMGR->SetPwd(QString(value.toHex())))
                accept();
            else
            {
                MessageBoxTip(tr("设置失败！"));
            }
        }
    });

    connect(m_btnClear, &QPushButton::clicked, [=]()
    {
        DATAMGR->SetPwd("");
        reject();
    });

    connect(m_btnCancel, &QPushButton::clicked, [=]()
    {
        reject();
    });
}

void SetPwdDlg::Relayout()
{
    QHBoxLayout *btnHLayout = new QHBoxLayout();
    btnHLayout->addStretch();
    btnHLayout->addWidget(m_btnCancel);
    btnHLayout->addWidget(m_btnClear);
    btnHLayout->addWidget(m_btnOk);

    QGridLayout *mainHLayout = new QGridLayout();
    mainHLayout->addWidget(m_labelPwd, 0, 0, 1, 1);
    mainHLayout->addWidget(m_editPwd, 0, 1, 1, 2);
    mainHLayout->addWidget(m_labelPwd2, 1, 0, 1, 1);
    mainHLayout->addWidget(m_editPwd2, 1, 1, 1, 2);
    mainHLayout->setSpacing(6);

    QVBoxLayout *layoutMain1 = new QVBoxLayout(m_widgetMain);
    layoutMain1->addStretch();
    layoutMain1->addWidget(m_labelTitle);
    layoutMain1->addLayout(mainHLayout);
    layoutMain1->addStretch();
    layoutMain1->addLayout(btnHLayout);


    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(m_widgetMain);
    layoutMain->setMargin(30);
    setLayout(layoutMain);
}
