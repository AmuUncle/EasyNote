#include "mainwnd.h"
#include "ui_mainwnd.h"

#include "nvrpane.h"
#include "notelistpane.h"
#include "noteviewpane.h"


MainWnd::MainWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWnd)
{
    ui->setupUi(this);

    m_pMainPane = NULL;
    m_pNvrPane = NULL;
    m_pNoteListPane = NULL;
    m_pNoteViewPane = NULL;

    GLOBAL_FUNC_RUN

    InitMainPaneLayout();
}

MainWnd::~MainWnd()
{
    delete ui;
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
    NEW_OBJECT(m_pNvrPane, NvrPane);
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
}

void MainWnd::InitSolts()
{
    connect(m_pNvrPane, SIGNAL(SignalIDChange(int)), m_pNoteListPane, SLOT(OnIdChange(int)));
    connect(m_pNvrPane, &NvrPane::SignalIDChange, [=](int id) {
        m_pNoteListPane->EnableGroupMode(id == DEFAULT);
    });

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

            break;

        case MENUTYPE_CLOSE:
            close();
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
