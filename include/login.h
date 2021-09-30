#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "global.h"


class Login : public QDialog
{
    Q_OBJECT
public:
    explicit Login(QWidget *parent = 0);

private:
    GLOBAL_FUNC

private:
    QWidget *m_widgetMain;
    QLabel *m_labelLogo;
    QLabel *m_labelTitle;
    QLineEdit *m_editPwd;
    QPushButton *m_btnCancel;
    QPushButton *m_btnOk;
};

#endif // LOGIN_H
