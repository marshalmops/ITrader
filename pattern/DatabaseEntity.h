#ifndef DATABASEENTITY_H
#define DATABASEENTITY_H

#include <QVector>
#include <QHash>
#include <QVariant>

class DatabaseEntity {
protected:
//    template<class T>
//    static bool getValueByVariant(const QVariant &variant, 
//                                  std::unique_ptr<T> &value)
//    {
//        if (!variant.isValid()) return false;
        
//        bool convFlag{true};
//        T    rawValue{};
        
//        switch (variant.typeId()) {
//        case QMetaType::Type::UChar:
//        case QMetaType::Type::Int: {
//            rawValue = variant.toInt(&convFlag); break;
//        }
//        case QMetaType::Type::ULong:
//        case QMetaType::Type::ULongLong: {
//            rawValue = variant.toULongLong(&convFlag); break;
//        }
//        case QMetaType::Type::Float: {
//            rawValue = variant.toFloat(&convFlag); break;
//        }
//        case QMetaType::Type::Double: {
//            rawValue = variant.toDouble(&convFlag); break;
//        }
//        case QMetaType::Type::QString: {
//            rawValue = variant.toString(); break;
//        }
//        default: return false;
//        }
        
//        if (!convFlag) return false;
        
//        value = std::make_unique<T>(std::move(value));
        
//        return true;
//    }
    
public:
    virtual bool fillWithVariantsHash(const QHash<QString, QVariant> &stringVariantHash) = 0;
};

#endif // DATABASEENTITY_H
