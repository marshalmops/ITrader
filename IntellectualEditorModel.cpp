#include "IntellectualEditorModel.h"

IntellectualEditorModel::IntellectualEditorModel(PatternTableModel *patternTableModel,
                                                 LinePatternTableModel *linePatternTableModel,
                                                 std::unique_ptr<DatabaseFacadeIntellectualEditor> &&facade, 
                                                 QObject *parent)
    : QObject{parent},
      m_patternTableModel{patternTableModel},
      m_linePatternTableModel{linePatternTableModel},
      m_facade{facade.release()}
{
    
}

PatternTableModel* IntellectualEditorModel::getPatternTableModel()
{
    return m_patternTableModel;
}

LinePatternTableModel* IntellectualEditorModel::getLinePatternTableModel()
{
    return m_linePatternTableModel;
}

void IntellectualEditorModel::resetFacade(std::shared_ptr<DatabaseFacadeIntellectualEditor> facade)
{
    m_facade = std::make_unique<DatabaseFacadeIntellectualEditor>(std::move(*facade));
}

void IntellectualEditorModel::insertNewPattern(const std::shared_ptr<Pattern> newPattern)
{
    if (!newPattern.get()) {
        emit errorOccurred(std::make_shared<ErrorAppIncorrectBehaviour>());
        
        return;
    }
    
    auto dbError = m_facade->insertPattern(newPattern);
    
    if (dbError.get()) {
        emit errorOccurred(std::shared_ptr<Error>(dbError.release()));
        
        return;
    }
    
    std::vector<std::shared_ptr<Pattern>> patterns{};
    
    dbError = m_facade->getPatterns(patterns);
    
    if (dbError.get()) {
        emit errorOccurred(std::shared_ptr<Error>(dbError.release()));
        
        return;
    }
    
    auto patternStore = PatternStore::getInstance();
    
    if (!patternStore.get()) {
        emit errorOccurred(std::make_shared<ErrorAppIncorrectBehaviour>());
        
        return;
    }
    
    if (!patternStore->setPatterns(patterns)) {
        emit errorOccurred(std::make_shared<ErrorAppIncorrectBehaviour>());
        
        return;
    }
    
    if (!m_patternTableModel->addPattern(newPattern)) {
        emit errorOccurred(std::make_shared<ErrorAppIncorrectBehaviour>());
        
        return;
    }
}

void IntellectualEditorModel::deleteSelectedPattern(const uint64_t patternIndex)
{
    std::shared_ptr<Pattern> patternToDelete{nullptr};
    
    if (!m_patternTableModel->getPatternByIndex(patternIndex, patternToDelete)) {
        emit errorOccurred(std::make_shared<ErrorIntellectualEditorIncorrectModelIndex>());
        
        return;
    }
    
    auto dbError = m_facade->deletePattern(patternToDelete);
    
    if (dbError.get()) {
        emit errorOccurred(std::shared_ptr<Error>(dbError.release()));
        
        return;
    }
    
    std::vector<std::shared_ptr<Pattern>> patterns{};
    
    dbError = m_facade->getPatterns(patterns);
    
    if (dbError.get()) {
        emit errorOccurred(std::shared_ptr<Error>(dbError.release()));
        
        return;
    }
    
    auto patternStore = PatternStore::getInstance();
    
    if (!patternStore.get()) {
        emit errorOccurred(std::make_shared<ErrorAppIncorrectBehaviour>());
        
        return;
    }
    
    if (!patternStore->setPatterns(patterns)) {
        emit errorOccurred(std::make_shared<ErrorAppIncorrectBehaviour>());
        
        return;
    }
    
    if (!m_patternTableModel->removePattern(patternIndex)) {
        emit errorOccurred(std::make_shared<ErrorAppIncorrectBehaviour>());
        
        return;
    }
}

void IntellectualEditorModel::prepareModels()
{
    auto patternStore = PatternStore::getInstance();
    
    if (!patternStore.get()) {
        emit errorOccurred(std::make_shared<ErrorAppIncorrectBehaviour>());
        
        return;
    }
    
    auto patterns = patternStore->getPatterns();
    
    if (!m_patternTableModel->setPatterns(patterns)) {
        emit errorOccurred(std::make_shared<ErrorAppIncorrectBehaviour>());
        
        return;
    }
}
