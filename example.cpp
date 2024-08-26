#include "hqvec.hpp"

#include <cstdlib>
#include <iostream>

using namespace HQ;

struct my_vec {
    float x;
    float y;
    float z;
};

int main() {

    printf("vec4 = %lu\n", sizeof(vec4<float>) / sizeof(float));
    printf("vec3 = %lu\n", sizeof(vec3<float>) / sizeof(float));
    printf("vec2 = %lu\n", sizeof(vec2<float>) / sizeof(float));

    float tmp[] = {9, 8};

    auto a = vec<float, 2>(tmp, 2);
    auto b = vec<float, 2>(1, 8);
    printf("%g\n", a.distance(b));
    float* a_ptr = (float*)a;
    a_ptr[0] = 10;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << (vec<int, 6>)(a * b).expand<6>() << std::endl;
    // std::cout << (vec<int,2>)(a * b).shrink<2>() << std::endl;
    (a * b).copy((float*)tmp, 2);
    std::cout << (vec<int, 2>)(a * b) << std::endl;
    std::cout << tmp[0] << ", " << tmp[1] << std::endl;
    std::cout << (a == a) << std::endl;

    std::cout << (vec2<int>)round(pow(a, vec2<float>(2, 2))) << std::endl;

    printf("%g\n", vec<float, 2>(1, 2).length2());

    // my_vec test = a.to_generic<my_vec>();
    // printf("%g %g %g\n",test.x,test.y,test.z);
    //  auto& t = a.get<0>();
    //  std::cout << a[0] << std::endl;
    //  std::cout << a[1] << std::endl;
    //  std::cout << a[2] << std::endl;

    // printf("sizeof vec = %lu\n",sizeof(vec<float,3>));
    // printf("sizeof vec3 = %lu\n",sizeof(vec3<float>));
    return 0;
}