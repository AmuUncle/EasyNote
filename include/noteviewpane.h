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

private:
    GLOBAL_FUNC

    QString GetJsRetString();

public slots: // 一定要这样定义哦，否则会收不到消息
    void recieveJsMessage(const QString& jsMsg);
    void OnItemChange(int nId);

    void OnNoteChange(TNoteItem tItem);
    void OnSelGroup();

    bool eventFilter(QObject *obj, QEvent *e);

signals:
    void signalRunJsOver();

private:
    QLineEdit *m_editTitle;
    QWebEngineView *m_webView;
    QWebChannel *m_pWebChannel;

    TNoteItem m_tNoteItem;

    QWidget *m_widgetTop;
    QWidget *m_widgetMenu;
    QPushButton *m_btnMin;
    QPushButton *m_btnMax;
    QPushButton *m_btnClose;
    QPushButton *m_btnAbout;

};

#endif // NOTEVIEWPANE_H
