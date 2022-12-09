#include "ErrorDatabaseInitFailed.h"

ErrorDatabaseInitFailed::ErrorDatabaseInitFailed()
    : ErrorDatabase{"Database initialization failed!", true}
{
    
}

ErrorType::ValueType ErrorDatabaseInitFailed::getType() const
{
    return ErrorType::Database::D_INIT_FAILED;
}
