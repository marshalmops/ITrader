#ifndef APPINITIALIZER_H
#define APPINITIALIZER_H

#include <QTableView>

#include "AppCore.h"
#include "MainWindowView.h"
#include "MainWindowModel.h"
#include "TrendSolver.h"
#include "IntellectualEditor.h"

#include "settings/SettingsManager.h"

#include "pattern/LinePatternStore.h"
#include "pattern/PatternStore.h"

class AppInitializer
{
public:
    AppInitializer() = delete;
    
    static bool initializeApp(std::unique_ptr<AppCore> &appCore,
                              std::unique_ptr<MainWindowView> &mainWindowView,
                              std::unique_ptr<MainWindowModel> &mainWindowModel,
                              std::unique_ptr<TrendSolver> &trendSolver,
                              std::unique_ptr<IntellectualEditor> &intellectualEditor);
};

#endif // APPINITIALIZER_H
