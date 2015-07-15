/****************************************************************************
** Meta object code from reading C++ file 'HomeView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../HomeView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HomeView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HomeView_t {
    QByteArrayData data[11];
    char stringdata[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HomeView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HomeView_t qt_meta_stringdata_HomeView = {
    {
QT_MOC_LITERAL(0, 0, 8), // "HomeView"
QT_MOC_LITERAL(1, 9, 10), // "updateView"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 20), // "showNewPatientDialog"
QT_MOC_LITERAL(4, 42, 21), // "showOpenPatientDialog"
QT_MOC_LITERAL(5, 64, 13), // "deletePatient"
QT_MOC_LITERAL(6, 78, 12), // "enterPatient"
QT_MOC_LITERAL(7, 91, 3), // "row"
QT_MOC_LITERAL(8, 95, 3), // "col"
QT_MOC_LITERAL(9, 99, 6), // "search"
QT_MOC_LITERAL(10, 106, 7) // "keyword"

    },
    "HomeView\0updateView\0\0showNewPatientDialog\0"
    "showOpenPatientDialog\0deletePatient\0"
    "enterPatient\0row\0col\0search\0keyword"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HomeView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    2,   48,    2, 0x08 /* Private */,
       9,    1,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void HomeView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HomeView *_t = static_cast<HomeView *>(_o);
        switch (_id) {
        case 0: _t->updateView(); break;
        case 1: _t->showNewPatientDialog(); break;
        case 2: _t->showOpenPatientDialog(); break;
        case 3: _t->deletePatient(); break;
        case 4: _t->enterPatient((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->search((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject HomeView::staticMetaObject = {
    { &View::staticMetaObject, qt_meta_stringdata_HomeView.data,
      qt_meta_data_HomeView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HomeView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HomeView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HomeView.stringdata))
        return static_cast<void*>(const_cast< HomeView*>(this));
    return View::qt_metacast(_clname);
}

int HomeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = View::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
