#include "DatabaseFacadeTrendSolver.h"

DatabaseFacadeTrendSolver::DatabaseFacadeTrendSolver(const std::shared_ptr<DatabaseQueryProcessor> &processor)
    : DatabaseFacade{processor}
{
    
}

std::unique_ptr<ErrorDatabase> DatabaseFacadeTrendSolver::getPatterns(const std::vector<LinePattern> &linePatterns,
                                                                      std::vector<Pattern> &patterns)
{
    if (linePatterns.empty()) 
        return std::make_unique<ErrorDatabaseIllegalState>();
    
    std::vector<std::string>   tablesVector{Pattern::C_DATABASE_TABLE_NAME};
    std::unique_ptr<QSqlQuery> query{};
    
    if (!m_processor->execSelectQuery(tablesVector, query))
        return std::make_unique<ErrorDatabaseQueryError>();
    
    std::vector<std::shared_ptr<Pattern>> loadedPatterns{};
    
    while (query->next()) {
        QVariant idVariant         {query->value(Pattern::C_DATABASE_ID_PROP)};
        QVariant nameVariant       {query->value(Pattern::C_DATABASE_NAME_PROP)};
        QVariant probabilityVariant{query->value(Pattern::C_DATABASE_PROBABILITY_PROP)};
        QVariant countOfUsesVariant{query->value(Pattern::C_DATABASE_USE_COUNT_PROP)};
        QVariant prevTrendVariant  {query->value(Pattern::C_DATABASE_PREV_TREND_PROP)};
        QVariant futureTrendVariant{query->value(Pattern::C_DATABASE_FUTURE_TREND_PROP)};
        
        QHash<QString, QVariant> patternStringVariantHash{
            {Pattern::C_DATABASE_ID_PROP,           idVariant},
            {Pattern::C_DATABASE_NAME_PROP,         nameVariant},
            {Pattern::C_DATABASE_PROBABILITY_PROP,  probabilityVariant},
            {Pattern::C_DATABASE_USE_COUNT_PROP,    countOfUsesVariant},
            {Pattern::C_DATABASE_PREV_TREND_PROP,   prevTrendVariant},
            {Pattern::C_DATABASE_FUTURE_TREND_PROP, futureTrendVariant}
        };
        
        Pattern loadedPattern{};
        
        if (!loadedPattern.fillWithVariantsHash(patternStringVariantHash))
            return std::make_unique<ErrorDatabaseQueryError>();
        
        loadedPatterns.push_back(std::make_shared<Pattern>(loadedPattern));
    }
    
    // loading lines of patterns...
    
    
    
    return std::unique_ptr<ErrorDatabase>{nullptr};
}
