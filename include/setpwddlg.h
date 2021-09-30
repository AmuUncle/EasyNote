#ifndef SETPWDDLG_H
#define SETPWDDLG_H

#include <QWidget>
#include "global.h"

class SetPwdDlg : public QDialog
{
    Q_OBJECT
public:
    explicit SetPwdDlg(QWidget *parent = 0);

private:
    GLOBAL_FUNC

private:
    QWidget *m_widgetMain;
    QLabel *m_labelTitle;
    QLabel *m_labelPwd;
    QLineEdit *m_editPwd;
    QLabel *m_labelPwd2;
    QLineEdit *m_editPwd2;
    QPushButton *m_btnCancel;
    QPushButton *m_btnClear;
    QPushButton *m_btnOk;
};

#endif // SETPWDDLG_H
