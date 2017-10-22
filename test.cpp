//
// Created by pilar on 21.10.2017.
//

#include "register_access.hpp"
#include <cstdint>

namespace test{
    template <typename T>
    struct check_if_is_void{
        static constexpr bool value = std::is_same<void, T>::value;
    };

    template <typename T, typename Y>
    constexpr bool eq = std::is_same<T, Y>::value;
};

int main(){
    using namespace register_access;
    using namespace utils;
    using namespace test;

    static_assert(are_same_size<int, int>::value, "are_same_size not implemented correctly");

    struct testA{};
    struct testB{};
    static_assert(eq<if_else<true, testA, testB>::type, testA>, "is_same is not implemented correctly");
    static_assert(eq<if_else<false, testA, testB>::type, testB>, "is_same is not implemented correctly");

    static_assert(eq<select_if<check_if_is_void, int, char>::type, select_if_not_selected>, "select_if not implemented correctly");
    static_assert(eq<select_if<check_if_is_void, int, char, void>::type, void>, "select_if not implemented correctly");

    static_assert(eq<pointer_int_type, uint32_t> || eq<pointer_int_type, uint64_t>,
                    "pointer_int_type is not implemented correctly or very strange architecture is chosen");
    static_assert(!eq<pointer_int_type, uint8_t>,
                    "pointer_int_type is not implemented correctly or very strange architecture is chosen");

    static_assert(are_same<void, void>::value, "are_same not implemented correctly");
    static_assert(!are_same<testA, testB>::value, "are_same not implemented correctly");
    static_assert(are_same<void, void, void ,void>::value, "are_same not implemented correctly");
    static_assert(!are_same<void, int, void ,void>::value, "are_same not implemented correctly");
    static_assert(!are_same<testA, int, testB,void>::value, "are_same not implemented correctly");
    static_assert(are_same<testA, testA, testA, testA>::value, "are_same not implemented correctly");


}