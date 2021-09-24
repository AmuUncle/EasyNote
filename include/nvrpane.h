#ifndef NVRPANE_H
#define NVRPANE_H

#include <QWidget>

#include "global.h"

class NvrPane : public QWidget
{
    Q_OBJECT
public:
    explicit NvrPane(QWidget *parent = 0);

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
