#ifndef TRENDSOLVER_H
#define TRENDSOLVER_H

#include <QObject>
#include <vector>

#include "error/ErrorSolver.h"
#include "error/ErrorSolverInvalidInputData.h"

#include "pattern/Pattern.h"
#include "pattern/PatternStore.h"
#include "pattern/StagePatternContainer.h"
#include "geometry/StageLineContainer.h"

#include "database/facade/DatabaseFacadeTrendSolver.h"

class TrendSolver : public QObject
{
    Q_OBJECT
public:
    TrendSolver(std::unique_ptr<DatabaseFacadeTrendSolver> &&facade,
                QObject *parent = nullptr);
    
signals:
    void errorOccurred(const std::shared_ptr<ErrorSolver> error);
    
    void patternGotten    (const std::shared_ptr<StagePatternLineContainer> pattern,
                           const std::vector<std::shared_ptr<Dot>> dots);
    void finalLinesChoosen(const std::shared_ptr<StageLineContainer> choosenLines);
    
public slots:
    void resetFacade(std::shared_ptr<DatabaseFacadeTrendSolver> facade);
    
    void analyseDots(const QList<uint64_t> inputDots);
    
private:
    std::unique_ptr<DatabaseFacadeTrendSolver> m_facade;
};

#endif // TRENDSOLVER_H
