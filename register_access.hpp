//
// Created by pilar on 21.10.2017.
//

#ifndef REGISTERACCESS_REGISTERACCESS_HPP
#define REGISTERACCESS_REGISTERACCESS_HPP

#include <type_traits>
#include <utility>
#include <cstdint>

namespace register_access {

    namespace utils {

        template<typename T, typename Y>
        struct are_same_size {
            static constexpr bool value = sizeof(T) == sizeof(Y);
        };

        template<bool Boolean, typename True_type, typename False_type>
        struct if_else {
            using type = True_type;
        };

        template<typename True_type, typename False_type>
        struct if_else<false, True_type, False_type> {
            using type = False_type;
        };

        struct select_if_not_selected {
        };

        template<template<typename> typename Predicate, typename T1, typename... T>
        struct select_if {
            using type = typename if_else<Predicate<T1>::value,
                    T1,
                    typename select_if<Predicate, T...>::type
            >::type;
        };

        template<template<typename> typename Predicate, typename T>
        struct select_if<Predicate, T> {
            using type = typename if_else<Predicate<T>::value,
                    T,
                    select_if_not_selected>::type;
        };

        template<typename T>
        struct is_ptr_size {
            static constexpr bool value = sizeof(T) == sizeof(void *);
        };

        using pointer_int_type = typename select_if<
                is_ptr_size,
                std::uint8_t, std::uint16_t, std::uint16_t, std::uint64_t>::type;

        template <typename ...Args>
        constexpr  sumBits(){

        }

        constexpr sumBits(){

        }
    }

    template<utils::pointer_int_type address>
    struct register_access{
        template <typename ...Args>
        void setBits(Args...){

        }
    };
}

#endif //REGISTERACCESS_REGISTERACCESS_HPP
