#include "hqvec.hpp"
#include <cstdlib>
#include <iostream>

using namespace HQ;

// some examples of 3d vector types you may encounter
struct some_libraries_3d_vector_type {
    float x, y, z;
};

typedef float some_other_libraries_3d_vector_type[3];

// function outputting `some_libraries_3d_vector_type`:
some_libraries_3d_vector_type example_output(float x, float y, float z) {
    some_libraries_3d_vector_type out;
    out.x = x;
    out.y = y;
    out.z = z;
    return out;
}

// function outputting `some_libraries_3d_vector_type`:
void example_output2(float x, float y, float z,
                     some_other_libraries_3d_vector_type out) {
    out[0] = x;
    out[1] = y;
    out[2] = z;
}

// function taking `some_other_libraries_3d_vector_type` as input
void example_input(some_other_libraries_3d_vector_type input) {
    std::cout << input[0] << "," << input[1] << "," << input[2] << std::endl;
}

// function taking `some_other_libraries_3d_vector_type` as input
void example_input2(some_libraries_3d_vector_type input) {
    std::cout << input.x << "," << input.y << "," << input.z << std::endl;
}

int main() {
    // I can use the input of `example_output` as the input for `example_input`:
    example_input((float*)vec3<float>::from_generic(example_output(1, 2, 3)));

    // or I could have done
    some_other_libraries_3d_vector_type my_vec;
    vec3<float>::from_generic(example_output(1, 2, 3)).copy_to(my_vec, 3);
    example_input(my_vec);

    // or the other way around
    some_other_libraries_3d_vector_type my_vec2;
    example_output2(1, 2, 3, my_vec2);
    example_input2(
        vec3<float>(my_vec2).to_generic<some_libraries_3d_vector_type>());

    // vec2/3/4 types
    vec2<float> v2;
    std::cout << v2 << std::endl;
    vec3<int> v3;
    std::cout << v3 << std::endl;
    vec4<double> v4;
    std::cout << v4 << std::endl;

    // nd vec type
    vec<float, 10> v10;
    std::cout << v10 << std::endl;

    // casting
    vec2<float> x = (vec2<float>)vec2<int>(1, 2);
    std::cout << x << std::endl;

    // exanding shrinking
    std::cout << x.expand<3>() << std::endl;
    std::cout << v10.shrink<5>() << std::endl;

    // typical overloads
    std::cout << v2 + x << std::endl;
    std::cout << v2 - x << std::endl;
    std::cout << v2 * x << std::endl;
    std::cout << v2 / x << std::endl;
    std::cout << x.length() << std::endl;
    std::cout << x.length2() << std::endl;
    std::cout << x.distance(v2) << std::endl;
    std::cout << x.distance2(v2) << std::endl;
    std::cout << sin(v2) << std::endl;
    std::cout << pow(v2, 2) << std::endl;
    std::cout << pow(v2, x) << std::endl;

    // access by index notation (without compile time bounds checking)
    v2[0] = 5;
    std::cout << v2[0] << std::endl;

    // or using get (with compile time bounds checking)
    v2.get<0>() = 6;
    std::cout << v2.get<0>() << std::endl;

    // or (for vec2,vec3,vec4), using .x, .y, etc..
    v2.x = 7;
    std::cout << v2.x << std::endl;

    return 0;
}