/****************************************************************************
** Meta object code from reading C++ file 'qenhancedgraphicsview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qenhancedgraphicsview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qenhancedgraphicsview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QEnhancedGraphicsView_t {
    QByteArrayData data[9];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QEnhancedGraphicsView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QEnhancedGraphicsView_t qt_meta_stringdata_QEnhancedGraphicsView = {
    {
QT_MOC_LITERAL(0, 0, 21), // "QEnhancedGraphicsView"
QT_MOC_LITERAL(1, 22, 8), // "clearAll"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 13), // "clearSelected"
QT_MOC_LITERAL(4, 46, 8), // "noEffect"
QT_MOC_LITERAL(5, 55, 10), // "blurEffect"
QT_MOC_LITERAL(6, 66, 16), // "dropShadowEffect"
QT_MOC_LITERAL(7, 83, 14), // "colorizeEffect"
QT_MOC_LITERAL(8, 98, 12) // "customEffect"

    },
    "QEnhancedGraphicsView\0clearAll\0\0"
    "clearSelected\0noEffect\0blurEffect\0"
    "dropShadowEffect\0colorizeEffect\0"
    "customEffect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QEnhancedGraphicsView[] = {

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
       1,    1,   49,    2, 0x08 /* Private */,
       3,    1,   52,    2, 0x08 /* Private */,
       4,    1,   55,    2, 0x08 /* Private */,
       5,    1,   58,    2, 0x08 /* Private */,
       6,    1,   61,    2, 0x08 /* Private */,
       7,    1,   64,    2, 0x08 /* Private */,
       8,    1,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void QEnhancedGraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QEnhancedGraphicsView *_t = static_cast<QEnhancedGraphicsView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clearAll((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->clearSelected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->noEffect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->blurEffect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->dropShadowEffect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->colorizeEffect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->customEffect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QEnhancedGraphicsView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_QEnhancedGraphicsView.data,
      qt_meta_data_QEnhancedGraphicsView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QEnhancedGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QEnhancedGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QEnhancedGraphicsView.stringdata0))
        return static_cast<void*>(const_cast< QEnhancedGraphicsView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int QEnhancedGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
