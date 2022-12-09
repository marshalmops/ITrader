#include "DatabaseQueryProcessorFabric.h"

bool DatabaseQueryProcessorFabric::createQueryProcessorWithSettings(const std::shared_ptr<DatabaseSettings> &dbSettings,
                                                                    std::unique_ptr<DatabaseDriver> &&dbDriver,
                                                                    std::unique_ptr<DatabaseQueryProcessor> &queryProcessor)
{
    DatabaseContext::Type dbType{dbSettings->getDatabaseType()};
    
    if (!DatabaseContext::checkDatabaseTypeValidity(dbType))
        return false;
    
    std::unique_ptr<DatabaseQueryProcessor> queryProcessorBuffer{};
    
    switch (dbType) {
    case DatabaseContext::Type::T_ODBC:
    case DatabaseContext::Type::T_SQLITE:
        queryProcessorBuffer = createQueryProcessorStandard(dbDriver);
    default: return false;
    }
    
    if (!queryProcessorBuffer.get())
        return false;
    
    queryProcessor = std::unique_ptr<DatabaseQueryProcessor>{queryProcessorBuffer.release()};
    
    return true;
}

std::unique_ptr<DatabaseQueryProcessor>&& DatabaseQueryProcessorFabric::createQueryProcessorStandard(std::unique_ptr<DatabaseDriver> &dbDriver)
{
    return std::make_unique<DatabaseQueryProcessor>(DatabaseQueryProcessor{std::move(dbDriver)});
}
