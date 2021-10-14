#ifndef UNLOCKTOOL_H
#define UNLOCKTOOL_H

#include <QWidget>
#include "global.h"

const int POINT_NUM = 9;

class UnlockTool : public QDialog
{
    Q_OBJECT
public:
    explicit UnlockTool(bool bUnlockMode = true, QWidget *parent = 0);

    void Clear() { m_dwPassword = 0; }
    uint GetPwd() { return m_dwPassword; }
    void EnableUnlockMode(bool bUnlockMode) { m_bUnlockMode = bUnlockMode; }

private:
    void paintEvent(QPaintEvent *event);
    void paintLookPane(QPainter *painter, QRect rcArec);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    GLOBAL_FUNC

signals:
    void SignalPwdChange(uint dwPassword);

private:
    uint m_dwPassword;
    bool m_bMousePress;
    QPoint m_aptCenter[POINT_NUM];
    bool m_bUnlockMode;

    QPoint m_ptMouseMove;

    QPushButton *m_btnCancel;
    QPushButton *m_btnClear;
    QPushButton *m_btnOk;
};

#endif // UNLOCKTOOL_H
