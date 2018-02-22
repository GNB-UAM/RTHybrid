/****************************************************************************
** Meta object code from reading C++ file 'rthybrid.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/rthybrid.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rthybrid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RTHybrid_t {
    QByteArrayData data[8];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RTHybrid_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RTHybrid_t qt_meta_stringdata_RTHybrid = {
    {
QT_MOC_LITERAL(0, 0, 8), // "RTHybrid"
QT_MOC_LITERAL(1, 9, 19), // "on_simulate_clicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 29), // "on_neuronModelCombo_activated"
QT_MOC_LITERAL(4, 60, 5), // "index"
QT_MOC_LITERAL(5, 66, 30), // "on_synapseModelCombo_activated"
QT_MOC_LITERAL(6, 97, 25), // "on_autocalCombo_activated"
QT_MOC_LITERAL(7, 123, 21) // "on_autoDetect_clicked"

    },
    "RTHybrid\0on_simulate_clicked\0\0"
    "on_neuronModelCombo_activated\0index\0"
    "on_synapseModelCombo_activated\0"
    "on_autocalCombo_activated\0"
    "on_autoDetect_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RTHybrid[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    1,   40,    2, 0x08 /* Private */,
       5,    1,   43,    2, 0x08 /* Private */,
       6,    1,   46,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,

       0        // eod
};

void RTHybrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RTHybrid *_t = static_cast<RTHybrid *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_simulate_clicked(); break;
        case 1: _t->on_neuronModelCombo_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_synapseModelCombo_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_autocalCombo_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_autoDetect_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject RTHybrid::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RTHybrid.data,
      qt_meta_data_RTHybrid,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RTHybrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RTHybrid::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RTHybrid.stringdata0))
        return static_cast<void*>(const_cast< RTHybrid*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int RTHybrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
