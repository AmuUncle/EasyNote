#ifndef BASICSDK_H
#define BASICSDK_H

#include "basicsdk_global.h"



int BASICSDKSHARED_EXPORT Add(int a, int b);

void BASICSDKSHARED_EXPORT Start();

bool BASICSDKSHARED_EXPORT Load(QString strFontPath);
void BASICSDKSHARED_EXPORT SetIcon(QLabel *label, QChar iconCode, uint dwSize = 26);
void BASICSDKSHARED_EXPORT SetIcon(QPushButton *btn, QChar iconCode, uint dwSize = 20);
void BASICSDKSHARED_EXPORT SetIcon(QPushButton *btn, QChar iconCode, const QString &strColor, uint dwSize = 20);
void BASICSDKSHARED_EXPORT SetIcon(QToolButton *btn, QChar iconCode, const QString &strColor = "#FFFFFF", uint dwIconSize = 26);
void BASICSDKSHARED_EXPORT SetIcon(QAction *action, QChar iconCode, const QString &strColor = "#000000", uint dwIconSize = 40);
void BASICSDKSHARED_EXPORT SetIcon(QLabel *label, const QString &strMainIcon = "", const QString &strSecIcon = "", const QString &strThirdIcon = "", uint dwIconSize = 24);
void BASICSDKSHARED_EXPORT SetIcon(QStandardItem *item, QChar iconCode, uint dwSize = 26);

#endif // BASICSDK_H
