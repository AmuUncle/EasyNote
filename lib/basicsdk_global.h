#ifndef BASICSDK_GLOBAL_H
#define BASICSDKL_GLOBAL_H

#include <QtCore/qglobal.h>

#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QAction>
#include <QStandardItem>

#if defined(BASICSDK_LIBRARY)
#  define BASICSDKSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BASICSDKSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BASICSDK_GLOBAL_H
