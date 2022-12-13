#ifndef TRENDSOLVER_TEST_H
#define TRENDSOLVER_TEST_H

#include <QObject>

#include "../../TrendSolver.h"
#include "../../settings/SettingsManager.h"
#include "../../database/DatabaseManager.h"

class TrendSolver_test : public QObject
{
    Q_OBJECT
public:
    explicit TrendSolver_test(QObject *parent = nullptr);
    
private slots:
    void initTestCase();
    void checkKlinToDownDotsAnalyzing_test();
    void checkTriangleToDownDotsAnalyzing_test();
    void checkIncorrectPrevTrendDotsAnalyzing_test();
    void checkIncorrectDotsAnalyzing_test();
    
private:
    std::unique_ptr<TrendSolver> m_trendSolver;
    std::vector<std::shared_ptr<Dot>> m_dots;
};

#endif // TRENDSOLVER_TEST_H
