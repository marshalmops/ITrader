#include "Line.h"

Line::Line(const std::shared_ptr<Dot> &first, 
           const std::shared_ptr<Dot> &second,
           const Side side,
           const Direction direction)
    : m_first{first},
      m_second{second},
      m_side{side},
      m_direction{direction}
{
    
}

std::unique_ptr<Line> Line::createLine(const std::shared_ptr<Dot> &first, 
                                       const std::shared_ptr<Dot> &second,
                                       const Line::Side side)
{
    if (!first.get() || !second.get())
        return std::unique_ptr<Line>();
    
    bool isValid = (first.get()->getX() != second.get()->getX())
                || (first.get()->getY() != second.get()->getY());
    
    if (!isValid) 
        return std::unique_ptr<Line>();
    
    Direction dir = ((first.get()->getY() > second.get()->getY())
                     ? Direction::D_TO_DOWN
                     : (first.get()->getY() < second.get()->getY())
                       ? Direction::D_TO_UP : Direction::D_PARALLEL);
    
    return std::make_unique<Line>(Line(first, second, side, dir));
}

const std::shared_ptr<Dot>& Line::getFirst() const {
    return m_first;
}

const std::shared_ptr<Dot>& Line::getSecond() const {
    return m_second;
}

const std::vector<std::shared_ptr<Dot>>& Line::getOtherDots() const {
    return m_otherDots;
}

const Line::Side Line::getSide() const {
    return m_side;
}

const Line::Direction Line::getDirection() const {
    return m_direction;
}

void Line::addDot(const std::shared_ptr<Dot>& dot) {
    m_otherDots.push_back(dot);
}

Line::CrossingType Line::checkDotCrossing(const std::shared_ptr<Dot>& dot) const {
    Dot::xCoord x = dot.get()->getX();
    Dot::xCoord x1 = m_first.get()->getX();
    Dot::xCoord x2 = m_second.get()->getX();
    
    Dot::yCoord y = dot.get()->getY();
    Dot::yCoord y1 = m_first.get()->getY();
    Dot::yCoord y2 = m_second.get()->getY();
    
    float yLine = (static_cast<float>(x - x1) / (x2 - x1)) * (y2 - y1) + y1;
    
    if ((yLine + yLine * TrendSolverContext::S_ACCEPTABLE_DOT_CROSSING_DEVIATION_PERCENT >= y
        && yLine <= y)
     || (yLine - yLine * TrendSolverContext::S_ACCEPTABLE_DOT_CROSSING_DEVIATION_PERCENT <= y
        && yLine >= y))
    {
        return CrossingType::CT_DOT;
    }
    
    switch (m_side) {
    case Line::Side::S_UP:   {
        return (yLine < y) ? CrossingType::CT_PINE : 
               CrossingType::CT_NOTHING;
    }
    case Line::Side::S_DOWN: {
        return (yLine > y) ? CrossingType::CT_PINE : 
               CrossingType::CT_NOTHING;
    }
    }
    
    return CrossingType::CT_NOTHING;
}

uint8_t Line::getCoverage() const {
    return m_second.get()->getX() - m_first.get()->getX() + 1;
}
