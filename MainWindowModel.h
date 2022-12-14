#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include <QObject>

#include "error/Error.h"

#include "DotTableModel.h"
#include "IntellectualEditorModel.h"

class MainWindowModel : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowModel(DotTableModel *dotTableModel,
                             IntellectualEditorModel *intellectualEditorModel,
                             QObject *parent = nullptr);
    
    DotTableModel* getDotTableModel();
    
    IntellectualEditorModel* getIntellectualEditorModel();
    
signals:
    void errorOccured(const std::shared_ptr<Error> error);
    
    void dotsToAnalyzeGotten(const QList<uint64_t> dots);
    
public slots:
    void analyzeDotsFromDotsModel();
    
    void addDotToModel();
    void removeDotFromModel();
    
private:
    DotTableModel *m_dotTableModel;
    IntellectualEditorModel *m_intellectualEditorModel;
};

#endif // MAINWINDOWMODEL_H
