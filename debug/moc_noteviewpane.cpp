/****************************************************************************
** Meta object code from reading C++ file 'noteviewpane.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/noteviewpane.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'noteviewpane.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NoteViewPane_t {
    QByteArrayData data[15];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NoteViewPane_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NoteViewPane_t qt_meta_stringdata_NoteViewPane = {
    {
QT_MOC_LITERAL(0, 0, 12), // "NoteViewPane"
QT_MOC_LITERAL(1, 13, 15), // "signalRunJsOver"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 16), // "recieveJsMessage"
QT_MOC_LITERAL(4, 47, 5), // "jsMsg"
QT_MOC_LITERAL(5, 53, 12), // "OnItemChange"
QT_MOC_LITERAL(6, 66, 3), // "nId"
QT_MOC_LITERAL(7, 70, 12), // "OnNoteChange"
QT_MOC_LITERAL(8, 83, 9), // "TNoteItem"
QT_MOC_LITERAL(9, 93, 5), // "tItem"
QT_MOC_LITERAL(10, 99, 10), // "OnSelGroup"
QT_MOC_LITERAL(11, 110, 11), // "eventFilter"
QT_MOC_LITERAL(12, 122, 3), // "obj"
QT_MOC_LITERAL(13, 126, 7), // "QEvent*"
QT_MOC_LITERAL(14, 134, 1) // "e"

    },
    "NoteViewPane\0signalRunJsOver\0\0"
    "recieveJsMessage\0jsMsg\0OnItemChange\0"
    "nId\0OnNoteChange\0TNoteItem\0tItem\0"
    "OnSelGroup\0eventFilter\0obj\0QEvent*\0e"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NoteViewPane[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   45,    2, 0x0a /* Public */,
       5,    1,   48,    2, 0x0a /* Public */,
       7,    1,   51,    2, 0x0a /* Public */,
      10,    0,   54,    2, 0x0a /* Public */,
      11,    2,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 13,   12,   14,

       0        // eod
};

void NoteViewPane::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NoteViewPane *_t = static_cast<NoteViewPane *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalRunJsOver(); break;
        case 1: _t->recieveJsMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->OnItemChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->OnNoteChange((*reinterpret_cast< TNoteItem(*)>(_a[1]))); break;
        case 4: _t->OnSelGroup(); break;
        case 5: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NoteViewPane::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoteViewPane::signalRunJsOver)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject NoteViewPane::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NoteViewPane.data,
      qt_meta_data_NoteViewPane,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NoteViewPane::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NoteViewPane::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NoteViewPane.stringdata0))
        return static_cast<void*>(const_cast< NoteViewPane*>(this));
    return QWidget::qt_metacast(_clname);
}

int NoteViewPane::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void NoteViewPane::signalRunJsOver()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
