#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include <QObject>

class MainWindowModel : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowModel(QObject *parent = nullptr);
    
signals:
    
};

#endif // MAINWINDOWMODEL_H
