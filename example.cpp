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

    printf("vec4 = %lu\n",sizeof(vec4<float>)/sizeof(float));
    printf("vec3 = %lu\n",sizeof(vec3<float>)/sizeof(float));
    printf("vec2 = %lu\n",sizeof(vec2<float>)/sizeof(float));

    float tmp[] = {9, 8};

    auto a = vec<float,5>(tmp, 2);
    auto b = vec<float,5>(1, 2);
    float* a_ptr = (float*)a;
    a_ptr[0] = 10;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << (vec<int, 6>)(a * b).expand<6>() << std::endl;
    // std::cout << (vec<int,2>)(a * b).shrink<2>() << std::endl;
    (a * b).copy((float*)tmp, 2);
    std::cout << (vec<int,5>)(a * b) << std::endl;
    std::cout << tmp[0] << ", " << tmp[1] << std::endl;
    std::cout << (a == a) << std::endl;

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