#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include <QMessageBox>

#include "error/Error.h"
#include "error/ErrorDatabaseInitFailed.h"

#include "database/DatabaseManager.h"

class AppCore : public QObject
{
    Q_OBJECT
    
    constexpr static const char* C_CRITICAL_ERROR_MESSAGE_TITLE = "Critical error";
    constexpr static const char* C_WARNING_MESSAGE_TITLE        = "Warning";
    
public:
    explicit AppCore(QObject *parent = nullptr);
    
signals:
//    void showMessage(const QString message);
    void resetTrendSolverFacade       (std::shared_ptr<DatabaseFacadeTrendSolver> facade);
    void resetIntellectualEditorFacade(std::shared_ptr<DatabaseFacadeIntellectualEditor> facade);
    
public slots:
    void processError(const std::shared_ptr<Error> error);
    void handleSettingsUpdate(); // from GUI;
};

#endif // APPCORE_H
