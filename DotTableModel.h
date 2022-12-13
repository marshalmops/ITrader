#ifndef DOTTABLEMODEL_H
#define DOTTABLEMODEL_H

#include <QAbstractTableModel>

#include "geometry/Dot.h"

class DotTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DotTableModel(QObject *parent = nullptr);
    
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual bool insertRows(int row, int count, const QModelIndex &parent) override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    
    const QList<uint64_t> &getDots() const;
    
    bool addDot();
    bool removeDot();
    
private:
    QList<uint64_t> m_dots;
};

#endif // DOTTABLEMODEL_H
