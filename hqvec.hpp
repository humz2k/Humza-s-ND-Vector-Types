#ifndef _HQVEC_HPP_
#define _HQVEC_HPP_

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

namespace HQ {

template <typename T, std::size_t n> class vec {
  private:
    T data[n] = {0};

  public:
    template <typename... Args>
    vec(Args... args) : data{static_cast<T>(args)...} {
        static_assert(n > 1, "no length 1 vector");
    }

    template <typename T1> vec(vec<T1, n> v) {
        static_assert(n > 1, "no length 1 vector");
        for (int i = 0; i < n; i++) {
            data[i] = v[i];
        }
    }

    vec(T in[], int count = n) {
        static_assert(n > 1, "no length 1 vector");
        for (int i = 0; i < count; i++) {
            data[i] = in[i];
        }
    }

    T& operator[](int i) { return data[i]; }

    T operator[](int i) const { return data[i]; }

    template <int i> T& get() {
        static_assert((i >= 0) && (i < n), "index out of bounds");
        return data[i];
    }

    template <int i> T get() const {
        static_assert((i >= 0) && (i < n), "index out of bounds");
        return data[i];
    }

    vec<T, n> operator+(const vec<T, n>& other) const {
        vec<T, n> out;
        for (int i = 0; i < n; i++) {
            out[i] = data[i] + other[i];
        }
        return out;
    }

    vec<T, n> operator*(const vec<T, n>& other) const {
        vec<T, n> out;
        for (int i = 0; i < n; i++) {
            out[i] = data[i] * other[i];
        }
        return out;
    }

    vec<T, n> operator-(const vec<T, n>& other) const {
        vec<T, n> out;
        for (int i = 0; i < n; i++) {
            out[i] = data[i] - other[i];
        }
        return out;
    }

    vec<T, n> operator/(const vec<T, n>& other) const {
        vec<T, n> out;
        for (int i = 0; i < n; i++) {
            out[i] = data[i] / other[i];
        }
        return out;
    }

    bool operator==(const vec<T, n>& other) const {
        for (int i = 0; i < n; i++) {
            if (other[i] != data[i])
                return false;
        }
        return true;
    }

    bool operator!=(const vec<T, n>& other) const {
        for (int i = 0; i < n; i++) {
            if (other[i] != data[i])
                return true;
        }
        return false;
    }

    operator T*() { return data; }

    operator const T*() const { return data; }

    void copy_to(T out[], int count = n) const {
        for (int i = 0; i < count; i++) {
            out[i] = data[i];
        }
    }

    template <typename T1> vec<T1, n> to() const {
        vec<T1, n> out;
        for (int i = 0; i < n; i++) {
            out[i] = data[i];
        }
        return out;
    }

    template <typename T1> operator vec<T1, n>() const { return to<T1, n>(); }

    template <std::size_t n1> vec<T, n1> expand() {
        static_assert(n1 > n, "n1 is smaller or equal to n");
        vec<T, n1> out;
        for (int i = 0; i < n; i++) {
            out[i] = data[i];
        }
        return out;
    }

    template <std::size_t n1> vec<T, n1> shrink() {
        static_assert((n1 < n) && (n1 > 1), "n1 is bigger or equal to n");
        vec<T, n1> out;
        for (int i = 0; i < n1; i++) {
            out[i] = data[i];
        }
        return out;
    }

    std::size_t size() const { return n; }

    T length2() const {
        float out = 0;
        for (int i = 0; i < n; i++) {
            float temp = data[i];
            out += temp * temp;
        }
        return out;
    }

    T length() const { return sqrt(length2()); }

    T distance2(const vec<T, n> v) const { return ((*this) - v).length2(); }

    T distance(const vec<T, n> v) const { return ((*this) - v).length(); }

    std::string to_string() const {
        std::string out = "vec<" + std::string(typeid(T).name()) + "," +
                          std::to_string(n) + ">(";
        for (int i = 0; i < (n - 1); i++) {
            out += std::to_string(data[i]) + ",";
        }
        out += std::to_string(data[n - 1]) + ")";
        return out;
    }

    friend std::ostream& operator<<(std::ostream& os, const vec<T, n>& v) {
        os << v.to_string();
        return os;
    }
};

template <typename T> class vec<T, 4> {
  public:
    T x = 0;
    T y = 0;
    T z = 0;
    T w = 0;
    vec(T x_ = 0, T y_ = 0, T z_ = 0, T w_ = 0) : x(x_), y(y_), z(z_), w(w_) {}

    vec(T in[], int count = 4) {
        if (count > 0)
            x = in[0];
        if (count > 1)
            y = in[1];
        if (count > 2)
            z = in[2];
        if (count > 3)
            z = in[3];
    }

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

    T operator[](int i) const {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return 4;
        default:
            assert(((i >= 0) && (i < 4)) && "index out of bounds");
            return x;
        }
    }

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

    vec<T, 4> operator+(const vec<T, 4>& other) const {
        return vec<T, 4>(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    vec<T, 4> operator-(const vec<T, 4>& other) const {
        return vec<T, 4>(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    vec<T, 4> operator*(const vec<T, 4>& other) const {
        return vec<T, 4>(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    vec<T, 4> operator/(const vec<T, 4>& other) const {
        return vec<T, 4>(x / other.x, y / other.y, z / other.z, w / other.w);
    }

    bool operator==(const vec<T, 4>& other) const {
        return (other.x == x) && (other.y == y) && (other.z == z) &&
               (other.w == w);
    }

    bool operator!=(const vec<T, 4>& other) const {
        return (other.x != x) || (other.y != y) || (other.z != z) ||
               (other.w != w);
    }

    operator T*() { return reinterpret_cast<T*>(this); }

    operator const T*() const { return reinterpret_cast<const T*>(this); }

    void copy_to(T out[], int count = 4) const {
        if (count > 0)
            out[0] = x;
        if (count > 1)
            out[1] = y;
        if (count > 2)
            out[2] = z;
        if (count > 3)
            out[3] = z;
    }

    template <typename T1> vec<T1, 4> to() const {
        return vec<T1, 4>(x, y, z, w);
    }

    template <typename T1> operator vec<T1, 4>() const { return to<T1>(); }

    template <typename T1> T1 to_generic() {
        T1 out;
        out.x = x;
        out.y = y;
        out.z = z;
        out.w = w;
        return out;
    }

    template <typename T1> static vec<T, 4> from_generic(const T1& other) {
        return vec<T, 4>(other.x, other.y, other.z, other.w);
    }

    template <std::size_t n1> vec<T, n1> expand() {
        static_assert(n1 > 4, "n1 is smaller or equal to 3");
        return vec<T, n1>(x, y, z, w);
    }

    template <std::size_t n1> vec<T, n1> shrink() {
        static_assert((n1 < 4) && (n1 > 1), "n1 is bigger or equal to 3");
        if (n1 == 3)
            return vec<T, n1>(x, y, z);
        return vec<T, n1>(x, y);
    }

    std::size_t size() const { return 4; }

    T length2() const { return x * x + y * y + z * z + w * w; }

    T length() const { return sqrt(length2()); }

    T distance2(const vec<T, 4> v) { return ((*this) - v).length2(); }

    T distance(const vec<T, 4> v) { return ((*this) - v).length(); }

    std::string to_string() const {
        return "vec<" + std::string(typeid(T).name()) + ",3>(" +
               std::to_string(x) + "," + std::to_string(y) + "," +
               std::to_string(z) + ")";
    }

    friend std::ostream& operator<<(std::ostream& os, const vec<T, 4>& v) {
        os << v.to_string();
        return os;
    }
};

template <typename T> class vec<T, 3> {
  public:
    T x = 0;
    T y = 0;
    T z = 0;
    vec(T x_ = 0, T y_ = 0, T z_ = 0) : x(x_), y(y_), z(z_) {}

    vec(T in[], int count = 3) {
        if (count > 0)
            x = in[0];
        if (count > 1)
            y = in[1];
        if (count > 2)
            z = in[2];
    }

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

    vec<T, 3> operator+(const vec<T, 3>& other) const {
        return vec<T, 3>(x + other.x, y + other.y, z + other.z);
    }

    vec<T, 3> operator-(const vec<T, 3>& other) const {
        return vec<T, 3>(x - other.x, y - other.y, z - other.z);
    }

    vec<T, 3> operator*(const vec<T, 3>& other) const {
        return vec<T, 3>(x * other.x, y * other.y, z * other.z);
    }

    vec<T, 3> operator/(const vec<T, 3>& other) const {
        return vec<T, 3>(x / other.x, y / other.y, z / other.z);
    }

    bool operator==(const vec<T, 3>& other) const {
        return (other.x == x) && (other.y == y) && (other.z == z);
    }

    bool operator!=(const vec<T, 3>& other) const {
        return (other.x != x) || (other.y != y) || (other.z != z);
    }

    operator T*() { return reinterpret_cast<T*>(this); }

    operator const T*() const { return reinterpret_cast<const T*>(this); }

    void copy_to(T out[], int count = 3) const {
        if (count > 0)
            out[0] = x;
        if (count > 1)
            out[1] = y;
        if (count > 2)
            out[2] = z;
    }

    template <typename T1> vec<T1, 3> to() const { return vec<T1, 3>(x, y, z); }

    template <typename T1> operator vec<T1, 3>() const { return to<T1>(); }

    template <typename T1> T1 to_generic() {
        T1 out;
        out.x = x;
        out.y = y;
        out.z = z;
        return out;
    }

    template <typename T1> static vec<T, 3> from_generic(const T1& other) {
        return vec<T, 3>(other.x, other.y, other.z);
    }

    template <std::size_t n1> vec<T, n1> expand() {
        static_assert(n1 > 3, "n1 is smaller or equal to 3");
        return vec<T, n1>(x, y, z);
    }

    template <std::size_t n1> vec<T, n1> shrink() {
        static_assert((n1 < 3) && (n1 > 1), "n1 is bigger or equal to 3");
        return vec<T, n1>(x, y);
    }

    std::size_t size() const { return 3; }

    T length2() const { return x * x + y * y + z * z; }

    T length() const { return sqrt(length2()); }

    T distance2(const vec<T, 3> v) { return ((*this) - v).length2(); }

    T distance(const vec<T, 3> v) { return ((*this) - v).length(); }

    std::string to_string() const {
        return "vec<" + std::string(typeid(T).name()) + ",3>(" +
               std::to_string(x) + "," + std::to_string(y) + "," +
               std::to_string(z) + ")";
    }

    friend std::ostream& operator<<(std::ostream& os, const vec<T, 3>& v) {
        os << v.to_string();
        return os;
    }
};

template <typename T> class vec<T, 2> {
  public:
    T x = 0;
    T y = 0;
    vec(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}

    vec(T in[], int count = 2) {
        if (count > 0)
            x = in[0];
        if (count > 1)
            y = in[1];
    }

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

    vec<T, 2> operator+(const vec<T, 2>& other) const {
        return vec<T, 2>(x + other.x, y + other.y);
    }

    vec<T, 2> operator-(const vec<T, 2>& other) const {
        return vec<T, 2>(x - other.x, y - other.y);
    }

    vec<T, 2> operator*(const vec<T, 2>& other) const {
        return vec<T, 2>(x * other.x, y * other.y);
    }

    vec<T, 2> operator/(const vec<T, 2>& other) const {
        return vec<T, 2>(x / other.x, y / other.y);
    }

    bool operator==(const vec<T, 2>& other) const {
        return (other.x == x) && (other.y == y);
    }

    bool operator!=(const vec<T, 2>& other) const {
        return (other.x != x) || (other.y != y);
    }

    operator T*() { return reinterpret_cast<T*>(this); }

    operator const T*() const { return reinterpret_cast<const T*>(this); }

    void copy_to(T out[], int count = 2) const {
        if (count > 0)
            out[0] = x;
        if (count > 1)
            out[1] = y;
    }

    template <typename T1> vec<T1, 2> to() const { return vec<T1, 2>(x, y); }

    template <typename T1> operator vec<T1, 2>() const { return to<T1>(); }

    template <typename T1> T1 to_generic() {
        T1 out;
        out.x = x;
        out.y = y;
        return out;
    }

    template <typename T1> static vec<T, 2> from_generic(const T1& other) {
        return vec<T, 2>(other.x, other.y);
    }

    template <std::size_t n1> vec<T, n1> expand() {
        static_assert(n1 > 2, "n1 is smaller or equal to 3");
        return vec<T, n1>(x, y);
    }

    std::size_t size() const { return 2; }

    T length2() const { return x * x + y * y; }

    T length() const { return sqrt(length2()); }

    T distance2(const vec<T, 2> v) { return ((*this) - v).length2(); }

    T distance(const vec<T, 2> v) { return ((*this) - v).length(); }

    std::string to_string() const {
        return "vec<" + std::string(typeid(T).name()) + ",2>(" +
               std::to_string(x) + "," + std::to_string(y) + ")";
    }

    friend std::ostream& operator<<(std::ostream& os, const vec<T, 2>& v) {
        os << v.to_string();
        return os;
    }
};

template <typename T> using vec4 = vec<T, 4>;

template <typename T> using vec3 = vec<T, 3>;

template <typename T> using vec2 = vec<T, 2>;

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