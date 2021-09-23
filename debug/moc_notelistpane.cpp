/****************************************************************************
** Meta object code from reading C++ file 'notelistpane.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/notelistpane.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'notelistpane.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NoteListPane_t {
    QByteArrayData data[10];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NoteListPane_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NoteListPane_t qt_meta_stringdata_NoteListPane = {
    {
QT_MOC_LITERAL(0, 0, 12), // "NoteListPane"
QT_MOC_LITERAL(1, 13, 16), // "SignalNoteChange"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 9), // "TNoteItem"
QT_MOC_LITERAL(4, 41, 5), // "tItem"
QT_MOC_LITERAL(5, 47, 14), // "SignalSelGroup"
QT_MOC_LITERAL(6, 62, 10), // "OnIdChange"
QT_MOC_LITERAL(7, 73, 3), // "nId"
QT_MOC_LITERAL(8, 77, 19), // "OnCurrentRowChanged"
QT_MOC_LITERAL(9, 97, 10) // "currentRow"

    },
    "NoteListPane\0SignalNoteChange\0\0TNoteItem\0"
    "tItem\0SignalSelGroup\0OnIdChange\0nId\0"
    "OnCurrentRowChanged\0currentRow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NoteListPane[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   38,    2, 0x08 /* Private */,
       8,    1,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void NoteListPane::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NoteListPane *_t = static_cast<NoteListPane *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalNoteChange((*reinterpret_cast< TNoteItem(*)>(_a[1]))); break;
        case 1: _t->SignalSelGroup(); break;
        case 2: _t->OnIdChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->OnCurrentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NoteListPane::*_t)(TNoteItem );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoteListPane::SignalNoteChange)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (NoteListPane::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoteListPane::SignalSelGroup)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject NoteListPane::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NoteListPane.data,
      qt_meta_data_NoteListPane,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NoteListPane::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NoteListPane::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NoteListPane.stringdata0))
        return static_cast<void*>(const_cast< NoteListPane*>(this));
    return QWidget::qt_metacast(_clname);
}

int NoteListPane::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void NoteListPane::SignalNoteChange(TNoteItem _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NoteListPane::SignalSelGroup()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
