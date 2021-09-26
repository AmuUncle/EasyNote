#ifndef MAINWND_H
#define MAINWND_H

#include <QWidget>

#include "global.h"

namespace Ui {
class MainWnd;
}

class NvrPane;
class NoteListPane;
class NoteViewPane;

class MainWnd : public QWidget
{
    Q_OBJECT

public:
    explicit MainWnd(QWidget *parent = 0);
    ~MainWnd();

private:
    GLOBAL_FUNC

    void InitMainPaneLayout();
    void PlayCloseAnimation();

    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWnd *ui;

    QWidget *m_pMainPane;
    NvrPane *m_pNvrPane;
    NoteListPane *m_pNoteListPane;
    NoteViewPane *m_pNoteViewPane;

    bool m_bCloseAnimationState;
};

#endif // MAINWND_H
