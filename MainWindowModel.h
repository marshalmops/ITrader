#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include <QObject>

#include "error/Error.h"

#include "DotTableModel.h"

class MainWindowModel : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowModel(DotTableModel *dotTableModel,
                             QObject *parent = nullptr);
    
signals:
    void errorOccured(const std::shared_ptr<Error> error);
    
    void dotsToAnalyzeGotten(const QList<uint64_t> dots);
    
public slots:
    void analyzeDotsFromDotsModel();
    
    void addDotToModel();
    void removeDotFromModel();
    
private:
    DotTableModel *m_dotTableModel;
};

#endif // MAINWINDOWMODEL_H
