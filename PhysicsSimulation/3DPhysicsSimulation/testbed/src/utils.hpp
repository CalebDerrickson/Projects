#pragma once
#include <stdint.h>

#ifndef STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_IMPLEMENTATION
#endif
enum FILE_EXTENSION {UNKNOWN, PNG, JPG};

enum STATE {OKAY, ERROR};
#define SIM_YES 1
#define SIM_NO 0
typedef unsigned int uint;

#define KB 2 << 9




namespace utils{
    
    template <typename T>
    inline T clamp(T val, T lower_bound, T upper_bound) {
        if (val < lower_bound) return lower_bound;
        if (val > upper_bound) return upper_bound;
        return val;
    } 
}
