#include <QApplication>

#include "AppInitializer.h"

int main(int argc, char** argv)
{
    QApplication app{argc, argv};
    
    std::unique_ptr<AppCore>            appCore{};
    std::unique_ptr<MainWindowView>     mainWindowView{};
    std::unique_ptr<MainWindowModel>    mainWindowModel{};
    std::unique_ptr<TrendSolver>        trendSolver{};
    std::unique_ptr<IntellectualEditor> intellectualEditor{};
    
    if (!AppInitializer::initializeApp(appCore, 
                                       mainWindowView, 
                                       mainWindowModel, 
                                       trendSolver, 
                                       intellectualEditor))
    {
        QMessageBox::critical(nullptr, 
                              QObject::tr("Critical error!"),
                              QObject::tr("App initialization error!"));
        
        return -1;
    }
    
    mainWindowView->show();
    
    return app.exec();
}
