#include "ErrorAppIncorrectBehaviour.h"

ErrorAppIncorrectBehaviour::ErrorAppIncorrectBehaviour()
    : ErrorApp{"Incorrect app behaviour has been occurred!", true}
{
    
}

ErrorType::ValueType ErrorAppIncorrectBehaviour::getType() const
{
    return ErrorType::App::A_INCORRECT_BEHAVIOUR;
}
