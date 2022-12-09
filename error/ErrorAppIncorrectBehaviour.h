#ifndef ERRORAPPINVALIDBEHAVIOUR_H
#define ERRORAPPINVALIDBEHAVIOUR_H

#include "ErrorApp.h"

class ErrorAppIncorrectBehaviour : public ErrorApp
{
public:
    ErrorAppIncorrectBehaviour();
    
    ErrorType::ValueType getType() const override;
};

#endif // ERRORAPPINVALIDBEHAVIOUR_H
