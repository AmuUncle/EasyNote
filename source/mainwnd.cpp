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

    connect(m_pNoteListPane, SIGNAL(SignalNoteChange(TNoteItem)), m_pNoteViewPane, SLOT(OnNoteChange(TNoteItem)));
    connect(m_pNoteListPane, SIGNAL(SignalSelGroup()), m_pNoteViewPane, SLOT(OnSelGroup()));
}

void MainWnd::Relayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_pMainPane);
    mainLayout->setMargin(10);
    setLayout(mainLayout);
}
