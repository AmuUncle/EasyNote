#ifndef GLOBAL_H
#define GLOBAL_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QtWidgets>

#include <QVBoxLayout>

#include <QDebug>
#include <QtWidgets>
#include <QPainter>
#include <QMouseEvent>

#include "basicsdk.h"

#define VERSION "v1.0"
#define AUTHOR "阿木大叔"
#define MAIL "hudejie2018@163.com"
#define MAX_OUTPUT_SIZE 1024
#define PRJ_NAME "EasyNote"

#define GLOBAL_FUNC \
        void CreateAllChildWnd(); \
        void InitCtrl(); \
        void InitSolts(); \
        void Relayout();

#define GLOBAL_FUNC_RUN \
        CreateAllChildWnd(); \
        InitCtrl(); \
        InitSolts(); \
        Relayout();

#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }


#define CANMOVE setProperty("canMove", "true");

enum NavItem
{
    DEFAULT = 0,
    RECENT = 10000,
    FAVORITES,
    DELETED,
};

enum ItemType
{
    GROUPS = 0,
    NOTE = 1
};

enum MenuType
{
    MENUTYPE_MIN = 0,
    MENUTYPE_MAX,
    MENUTYPE_ABOUT,
    MENUTYPE_CLOSE,
    MENUTYPE_SETPWD,
    MENUITEM_THEME_DEFAULT = 100,
    MENUITEM_THEME_FLATUI,
    MENUITEM_THEME_PS,
    MENUITEM_THEME_SIPMPLE,
};

struct TUserCustomItem
{
    int nId;
    QString strName;
};

struct TNoteItem
{
    int nId;
    int nFId;
    QString strTitle;
    QString strContent;
    QString strContentSrc;
    QString strTime;
    bool bFavorited;
};


int MessageBoxExt(QString strText);
int MessageBoxTip(QString strText);

#endif // GLOBAL_H
