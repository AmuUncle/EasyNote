#ifndef ADDFOLDER_H
#define ADDFOLDER_H

#include <QWidget>
#include "global.h"


class AddFolder : public QDialog
{
    Q_OBJECT
public:
    explicit AddFolder(QWidget *parent = 0);

    QString GetName() { return m_strName; }

private:
    GLOBAL_FUNC

private:
    QWidget *m_widgetMain;
    QLabel *m_labelTitle;
    QLineEdit *m_editName;
    QPushButton *m_btnCancel;
    QPushButton *m_btnOk;

    QString m_strName;
};

#endif // ADDFOLDER_H
