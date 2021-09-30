#include "mainwnd.h"
#include <QApplication>

#include "basicsdk.h"
#include "datamgr.h"
#include "messagebox.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 10));
    a.setWindowIcon(QIcon(":/img/img/icon.png"));

    QApplication::setQuitOnLastWindowClosed(false);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    DATAMGR->Open();
    Start();
    Load(":/img/font/iconfont.ttf");

    MenuType eTheme = DATAMGR->GetTheme();
    switch (eTheme) {
    case MENUITEM_THEME_DEFAULT:
        {
            QFile file(":/css/css/youdao.css");
            if (file.open(QFile::ReadOnly))
            {
                QString qss = QLatin1String(file.readAll());
                QString paletteColor = qss.mid(20, 7);
                qApp->setPalette(QPalette(QColor(paletteColor)));
                qApp->setStyleSheet(qss);
                file.close();
            }
        }
        break;

    case MENUITEM_THEME_FLATUI:
        {
            QFile file(":/css/css/flatui.css");
            if (file.open(QFile::ReadOnly))
            {
                QString qss = QLatin1String(file.readAll());
                QString paletteColor = qss.mid(20, 7);
                qApp->setPalette(QPalette(QColor(paletteColor)));
                qApp->setStyleSheet(qss);
                file.close();
            }
        }
        break;

    case MENUITEM_THEME_PS:
        {
            QFile file(":/css/css/ps.css");
            if (file.open(QFile::ReadOnly))
            {
                QString qss = QLatin1String(file.readAll());
                QString paletteColor = qss.mid(20, 7);
                qApp->setPalette(QPalette(QColor(paletteColor)));
                qApp->setStyleSheet(qss);
                file.close();
            }
        }
        break;

    case MENUITEM_THEME_SIPMPLE:
        {
            QFile file(":/css/css/simple.css");
            if (file.open(QFile::ReadOnly))
            {
                QString qss = QLatin1String(file.readAll());
                QString paletteColor = qss.mid(20, 7);
                qApp->setPalette(QPalette(QColor(paletteColor)));
                qApp->setStyleSheet(qss);
                file.close();
            }
        }
        break;

    default:
        break;
    }

    MainWnd w;
    w.hide();
    w.PreLogin();

    return a.exec();
}

int MessageBoxExt(QString strText)
{
    QMessageBoxEx msg(false);
    msg.setText(strText);
    return msg.exec();
}

int MessageBoxTip(QString strText)
{
    QMessageBoxEx msg;
    msg.setText(strText);
    return msg.exec();
}
