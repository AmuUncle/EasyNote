#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include "global.h"


class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

private:
    GLOBAL_FUNC

private:
    QWidget *m_widgetMain;
    QLabel *m_labelLogo;
    QLabel *m_labelVersion;
    QPushButton *m_btnOk;
};

#endif // ABOUT_H
