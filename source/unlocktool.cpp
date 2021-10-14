#include "unlocktool.h"
#include "datamgr.h"

const int POINT_RADIUS = 40;

UnlockTool::UnlockTool(bool bUnlockMode, QWidget *parent) : QDialog(parent)
{
    m_dwPassword = 0;
    m_bMousePress = false;
    m_btnOk = NULL;
    m_btnClear = NULL;
    m_btnCancel = NULL;
    m_bUnlockMode = bUnlockMode;

    setWindowFlags(windowFlags() | (Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::Dialog));
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式

    setFixedSize(430, 500);

    GLOBAL_FUNC_RUN
}

void UnlockTool::CreateAllChildWnd()
{
    NEW_OBJECT(m_btnOk, QPushButton);
    NEW_OBJECT(m_btnClear, QPushButton);
    NEW_OBJECT(m_btnCancel, QPushButton);
}

void UnlockTool::InitCtrl()
{
    setProperty("form", "About");

    m_btnCancel->setFixedSize(100, 30);
    m_btnCancel->setText(tr("取消"));
    m_btnCancel->setProperty("default_btn", true);

    m_btnOk->setFixedSize(100, 30);
    m_btnOk->setText(tr("确认"));
    m_btnOk->setProperty("default_btn", true);

    m_btnClear->setFixedSize(100, 30);
    m_btnClear->setText(tr("清除密码"));
    m_btnClear->setProperty("default_btn", true);

    m_btnOk->setDefault(true);

    m_btnClear->setVisible(false);
    m_btnOk->setVisible(!m_bUnlockMode);
}

void UnlockTool::InitSolts()
{
    connect(m_btnOk, &QPushButton::clicked, [=]()
    {
        accept();
    });

    connect(m_btnCancel, &QPushButton::clicked, [=]()
    {
        if (m_bUnlockMode)
            exit(0);

        reject();
    });
}

void UnlockTool::Relayout()
{
    QHBoxLayout *btnHLayout = new QHBoxLayout();
    btnHLayout->addStretch();
    btnHLayout->addWidget(m_btnCancel);
    btnHLayout->addWidget(m_btnClear);
    btnHLayout->addWidget(m_btnOk);
    btnHLayout->addStretch();


    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->addStretch();
    layoutMain->addLayout(btnHLayout);
    layoutMain->setMargin(30);
    setLayout(layoutMain);
}


void UnlockTool::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);         // 创建画家对象
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, true); // 抗锯齿和使用平滑转换算法

    QRect rcClient = rect();
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#313139"));
    painter.drawRoundedRect(rcClient, 5, 5);

    QRect rcArec = rcClient;
    rcArec.setTop(rcArec.bottom() - rcArec.width() + 1);
    paintLookPane(&painter, rcArec);
}

void UnlockTool::paintLookPane(QPainter *painter, QRect rcArec)
{
    // 原点、比例转换
    QRect rcBase = rcArec;

    const int POINT_BORDER = 5;
    const int POINT_DIAMETER = POINT_RADIUS * 2;
    const int POINT_MARGIN = (rcBase.width() - POINT_DIAMETER * 3) / 4;

    QColor boderColor("#3A3A3A");
    QColor clockDialColor("#212126");
    QColor clockSel("#fbd35a");

    QString area = QString::number(m_dwPassword);
    int nLen = area.length();
    int anWord[9] = {0};

    for (int i = 0; i < nLen; i++)
    {
       anWord[i] = QString(area.at(i)).toInt();
    }

    int nIndex = 0;
    for (int j = 0; j < 3; j++)
    {
       for (int i = 0; i < 3; i++)
       {
           QPoint ptCenter;
           ptCenter.setX(POINT_MARGIN * (i + 1) + POINT_RADIUS + POINT_DIAMETER * i);
           ptCenter.setY(POINT_MARGIN * (j + 1) + POINT_RADIUS + POINT_DIAMETER * j);

           m_aptCenter[nIndex++] = ptCenter;

           painter->save();
           painter->setPen(Qt::NoPen);
           painter->setBrush(boderColor);
           painter->drawEllipse(ptCenter, POINT_RADIUS, POINT_RADIUS);
           painter->setBrush(clockDialColor);
           painter->drawEllipse(ptCenter, POINT_RADIUS - POINT_BORDER, POINT_RADIUS - POINT_BORDER);

           for (int k = 0; k < nLen; k++)
           {
               if (anWord[k] == (3 * j) + (i + 1))
               {
                   painter->setBrush(clockSel);
                   painter->drawEllipse(ptCenter, POINT_RADIUS / 2, POINT_RADIUS / 2);
               }
           }

           painter->restore();
       }
    }

    painter->save();
    painter->setPen(QPen(clockSel, 4));

    QPoint points[10];

    for (int i = 0; i < nLen; i++)
    {
       points[i] = m_aptCenter[anWord[i] - 1];
    }

    if (m_bMousePress)
    {
       points[nLen] = m_ptMouseMove;
       nLen++;
    }

    painter->drawPolyline(points, nLen);

    painter->restore();
}

void UnlockTool::mousePressEvent(QMouseEvent *event)
{
    for(int i = 0; i < 9; i++)
    {
        QPoint pt1 = m_aptCenter[i];
        QPoint pt2 = event->pos();

        double c = qPow(qPow(pt1.x()-pt2.x(), 2)+qPow(pt1.y()-pt2.y(), 2),0.5);

        if (c <= POINT_RADIUS)
        {
            m_bMousePress = true;
            m_dwPassword = i + 1;
            m_ptMouseMove = event->pos();

            update();
            break;
        }
    }
}

void UnlockTool::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_bMousePress)
        return;

    m_ptMouseMove = event->pos();

    for(int i = 0; i < 9; i++)
    {
        QPoint pt1 = m_aptCenter[i];
        QPoint pt2 = event->pos();

        double c = qPow(qPow(pt1.x()-pt2.x(), 2)+qPow(pt1.y()-pt2.y(), 2),0.5);

        if (c <= POINT_RADIUS)
        {
            m_bMousePress = true;

            QString strNums = QString::number(m_dwPassword);

            if (strNums.contains(QString::number(i + 1)))
                continue;

            m_dwPassword = m_dwPassword * 10 + (i + 1);
            break;
        }
    }

    update();
}

void UnlockTool::mouseReleaseEvent(QMouseEvent *event)
{
    m_bMousePress = false;
    update();

    if (m_dwPassword > 0)
        emit SignalPwdChange(m_dwPassword);
}
