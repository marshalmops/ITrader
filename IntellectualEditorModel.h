#ifndef INTELLECTUALEDITORMODEL_H
#define INTELLECTUALEDITORMODEL_H

#include <QObject>
#include <vector>

#include "error/Error.h"

#include "pattern/PatternStore.h"

#include "database/facade/DatabaseFacadeIntellectualEditor.h"

#include "PatternTableModel.h"
#include "LinePatternTableModel.h"

class IntellectualEditorModel : public QObject
{
    Q_OBJECT
public:
    IntellectualEditorModel(PatternTableModel *patternTableModel,
                            LinePatternTableModel *linePatternTableModel,
                            std::unique_ptr<DatabaseFacadeIntellectualEditor> &&facade,
                            
                            QObject *parent = nullptr);
    
signals:
    void errorOccurred(const std::shared_ptr<Error> error);
    
public slots:
    void resetFacade(std::shared_ptr<DatabaseFacadeIntellectualEditor> facade);
    
    void insertNewPattern     ();
    void deleteSelectedPattern(const uint64_t patternId);
    
private:
    PatternTableModel     *m_patternTableModel;
    LinePatternTableModel *m_linePatternTableModel;
    
    std::unique_ptr<DatabaseFacadeIntellectualEditor> m_facade;
};

#endif // INTELLECTUALEDITORMODEL_H
