#ifndef DATABASEFACADEINTERFACE_H
#define DATABASEFACADEINTERFACE_H

#include <memory>

#include "../queryProcessor/DatabaseQueryProcessor.h"

#include "pattern/Pattern.h"
#include "pattern/LinePattern.h"

#include "../../error/ErrorDatabaseQueryError.h"
#include "../../error/ErrorDatabaseIncorrectQuery.h"
#include "../../error/ErrorDatabaseIllegalState.h"

class DatabaseFacade {
protected:
    std::shared_ptr<DatabaseQueryProcessor> m_processor;
    
public:
    DatabaseFacade(const std::shared_ptr<DatabaseQueryProcessor> &processor);
    
    std::unique_ptr<ErrorDatabase> getLinePatterns(std::vector<std::shared_ptr<LinePattern>> &linePatterns);
    std::unique_ptr<ErrorDatabase> getPatterns    (const std::vector<std::shared_ptr<LinePattern>> &linePatterns,
                                                   std::vector<std::shared_ptr<Pattern>> &patterns);
    
private:
    std::unique_ptr<ErrorDatabase> getPatternLines(const std::shared_ptr<Pattern> &pattern,
                                                   std::vector<PatternLine> &patternLines);
};

#endif // DATABASEFACADEINTERFACE_H
