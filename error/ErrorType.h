#ifndef ERRORTYPE_H
#define ERRORTYPE_H

#include <cstdint>

namespace ErrorType {
    using ValueType = uint8_t;

    enum App : ValueType {
        A_INCORRECT_BEHAVIOUR = 0b0000'0000
        
        // to 0b0011'1111;
    };
    
    enum Solver : ValueType {
        S_INVALID_INPUT_DATA = 0b0100'0000,
        S_LACK_OF_DATA
        
        // to 0b0111'1111;
    };
    
    enum Database : ValueType {
        D_INIT_FAILED = 0b1000'0000,
        D_QUERY_ERROR,
        D_INCORRECT_QUERY,
        D_ILLEGAL_STATE
        
        // to 0b1011'1111
    };
    
    enum IntellectualEditor : ValueType {
        IE_INCORRECT_MODEL_INDEX = 0b1100'0000
        
        // to 0b1111'1111
    };
}

#endif // ERRORTYPE_H
