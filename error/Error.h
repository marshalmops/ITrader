#ifndef ERROR_H
#define ERROR_H

#include <string>

#include "ErrorType.h"

class Error
{
protected:
    Error(const std::string message,
          bool isCritical);
    
public:
    virtual ErrorType::ValueType getType() const = 0;
    
    const std::string& getMessage() const;
    bool isCritical() const;
    
private:
    std::string m_message;
    bool m_isCritical;
};

#endif // ERROR_H
