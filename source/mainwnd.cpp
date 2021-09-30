#include "mainwnd.h"

#include "navpane.h"
#include "notelistpane.h"
#include "noteviewpane.h"
#include "about.h"
#include "login.h"
#include "setpwddlg.h"

#define STANDBY_TRIGGER_TIME  10 * 60 * 1000     // 鼠标无操作，自动进入锁定界面

MainWnd::MainWnd(QWidget *parent) :
    QWidget(parent)
{
    m_bCloseAnimationState = false;

    m_pMainPane = NULL;
    m_pNvrPane = NULL;
    m_pNoteListPane = NULL;
    m_pNoteViewPane = NULL;

    GLOBAL_FUNC_RUN

    InitMainPaneLayout();

}

MainWnd::~MainWnd()
{
}

void MainWnd::InitMainPaneLayout()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(m_pMainPane);
    mainLayout->addWidget(m_pNvrPane);
    mainLayout->addWidget(m_pNoteListPane);
    mainLayout->addWidget(m_pNoteViewPane);
    mainLayout->setMargin(1);
    mainLayout->setSpacing(0);
}

void MainWnd::CreateAllChildWnd()
{
    NEW_OBJECT(m_pMainPane, QWidget);
    NEW_OBJECT(m_pNvrPane, NavPane);
    NEW_OBJECT(m_pNoteListPane, NoteListPane);
    NEW_OBJECT(m_pNoteViewPane, NoteViewPane);
}

void MainWnd::InitCtrl()
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    setFixedSize(1366, 768);
    setProperty("canMove", "true");
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setAttribute(Qt::WA_TranslucentBackground, true);
    setProperty("form", "mainpane");

    m_pMainPane->setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    m_pMainPane->setProperty("form", "mainpane");

    qApp->installEventFilter(this);

    m_timeMouseTrigger = QTime::currentTime();

    m_pMouseWatcher = new QTimer(this);
    connect(m_pMouseWatcher, &QTimer::timeout, [=]()
    {
        if (!m_timeMouseTrigger.isNull() && qAbs(m_timeMouseTrigger.msecsTo(QTime::currentTime())) > STANDBY_TRIGGER_TIME)
            PreLogin();
    });

    m_pMouseWatcher->start(1000);
}

void MainWnd::InitSolts()
{
    connect(m_pNvrPane, &NavPane::SignalIDChange, [=](int id) {
        m_pNoteListPane->EnableGroupMode(id == DEFAULT);
        DATAMGR->SetNavItem((NavItem)id);
    });

    connect(m_pNvrPane, SIGNAL(SignalIDChange(int)), m_pNoteListPane, SLOT(OnIdChange(int)));

    connect(m_pNvrPane, SIGNAL(SignalNewNote()), m_pNoteListPane, SLOT(OnAddNewNote()));

    connect(m_pNoteViewPane, SIGNAL(signalTitleChange(QString)), m_pNoteListPane, SLOT(OnTitleChange(QString)));

    connect(m_pNoteListPane, SIGNAL(SignalNoteChange(TNoteItem)), m_pNoteViewPane, SLOT(OnNoteChange(TNoteItem)));
    connect(m_pNoteListPane, SIGNAL(SignalSelGroup()), m_pNoteViewPane, SLOT(OnSelGroup()));

    connect(m_pNoteViewPane, &NoteViewPane::SignalMenuClicked, [=](MenuType eType) {
        static bool m_bMaxWindows = false;

        switch (eType) {
        case MENUTYPE_MIN:
            setWindowState(Qt::WindowMinimized);
            update();
            break;

        case MENUTYPE_MAX:
            m_bMaxWindows = !m_bMaxWindows;

            if (m_bMaxWindows)
                setWindowState(Qt::WindowMaximized);
            else
                setWindowState(Qt::WindowNoState);
            break;

        case MENUTYPE_ABOUT:
            {
                About dlg(this);
                dlg.exec();
            }
            break;

        case MENUTYPE_CLOSE:
            close();
            break;

        case MENUTYPE_SETPWD:
            {

                SetPwdDlg dlg(this);
                dlg.exec();
            }
            break;

        case MENUITEM_THEME_DEFAULT:
            {
                QFile file(":/css/css/youdao.css");
                if (file.open(QFile::ReadOnly))
                {
                    QString qss = QLatin1String(file.readAll());
                    QString paletteColor = qss.mid(20, 7);
                    qApp->setPalette(QPalette(QColor(paletteColor)));
                    qApp->setStyleSheet(qss);
                    file.close();

                    DATAMGR->SetTheme(eType);
                }
            }
            break;

        case MENUITEM_THEME_FLATUI:
            {
                QFile file(":/css/css/flatui.css");
                if (file.open(QFile::ReadOnly))
                {
                    QString qss = QLatin1String(file.readAll());
                    QString paletteColor = qss.mid(20, 7);
                    qApp->setPalette(QPalette(QColor(paletteColor)));
                    qApp->setStyleSheet(qss);
                    file.close();

                    DATAMGR->SetTheme(eType);
                }
            }
            break;

        case MENUITEM_THEME_PS:
            {
                QFile file(":/css/css/ps.css");
                if (file.open(QFile::ReadOnly))
                {
                    QString qss = QLatin1String(file.readAll());
                    QString paletteColor = qss.mid(20, 7);
                    qApp->setPalette(QPalette(QColor(paletteColor)));
                    qApp->setStyleSheet(qss);
                    file.close();

                    DATAMGR->SetTheme(eType);
                }
            }
            break;

        case MENUITEM_THEME_SIPMPLE:
            {
                QFile file(":/css/css/simple.css");
                if (file.open(QFile::ReadOnly))
                {
                    QString qss = QLatin1String(file.readAll());
                    QString paletteColor = qss.mid(20, 7);
                    qApp->setPalette(QPalette(QColor(paletteColor)));
                    qApp->setStyleSheet(qss);
                    file.close();

                    DATAMGR->SetTheme(eType);
                }
            }
            break;

        default:
            break;
        }
    });
}

void MainWnd::Relayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_pMainPane);
    mainLayout->setMargin(0);
    setLayout(mainLayout);
}

void MainWnd::closeEvent(QCloseEvent *event)
{
    if(!m_bCloseAnimationState)
    {
        PlayCloseAnimation();
        event->ignore();
    }
    else{
        event->accept();
        exit(0);
    }
}

bool MainWnd::eventFilter(QObject *obj, QEvent *evt)
{
    switch (evt->type())
    {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseButtonDblClick:
        case QEvent::MouseMove:
        case QEvent::KeyPress:
        case QEvent::KeyRelease:
        case QEvent::Move:
        {
            m_timeMouseTrigger = QTime::currentTime();
        }
        break;
    }

    return QObject::eventFilter(obj, evt);
}

void MainWnd::PreLogin()
{
    if (DATAMGR->HasPwd())
    {
        hide();
        m_pMouseWatcher->stop();

        Login dlg;
        dlg.exec();
    }

    show();
    m_pMouseWatcher->start(1000);
}


void MainWnd::PlayCloseAnimation()
{
    setDisabled(true);
    setMinimumSize(0,0);

    QPropertyAnimation* closeAnimation = new QPropertyAnimation(this,"geometry");
    closeAnimation->setStartValue(geometry());
    closeAnimation->setEndValue(QRect(geometry().x(), geometry().y()+height()/2, width(), 0));
    closeAnimation->setDuration(500);
    m_bCloseAnimationState = true;

    closeAnimation->setEasingCurve(QEasingCurve::OutBounce);  // 缓和曲线风格

    connect(closeAnimation,SIGNAL(finished()),this,SLOT(close()));
    closeAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}
