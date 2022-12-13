#include "DotTableModel.h"

DotTableModel::DotTableModel(QObject *parent)
    : QAbstractTableModel{parent},
      m_dots{QList<uint64_t>{}}
{
    // defaults (testing...):
    
    m_dots.append(1245);
    m_dots.append(2415);
    m_dots.append(3412);
    m_dots.append(3754);
    m_dots.append(4512);
    m_dots.append(4562);
    m_dots.append(3512);
    m_dots.append(3545);
    m_dots.append(3002);
    m_dots.append(2951);
    m_dots.append(2687);
    m_dots.append(3425);
    m_dots.append(4512);
    m_dots.append(5616);
    m_dots.append(6312);
    m_dots.append(5643);
    m_dots.append(5421);
    m_dots.append(5261);
    m_dots.append(4843);
    m_dots.append(5627);
    m_dots.append(7623);
    m_dots.append(8975);
    m_dots.append(9373);
    m_dots.append(9142);
    m_dots.append(9252);
    m_dots.append(8942);
    m_dots.append(8642);
    m_dots.append(8251);
    m_dots.append(7846);
    m_dots.append(6427);
    
//    m_dots.append(17183);
//    m_dots.append(17181);
//    m_dots.append(17177);
//    m_dots.append(17176);
//    m_dots.append(17173);
//    m_dots.append(17177);
//    m_dots.append(17178);
//    m_dots.append(17177);
//    m_dots.append(17180);
//    m_dots.append(17180);
//    m_dots.append(17170);
//    m_dots.append(17165);
//    m_dots.append(17175);
//    m_dots.append(17177);
//    m_dots.append(17189);
//    m_dots.append(17188);
//    m_dots.append(17188);
//    m_dots.append(17184);
//    m_dots.append(17185);
//    m_dots.append(17188);
//    m_dots.append(17191);
//    m_dots.append(17201);
//    m_dots.append(17207);
//    m_dots.append(17188);
//    m_dots.append(17159);
//    m_dots.append(17148);
//    m_dots.append(17143);
//    m_dots.append(17116);
//    m_dots.append(17147);
//    m_dots.append(17164);
}

int DotTableModel::rowCount(const QModelIndex &parent = QModelIndex{}) const
{
    return m_dots.size();
}

int DotTableModel::columnCount(const QModelIndex &parent = QModelIndex{}) const
{
    return 1;
}

QVariant DotTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid()) 
        return QVariant{};
    
    if (index.row() >= m_dots.size())
        return QVariant{};
    
    auto curDot = m_dots.at(index.row());
    
    return QVariant{curDot};
}

bool DotTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || !value.isValid() || role != Qt::EditRole)
        return false;
    if (index.row() >= m_dots.size() || index.row() < 0 || index.column() > 0)
        return false;
    
    QString valueString{value.toString()};
    
    if (valueString.isEmpty()) return false;
    
    bool isConvOK{false};
    
    uint64_t newY{valueString.toUInt(&isConvOK, 0)};
    
    if (!isConvOK) return false;
    
    uint64_t &dotRef = m_dots[index.row()];
    
    dotRef = newY;
    
    emit dataChanged(index, index);
    
    return true;
}

QVariant DotTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant{};
    
    switch (orientation) {
    case Qt::Orientation::Horizontal: {
        switch (section) {
            case 0: return QVariant{tr("Cost")};
        }
        
        return QVariant{};
    }
    case Qt::Orientation::Vertical: {
        if (section > m_dots.size() || section < 0)
            return QVariant{};
        
        return QVariant{section};
    }
    }
    
    return QVariant{};
}

bool DotTableModel::insertRows(int row, int count, const QModelIndex &parent = QModelIndex{})
{
    auto dotsCount = m_dots.size();
    
    if (row != rowCount()) return false;
    if (parent.isValid())  return false;
    if (count > 1)         return false;
    
    beginInsertRows(QModelIndex{}, row, row);
    
    m_dots.append(0);
    
    endInsertRows();
    
    return true;
}

bool DotTableModel::removeRows(int row, int count, const QModelIndex &parent = QModelIndex{})
{
    auto dotsCount = m_dots.size();
    
    if (row != rowCount() - 1)  return false;
    if (parent.isValid())       return false;
    if (count > 1)              return false;
    
    beginRemoveRows(QModelIndex{}, row, row);
    
    m_dots.removeAt(row);
    
    endRemoveRows();
    
    return true;
}

Qt::ItemFlags DotTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemFlags{Qt::ItemFlag::ItemIsEditable | Qt::ItemFlag::ItemIsEnabled};
}

const QList<uint64_t> &DotTableModel::getDots() const
{
    return m_dots;
}

bool DotTableModel::addDot()
{
    return insertRows(rowCount(), 1);
}

bool DotTableModel::removeDot()
{
    return removeRows(rowCount() - 1, 1);
}
