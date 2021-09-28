#include "mainwnd.h"
#include <QApplication>

#include "basicsdk.h"
#include "datamgr.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 10));
    a.setWindowIcon(QIcon(":/img/img/icon.png"));

    Start();
    Load(":/img/font/iconfont.ttf");

    //加载样式表
    QFile file(":/css/css/flatui.css");
    if (file.open(QFile::ReadOnly))
    {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }

    DATAMGR->Open();

    MainWnd w;
    w.show();

    return a.exec();
}
