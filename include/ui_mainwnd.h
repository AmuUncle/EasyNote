/********************************************************************************
** Form generated from reading UI file 'mainwnd.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWND_H
#define UI_MAINWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWnd
{
public:

    void setupUi(QWidget *MainWnd)
    {
        if (MainWnd->objectName().isEmpty())
            MainWnd->setObjectName(QStringLiteral("MainWnd"));
        MainWnd->resize(400, 300);

        retranslateUi(MainWnd);

        QMetaObject::connectSlotsByName(MainWnd);
    } // setupUi

    void retranslateUi(QWidget *MainWnd)
    {
        MainWnd->setWindowTitle(QApplication::translate("MainWnd", "MainWnd", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWnd: public Ui_MainWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWND_H
