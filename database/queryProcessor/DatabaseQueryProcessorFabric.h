#ifndef DATABASEQUERYPROCESSORFABRIC_H
#define DATABASEQUERYPROCESSORFABRIC_H

#include "../DatabaseContext.h"
#include "../../settings/SettingsManager.h"

#include "DatabaseQueryProcessor.h"

class DatabaseQueryProcessorFabric
{
public:
    DatabaseQueryProcessorFabric() = delete;
    
    static bool createQueryProcessorWithSettings(const std::shared_ptr<DatabaseSettings> &dbSettings,
                                                 std::unique_ptr<DatabaseDriver> &&dbDriver,
                                                 std::unique_ptr<DatabaseQueryProcessor> &queryProcessor);
    
private:
    static std::unique_ptr<DatabaseQueryProcessor>&& createQueryProcessorStandard(std::unique_ptr<DatabaseDriver> &dbDriver);
};

#endif // DATABASEQUERYPROCESSORFABRIC_H
