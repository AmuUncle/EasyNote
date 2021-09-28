#ifndef NVRPANE_H
#define NVRPANE_H

#include <QWidget>

#include "global.h"

class NavPane : public QWidget
{
    Q_OBJECT
public:
    explicit NavPane(QWidget *parent = 0);

private:
    GLOBAL_FUNC

private slots:
    void OnItemClicked(QListWidgetItem *item);

    void AddItem(QListWidgetItem *item, QString strName, QChar icon);
    void OnBtnNewClicked();

signals:
    void SignalIDChange(int nId);
    void SignalNewNote();

private:
    QLabel *m_labelLogo;
    QPushButton *m_btnNewNote;
    QListWidget *m_listNav;
};

#endif // NVRPANE_H
