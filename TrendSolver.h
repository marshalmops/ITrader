#ifndef TRENDSOLVER_H
#define TRENDSOLVER_H

#include <QObject>
#include <vector>

#include "error/ErrorSolver.h"
#include "pattern/Pattern.h"
#include "geometry/StageLineContainer.h"

#include "database/DatabaseManager.h"

class TrendSolver : public QObject
{
    Q_OBJECT
public:
    TrendSolver(QObject *parent = nullptr);
    
signals:
    void errorOccurred(const std::shared_ptr<ErrorSolver> error);
    
    void trendDetected    (const TrendSolverContext::Trend trend);
    void patternGotten    (const std::shared_ptr<Pattern> pattern);
    void finalLinesChoosen(const std::shared_ptr<StageLineContainer> choosenLines);
    
public slots:
    void analyseDots(const std::vector<Dot> inputDots);
    
private:
    // facade ptr...
    
    std::vector<std::shared_ptr<Pattern>>     m_patternLoadCache; // for storing patterns WITHOUT FREQUENT DB QUERRIES;
    std::vector<std::shared_ptr<LinePattern>> m_linePatternLoadCache; // for storing LINE patterns WITHOUT FREQUENT DB QUERRIES;
};

#endif // TRENDSOLVER_H
