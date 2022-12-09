#include "AppCore.h"

AppCore::AppCore(QObject *parent)
    : QObject{parent}
{
    
}

void AppCore::processError(std::shared_ptr<Error> error)
{
    if (error->isCritical()) {
        QMessageBox::critical(nullptr, C_CRITICAL_ERROR_MESSAGE_TITLE, error->getMessage().c_str());
        
        QCoreApplication::exit(-1);
        
    } else
        QMessageBox::warning(nullptr, C_WARNING_MESSAGE_TITLE, error->getMessage().c_str());
}

void AppCore::handleDatabaseSettingsUpdate()
{
    if (!DatabaseManager::initWithSettings())
        processError(std::make_shared<Error>(ErrorDatabaseInitFailed()));
    
}
