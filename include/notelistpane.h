#ifndef NOTELISTPANE_H
#define NOTELISTPANE_H

#include <QWidget>

#include "global.h"

class NoteListPane : public QWidget
{
    Q_OBJECT
public:
    explicit NoteListPane(QWidget *parent = 0);

public:
    void EnableGroupMode(bool bMode) { m_bGroupMode = bMode; }

private:
    GLOBAL_FUNC

    void AddItem(QListWidgetItem *item, QString strName, QChar icon, QString strTime);
    void UpdateCtrlStatus();

private slots:
    void OnIdChange(int nId);
    void OnCurrentRowChanged(int currentRow);
    void OnItemDoubleClicked(QListWidgetItem *item);
    void OnBtnBackClicked();
    void OnBtnAddFolderClicked();
    void OnBtnClearClicked();

    void OnTitleChange(const QString &strTitle);
    void OnUpdateList();
    void OnAddNewNote();

    void OnListChange();

    void Serach(const QString &key);

signals:
    void SignalNoteChange(TNoteItem tItem);
    void SignalSelGroup();

private:
    QPushButton *m_btnBack;
    QLineEdit *m_editSearch;
    QPushButton *m_btnAddFolder;
    QPushButton *m_btnClear;

    QListWidget *m_listNoteItems;

    int m_nId;
    bool m_bGroupMode;
};

#endif // NOTELISTPANE_H
