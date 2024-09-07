// Templated math library for matrix operations only
// Operations for mat2 and mat3
// matrix of arbitrary size will come later

#include "utils_math.hpp"

#define MAT_3_SIZE (3 * 3)
#define MAT_2_SIZE (2 * 2)

namespace matrix {

    template<typename T>
    struct mat2{

        T elements[MAT_2_SIZE];

        // constructors
        mat2() { std::fill(elements, elements + MAT_2_SIZE, 0); }
        mat2(T fill_array[MAT_2_SIZE]) { std::copy(fill_array, fill_array + MAT_2_SIZE, elements); }
        mat2(T val) { std::fill(elements, elements + MAT_2_SIZE, val); }

        T AT(int i, int j) {
            return elements[2*i + j];
        }


        // Prefix ++
        mat2<T>& operator++() {
            for (int i = 0; i < MAT_2_SIZE; i++) {
                    this->elements[i]++; 
            }
            return *this;
        }

        // Postfix ++
        mat2<T> operator++(int) {
            mat2<T> temp = *this;
            for (int i = 0; i < MAT_2_SIZE; i++) {
                elements[i]++;
            }
            return temp;
        }

        // Prefix --
        mat2<T>& operator--() {
            for (int i = 0; i < MAT_2_SIZE; i++) {
                this->elements[i]--;
            }
            return *this;
        }

        // Postfix --
        mat2<T> operator--(int) {
            mat2<T> temp = *this;
            for (int i = 0; i < MAT_2_SIZE; i++) {
                temp.elements[i]--;
            }
            return temp;
        }


        // matrix - scalar operations

        mat2<T> operator-=(T scalar) {
            mat2<T> temp = *this;
            for (int i = 0; i < MAT_2_SIZE; i++) {
                temp.elements[i] -= scalar;
            }
            return temp;
        }


        // Example use : mat2 = mat2 * 3;
        mat2<T> operator*(T scalar) const {
            T temp[MAT_2_SIZE];
            for (int i = 0; i < MAT_2_SIZE; i++) {
                temp[i] = scalar * elements[i];
            }
            return mat2<T>(temp);
        }

        // Example use: mat2 *= 3;
        mat2<T>& operator*=(T scalar) {
            for (int i = 0; i < MAT_2_SIZE; i++) {
                elements[i] *= scalar;
            }
            return *this;
        }

        // Example use: mat2 = mat2 / 3;
        mat2<T> operator/(T scalar) const {
            if (std::fabs(scalar) > EPS) {
                T temp[MAT_2_SIZE];
                for (int i = 0; i < MAT_2_SIZE; i++) {
                    temp[i] /= scalar;
                }
                return mat2<T>(temp);
            } else {
                throw std::runtime_error("Dividing by zero or near zero");
            }
        }

        // Example use: mat /= 3;
        mat2<T>& operator/=(T scalar) {
            if (std::fabs(scalar) > EPS) {
                for (int i = 0; i < MAT_2_SIZE; i++) {
                    elements[i]/= scalar;
                } 
            } else {
                throw std::runtime_error("Dividing by zero or near zero");
            }
            return *this;
        }

        // matrix - matrix operations

        mat2<T>& operator+=(const mat2<T>& other) {
            for (int i = 0; i < MAT_2_SIZE; i++) {
                elements[i] += other.elements[i];
            }
            return *this;
        }


        mat2<T>& operator-=(const mat2<T>& other) {
            for (int i = 0; i < MAT_2_SIZE; i++) {
                elements[i] -= other.elements[i];
            }
            return *this;
        }

        mat2<T> operator-(const mat2<T>& other) const {
            T temp[MAT_2_SIZE] = elements;
            for (int i = 0; i < MAT_2_SIZE; i++) {
                temp[i] -= other.elements[i];
            }
            return mat2<T>(elements);
        }

        mat2<T> operator+(const mat2<T>& other) const {
            T temp[MAT_2_SIZE] = elements;
            for (int i = 0; i < MAT_2_SIZE; i++) {
                temp[i] += other.elements[i];
            }
            return mat2<T>(elements);
        }
        

    };

    template <typename T>
    struct mat3{

        T elements[MAT_3_SIZE];

        // constructors
        mat3() { std::fill(elements, elements + MAT_3_SIZE, 0); }
        mat3(T fill_array[MAT_3_SIZE]) { std::copy(fill_array, fill_array + MAT_3_SIZE, elements); }
        mat3(T val) { std::fill(elements, elements + MAT_3_SIZE, val); }

        T AT(int i, int j) {
            return elements[3*i + j];
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
            for (int i = 0; i < MAT_3_SIZE; i++) {
                elements[i]++; 
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
                elements[i]--;
            }
            return temp;
        }


        // matrix - scalar operations

        mat3<T> operator-=(T scalar) {
            mat3<T> temp = *this;
            for (int i = 0; i < MAT_3_SIZE; i++) {
                temp.elements[i] -= scalar;
            }
            return temp;
        }


        // Example use : mat3 = mat3 * 3;
        mat3<T> operator*(T scalar) const {
            T temp[MAT_3_SIZE];
            for (int i = 0; i < MAT_3_SIZE; i++) {
                temp[i] = scalar * elements[i];
            }
            return mat3<T>(temp);
        }

        // Example use: mat3 *= 3;
        mat3<T>& operator*=(T scalar) {
            for (int i = 0; i < MAT_3_SIZE; i++) {
                elements[i] *= scalar;
            }
            return *this;
        }


        // Example use: mat3 = mat3 / 3;
        mat3<T> operator/(T scalar) const {
            if (std::fabs(scalar) > EPS) {
                T temp[MAT_3_SIZE];
                for (int i = 0; i < MAT_3_SIZE; i++) {
                    temp[i] /= scalar;
                }
                return mat3<T>(temp);
            } else {
                throw std::runtime_error("Dividing by zero or near zero");
            }
        }

        // Example use: mat /= 3;
        mat3<T>& operator/=(T scalar) {
            if (std::fabs(scalar) > EPS) {
                for (int i = 0; i < MAT_3_SIZE; i++) {
                    elements[i]/= scalar;
                } 
            } else {
                throw std::runtime_error("Dividing by zero or near zero");
            }
            return *this;
        }

        // matrix - matrix operations

        mat3<T>& operator+=(const mat3<T>& other) {
            for (int i = 0; i < MAT_3_SIZE; i++) {
                elements[i] += other.elements[i];
            }
            return *this;
        }


        mat3<T>& operator-=(const mat3<T>& other) {
            for (int i = 0; i < MAT_3_SIZE; i++) {
                elements[i] -= other.elements[i];
            }
            return *this;
        }

        mat3<T> operator-(const mat3<T>& other) const {
            T temp[MAT_3_SIZE] = elements;
            for (int i = 0; i < MAT_3_SIZE; i++) {
                temp[i] -= other.elements[i];
            }
            return mat3<T>(elements);
        }

        mat3<T> operator+(const mat3<T>& other) const {
            T temp[MAT_3_SIZE] = elements;
            for (int i = 0; i < MAT_3_SIZE; i++) {
                temp[i] += other.elements[i];
            }
            return mat3<T>(elements);
        }
        
    };


    // standard math usage: 3*mat
    template <typename T, typename S>
    mat3<T> operator*(S scalar, const mat3<T>& mat) {
        T temp[MAT_3_SIZE];
        for (int i = 0; i < MAT_3_SIZE; i++) {
            temp[i] = scalar * mat.elements[i];
        }
        
        return mat3<T>(temp);
    }

    // not exactly standard math usage
    // 3/mat = {mat.x / 3, mat.y / 3};
    template <typename T, typename S>
    mat3<T> operator/(S scalar, const mat3<T>& mat) {
        T temp[MAT_3_SIZE];
        if (std::fabs(scalar) > EPS) {
            
            for (int i = 0; i < MAT_3_SIZE; i++) {
                temp[i] = mat.elements[i] / scalar;
            }
        }
        else {
            throw std::runtime_error("Dividing by zero or near zero");
        }
        return mat3<T>(temp);
    }

    // common matrix operations

    
    // mat3

    // Naiive
    template<typename T> 
    mat3<T> matmult(mat3<T>& mat1, mat3<T>& mat2) {
        mat3<T> res;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                T sum = 0;
                for (int k = 0; k < 3; k++) {
                    sum += mat1.AT(i, k) * mat2.AT(k, j);
                }    
                res.elements[3*i + j] = sum;
            }
        }
        return res;
    }

    template<typename T>
    void set(const mat3<T>& mat, T val) {
        for (int i = 0; i < MAT_3_SIZE; i++) {
            mat[i] = val;
        }
    }

    template<typename T>
    void print(mat3<T>& mat) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                std::cout << mat.AT(i, j) << ' ';
            }
            std::cout << std::endl;
        }
    }
    // mat2
    // Naiive
    template<typename T> 
    mat2<T> matmult(mat2<T>& mata, mat2<T>& matb) {
        mat2<T> res;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                T sum = 0;
                for (int k = 0; k < 2; k++) {
                    sum += mata.AT(i, k) * matb.AT(k, j);
                }    
                res.elements[2*i + j] = sum;
            }
        }
        return res;
    }

    template<typename T>
    void set(const mat2<T>& mat, T val) {
        for (int i = 0; i < MAT_2_SIZE; i++) {
            mat[i] = val;
        }
    }

    
    template<typename T>
    void print(mat2<T>& mat) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                std::cout<<mat.AT(i, j)<<' ';
            }
            std::cout<<std::endl;
        }
    }
}

