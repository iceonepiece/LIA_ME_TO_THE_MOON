/****************************************************************************
** Meta object code from reading C++ file 'PatientView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PatientView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PatientView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PatientView_t {
    QByteArrayData data[13];
    char stringdata[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PatientView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PatientView_t qt_meta_stringdata_PatientView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "PatientView"
QT_MOC_LITERAL(1, 12, 10), // "updateView"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 9), // "groupType"
QT_MOC_LITERAL(4, 34, 5), // "index"
QT_MOC_LITERAL(5, 40, 11), // "enterFolder"
QT_MOC_LITERAL(6, 52, 3), // "row"
QT_MOC_LITERAL(7, 56, 3), // "col"
QT_MOC_LITERAL(8, 60, 12), // "deleteFolder"
QT_MOC_LITERAL(9, 73, 6), // "goHome"
QT_MOC_LITERAL(10, 80, 19), // "showNewFolderDialog"
QT_MOC_LITERAL(11, 100, 6), // "search"
QT_MOC_LITERAL(12, 107, 7) // "keyword"

    },
    "PatientView\0updateView\0\0groupType\0"
    "index\0enterFolder\0row\0col\0deleteFolder\0"
    "goHome\0showNewFolderDialog\0search\0"
    "keyword"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PatientView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    1,   50,    2, 0x08 /* Private */,
       5,    2,   53,    2, 0x08 /* Private */,
       8,    0,   58,    2, 0x08 /* Private */,
       9,    0,   59,    2, 0x08 /* Private */,
      10,    0,   60,    2, 0x08 /* Private */,
      11,    1,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,

       0        // eod
};

void PatientView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PatientView *_t = static_cast<PatientView *>(_o);
        switch (_id) {
        case 0: _t->updateView(); break;
        case 1: _t->groupType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->enterFolder((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->deleteFolder(); break;
        case 4: _t->goHome(); break;
        case 5: _t->showNewFolderDialog(); break;
        case 6: _t->search((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject PatientView::staticMetaObject = {
    { &View::staticMetaObject, qt_meta_stringdata_PatientView.data,
      qt_meta_data_PatientView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PatientView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PatientView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PatientView.stringdata))
        return static_cast<void*>(const_cast< PatientView*>(this));
    return View::qt_metacast(_clname);
}

int PatientView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = View::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
