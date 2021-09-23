#ifndef NOTELISTPANE_H
#define NOTELISTPANE_H

#include <QWidget>

#include "global.h"

class NoteListPane : public QWidget
{
    Q_OBJECT
public:
    explicit NoteListPane(QWidget *parent = 0);

private:
    GLOBAL_FUNC

    void AddItem(QListWidgetItem *item, QString strName, QChar icon, QString strTime);

private slots:
    void OnIdChange(int nId);
    void OnCurrentRowChanged(int currentRow);

signals:
    void SignalNoteChange(TNoteItem tItem);
    void SignalSelGroup();

private:
    QPushButton *m_btnBack;
    QLineEdit *m_editSearch;

    QListWidget *m_listNoteItems;
};

#endif // NOTELISTPANE_H
