#include "DatabaseFacadeIntellectualEditor.h"


DatabaseFacadeIntellectualEditor::DatabaseFacadeIntellectualEditor(const std::shared_ptr<DatabaseQueryProcessor> &processor)
    : DatabaseFacade{processor}
{
    
}

std::unique_ptr<ErrorDatabase> DatabaseFacadeIntellectualEditor::insertPattern(const std::shared_ptr<Pattern> &pattern)
{
    if (!pattern.get()) 
        return std::make_unique<ErrorDatabaseIllegalState>();
    
    std::vector<std::string> paramVector{
        Pattern::C_DATABASE_NAME_PROP, 
        Pattern::C_DATABASE_PROBABILITY_PROP, 
        Pattern::C_DATABASE_PREV_TREND_PROP, 
        Pattern::C_DATABASE_FUTURE_TREND_PROP
    };
    std::vector<std::string> valueVector{
        pattern->getName(),
        std::to_string(pattern->getProbability()),
        std::to_string(TrendSolverContext::getTrendValue(pattern->getPrevTrend())),
        std::to_string(TrendSolverContext::getTrendValue(pattern->getFutureTrend()))
    };
    
    if (!m_processor->execInsertQuery(Pattern::C_DATABASE_TABLE_NAME, valueVector, paramVector))
        return std::make_unique<ErrorDatabaseQueryError>();
    
    // getting INSERTED patttern:
    
    std::shared_ptr<Pattern>       insertedPattern    {};
    std::unique_ptr<ErrorDatabase> selectionQueryError{};
    
    if ((selectionQueryError = getPatternByNameAndTrends(pattern->getName(), 
                                                         pattern->getPrevTrend(),
                                                         pattern->getFutureTrend(), 
                                                         insertedPattern)).get())
    {
        return std::move(selectionQueryError);
    }
    
    if (!insertedPattern.get())
        return std::make_unique<ErrorDatabaseQueryError>();
    
    // inserting LINES of pattern:
    
    for (const auto& line : pattern->getPatternLines()) {
        std::vector<std::string> paramVector{
            PatternLine::C_DATABASE_PATTERN_ID_PROP, 
            PatternLine::C_DATABASE_LINE_ID_PROP, 
            PatternLine::C_DATABASE_LINE_INDEX_PROP, 
            PatternLine::C_DATABASE_LINE_SIDE_PROP
        };
        std::vector<std::string> valueVector{
            std::to_string(insertedPattern->getId()),
            std::to_string(line.getLineId()),
            std::to_string(line.getIndex()),
            std::to_string(static_cast<Line::SideType>(line.getSide()))
        };
        
        if (!m_processor->execInsertQuery(PatternLine::C_DATABASE_TABLE_NAME, valueVector, paramVector))
            return std::make_unique<ErrorDatabaseQueryError>();
    }
    
    return std::unique_ptr<ErrorDatabase>(nullptr);
}

std::unique_ptr<ErrorDatabase> DatabaseFacadeIntellectualEditor::deletePattern(const std::shared_ptr<Pattern> &pattern)
{
    if (!pattern.get()) 
        return std::make_unique<ErrorDatabaseIllegalState>();
    
    std::vector<std::string> conditionVector{
        std::string{Pattern::C_DATABASE_ID_PROP} + " = \'" + std::to_string(pattern->getId()) + '\''
    };
    
    if (!m_processor->execDeleteQuery(Pattern::C_DATABASE_TABLE_NAME, conditionVector))
        return std::make_unique<ErrorDatabaseQueryError>();
    
    return std::unique_ptr<ErrorDatabase>(nullptr);
}

std::unique_ptr<ErrorDatabase> DatabaseFacadeIntellectualEditor::getPatternByNameAndTrends(const std::string &name,
                                                                                           const Pattern::Trend prevTrend,
                                                                                           const Pattern::Trend futureTrend,
                                                                                           std::shared_ptr<Pattern> &gottenPattern)
{
    if (name.empty() || prevTrend >= Pattern::Trend::T_COUNT 
     || futureTrend >= Pattern::Trend::T_COUNT)
    {
        return std::make_unique<ErrorDatabaseIllegalState>();
    }
    
    std::vector<std::string>   tablesVector{Pattern::C_DATABASE_TABLE_NAME};
    std::vector<std::string>   conditionVector{
        std::string{Pattern::C_DATABASE_NAME_PROP} + " = \'" + name + '\'',
        std::string{Pattern::C_DATABASE_PREV_TREND_PROP} + " = \'" + std::to_string(TrendSolverContext::getTrendValue(prevTrend)) + '\'',
        std::string{Pattern::C_DATABASE_FUTURE_TREND_PROP} + " = \'" + std::to_string(TrendSolverContext::getTrendValue(futureTrend)) + '\'',
    };
    std::unique_ptr<QSqlQuery> query{};
    
    if (!m_processor->execSelectQuery(tablesVector, query, std::vector<std::string>{}, conditionVector))
        return std::make_unique<ErrorDatabaseQueryError>();
    
    query->next();
    
    QHash<QString, QVariant> patternStringVariantHash{};
    
    if (!getPatternStringVariantHashWithQuery(query, patternStringVariantHash))
        return std::make_unique<ErrorDatabaseQueryError>();
    
    std::shared_ptr<Pattern> loadedPattern{std::make_shared<Pattern>()};
    
    if (!loadedPattern->fillWithVariantsHash(patternStringVariantHash))
        return std::make_unique<ErrorDatabaseQueryError>();
    
    std::vector<PatternLine> curPatternLines{};
    
    std::unique_ptr<ErrorDatabase> patternLinesQueryError{getPatternLines(loadedPattern, curPatternLines)};
    
    if (patternLinesQueryError.get())
        return std::move(patternLinesQueryError);
    
    if (!loadedPattern->initPatternLines(std::move(curPatternLines)))
        return std::make_unique<ErrorDatabaseQueryError>();
    
    gottenPattern = loadedPattern;
    
    return std::unique_ptr<ErrorDatabase>{nullptr};
}
