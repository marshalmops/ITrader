#include "Dot.h"

Dot::Dot(const xCoord x, const yCoord y)
    : m_x{x}, m_y{y}
{
    
}

Dot::xCoord Dot::getX() {
    return m_x;
}

Dot::yCoord Dot::getY() {
    return m_y;
}
