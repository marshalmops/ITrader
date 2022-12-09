#include "ErrorDatabaseIllegalState.h"

ErrorDatabaseIllegalState::ErrorDatabaseIllegalState()
    : ErrorDatabase{"Database data illegal state is occurred!", true}
{
    
}

ErrorType::ValueType ErrorDatabaseIllegalState::getType() const
{
    return ErrorType::Database::D_ILLEGAL_STATE;
}
