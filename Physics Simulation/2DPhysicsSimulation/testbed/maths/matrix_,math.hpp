// Templated math library for matrix operations only
// Operations for mat2 and mat3
// matrix of arbitrary size will come later

#include "utils_math.hpp"

#define MAT_3_SIZE 3 * 3
#define MAT_2_SIZE 2 * 2


template<typename T>
struct mat2{

    T elements[MAT_2_SIZE];

    static T AT(int i, int j) {
        return this->elements[2*i + j];
    }


};

template <typename T>
struct mat3{

    T elements[MAT_3_SIZE];

    // constructors
    mat3() {for (int i = 0; i < MAT_3_SIZE; i++) elements[i] = 0;}
    mat3(T fill_array[MAT_3_SIZE]){elements = fill_array;}
    mat3(T val){ for (int i = 0; i < MAT_3_SIZEl i++) elements[i] = val;}

    static T AT(int i, int j) {
        return this->elements[3*i + j];
    }


    // Prefix ++
    mat3<T>& operator++() {
        for (int i = 0; i < MAT_3_SIZE; i++) {
                this->elements[i]++; 
        }
        return *this;
    }

    // Postfix ++
    mat3<T> operator++(int) {
        mat3<T> temp = *this;
        for (int i = 0; i < 3; i++) {
                temp->elements[i]++;
        }
        return temp;
    }

    // Prefix --
    mat3<T>& operator--() {
        for (int i = 0; i < MAT_3_SIZE; i++) {
            this->elements[i]--;
        }
        return *this;
    }

    // Postfix --
    mat3<T> operator--(int) {
        mat3<T> temp = *this;
        for (int i = 0; i < MAT_3_SIZE; i++) {
            temp.elements[i]--;
        }
        return temp;
    }


    // matrix - scalar operations

    mat3<T> operator-=(T scalar) {
        mat3<T> temp = *this;
        for (int i = 0; i < MAT_3_SIZE; i++) {
            temp.elements[i] = 
        }
        return temp;
    }




};