#ifndef MAINWND_H
#define MAINWND_H

#include <QWidget>

#include "global.h"


class NavPane;
class NoteListPane;
class NoteViewPane;
class UnlockTool;

class MainWnd : public QWidget
{
    Q_OBJECT

public:
    explicit MainWnd(QWidget *parent = 0);
    ~MainWnd();

public:
    void PreLogin();

private:
    GLOBAL_FUNC

    void InitMainPaneLayout();
    void PlayCloseAnimation();

    void closeEvent(QCloseEvent *event);

protected:
    bool eventFilter(QObject *obj, QEvent *evt);

private:
    QWidget *m_pMainPane;
    NavPane *m_pNvrPane;
    NoteListPane *m_pNoteListPane;
    NoteViewPane *m_pNoteViewPane;
    UnlockTool *m_pUnlockdlg;

    bool m_bCloseAnimationState;

    QTimer *m_pMouseWatcher;
    QTime m_timeMouseTrigger;
};

#endif // MAINWND_H
