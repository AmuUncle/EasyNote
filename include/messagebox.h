#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QWidget>
#include "global.h"

class QMessageBoxEx : public QDialog
{
    Q_OBJECT
public:
    explicit QMessageBoxEx(bool bTipMode = true, QWidget *parent = 0);

    void setText(QString strText);

private:
    GLOBAL_FUNC

private:
    QWidget *m_widgetMain;
    QLabel *m_labelLogo;
    QLabel *m_labelTitle;
    QPushButton *m_btnCancel;
    QPushButton *m_btnOk;

    bool m_bTipMode;
};

#endif // MESSAGEBOX_H
