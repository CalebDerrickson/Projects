// Templated math library for vector operations only
// Operations for vec2 and vec3
// vector of arbitrary length will come later


#include <cmath>
#include <iostream>
#include <stdexcept> // For std::runtime_error
#include <stdint.h>
#include "utils_math.hpp"

// Common structs for vectors
// Standard usecase will be for numbers
template <typename T>
struct vec3 {

    T x;
    T y;
    T z;

    // constructors
    vec3() : x(0), y(0), z(0) {}
    vec3(T val) : x(val), y(val), z(val) {}
    vec3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}


    // Prefix ++
    vec3<T>& operator++() {
        ++x;
        ++y;
        ++z;
        return *this;
    }

    // Postfix ++
    vec3<T> operator++(int) {
        vec3<T> temp = *this;
        ++x;
        ++y;
        ++z;
        return temp;
    }

    // Prefix --
    vec3<T> operator--() {
        return vec3<T>{--x, --y, --z};
    }

    // Postfix --
    vec3<T> operator--(int) {
        vec3<T> temp = *this;
        --x;
        --y;
        --z;
        return temp;
    }

    // vector - scalar operations

    vec3<T> operator+=(T scalar) {
        vec3<T> temp = *this;
        x+= scalar;
        y+= scalar;
        z+= scalar;
        return temp;
    }

    
    vec3<T> operator-=(T scalar) {
        vec3<T> temp = *this;
        x-= scalar;
        y-= scalar;
        z-= scalar;
        return temp;
    }




    // Example use : vec = vec * 3;
    vec3<T> operator*(T scalar) const {
        return vec3<T>{x * scalar, y * scalar, z * scalar};
    }

    // Example use: vec *= 3;
    vec3<T> operator*=(T scalar) {
        vec3<T> temp = *this;
        x*= scalar;
        y*= scalar;
        z*= scalar;
        return temp;
    }

    // Example use: vec = vec / 3;
    vec3<T> operator/(T scalar) const {
        if (std::fabs(scalar) > EPS) {
            return vec3<T>{x / scalar, y / scalar, z / scalar};
        } else {
            throw std::runtime_error("Dividing by zero or near zero");
        }
    }
    

    // Example use: vec /= 3;
    vec3<T>& operator/=(T scalar) {
        if (std::fabs(scalar) > EPS) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
        } else {
            throw std::runtime_error("Dividing by zero or near zero");
        }
        return *this;
    }

    // vector - vector operations

    vec3<T>& operator+=(const vec3<T>& other) {
        x+= other.x;
        y+= other.y;
        z+= other.z;
        return *this;
    }


    vec3<T>& operator-=(const vec3<T>& other) {
        x-= other.x;
        y-= other.y;
        z-= other.z;
        return *this;
    }

    vec3<T> operator-(const vec3<T>& other) const {
        return vec3<T>{x-other.x, y-other.y, z-other.z};
    }

    vec3<T> operator+(const vec3<T>& other) const {
        return vec3<T>{x+other.x, y+other.y, z+other.z};
    }


    // Overloaded [] operator for element access
    // read-write
    T& operator[](std::size_t index) {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        throw std::out_of_range("Index out of range for vec3");
    }

    // read
    const T& operator[](std::size_t index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        throw std::out_of_range("Index out of range for vec3");
    }

};

// standard math usage: 3*vec
template <typename T, typename S>
vec3<T> operator*(S scalar, const vec3<T>& v) {
    return vec3<T>{scalar * v.x, scalar * v.y, scalar * v.z};
}

// not exactly standard math usage
// 3/vec = {vec.x / 3, vec.y / 3, vec.z / 3};
template <typename T, typename S>
vec3<T> operator/(S scalar, const vec3<T>& v) {
    if (std::fabs(scalar) > EPS) {
        return vec3<T>{v.x / scalar, v.y / scalar, v.z / scalar};
    }
    else {
        throw std::runtime_error("Dividing by zero or near zero");
    }
}



template <typename T>
struct vec2
{
    T x;
    T y;
    

    // constructors
    vec2() : x(0), y(0) {}
    vec2(T val) : x(val), y(val) {}
    vec2(T x_, T y_) : x(x_), y(y_) {}

    // Prefix ++
    vec2<T>& operator++() {
        ++x;
        ++y;
        return *this;
    }

    // Postfix ++
    vec2<T> operator++(int) {
        vec2<T> temp = *this;
        ++x;
        ++y;
        return temp;
    }

    // Prefix --
    vec2<T> operator--() {
        return vec2<T>{--x, --y};
    }

    // Postfix --
    vec2<T> operator--(int) {
        vec2<T> temp = *this;
        --x;
        --y;
        return temp;
    }

    // vector - scalar operations

    vec2<T> operator+=(T scalar) {
        vec2<T> temp = *this;
        x+= scalar;
        y+= scalar;
        return temp;
    }
    
    vec2<T> operator-=(T scalar) {
        vec2<T> temp = *this;
        x-= scalar;
        y-= scalar;
        return temp;
    }

    // Example use : vec = vec * 3;
    vec2<T> operator*(T scalar) const {
        return vec2<T>{x * scalar, y * scalar};
    }

    // Example use: vec *= 3;
    vec2<T> operator*=(T scalar) {
        vec2<T> temp = *this;
        x*= scalar;
        y*= scalar;
        return temp;
    }

    // Example use: vec = vec / 3;
    vec2<T> operator/(T scalar) const {
        if (std::fabs(scalar) > EPS) {
            return vec2<T>{x / scalar, y / scalar};
        } else {
            throw std::runtime_error("Dividing by zero or near zero");
        }
    }

    // Example use: vec /= 3;
    vec2<T>& operator/=(T scalar) {
        if (std::fabs(scalar) > EPS) {
            x /= scalar;
            y /= scalar;
        } else {
            throw std::runtime_error("Dividing by zero or near zero");
        }
        return *this;
    }

    // vector - vector operations

    vec2<T>& operator+=(const vec2<T>& other) {
        x+= other.x;
        y+= other.y;
        return *this;
    }


    vec2<T>& operator-=(const vec2<T>& other) {
        x-= other.x;
        y-= other.y;
        return *this;
    }

    vec2<T> operator-(const vec2<T>& other) const {
        return vec2<T>{x-other.x, y-other.y};
    }

    vec2<T> operator+(const vec2<T>& other) const {
        return vec2<T>{x+other.x, y+other.y};
    }
    
    // Overloaded [] operator for element access
    // read-write
    T& operator[](std::size_t index) {
        if (index == 0) return x;
        if (index == 1) return y;
        throw std::out_of_range("Index out of range for vec3");
    }

    // read
    const T& operator[](std::size_t index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        throw std::out_of_range("Index out of range for vec3");
    }
};

// standard math usage: 3*vec
template <typename T, typename S>
vec2<T> operator*(S scalar, const vec2<T>& v) {
    return vec2<T>{scalar * v.x, scalar * v.y};
}

// not exactly standard math usage
// 3/vec = {vec.x / 3, vec.y / 3};
template <typename T, typename S>
vec2<T> operator/(S scalar, const vec2<T>& v) {
    if (std::fabs(scalar) > EPS) {
        return vec2<T>{v.x / scalar, v.y / scalar};
    }
    else {
        throw std::runtime_error("Dividing by zero or near zero");
    }

    
}


// Common vector operations 
namespace vector {
    // vec3
    template<typename T, typename S>
    T dot(const vec3<T>& vec1, const vec3<T>& vec2) {
        return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
    }

    template<typename T, typename S>
    vec3<T> haddamard(const vec3<T>& vec1, const vec3<T>& vec2) {
        return vec3<T>{vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z};
    }

    template <typename T, typename S>
    vec3<T> cross(const vec3<T>& vec1, const vec3<T>& vec2) {
        return vec3<T>{ 
            vec1.y * vec2.z - vec1.z * vec2.y,
            vec1.x * vec2.z - vec1.z * vec2.x,
            vec1.x * vec2.y - vec1.y * vec2.x,
        }
    }

    template<typename T>
    int64_t magnitude(const vec3<T>& vec) {
        return std::sqrt(
            vec.x*vec.x + vec.y*vec.y + vec.z*vec.z
        );
    }

    template<typename T> 
    void set(vec3<T>& vec, T val) {
        vec.x = val;
        vec.y = val;
        vec.z = val;
    }

    // vec2
    template<typename T, typename S>
    T dot(const vec2<T>& vec1, const vec2<T>& vec2) {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }

    template<typename T, typename S>
    vec2<T> haddamard(const vec2<T>& vec1, const vec2<T>& vec2) {
        return vec2<T>{vec1.x * vec2.x, vec1.y * vec2.y};
    }

    template <typename T, typename S>
    vec2<T> cross(const vec2<T>& vec1, const vec2<T>& vec2) {
        return vec2<T>{ 
            0,
            0,
            vec1.x * vec2.y - vec1.y * vec2.x,
        }
    }

    template<typename T>
    int64_t magnitude(const vec2<T>& vec) {
        return std::sqrt(
            vec.x*vec.x + vec.y*vec.y
        );
    }


    template<typename T> 
    void set(vec2<T>& vec, T val) {
        vec.x = val;
        vec.y = val;
    }

    
}