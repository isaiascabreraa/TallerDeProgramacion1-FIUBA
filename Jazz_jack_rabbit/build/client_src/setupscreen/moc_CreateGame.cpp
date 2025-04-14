/****************************************************************************
** Meta object code from reading C++ file 'CreateGame.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../client_src/setupscreen/CreateGame.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CreateGame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CreateGame_t {
    QByteArrayData data[10];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreateGame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreateGame_t qt_meta_stringdata_CreateGame = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CreateGame"
QT_MOC_LITERAL(1, 11, 19), // "createGameRequested"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 8), // "gameName"
QT_MOC_LITERAL(4, 41, 11), // "std::string"
QT_MOC_LITERAL(5, 53, 12), // "map_selected"
QT_MOC_LITERAL(6, 66, 8), // "uint32_t"
QT_MOC_LITERAL(7, 75, 10), // "maxPlayers"
QT_MOC_LITERAL(8, 86, 21), // "std::vector<uint32_t>"
QT_MOC_LITERAL(9, 108, 6) // "cheats"

    },
    "CreateGame\0createGameRequested\0\0"
    "gameName\0std::string\0map_selected\0"
    "uint32_t\0maxPlayers\0std::vector<uint32_t>\0"
    "cheats"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreateGame[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4, 0x80000000 | 6, 0x80000000 | 8,    3,    5,    7,    9,

       0        // eod
};

void CreateGame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CreateGame *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->createGameRequested((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< const uint32_t(*)>(_a[3])),(*reinterpret_cast< const std::vector<uint32_t>(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CreateGame::*)(const QString & , const std::string & , const uint32_t & , const std::vector<uint32_t> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CreateGame::createGameRequested)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CreateGame::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CreateGame.data,
    qt_meta_data_CreateGame,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CreateGame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreateGame::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CreateGame.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CreateGame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CreateGame::createGameRequested(const QString & _t1, const std::string & _t2, const uint32_t & _t3, const std::vector<uint32_t> & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
