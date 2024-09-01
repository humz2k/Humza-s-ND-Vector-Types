/**
 * @file hqvec.hpp
 * @brief This file defines a template-based vector class with various
 * mathematical operations.
 */

#ifndef _HQVEC_HPP_
#define _HQVEC_HPP_

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

namespace HQ {

/**
 * @brief A template class representing a mathematical vector of fixed size.
 *
 * @tparam T The data type of the vector elements.
 * @tparam n The dimension of the vector.
 */
template <typename T, std::size_t n> class vec {
  private:
    /** @brief Internal array to hold the vector data. */
    T m_data[n] = {0};

  public:
    /**
     * @brief Constructs a vector from a variable number of arguments.
     *
     * @tparam Args Variadic template parameter for constructor arguments.
     * @param args The elements to initialize the vector with.
     */
    template <typename... Args>
    vec(Args... args) : m_data{static_cast<T>(args)...} {
        static_assert(n > 1, "no length 1 vector");
    }

    /**
     * @brief Constructs a vector by copying from another vector with a possibly
     * different data type.
     *
     * @tparam T1 The data type of the input vector.
     * @param v The input vector to copy from.
     */
    template <typename T1> vec(vec<T1, n> v) {
        static_assert(n > 1, "no length 1 vector");
        for (int i = 0; i < n; i++) {
            m_data[i] = v[i];
        }
    }

    /**
     * @brief Constructs a vector from an array.
     *
     * @param in The input array to initialize the vector with.
     * @param count The number of elements to copy from the array.
     */
    vec(T in[], int count = n) {
        static_assert(n > 1, "no length 1 vector");
        for (int i = 0; i < count; i++) {
            m_data[i] = in[i];
        }
    }

    /**
     * @brief Accesses an element of the vector.
     *
     * @param i The index of the element.
     * @return T& Reference to the element.
     */
    T& operator[](int i) { return m_data[i]; }

    /**
     * @brief Accesses an element of the vector (const version).
     *
     * @param i The index of the element.
     * @return T The value of the element.
     */
    T operator[](int i) const { return m_data[i]; }

    /**
     * @brief Accesses an element of the vector by index at compile-time.
     *
     * @tparam i The index of the element.
     * @return T& Reference to the element.
     */
    template <int i> T& get() {
        static_assert((i >= 0) && (i < n), "index out of bounds");
        return m_data[i];
    }

    /**
     * @brief Accesses an element of the vector by index at compile-time (const
     * version).
     *
     * @tparam i The index of the element.
     * @return T The value of the element.
     */
    template <int i> T get() const {
        static_assert((i >= 0) && (i < n), "index out of bounds");
        return m_data[i];
    }

    /**
     * @brief Adds two vectors element-wise.
     *
     * @param other The vector to add.
     * @return vec<T, n> The resulting vector.
     */
    vec<T, n> operator+(const vec<T, n>& other) const {
        vec<T, n> out;
        for (int i = 0; i < n; i++) {
            out[i] = m_data[i] + other[i];
        }
        return out;
    }

    /**
     * @brief Adds vector and scalar
     *
     * @param other Scalar
     * @return vec<T, n> The resulting vector.
     */
    vec<T, n> operator+(T other) const {
        vec<T, n> out;
        for (int i = 0; i < n; i++) {
            out[i] = m_data[i] + other;
        }
        return out;
    }

    /**
     * @brief Multiplies two vectors element-wise.
     *
     * @param other The vector to multiply.
     * @return vec<T, n> The resulting vector.
     */
    vec<T, n> operator*(const vec<T, n>& other) const {
        vec<T, n> out;
        for (int i = 0; i < n; i++) {
            out[i] = m_data[i] * other[i];
        }
        return out;
    }

    /**
     * @brief Multiplies vector and scalar
     *
     * @param other Scalar
     * @return vec<T, n> The resulting vector.
     */
    vec<T, n> operator*(T other) const {
        vec<T, n> out;
        for (int i = 0; i < n; i++) {
            out[i] = m_data[i] * other;
        }
        return out;
    }

    /**
     * @brief Subtracts two vectors element-wise.
     *
     * @param other The vector to subtract.
     * @return vec<T, n> The resulting vector.
     */
    vec<T, n> operator-(const vec<T, n>& other) const {
        vec<T, n> out;
        for (int i = 0; i < n; i++) {
            out[i] = m_data[i] - other[i];
        }
        return out;
    }

    /**
     * @brief Subtracts vector and scalar
     *
     * @param other The vector to subtract.
     * @return vec<T, n> The resulting vector.
     */
    vec<T, n> operator-(T other) const {
        vec<T, n> out;
        for (int i = 0; i < n; i++) {
            out[i] = m_data[i] - other;
        }
        return out;
    }

    /**
     * @brief Divides two vectors element-wise.
     *
     * @param other The vector to divide by.
     * @return vec<T, n> The resulting vector.
     */
    vec<T, n> operator/(const vec<T, n>& other) const {
        vec<T, n> out;
        for (int i = 0; i < n; i++) {
            out[i] = m_data[i] / other[i];
        }
        return out;
    }

    /**
     * @brief Divides vector and scalar
     *
     * @param other Scalar
     * @return vec<T, n> The resulting vector.
     */
    vec<T, n> operator/(T other) const {
        vec<T, n> out;
        for (int i = 0; i < n; i++) {
            out[i] = m_data[i] / other;
        }
        return out;
    }

    /**
     * @brief Compares two vectors for equality.
     *
     * @param other The vector to compare with.
     * @return bool True if the vectors are equal, false otherwise.
     */
    bool operator==(const vec<T, n>& other) const {
        for (int i = 0; i < n; i++) {
            if (other[i] != m_data[i])
                return false;
        }
        return true;
    }

    /**
     * @brief Compares two vectors for inequality.
     *
     * @param other The vector to compare with.
     * @return bool True if the vectors are not equal, false otherwise.
     */
    bool operator!=(const vec<T, n>& other) const {
        for (int i = 0; i < n; i++) {
            if (other[i] != m_data[i])
                return true;
        }
        return false;
    }

    /**
     * @brief Converts the vector to a pointer to its internal data.
     *
     * @return T* Pointer to the internal data.
     */
    operator T*() { return m_data; }

    /**
     * @brief Converts the vector to a const pointer to its internal data.
     *
     * @return const T* Const pointer to the internal data.
     */
    operator const T*() const { return m_data; }

    /**
     * @brief Copies the vector's data to an external array.
     *
     * @param out The output array.
     * @param count The number of elements to copy.
     */
    void copy_to(T out[], int count = n) const {
        for (int i = 0; i < count; i++) {
            out[i] = m_data[i];
        }
    }

    /**
     * @brief Converts the vector to another data type.
     *
     * @tparam T1 The target data type.
     * @return vec<T1, n> The resulting vector with the new data type.
     */
    template <typename T1> vec<T1, n> to() const {
        vec<T1, n> out;
        for (int i = 0; i < n; i++) {
            out[i] = m_data[i];
        }
        return out;
    }

    /**
     * @brief Conversion operator to another vector type.
     *
     * @tparam T1 The target data type.
     * @return vec<T1, n> The resulting vector with the new data type.
     */
    template <typename T1> operator vec<T1, n>() const { return to<T1, n>(); }

    /**
     * @brief Expands the vector to a larger size.
     *
     * `n1` should be bigger than `n`.
     *
     * @tparam n1 The new size of the vector.
     * @return vec<T, n1> The resulting vector with the expanded size.
     */
    template <std::size_t n1> vec<T, n1> expand() {
        static_assert(n1 > n, "n1 is smaller or equal to n");
        vec<T, n1> out;
        for (int i = 0; i < n; i++) {
            out[i] = m_data[i];
        }
        return out;
    }

    /**
     * @brief Shrinks the vector to a smaller size.
     *
     * `n1` should be less than `n` and bigger than `1`.
     *
     * @tparam n1 The new size of the vector.
     * @return vec<T, n1> The resulting vector with the shrunk size.
     */
    template <std::size_t n1> vec<T, n1> shrink() {
        static_assert((n1 < n) && (n1 > 1), "n1 is bigger or equal to n");
        vec<T, n1> out;
        for (int i = 0; i < n1; i++) {
            out[i] = m_data[i];
        }
        return out;
    }

    /**
     * @brief Returns the size of the vector.
     *
     * @return std::size_t The size of the vector.
     */
    std::size_t size() const { return n; }

    /**
     * @brief Computes the squared length of the vector.
     *
     * @return T The squared length of the vector.
     */
    T length2() const {
        T out = 0;
        for (int i = 0; i < n; i++) {
            T temp = m_data[i];
            out += temp * temp;
        }
        return out;
    }

    /**
     * @brief Computes the length of the vector.
     *
     * @return T The length of the vector.
     */
    T length() const { return sqrt(length2()); }

    /**
     * @brief Computes the squared distance between two vectors.
     *
     * @param v The other vector.
     * @return T The squared distance between the two vectors.
     */
    T distance2(const vec<T, n> v) const { return ((*this) - v).length2(); }

    /**
     * @brief Computes the distance between two vectors.
     *
     * @param v The other vector.
     * @return T The distance between the two vectors.
     */
    T distance(const vec<T, n> v) const { return ((*this) - v).length(); }

    /**
     * @brief Computes the dot product of two vectors
     *
     * @param v The other vector.
     * @return T The dot product of the two vectors.
     */
    T dot(const vec<T, n> v) const {
        T out = 0;
        for (int i = 0; i < n; i++) {
            out += m_data[i] * v[i];
        }
        return out;
    }

    /**
     * @brief Converts the vector to a string representation.
     *
     * @return std::string The string representation of the vector.
     */
    std::string to_string() const {
        std::string out = "vec<" + std::string(typeid(T).name()) + "," +
                          std::to_string(n) + ">(";
        for (int i = 0; i < (n - 1); i++) {
            out += std::to_string(m_data[i]) + ",";
        }
        out += std::to_string(m_data[n - 1]) + ")";
        return out;
    }

    /**
     * @brief Outputs the vector to a stream.
     *
     * @param os The output stream.
     * @param v The vector to output.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const vec<T, n>& v) {
        os << v.to_string();
        return os;
    }
};

/**
 * @brief A specialized class template for 4-dimensional vectors.
 *
 * @tparam T Type of the vector elements.
 */
template <typename T> class vec<T, 4> {
  public:
    /** @brief X component of the vector. */
    T x = 0;
    /** @brief Y component of the vector. */
    T y = 0;
    /** @brief Z component of the vector. */
    T z = 0;
    /** @brief W component of the vector. */
    T w = 0;

    /**
     * @brief Constructs a 4-dimensional vector with specified components.
     *
     * @param x_ X component.
     * @param y_ Y component.
     * @param z_ Z component.
     * @param w_ W component.
     */
    vec(T x_ = 0, T y_ = 0, T z_ = 0, T w_ = 0) : x(x_), y(y_), z(z_), w(w_) {}

    /**
     * @brief Constructs a 4-dimensional vector from an array.
     *
     * @param in Array of components.
     * @param count Number of components to initialize, defaults to 4.
     */
    vec(T in[], int count = 4) {
        if (count > 0)
            x = in[0];
        if (count > 1)
            y = in[1];
        if (count > 2)
            z = in[2];
        if (count > 3)
            w = in[3];
    }

    /**
     * @brief Accesses an element of the vector.
     *
     * @param i The index of the element.
     * @return T& Reference to the element.
     */
    T& operator[](int i) {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            assert(((i >= 0) && (i < 4)) && "index out of bounds");
            return x;
        }
    }

    /**
     * @brief Accesses an element of the vector (const version).
     *
     * @param i The index of the element.
     * @return T The value of the element.
     */
    T operator[](int i) const {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            assert(((i >= 0) && (i < 4)) && "index out of bounds");
            return x;
        }
    }

    /**
     * @brief Accesses an element of the vector by index at compile-time.
     *
     * @tparam i The index of the element.
     * @return T& Reference to the element.
     */
    template <int i> T& get() {
        static_assert((i >= 0) && (i < 4), "index out of bounds");
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            // should not be reachable
            return x;
        }
    }

    /**
     * @brief Accesses an element of the vector by index at compile-time (const
     * version).
     *
     * @tparam i The index of the element.
     * @return T The value of the element.
     */
    template <int i> T get() const {
        static_assert((i >= 0) && (i < 4), "index out of bounds");
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            // should not be reachable
            return x;
        }
    }

    /**
     * @brief Adds two vectors element-wise.
     *
     * @param other The vector to add.
     * @return vec<T, 4> The resulting vector.
     */
    vec<T, 4> operator+(const vec<T, 4>& other) const {
        return vec<T, 4>(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    /**
     * @brief Adds vector and scalar
     *
     * @param other Scalar
     * @return vec<T, 4> The resulting vector.
     */
    vec<T, 4> operator+(T other) const {
        return vec<T, 4>(x + other, y + other, z + other, w + other);
    }

    /**
     * @brief Subtracts two vectors element-wise.
     *
     * @param other The vector to subtract.
     * @return vec<T, 4> The resulting vector.
     */
    vec<T, 4> operator-(const vec<T, 4>& other) const {
        return vec<T, 4>(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    /**
     * @brief Subtracts vector and scalar
     *
     * @param other Scalar
     * @return vec<T, 4> The resulting vector.
     */
    vec<T, 4> operator-(T other) const {
        return vec<T, 4>(x - other, y - other, z - other, w - other);
    }

    /**
     * @brief Multiplies two vectors element-wise.
     *
     * @param other The vector to multiply.
     * @return vec<T, 4> The resulting vector.
     */
    vec<T, 4> operator*(const vec<T, 4>& other) const {
        return vec<T, 4>(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    /**
     * @brief Multiplies vector and scalar
     *
     * @param other Scalar
     * @return vec<T, 4> The resulting vector.
     */
    vec<T, 4> operator*(T other) const {
        return vec<T, 4>(x * other, y * other, z * other, w * other);
    }

    /**
     * @brief Divides two vectors element-wise.
     *
     * @param other The vector to divide by.
     * @return vec<T, 4> The resulting vector.
     */
    vec<T, 4> operator/(const vec<T, 4>& other) const {
        return vec<T, 4>(x / other.x, y / other.y, z / other.z, w / other.w);
    }

    /**
     * @brief Divides vector and scalar
     *
     * @param other Scalar
     * @return vec<T, 4> The resulting vector.
     */
    vec<T, 4> operator/(T other) const {
        return vec<T, 4>(x / other, y / other, z / other, w / other);
    }

    /**
     * @brief Compares two vectors for equality.
     *
     * @param other The vector to compare with.
     * @return bool True if the vectors are equal, false otherwise.
     */
    bool operator==(const vec<T, 4>& other) const {
        return (other.x == x) && (other.y == y) && (other.z == z) &&
               (other.w == w);
    }

    /**
     * @brief Compares two vectors for inequality.
     *
     * @param other The vector to compare with.
     * @return bool True if the vectors are not equal, false otherwise.
     */
    bool operator!=(const vec<T, 4>& other) const {
        return (other.x != x) || (other.y != y) || (other.z != z) ||
               (other.w != w);
    }

    /**
     * @brief Converts the vector to a pointer to its internal data.
     *
     * @return T* Pointer to the internal data.
     */
    operator T*() { return reinterpret_cast<T*>(this); }

    /**
     * @brief Converts the vector to a const pointer to its internal data.
     *
     * @return const T* Const pointer to the internal data.
     */
    operator const T*() const { return reinterpret_cast<const T*>(this); }

    /**
     * @brief Copies the vector's data to an external array.
     *
     * @param out The output array.
     * @param count The number of elements to copy.
     */
    void copy_to(T out[], int count = 4) const {
        if (count > 0)
            out[0] = x;
        if (count > 1)
            out[1] = y;
        if (count > 2)
            out[2] = z;
        if (count > 3)
            out[3] = w;
    }

    /**
     * @brief Converts the vector to another data type.
     *
     * @tparam T1 The target data type.
     * @return vec<T1, 4> The resulting vector with the new data type.
     */
    template <typename T1> vec<T1, 4> to() const {
        return vec<T1, 4>(x, y, z, w);
    }

    /**
     * @brief Conversion operator to another vector type.
     *
     * @tparam T1 The target data type.
     * @return vec<T1, 4> The resulting vector with the new data type.
     */
    template <typename T1> operator vec<T1, 4>() const { return to<T1>(); }

    /**
     * @brief Explicit conversion to some generic vector type
     *
     * @tparam T1 The type of vector to convert to.
     * @return T1 The converted vector.
     */
    template <typename T1> T1 to_generic() {
        T1 out;
        out.x = x;
        out.y = y;
        out.z = z;
        out.w = w;
        return out;
    }

    /**
     * @brief Explicit conversion from some generic vector type
     *
     * @tparam T1 The type of vector to convert from.
     * @return vec<T,4> The converted vector.
     */
    template <typename T1> static vec<T, 4> from_generic(const T1& other) {
        return vec<T, 4>(other.x, other.y, other.z, other.w);
    }

    /**
     * @brief Expands the vector to a larger size.
     *
     * `n1` should be bigger than `4`.
     *
     * @tparam n1 The new size of the vector.
     * @return vec<T, n1> The resulting vector with the expanded size.
     */
    template <std::size_t n1> vec<T, n1> expand() {
        static_assert(n1 > 4, "n1 is smaller or equal to 3");
        return vec<T, n1>(x, y, z, w);
    }

    /**
     * @brief Shrinks the vector to a smaller size.
     *
     * `n1` should be smaller than `4` and bigger than `1`.
     *
     * @tparam n1 The new size of the vector.
     * @return vec<T, n1> The resulting vector with the shrunk size.
     */
    template <std::size_t n1> vec<T, n1> shrink() {
        static_assert((n1 < 4) && (n1 > 1), "n1 is bigger or equal to 3");
        if (n1 == 3)
            return vec<T, n1>(x, y, z);
        return vec<T, n1>(x, y);
    }

    /**
     * @brief Returns the size of the vector.
     *
     * @return std::size_t The size of the vector.
     */
    std::size_t size() const { return 4; }

    /**
     * @brief Computes the squared length of the vector.
     *
     * @return T The squared length of the vector.
     */
    T length2() const { return x * x + y * y + z * z + w * w; }

    /**
     * @brief Computes the length of the vector.
     *
     * @return T The length of the vector.
     */
    T length() const { return sqrt(length2()); }

    /**
     * @brief Computes the squared distance between two vectors.
     *
     * @param v The other vector.
     * @return T The squared distance between the two vectors.
     */
    T distance2(const vec<T, 4> v) { return ((*this) - v).length2(); }

    /**
     * @brief Computes the distance between two vectors.
     *
     * @param v The other vector.
     * @return T The distance between the two vectors.
     */
    T distance(const vec<T, 4> v) { return ((*this) - v).length(); }

    /**
     * @brief Computes the dot product of two vectors
     *
     * @param v The other vector.
     * @return T The dot product of the two vectors.
     */
    T dot(const vec<T, 4> v) const {
        return x * v.x + y * v.y + z * v.z + w * v.w;
    }

    /**
     * @brief Converts the vector to a string representation.
     *
     * @return std::string The string representation of the vector.
     */
    std::string to_string() const {
        return "vec<" + std::string(typeid(T).name()) + ",4>(" +
               std::to_string(x) + "," + std::to_string(y) + "," +
               std::to_string(z) + "," + std::to_string(w) + ")";
    }

    /**
     * @brief Outputs the vector to a stream.
     *
     * @param os The output stream.
     * @param v The vector to output.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const vec<T, 4>& v) {
        os << v.to_string();
        return os;
    }
};

/**
 * @brief A specialized class template for 3-dimensional vectors.
 *
 * @tparam T Type of the vector elements.
 */
template <typename T> class vec<T, 3> {
  public:
    /** @brief X component of the vector. */
    T x = 0;
    /** @brief Y component of the vector. */
    T y = 0;
    /** @brief Z component of the vector. */
    T z = 0;

    /**
     * @brief Constructs a 3-dimensional vector with specified components.
     *
     * @param x_ X component.
     * @param y_ Y component.
     * @param z_ Z component.
     */
    vec(T x_ = 0, T y_ = 0, T z_ = 0) : x(x_), y(y_), z(z_) {}

    /**
     * @brief Constructs a 3-dimensional vector from an array.
     *
     * @param in Array of components.
     * @param count Number of components to initialize, defaults to 3.
     */
    vec(T in[], int count = 3) {
        if (count > 0)
            x = in[0];
        if (count > 1)
            y = in[1];
        if (count > 2)
            z = in[2];
    }

    /**
     * @brief Accesses an element of the vector.
     *
     * @param i The index of the element.
     * @return T& Reference to the element.
     */
    T& operator[](int i) {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            assert(((i >= 0) && (i < 3)) && "index out of bounds");
            return x;
        }
    }

    /**
     * @brief Accesses an element of the vector (const version).
     *
     * @param i The index of the element.
     * @return T The value of the element.
     */
    T operator[](int i) const {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            assert(((i >= 0) && (i < 3)) && "index out of bounds");
            return x;
        }
    }

    /**
     * @brief Accesses an element of the vector by index at compile-time.
     *
     * @tparam i The index of the element.
     * @return T& Reference to the element.
     */
    template <int i> T& get() {
        static_assert((i >= 0) && (i < 3), "index out of bounds");
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            // should not be reachable
            return x;
        }
    }

    /**
     * @brief Accesses an element of the vector by index at compile-time (const
     * version).
     *
     * @tparam i The index of the element.
     * @return T The value of the element.
     */
    template <int i> T get() const {
        static_assert((i >= 0) && (i < 3), "index out of bounds");
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            // should not be reachable
            return x;
        }
    }

    /**
     * @brief Adds two vectors element-wise.
     *
     * @param other The vector to add.
     * @return vec<T, 3> The resulting vector.
     */
    vec<T, 3> operator+(const vec<T, 3>& other) const {
        return vec<T, 3>(x + other.x, y + other.y, z + other.z);
    }

    /**
     * @brief Adds vector and scalar
     *
     * @param other Scalar
     * @return vec<T, 3> The resulting vector.
     */
    vec<T, 3> operator+(T other) const {
        return vec<T, 3>(x + other, y + other, z + other);
    }

    /**
     * @brief Subtracts two vectors element-wise.
     *
     * @param other The vector to subtract.
     * @return vec<T, 3> The resulting vector.
     */
    vec<T, 3> operator-(const vec<T, 3>& other) const {
        return vec<T, 3>(x - other.x, y - other.y, z - other.z);
    }

    /**
     * @brief Subtracts vector and scalar
     *
     * @param other Scalar
     * @return vec<T, 3> The resulting vector.
     */
    vec<T, 3> operator-(T other) const {
        return vec<T, 3>(x - other, y - other, z - other);
    }

    /**
     * @brief Multiplies two vectors element-wise.
     *
     * @param other The vector to multiply.
     * @return vec<T, 3> The resulting vector.
     */
    vec<T, 3> operator*(const vec<T, 3>& other) const {
        return vec<T, 3>(x * other.x, y * other.y, z * other.z);
    }

    /**
     * @brief Multiplies vector and scalar
     *
     * @param other Scalar
     * @return vec<T, 3> The resulting vector.
     */
    vec<T, 3> operator*(T other) const {
        return vec<T, 3>(x * other, y * other, z * other);
    }

    /**
     * @brief Divides two vectors element-wise.
     *
     * @param other The vector to divide by.
     * @return vec<T, 3> The resulting vector.
     */
    vec<T, 3> operator/(const vec<T, 3>& other) const {
        return vec<T, 3>(x / other.x, y / other.y, z / other.z);
    }

    /**
     * @brief Divides vector and scalar
     *
     * @param other Scalar
     * @return vec<T, 3> The resulting vector.
     */
    vec<T, 3> operator/(T other) const {
        return vec<T, 3>(x / other, y / other, z / other);
    }

    /**
     * @brief Compares two vectors for equality.
     *
     * @param other The vector to compare with.
     * @return bool True if the vectors are equal, false otherwise.
     */
    bool operator==(const vec<T, 3>& other) const {
        return (other.x == x) && (other.y == y) && (other.z == z);
    }

    /**
     * @brief Compares two vectors for inequality.
     *
     * @param other The vector to compare with.
     * @return bool True if the vectors are not equal, false otherwise.
     */
    bool operator!=(const vec<T, 3>& other) const {
        return (other.x != x) || (other.y != y) || (other.z != z);
    }

    /**
     * @brief Converts the vector to a pointer to its internal data.
     *
     * @return T* Pointer to the internal data.
     */
    operator T*() { return reinterpret_cast<T*>(this); }

    /**
     * @brief Converts the vector to a const pointer to its internal data.
     *
     * @return const T* Const pointer to the internal data.
     */
    operator const T*() const { return reinterpret_cast<const T*>(this); }

    /**
     * @brief Copies the vector's data to an external array.
     *
     * @param out The output array.
     * @param count The number of elements to copy.
     */
    void copy_to(T out[], int count = 3) const {
        if (count > 0)
            out[0] = x;
        if (count > 1)
            out[1] = y;
        if (count > 2)
            out[2] = z;
    }

    /**
     * @brief Converts the vector to another data type.
     *
     * @tparam T1 The target data type.
     * @return vec<T1, 3> The resulting vector with the new data type.
     */
    template <typename T1> vec<T1, 3> to() const { return vec<T1, 3>(x, y, z); }

    /**
     * @brief Conversion operator to another vector type.
     *
     * @tparam T1 The target data type.
     * @return vec<T1, 3> The resulting vector with the new data type.
     */
    template <typename T1> operator vec<T1, 3>() const { return to<T1>(); }

    /**
     * @brief Explicit conversion to some generic vector type
     *
     * @tparam T1 The type of vector to convert to.
     * @return T1 The converted vector.
     */
    template <typename T1> T1 to_generic() {
        T1 out;
        out.x = x;
        out.y = y;
        out.z = z;
        return out;
    }

    /**
     * @brief Explicit conversion from some generic vector type
     *
     * @tparam T1 The type of vector to convert from.
     * @return vec<T,3> The converted vector.
     */
    template <typename T1> static vec<T, 3> from_generic(const T1& other) {
        return vec<T, 3>(other.x, other.y, other.z);
    }

    /**
     * @brief Expands the vector to a larger size.
     *
     * `n1` should be bigger than `3`.
     *
     * @tparam n1 The new size of the vector.
     * @return vec<T, n1> The resulting vector with the expanded size.
     */
    template <std::size_t n1> vec<T, n1> expand() {
        static_assert(n1 > 3, "n1 is smaller or equal to 3");
        return vec<T, n1>(x, y, z);
    }

    /**
     * @brief Shrinks the vector to a smaller size.
     *
     * `n1` should be smaller than `3` and bigger than `1`.
     *
     * @tparam n1 The new size of the vector.
     * @return vec<T, n1> The resulting vector with the shrunk size.
     */
    template <std::size_t n1> vec<T, n1> shrink() {
        static_assert((n1 < 3) && (n1 > 1), "n1 is bigger or equal to 3");
        return vec<T, n1>(x, y);
    }

    /**
     * @brief Returns the size of the vector.
     *
     * @return std::size_t The size of the vector.
     */
    std::size_t size() const { return 3; }

    /**
     * @brief Computes the squared length of the vector.
     *
     * @return T The squared length of the vector.
     */
    T length2() const { return x * x + y * y + z * z; }

    /**
     * @brief Computes the length of the vector.
     *
     * @return T The length of the vector.
     */
    T length() const { return sqrt(length2()); }

    /**
     * @brief Computes the squared distance between two vectors.
     *
     * @param v The other vector.
     * @return T The squared distance between the two vectors.
     */
    T distance2(const vec<T, 3> v) { return ((*this) - v).length2(); }

    /**
     * @brief Computes the distance between two vectors.
     *
     * @param v The other vector.
     * @return T The distance between the two vectors.
     */
    T distance(const vec<T, 3> v) { return ((*this) - v).length(); }

    /**
     * @brief Computes the dot product of two vectors
     *
     * @param v The other vector.
     * @return T The dot product of the two vectors.
     */
    T dot(const vec<T, 3> v) const { return x * v.x + y * v.y + z * v.z; }

    /**
     * @brief Computers the cross product of two 3D vectors
     *
     * @param v The other vector.
     * @return vec<T,3> The cross product of the two 3D vectors.
     */
    vec<T, 3> cross(const vec<T, 3> v) const {
        return vec<T, 3>(y * v.z - z * v.y, z * v.x - x * b.z,
                         x * v.y - y * v.x);
    }

    /**
     * @brief Converts the vector to a string representation.
     *
     * @return std::string The string representation of the vector.
     */
    std::string to_string() const {
        return "vec<" + std::string(typeid(T).name()) + ",3>(" +
               std::to_string(x) + "," + std::to_string(y) + "," +
               std::to_string(z) + ")";
    }

    /**
     * @brief Outputs the vector to a stream.
     *
     * @param os The output stream.
     * @param v The vector to output.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const vec<T, 3>& v) {
        os << v.to_string();
        return os;
    }
};

/**
 * @brief A specialized class template for 2-dimensional vectors.
 *
 * @tparam T Type of the vector elements.
 */
template <typename T> class vec<T, 2> {
  public:
    /** @brief X component of the vector. */
    T x = 0;
    /** @brief Y component of the vector. */
    T y = 0;

    /**
     * @brief Constructs a 2-dimensional vector with specified components.
     *
     * @param x_ X component.
     * @param y_ Y component.
     */
    vec(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}

    /**
     * @brief Constructs a 2-dimensional vector from an array.
     *
     * @param in Array of components.
     * @param count Number of components to initialize, defaults to 2.
     */
    vec(T in[], int count = 2) {
        if (count > 0)
            x = in[0];
        if (count > 1)
            y = in[1];
    }

    /**
     * @brief Accesses an element of the vector.
     *
     * @param i The index of the element.
     * @return T& Reference to the element.
     */
    T& operator[](int i) {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            assert(((i >= 0) && (i < 2)) && "index out of bounds");
            return x;
        }
    }

    /**
     * @brief Accesses an element of the vector (const version).
     *
     * @param i The index of the element.
     * @return T The value of the element.
     */
    T operator[](int i) const {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            assert(((i >= 0) && (i < 2)) && "index out of bounds");
            return x;
        }
    }

    /**
     * @brief Accesses an element of the vector by index at compile-time.
     *
     * @tparam i The index of the element.
     * @return T& Reference to the element.
     */
    template <int i> T& get() {
        static_assert((i >= 0) && (i < 2), "index out of bounds");
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            // should not be reachable
            return x;
        }
    }

    /**
     * @brief Accesses an element of the vector by index at compile-time (const
     * version).
     *
     * @tparam i The index of the element.
     * @return T The value of the element.
     */
    template <int i> T get() const {
        static_assert((i >= 0) && (i < 2), "index out of bounds");
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            // should not be reachable
            return x;
        }
    }

    /**
     * @brief Adds two vectors element-wise.
     *
     * @param other The vector to add.
     * @return vec<T, 2> The resulting vector.
     */
    vec<T, 2> operator+(const vec<T, 2>& other) const {
        return vec<T, 2>(x + other.x, y + other.y);
    }

    /**
     * @brief Adds vector and scalar
     *
     * @param other Scalar
     * @return vec<T, 2> The resulting vector.
     */
    vec<T, 2> operator+(T other) const {
        return vec<T, 2>(x + other, y + other);
    }

    /**
     * @brief Subtracts two vectors element-wise.
     *
     * @param other The vector to subtract.
     * @return vec<T, 2> The resulting vector.
     */
    vec<T, 2> operator-(const vec<T, 2>& other) const {
        return vec<T, 2>(x - other.x, y - other.y);
    }

    /**
     * @brief Subtracts vector and scalar
     *
     * @param other Scalar
     * @return vec<T, 2> The resulting vector.
     */
    vec<T, 2> operator-(T other) const {
        return vec<T, 2>(x - other, y - other);
    }

    /**
     * @brief Multiplies two vectors element-wise.
     *
     * @param other The vector to multiply.
     * @return vec<T, 2> The resulting vector.
     */
    vec<T, 2> operator*(const vec<T, 2>& other) const {
        return vec<T, 2>(x * other.x, y * other.y);
    }

    /**
     * @brief Multiplies vector and scalar
     *
     * @param other Scalar
     * @return vec<T, 2> The resulting vector.
     */
    vec<T, 2> operator*(T other) const {
        return vec<T, 2>(x * other, y * other);
    }

    /**
     * @brief Divides two vectors element-wise.
     *
     * @param other The vector to divide by.
     * @return vec<T, 2> The resulting vector.
     */
    vec<T, 2> operator/(const vec<T, 2>& other) const {
        return vec<T, 2>(x / other.x, y / other.y);
    }

    /**
     * @brief Divides vector and scalar
     *
     * @param other Scalar
     * @return vec<T, 2> The resulting vector.
     */
    vec<T, 2> operator/(T other) const {
        return vec<T, 2>(x / other, y / other);
    }

    /**
     * @brief Compares two vectors for equality.
     *
     * @param other The vector to compare with.
     * @return bool True if the vectors are equal, false otherwise.
     */
    bool operator==(const vec<T, 2>& other) const {
        return (other.x == x) && (other.y == y);
    }

    /**
     * @brief Compares two vectors for inequality.
     *
     * @param other The vector to compare with.
     * @return bool True if the vectors are not equal, false otherwise.
     */
    bool operator!=(const vec<T, 2>& other) const {
        return (other.x != x) || (other.y != y);
    }

    /**
     * @brief Converts the vector to a pointer to its internal data.
     *
     * @return T* Pointer to the internal data.
     */
    operator T*() { return reinterpret_cast<T*>(this); }

    /**
     * @brief Converts the vector to a const pointer to its internal data.
     *
     * @return const T* Const pointer to the internal data.
     */
    operator const T*() const { return reinterpret_cast<const T*>(this); }

    /**
     * @brief Copies the vector's data to an external array.
     *
     * @param out The output array.
     * @param count The number of elements to copy.
     */
    void copy_to(T out[], int count = 2) const {
        if (count > 0)
            out[0] = x;
        if (count > 1)
            out[1] = y;
    }

    /**
     * @brief Converts the vector to another data type.
     *
     * @tparam T1 The target data type.
     * @return vec<T1, 2> The resulting vector with the new data type.
     */
    template <typename T1> vec<T1, 2> to() const { return vec<T1, 2>(x, y); }

    /**
     * @brief Conversion operator to another vector type.
     *
     * @tparam T1 The target data type.
     * @return vec<T1, 2> The resulting vector with the new data type.
     */
    template <typename T1> operator vec<T1, 2>() const { return to<T1>(); }

    /**
     * @brief Explicit conversion to some generic vector type
     *
     * @tparam T1 The type of vector to convert to.
     * @return T1 The converted vector.
     */
    template <typename T1> T1 to_generic() {
        T1 out;
        out.x = x;
        out.y = y;
        return out;
    }

    /**
     * @brief Explicit conversion from some generic vector type
     *
     * @tparam T1 The type of vector to convert from.
     * @return vec<T,2> The converted vector.
     */
    template <typename T1> static vec<T, 2> from_generic(const T1& other) {
        return vec<T, 2>(other.x, other.y);
    }

    /**
     * @brief Expands the vector to a larger size.
     *
     * `n1` should be bigger than `2`.
     *
     * @tparam n1 The new size of the vector.
     * @return vec<T, n1> The resulting vector with the expanded size.
     */
    template <std::size_t n1> vec<T, n1> expand() {
        static_assert(n1 > 2, "n1 is smaller or equal to 3");
        return vec<T, n1>(x, y);
    }

    /**
     * @brief Returns the size of the vector.
     *
     * @return std::size_t The size of the vector.
     */
    std::size_t size() const { return 2; }

    /**
     * @brief Computes the squared length of the vector.
     *
     * @return T The squared length of the vector.
     */
    T length2() const { return x * x + y * y; }

    /**
     * @brief Computes the length of the vector.
     *
     * @return T The length of the vector.
     */
    T length() const { return sqrt(length2()); }

    /**
     * @brief Computes the squared distance between two vectors.
     *
     * @param v The other vector.
     * @return T The squared distance between the two vectors.
     */
    T distance2(const vec<T, 2> v) { return ((*this) - v).length2(); }

    /**
     * @brief Computes the distance between two vectors.
     *
     * @param v The other vector.
     * @return T The distance between the two vectors.
     */
    T distance(const vec<T, 2> v) { return ((*this) - v).length(); }

    /**
     * @brief Computes the dot product of two vectors
     *
     * @param v The other vector.
     * @return T The dot product of the two vectors.
     */
    T dot(const vec<T, 2> v) const { return x * v.x + y * v.y; }

    /**
     * @brief Converts the vector to a string representation.
     *
     * @return std::string The string representation of the vector.
     */
    std::string to_string() const {
        return "vec<" + std::string(typeid(T).name()) + ",2>(" +
               std::to_string(x) + "," + std::to_string(y) + ")";
    }

    /**
     * @brief Outputs the vector to a stream.
     *
     * @param os The output stream.
     * @param v The vector to output.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const vec<T, 2>& v) {
        os << v.to_string();
        return os;
    }
};

/**
 * @brief Alias for a 4-dimensional vector.
 *
 * @tparam T Type of the vector elements.
 */
template <typename T> using vec4 = vec<T, 4>;

/**
 * @brief Alias for a 3-dimensional vector.
 *
 * @tparam T Type of the vector elements.
 */
template <typename T> using vec3 = vec<T, 3>;

/**
 * @brief Alias for a 2-dimensional vector.
 *
 * @tparam T Type of the vector elements.
 */
template <typename T> using vec2 = vec<T, 2>;

// Macros for defining mathematical functions on vectors

#define HQ_MATH_FUNC(name)                                                     \
    template <typename T, std::size_t n,                                       \
              typename = typename std::enable_if<                              \
                  std::is_floating_point<T>::value>::type>                     \
    static inline vec<T, n> name(const vec<T, n>& v) {                         \
        vec<T, n> out;                                                         \
        for (int i = 0; i < n; i++) {                                          \
            out[i] = std::name(v[i]);                                          \
        }                                                                      \
        return out;                                                            \
    }

#define HQ_MATH_FUNC_2(name)                                                   \
    template <typename T, std::size_t n, typename T2,                          \
              typename = typename std::enable_if<                              \
                  std::is_floating_point<T>::value>::type>                     \
    static inline vec<T, n> name(const vec<T, n>& v, T2 y) {                   \
        vec<T, n> out;                                                         \
        for (int i = 0; i < n; i++) {                                          \
            out[i] = std::name(v[i], y);                                       \
        }                                                                      \
        return out;                                                            \
    }                                                                          \
    template <typename T, std::size_t n,                                       \
              typename = typename std::enable_if<                              \
                  std::is_floating_point<T>::value>::type>                     \
    static inline vec<T, n> name(const vec<T, n>& v, const vec<T, n>& y) {     \
        vec<T, n> out;                                                         \
        for (int i = 0; i < n; i++) {                                          \
            out[i] = std::name(v[i], y[i]);                                    \
        }                                                                      \
        return out;                                                            \
    }

HQ_MATH_FUNC(acos)

HQ_MATH_FUNC(asin)

HQ_MATH_FUNC(atan)

HQ_MATH_FUNC(cos)

HQ_MATH_FUNC(cosh)

HQ_MATH_FUNC(sin)

HQ_MATH_FUNC(sinh)

HQ_MATH_FUNC(tan)

HQ_MATH_FUNC(exp)

HQ_MATH_FUNC(log)

HQ_MATH_FUNC(log10)

HQ_MATH_FUNC(sqrt)

HQ_MATH_FUNC(ceil)

HQ_MATH_FUNC(fabs)

HQ_MATH_FUNC(floor)

HQ_MATH_FUNC(round)

HQ_MATH_FUNC_2(atan2)

HQ_MATH_FUNC_2(pow)

HQ_MATH_FUNC_2(fmod)

#undef HQ_MATH_FUNC
#undef HQ_MATH_FUNC_2

} // namespace HQ

#endif // _HQVEC_HPP_