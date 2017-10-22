//
// Created by pilar on 21.10.2017.
//

#ifndef REGISTERACCESS_REGISTERACCESS_HPP
#define REGISTERACCESS_REGISTERACCESS_HPP

#include <type_traits>
#include <utility>
#include <cstdint>
#include <limits>

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

        template <typename T1, typename T2, typename ...T>
        struct are_same{
            static constexpr bool value = std::is_same<T1, T2>::value and are_same<T...>::value;
        };

        template <typename T1, typename T2>
        struct are_same<T1, T2>{
            static constexpr bool value = std::is_same<T1, T2>::value;
        };

        template <typename T1, typename... T>
        struct first_type{ // todo change for list_idx, which gets nth idx of the given parameter pack
            using type = T1;
        };

        template <typename... T>
        struct common_type{
            static_assert(are_same<T...>::value, "Given types are not the same. Cannot determine common type");
            using type = typename first_type<T...>::type;
        };

    }

    template<utils::pointer_int_type address, typename underlying_type>
    struct register_access{
        static constexpr underlying_type bitsClear = 0;
        static constexpr underlying_type bitsSet = std::numeric_limits<underlying_type>::max();



        void clear(){
            *reinterpret_cast<volatile underlying_type*>(address) = bitsClear;
        }

        void setAll(){
            *reinterpret_cast<volatile underlying_type*>(address) = bitsSet;
        }
    };

}

#endif //REGISTERACCESS_REGISTERACCESS_HPP
