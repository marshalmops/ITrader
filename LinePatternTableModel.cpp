#include "LinePatternTableModel.h"

LinePatternTableModel::LinePatternTableModel(QObject *parent)
    : QAbstractTableModel{parent},
      m_linePatterns{}
{
    
}

int LinePatternTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;

    return m_linePatterns.size();
}

int LinePatternTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;

    return C_PROP_TO_SHOW_COUNT;
}

QVariant LinePatternTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid())
        return QVariant{};

    if (index.row() >= m_linePatterns.size())
        return QVariant{};

    auto curLinePattern = m_linePatterns.at(index.row());

    if (!curLinePattern.get())
        return QVariant{};

    switch (index.column()) {
    case 0: return QVariant{curLinePattern->getName().c_str()};
    case 1: return QVariant{LinePattern::angleTypeToString(curLinePattern->getAngleType())};
    }

    return QVariant{};
}

QVariant LinePatternTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant{};

    switch (orientation) {
    case Qt::Orientation::Horizontal: {
        switch (section) {
        case 0: return QVariant{LinePattern::C_DATABASE_NAME_PROP};
        case 1: return QVariant{LinePattern::C_DATABASE_ANGLE_TYPE};
        }

        return QVariant{};
    }
    case Qt::Orientation::Vertical: {
        if (section > m_linePatterns.size() || section < 0)
            return QVariant{};

        return QVariant{section};
    }
    }

    return QVariant{};
}

Qt::ItemFlags LinePatternTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemFlags{Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsSelectable};
}

bool LinePatternTableModel::addLinePattern(const std::shared_ptr<LinePattern> &linePattern)
{
    if (!linePattern.get()) return false;

    auto countOfLinePatterns = rowCount();
    
    beginInsertRows(QModelIndex{}, countOfLinePatterns, countOfLinePatterns);

    m_linePatterns.append(linePattern);

    endInsertRows();

    return true;
}

bool LinePatternTableModel::removeLinePattern(const int linePatternIndex)
{
    auto countOfLinePatterns = rowCount();
    
    if (linePatternIndex >= countOfLinePatterns) return false;
    
    beginRemoveRows(QModelIndex{}, linePatternIndex, linePatternIndex);

    m_linePatterns.removeAt(linePatternIndex);

    endRemoveRows();

    return true;
}

bool LinePatternTableModel::getLinePatternByIndex(const int linePatternIndex, 
                                                  std::shared_ptr<LinePattern> &linePattern)
{
    if (linePatternIndex >= rowCount()) return false;
    
    linePattern = m_linePatterns.at(linePatternIndex);
    
    return true;
}

bool LinePatternTableModel::setLinePatterns(const std::vector<std::shared_ptr<LinePattern>> linePatternsToBeSet)
{
    clearLinePatterns();
    
    for (const auto &linePattern : linePatternsToBeSet)
        if (!addLinePattern(linePattern)) return false;
    
    return true;
}

std::vector<std::shared_ptr<LinePattern>> LinePatternTableModel::getLinePatterns() const
{
    std::vector<std::shared_ptr<LinePattern>> linePatterns{};
    
    for (const auto &linePattern : m_linePatterns)
        linePatterns.push_back(linePattern);
    
    return std::move(linePatterns);
}

void LinePatternTableModel::clearLinePatterns()
{
    beginRemoveRows(QModelIndex{}, 0, rowCount());
    
    m_linePatterns.clear();
    
    endRemoveRows();
    
    emit layoutChanged();
}
