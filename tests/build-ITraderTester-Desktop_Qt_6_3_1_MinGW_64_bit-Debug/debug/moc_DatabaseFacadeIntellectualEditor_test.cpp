/****************************************************************************
** Meta object code from reading C++ file 'DatabaseFacadeIntellectualEditor_test.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ITraderTester/database/DatabaseFacadeIntellectualEditor_test.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DatabaseFacadeIntellectualEditor_test.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DatabaseFacadeIntellectualEditor_test_t {
    const uint offsetsAndSize[10];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_DatabaseFacadeIntellectualEditor_test_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_DatabaseFacadeIntellectualEditor_test_t qt_meta_stringdata_DatabaseFacadeIntellectualEditor_test = {
    {
QT_MOC_LITERAL(0, 37), // "DatabaseFacadeIntellectualEdi..."
QT_MOC_LITERAL(38, 12), // "initTestCase"
QT_MOC_LITERAL(51, 0), // ""
QT_MOC_LITERAL(52, 23), // "checkPatternInsert_test"
QT_MOC_LITERAL(76, 23) // "checkPatternDelete_test"

    },
    "DatabaseFacadeIntellectualEditor_test\0"
    "initTestCase\0\0checkPatternInsert_test\0"
    "checkPatternDelete_test"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DatabaseFacadeIntellectualEditor_test[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x08,    1 /* Private */,
       3,    0,   33,    2, 0x08,    2 /* Private */,
       4,    0,   34,    2, 0x08,    3 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DatabaseFacadeIntellectualEditor_test::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DatabaseFacadeIntellectualEditor_test *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->checkPatternInsert_test(); break;
        case 2: _t->checkPatternDelete_test(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject DatabaseFacadeIntellectualEditor_test::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DatabaseFacadeIntellectualEditor_test.offsetsAndSize,
    qt_meta_data_DatabaseFacadeIntellectualEditor_test,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_DatabaseFacadeIntellectualEditor_test_t
, QtPrivate::TypeAndForceComplete<DatabaseFacadeIntellectualEditor_test, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *DatabaseFacadeIntellectualEditor_test::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DatabaseFacadeIntellectualEditor_test::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DatabaseFacadeIntellectualEditor_test.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DatabaseFacadeIntellectualEditor_test::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
