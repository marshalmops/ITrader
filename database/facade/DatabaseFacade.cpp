#include "DatabaseFacade.h"

bool DatabaseFacade::getPatternStringVariantHashWithQuery(const std::unique_ptr<QSqlQuery> &query,
                                                          QHash<QString, QVariant> &patternStringVariantHash)
{
    if (!query->isValid()) return false;
    
    QVariant idVariant         {query->value(Pattern::C_DATABASE_ID_PROP)};
    QVariant nameVariant       {query->value(Pattern::C_DATABASE_NAME_PROP)};
    QVariant probabilityVariant{query->value(Pattern::C_DATABASE_PROBABILITY_PROP)};
    QVariant countOfUsesVariant{query->value(Pattern::C_DATABASE_USE_COUNT_PROP)};
    QVariant prevTrendVariant  {query->value(Pattern::C_DATABASE_PREV_TREND_PROP)};
    QVariant futureTrendVariant{query->value(Pattern::C_DATABASE_FUTURE_TREND_PROP)};
    
    patternStringVariantHash = QHash<QString, QVariant>{
        {Pattern::C_DATABASE_ID_PROP,           idVariant},
        {Pattern::C_DATABASE_NAME_PROP,         nameVariant},
        {Pattern::C_DATABASE_PROBABILITY_PROP,  probabilityVariant},
        {Pattern::C_DATABASE_USE_COUNT_PROP,    countOfUsesVariant},
        {Pattern::C_DATABASE_PREV_TREND_PROP,   prevTrendVariant},
        {Pattern::C_DATABASE_FUTURE_TREND_PROP, futureTrendVariant}
    };
    
    return true;
}

DatabaseFacade::DatabaseFacade(const std::shared_ptr<DatabaseQueryProcessor> &processor)
    : m_processor{processor}
{
    
}

std::unique_ptr<ErrorDatabase> DatabaseFacade::getLinePatterns(std::vector<std::shared_ptr<LinePattern>> &linePatterns)
{
    std::vector<std::string>   linePatternQueryTables{LinePattern::C_DATABASE_TABLE_NAME};
    std::unique_ptr<QSqlQuery> queryResult           {nullptr};
    
    if (!m_processor->execSelectQuery(linePatternQueryTables, queryResult))
        return std::make_unique<ErrorDatabaseQueryError>();
    
    std::vector<std::shared_ptr<LinePattern>> loadedLinePatterns{};
    
    while (queryResult->next()) {
        QVariant idVariant       {queryResult->value(LinePattern::C_DATABASE_ID_PROP)};
        QVariant nameVariant     {queryResult->value(LinePattern::C_DATABASE_NAME_PROP)};
        QVariant angleTypeVariant{queryResult->value(LinePattern::C_DATABASE_ANGLE_TYPE)};
        
        QHash<QString, QVariant> curLinePatternHashMap{
            {LinePattern::C_DATABASE_ID_PROP,    idVariant},
            {LinePattern::C_DATABASE_NAME_PROP,  nameVariant},
            {LinePattern::C_DATABASE_ANGLE_TYPE, angleTypeVariant}
        };
        
        std::unique_ptr<LinePattern> curLinePattern{std::make_unique<LinePattern>()};
        
        if (!curLinePattern->fillWithVariantsHash(curLinePatternHashMap))
            return std::make_unique<ErrorDatabaseQueryError>();
        
        loadedLinePatterns.push_back(std::make_shared<LinePattern>(*curLinePattern.release()));
    }
    
    linePatterns = std::move(loadedLinePatterns);
    
    return std::unique_ptr<ErrorDatabase>{nullptr};
}

std::unique_ptr<ErrorDatabase> DatabaseFacade::getPatterns(std::vector<std::shared_ptr<Pattern>> &patterns)
{
    auto linePatternStore = LinePatternStore::getInstance();
    
    if (!linePatternStore.get()) 
        return std::make_unique<ErrorDatabaseIllegalState>();
    
    auto linePatterns = linePatternStore->getLinePatterns();
    
    if (linePatterns.empty()) 
        return std::make_unique<ErrorDatabaseIllegalState>();
    
    std::vector<std::string>   tablesVector{Pattern::C_DATABASE_TABLE_NAME};
    std::unique_ptr<QSqlQuery> query{};
    
    if (!m_processor->execSelectQuery(tablesVector, query))
        return std::make_unique<ErrorDatabaseQueryError>();
    
    std::vector<std::shared_ptr<Pattern>> loadedPatterns{};
    
    while (query->next()) {
//        QVariant idVariant         {query->value(Pattern::C_DATABASE_ID_PROP)};
//        QVariant nameVariant       {query->value(Pattern::C_DATABASE_NAME_PROP)};
//        QVariant probabilityVariant{query->value(Pattern::C_DATABASE_PROBABILITY_PROP)};
//        QVariant countOfUsesVariant{query->value(Pattern::C_DATABASE_USE_COUNT_PROP)};
//        QVariant prevTrendVariant  {query->value(Pattern::C_DATABASE_PREV_TREND_PROP)};
//        QVariant futureTrendVariant{query->value(Pattern::C_DATABASE_FUTURE_TREND_PROP)};
        
//        QHash<QString, QVariant> patternStringVariantHash{
//            {Pattern::C_DATABASE_ID_PROP,           idVariant},
//            {Pattern::C_DATABASE_NAME_PROP,         nameVariant},
//            {Pattern::C_DATABASE_PROBABILITY_PROP,  probabilityVariant},
//            {Pattern::C_DATABASE_USE_COUNT_PROP,    countOfUsesVariant},
//            {Pattern::C_DATABASE_PREV_TREND_PROP,   prevTrendVariant},
//            {Pattern::C_DATABASE_FUTURE_TREND_PROP, futureTrendVariant}
//        };
        
        QHash<QString, QVariant> patternStringVariantHash{};
        
        if (!getPatternStringVariantHashWithQuery(query, patternStringVariantHash))
            return std::make_unique<ErrorDatabaseQueryError>();
        
        std::unique_ptr<Pattern> loadedPattern{std::make_unique<Pattern>()};
        
        if (!loadedPattern->fillWithVariantsHash(patternStringVariantHash))
            return std::make_unique<ErrorDatabaseQueryError>();
        
        loadedPatterns.push_back(std::make_shared<Pattern>(*loadedPattern.release()));
    }
    
    for (auto &pattern : loadedPatterns) {
        std::vector<PatternLine> curPatternLines{};
        
        std::unique_ptr<ErrorDatabase> patternLinesQueryError{getPatternLines(pattern, curPatternLines)};
        
        if (patternLinesQueryError.get())
            return std::move(patternLinesQueryError);
        
        if (!pattern->initPatternLines(std::move(curPatternLines)))
            return std::make_unique<ErrorDatabaseQueryError>();
    }
    
    patterns = std::move(loadedPatterns);
    
    return std::unique_ptr<ErrorDatabase>{nullptr};
}

std::unique_ptr<ErrorDatabase> DatabaseFacade::getPatternById(const uint64_t patternId,
                                                              std::shared_ptr<Pattern> &pattern)
{
    auto linePatternStore = LinePatternStore::getInstance();
    
    if (!linePatternStore.get()) 
        return std::make_unique<ErrorDatabaseIllegalState>();
    
    auto linePatterns = linePatternStore->getLinePatterns();
    
    if (linePatterns.empty()) 
        return std::make_unique<ErrorDatabaseIllegalState>();
    
    std::vector<std::string>   tablesVector{Pattern::C_DATABASE_TABLE_NAME};
    std::vector<std::string>   conditionVector{std::string{Pattern::C_DATABASE_ID_PROP} + " = \'" + std::to_string(patternId) + '\''};
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
    
    pattern = loadedPattern;
    
    return std::unique_ptr<ErrorDatabase>{nullptr};
}

std::unique_ptr<ErrorDatabase> DatabaseFacade::getPatternLines(const std::shared_ptr<Pattern> &pattern,
                                                               std::vector<PatternLine> &patternLines)
{
    std::vector<std::string> tablesVector   {PatternLine::C_DATABASE_TABLE_NAME};
    std::vector<std::string> conditionVector{std::string{PatternLine::C_DATABASE_PATTERN_ID_PROP}
                                             + " = " + std::to_string(pattern->getId())};
    std::vector<std::pair<std::string, DatabaseQueryProcessor::OrderFlag>> orderParamFlagVector{
        {PatternLine::C_DATABASE_LINE_INDEX_PROP, DatabaseQueryProcessor::OrderFlag::OF_ASC}
    };
    
    std::unique_ptr<QSqlQuery> query{};
    
    if (!m_processor->execSelectQuery(tablesVector, query, std::vector<std::string>{}, conditionVector, orderParamFlagVector))
        return std::make_unique<ErrorDatabaseQueryError>();
    
    std::vector<PatternLine> loadedPatternLines{};
    
    while (query->next()) {
        QVariant patternIdVariant{query->value(PatternLine::C_DATABASE_PATTERN_ID_PROP)};
        QVariant lineIdVariant   {query->value(PatternLine::C_DATABASE_LINE_ID_PROP)};
        QVariant lineIndexVariant{query->value(PatternLine::C_DATABASE_LINE_INDEX_PROP)};
        QVariant lineSideVariant {query->value(PatternLine::C_DATABASE_LINE_SIDE_PROP)};
        
        QHash<QString, QVariant> curPatternLineStringVariantHash{
            {PatternLine::C_DATABASE_PATTERN_ID_PROP, patternIdVariant},
            {PatternLine::C_DATABASE_LINE_ID_PROP,    lineIdVariant},
            {PatternLine::C_DATABASE_LINE_INDEX_PROP, lineIndexVariant},
            {PatternLine::C_DATABASE_LINE_SIDE_PROP,  lineSideVariant}
        };
        
        std::unique_ptr<PatternLine> loadedPatternLine{std::make_unique<PatternLine>()};
        
        if (!loadedPatternLine->fillWithVariantsHash(curPatternLineStringVariantHash))
            return std::make_unique<ErrorDatabaseQueryError>();
        
        loadedPatternLines.push_back(*loadedPatternLine.release());
    }
    
    patternLines = std::move(loadedPatternLines);
    
    return std::unique_ptr<ErrorDatabase>{nullptr};
}
