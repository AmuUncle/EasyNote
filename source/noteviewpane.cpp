#include "noteviewpane.h"

NoteViewPane::NoteViewPane(QWidget *parent) : QWidget(parent)
{
    m_editTitle = NULL;
    m_webView = NULL;
    m_pWebChannel = NULL;

    m_widgetTop = NULL;
    m_widgetMenu = NULL;
    m_btnMin = NULL;
    m_btnMax = NULL;
    m_btnClose = NULL;
    m_btnAbout = NULL;

    GLOBAL_FUNC_RUN
}

void NoteViewPane::CreateAllChildWnd()
{
    NEW_OBJECT(m_editTitle, QLineEdit);
    NEW_OBJECT(m_webView, QWebEngineView);
    NEW_OBJECT(m_pWebChannel, QWebChannel);

    NEW_OBJECT(m_widgetTop, QWidget);

    NEW_OBJECT(m_widgetMenu, QWidget);
    NEW_OBJECT(m_btnMin, QPushButton);
    NEW_OBJECT(m_btnMax, QPushButton);
    NEW_OBJECT(m_btnClose, QPushButton);
    NEW_OBJECT(m_btnAbout, QPushButton);
}

void NoteViewPane::InitCtrl()
{
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "NoteViewPane");

    qApp->installEventFilter(this);

    m_editTitle->setFixedHeight(60);
    m_widgetTop->setFixedHeight(60);
    m_widgetMenu->setFixedSize(30 * 4, 30);

    m_btnMin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_btnMax->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_btnClose->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_btnAbout->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_btnMin->setProperty("title_btn", true);
    m_btnClose->setProperty("title_btn", true);
    m_btnAbout->setProperty("title_btn", true);
    m_btnMax->setProperty("title_btn", true);

    SetIcon(m_btnMin, QChar(0xe614));
    SetIcon(m_btnMax, QChar(0xe614));
    SetIcon(m_btnClose, QChar(0xe677));
    SetIcon(m_btnAbout, QChar(0xe601));

    QWebEngineSettings *webSetting = QWebEngineSettings::globalSettings();
    webSetting->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    webSetting->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    webSetting->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
    m_webView->load(QUrl("file:///E:/CODE/gitlab/vue_doc/index.html"));

    // 注册一个qtui对象  html端通过此名称向qt端发送消息
    m_pWebChannel->registerObject(QString("qtui"), this);
    m_webView->page()->setWebChannel(m_pWebChannel);
    QTimer::singleShot(100, this, [=]()
    {
        QList<QWidget*> items = findChildren<QWidget*>();
        for (QWidget *item : items) {
            if (!item->property("title_btn").toBool())
                item->hide();
        }
    });
}

void NoteViewPane::InitSolts()
{
}

void NoteViewPane::Relayout()
{
    QHBoxLayout *MenuLayout = new QHBoxLayout(m_widgetMenu);
    MenuLayout->addWidget(m_btnAbout);
    MenuLayout->addWidget(m_btnMin);
    MenuLayout->addWidget(m_btnMax);
    MenuLayout->addWidget(m_btnClose);
    MenuLayout->setContentsMargins(0, 0, 0, 0);
    MenuLayout->setSpacing(0);



    QVBoxLayout *barLayout = new QVBoxLayout();
    barLayout->addWidget(m_widgetMenu);
    barLayout->addStretch();
    barLayout->setContentsMargins(0, 0, 0, 0);
    barLayout->setSpacing(0);

    QHBoxLayout *topLayout = new QHBoxLayout(m_widgetTop);
    topLayout->addWidget(m_editTitle);
    topLayout->addLayout(barLayout);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_widgetTop);
    mainLayout->addWidget(m_webView);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

void NoteViewPane::recieveJsMessage(const QString &jsMsg)
{

}

void NoteViewPane::OnItemChange(int nId)
{

}

void NoteViewPane::OnNoteChange(TNoteItem tItem)
{
    m_tNoteItem = tItem;

    QList<QWidget*> items = findChildren<QWidget*>();
    for (QWidget *item : items) {
        if (!item->property("title_btn").toBool())
            item->show();
    }

    m_editTitle->setText(m_tNoteItem.strTitle);
    QString jsStr = QString(QString("setHtml('%1')").arg(m_tNoteItem.strContent));
    m_webView->page()->runJavaScript(jsStr);
}

void NoteViewPane::OnSelGroup()
{
    QList<QWidget*> items = findChildren<QWidget*>();
    for (QWidget *item : items) {
        if (!item->property("title_btn").toBool())
            item->hide();
    }

    GetJsRetString();
}

QString NoteViewPane::GetJsRetString()
{
    if (!m_webView->isVisible())
        return "";

    QEventLoop loop;
    connect(this, &NoteViewPane::signalRunJsOver, &loop, &QEventLoop::quit);

    QString jsStr = "getHtml();";// getHtml

    QString retStr{}; // 返回值
    // 通过loop循环等到回调上来数据再继续
    m_webView->page()->runJavaScript(jsStr, [&](const QVariant &v)
    {
        retStr = v.toString();
        qDebug() << retStr;

        m_tNoteItem.strContent = retStr;
        m_tNoteItem.strTitle = m_editTitle->text();

        DATAMGR->SaveNote(m_tNoteItem);

        // 在头文件中定义这个函数，收到js的回调返回值后，结束loop循环
        emit signalRunJsOver();
    });

    loop.exec(); // 收不到回调处理结束信号,我就在这里循环等待

    return retStr;
}

bool NoteViewPane::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *event = static_cast<QKeyEvent *>(e);
        if (event->key() == Qt::Key_S && (event->modifiers() & Qt::ControlModifier))
        {
            GetJsRetString();
            return true;
        }
    }

    return QObject::eventFilter(obj, e);
}
