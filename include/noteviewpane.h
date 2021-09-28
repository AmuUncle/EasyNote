#ifndef NOTEVIEWPANE_H
#define NOTEVIEWPANE_H

#include <QWidget>
#include <QtWebEngineWidgets>

#include "global.h"
#include "datamgr.h"

class NoteViewPane : public QWidget
{
    Q_OBJECT
public:
    explicit NoteViewPane(QWidget *parent = 0);
    ~NoteViewPane();

public:
    QString GetTitle() { return m_editTitle->text(); }

private:
    GLOBAL_FUNC

    void UpdateLayout();

    QString GetJsRetString();

public slots: // 一定要这样定义哦，否则会收不到消息
    void recieveJsMessage(const QString& jsBase64Msg, const QString& jsMsg);
    void OnItemChange(int nId);

    void OnNoteChange(TNoteItem tItem);
    void OnSelGroup();
    void OnTitleChange(const QString &strTitle);
    void OnBtnMoreClicked();
    void OnMenuTriggered(QAction*);

    bool eventFilter(QObject *obj, QEvent *e);

signals:
    void signalRunJsOver();
    void signalTitleChange(QString strTitle);
    void SignalMenuClicked(MenuType eType);

private:
    QLineEdit *m_editTitle;
    QWebEngineView *m_webView;
    QWebChannel *m_pWebChannel;

    TNoteItem m_tNoteItem;

    QWidget *m_widgetMenu;
    QPushButton *m_btnMin;
    QPushButton *m_btnMax;
    QPushButton *m_btnClose;
    QPushButton *m_btnAbout;

    QWidget *m_widgetEmpty;
};

#endif // NOTEVIEWPANE_H
