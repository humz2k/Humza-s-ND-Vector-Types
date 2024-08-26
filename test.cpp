#include "hqvec.hpp"
#include <iostream>

using namespace HQ;

static int tests_passed = 0;
static int tests_failed = 0;

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define TEST(expr)                                                             \
    {                                                                          \
        std::cout << "Testing '" << TOSTRING(expr) << "': ";                   \
        if ((expr)) {                                                          \
            tests_passed++;                                                    \
            std::cout << "pass";                                               \
        } else {                                                               \
            tests_failed++;                                                    \
            std::cout << "fail";                                               \
        }                                                                      \
        std::cout << std::endl;                                                \
    }

#define RUN_TEST(test_name, expr) test_name(expr)

#define RUN_TESTS(test_name)                                                   \
    {                                                                          \
        RUN_TEST(test_name, float)                                             \
        RUN_TEST(test_name, double)                                            \
        RUN_TEST(test_name, char)                                              \
        RUN_TEST(test_name, unsigned char)                                     \
        RUN_TEST(test_name, short)                                             \
        RUN_TEST(test_name, unsigned short)                                    \
        RUN_TEST(test_name, int)                                               \
        RUN_TEST(test_name, unsigned int)                                      \
        RUN_TEST(test_name, long long int)                                     \
        RUN_TEST(test_name, unsigned long long int)                            \
    }

template <typename T, std::size_t n, typename... Args>
bool test_constructor_varargs(Args... args) {
    T values[] = {static_cast<T>(args)...};
    vec<T, n> v(args...);
    bool constructor_succeeded = true;
    for (int i = 0; i < sizeof(values) / sizeof(T); i++) {
        if (v[i] != values[i]) {
            constructor_succeeded = false;
            break;
        }
    }
    return constructor_succeeded;
}

#define CONSTRUCTOR_VARARGS_TEST(type)                                         \
    {                                                                          \
        TEST((test_constructor_varargs<type, 2>(1, 2)))                        \
        TEST((test_constructor_varargs<type, 3>(1, 2, 3)))                     \
        TEST((test_constructor_varargs<type, 4>(1, 2, 3, 4)))                  \
        TEST((test_constructor_varargs<type, 5>(1, 2, 3, 4, 5)))               \
        TEST((test_constructor_varargs<type, 6>(1, 2, 3, 4, 5, 6)))            \
    }

template <typename T, std::size_t n> bool test_constructor_pointer() {
    T* values = (T*)malloc(sizeof(T) * n);

    for (int i = 0; i < n; i++) {
        values[i] = i;
    }

    bool constructors_succeeded = true;
    for (int start = 0; start < n; start++) {
        vec<T, n> v(values, start);

        for (int i = 0; i < start; i++) {
            if (v[i] != values[i]) {
                constructors_succeeded = false;
                goto end;
            }
        }

        for (int i = start; i < n; i++) {
            if (v[i] != 0) {
                constructors_succeeded = false;
                goto end;
            }
        }
    }

end:
    free(values);
    return constructors_succeeded;
}

#define CONSTRUCTOR_VARARGS_POINTER_TEST(type)                                 \
    {                                                                          \
        TEST((test_constructor_pointer<type, 2>()))                            \
        TEST((test_constructor_pointer<type, 3>()))                            \
        TEST((test_constructor_pointer<type, 4>()))                            \
        TEST((test_constructor_pointer<type, 5>()))                            \
        TEST((test_constructor_pointer<type, 6>()))                            \
    }

template <typename T, std::size_t n> bool test_zero_initialization() {
    vec<T, n> v;
    for (int i = 0; i < n; i++) {
        if (v[i] != 0)
            return false;
    }
    return true;
}

#define ZERO_INITIALIZATION_TEST(type)                                         \
    {                                                                          \
        TEST((test_zero_initialization<type, 2>()))                            \
        TEST((test_zero_initialization<type, 3>()))                            \
        TEST((test_zero_initialization<type, 4>()))                            \
        TEST((test_zero_initialization<type, 5>()))                            \
        TEST((test_zero_initialization<type, 6>()))                            \
    }

template <typename T, std::size_t n> bool test_reassign(int start = 5) {
    vec<T, n> v;
    for (int i = 0; i < n; i++) {
        if (v[i] != 0)
            return false;
    }
    for (int i = 0; i < n; i++) {
        v[i] = start + i;
    }
    for (int i = 0; i < n; i++) {
        if (v[i] != start + i)
            return false;
    }
    return true;
}

#define REASSIGN_TEST(type)                                                    \
    {                                                                          \
        TEST((test_reassign<type, 2>()))                                       \
        TEST((test_reassign<type, 3>()))                                       \
        TEST((test_reassign<type, 4>()))                                       \
        TEST((test_reassign<type, 5>()))                                       \
        TEST((test_reassign<type, 6>()))                                       \
    }

template <typename T> bool test_special_reassign() {
    {
        vec<T, 2> v;
        v.x = 1;
        v.y = 2;
        if (v.x != 1)
            return false;
        if (v.y != 2)
            return false;
    }

    {
        vec<T, 3> v;
        v.x = 1;
        v.y = 2;
        v.z = 3;
        if (v.x != 1)
            return false;
        if (v.y != 2)
            return false;
        if (v.z != 3)
            return false;
    }

    {
        vec<T, 4> v;
        v.x = 1;
        v.y = 2;
        v.z = 3;
        v.w = 4;
        if (v.x != 1)
            return false;
        if (v.y != 2)
            return false;
        if (v.z != 3)
            return false;
        if (v.w != 4)
            return false;
    }
    return true;
}

#define SPECIAL_REASSIGN_TEST(type)                                            \
    { TEST((test_special_reassign<type>())) }

int main() {

    RUN_TESTS(CONSTRUCTOR_VARARGS_TEST)
    RUN_TESTS(CONSTRUCTOR_VARARGS_POINTER_TEST)
    RUN_TESTS(ZERO_INITIALIZATION_TEST)
    RUN_TESTS(REASSIGN_TEST)
    RUN_TESTS(SPECIAL_REASSIGN_TEST)

    std::cout << "Passed: " << tests_passed << "/"
              << (tests_passed + tests_failed) << std::endl;
    return 0;
}