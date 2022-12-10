#ifndef DATABASEFACADEINTERFACE_H
#define DATABASEFACADEINTERFACE_H

#include <memory>

#include "../queryProcessor/DatabaseQueryProcessor.h"

#include "../../pattern/Pattern.h"
#include "../../pattern/LinePattern.h"
#include "../../pattern/LinePatternStore.h"

#include "../../error/ErrorDatabaseQueryError.h"
#include "../../error/ErrorDatabaseIncorrectQuery.h"
#include "../../error/ErrorDatabaseIllegalState.h"

class DatabaseFacade {
protected:
    std::shared_ptr<DatabaseQueryProcessor> m_processor;
    
public:
    DatabaseFacade(const std::shared_ptr<DatabaseQueryProcessor> &processor);
    
    
    std::unique_ptr<ErrorDatabase> getLinePatterns(std::vector<std::shared_ptr<LinePattern>> &linePatterns);
    std::unique_ptr<ErrorDatabase> getPatterns    (std::vector<std::shared_ptr<Pattern>> &patterns);
    std::unique_ptr<ErrorDatabase> getPatternById (const uint64_t patternId, 
                                                   std::shared_ptr<Pattern> &pattern);
    
protected:
    std::unique_ptr<ErrorDatabase> getPatternLines(const std::shared_ptr<Pattern> &pattern,
                                                   std::vector<PatternLine> &patternLines);
    bool getPatternStringVariantHashWithQuery(const std::unique_ptr<QSqlQuery> &query,
                                              QHash<QString, QVariant> &patternStringVariantHash);
};

#endif // DATABASEFACADEINTERFACE_H
