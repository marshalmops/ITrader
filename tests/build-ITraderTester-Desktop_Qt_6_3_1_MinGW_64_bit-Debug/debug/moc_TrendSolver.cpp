/****************************************************************************
** Meta object code from reading C++ file 'TrendSolver.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../TrendSolver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrendSolver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TrendSolver_t {
    const uint offsetsAndSize[34];
    char stringdata0[278];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_TrendSolver_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_TrendSolver_t qt_meta_stringdata_TrendSolver = {
    {
QT_MOC_LITERAL(0, 11), // "TrendSolver"
QT_MOC_LITERAL(12, 13), // "errorOccurred"
QT_MOC_LITERAL(26, 0), // ""
QT_MOC_LITERAL(27, 28), // "std::shared_ptr<ErrorSolver>"
QT_MOC_LITERAL(56, 5), // "error"
QT_MOC_LITERAL(62, 13), // "trendDetected"
QT_MOC_LITERAL(76, 25), // "TrendSolverContext::Trend"
QT_MOC_LITERAL(102, 5), // "trend"
QT_MOC_LITERAL(108, 13), // "patternGotten"
QT_MOC_LITERAL(122, 24), // "std::shared_ptr<Pattern>"
QT_MOC_LITERAL(147, 7), // "pattern"
QT_MOC_LITERAL(155, 17), // "finalLinesChoosen"
QT_MOC_LITERAL(173, 35), // "std::shared_ptr<StageLineCont..."
QT_MOC_LITERAL(209, 12), // "choosenLines"
QT_MOC_LITERAL(222, 11), // "analyseDots"
QT_MOC_LITERAL(234, 33), // "std::vector<std::shared_ptr<D..."
QT_MOC_LITERAL(268, 9) // "inputDots"

    },
    "TrendSolver\0errorOccurred\0\0"
    "std::shared_ptr<ErrorSolver>\0error\0"
    "trendDetected\0TrendSolverContext::Trend\0"
    "trend\0patternGotten\0std::shared_ptr<Pattern>\0"
    "pattern\0finalLinesChoosen\0"
    "std::shared_ptr<StageLineContainer>\0"
    "choosenLines\0analyseDots\0"
    "std::vector<std::shared_ptr<Dot>>\0"
    "inputDots"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TrendSolver[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,    1 /* Public */,
       5,    1,   47,    2, 0x06,    3 /* Public */,
       8,    1,   50,    2, 0x06,    5 /* Public */,
      11,    1,   53,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      14,    1,   56,    2, 0x0a,    9 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

void TrendSolver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TrendSolver *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<ErrorSolver>>>(_a[1]))); break;
        case 1: _t->trendDetected((*reinterpret_cast< std::add_pointer_t<TrendSolverContext::Trend>>(_a[1]))); break;
        case 2: _t->patternGotten((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Pattern>>>(_a[1]))); break;
        case 3: _t->finalLinesChoosen((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<StageLineContainer>>>(_a[1]))); break;
        case 4: _t->analyseDots((*reinterpret_cast< std::add_pointer_t<std::vector<std::shared_ptr<Dot>>>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TrendSolver::*)(const std::shared_ptr<ErrorSolver> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrendSolver::errorOccurred)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TrendSolver::*)(const TrendSolverContext::Trend );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrendSolver::trendDetected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TrendSolver::*)(const std::shared_ptr<Pattern> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrendSolver::patternGotten)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TrendSolver::*)(const std::shared_ptr<StageLineContainer> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrendSolver::finalLinesChoosen)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject TrendSolver::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TrendSolver.offsetsAndSize,
    qt_meta_data_TrendSolver,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_TrendSolver_t
, QtPrivate::TypeAndForceComplete<TrendSolver, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::shared_ptr<ErrorSolver>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const TrendSolverContext::Trend, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::shared_ptr<Pattern>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::shared_ptr<StageLineContainer>, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::vector<std::shared_ptr<Dot>>, std::false_type>


>,
    nullptr
} };


const QMetaObject *TrendSolver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrendSolver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TrendSolver.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TrendSolver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void TrendSolver::errorOccurred(const std::shared_ptr<ErrorSolver> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TrendSolver::trendDetected(const TrendSolverContext::Trend _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TrendSolver::patternGotten(const std::shared_ptr<Pattern> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TrendSolver::finalLinesChoosen(const std::shared_ptr<StageLineContainer> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
