#ifndef DOT_H
#define DOT_H

#include <cstdint>

class Dot {
public:
    using xCoord = uint8_t;
    using yCoord = uint8_t;
    
    
private:
    xCoord m_x;
    yCoord m_y;
    
public:
    Dot(const xCoord x, const yCoord y);
    
    xCoord getX();
    yCoord getY();
};

#endif // DOT_H
