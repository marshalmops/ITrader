#include "Error.h"

Error::Error(const std::string message,
             bool isCritical)
    : m_message{std::move(message)},
      m_isCritical{isCritical}
{
    
}

const std::string &Error::getMessage() const
{
    return m_message;
}

bool Error::isCritical() const
{
    return m_isCritical;
}
