#ifndef SRC_RENDERING_RAII_H
#define SRC_RENDERING_RAII_H

#include "shader.h"
#include <functional>
#include <deque>
#include <memory>
#include <GL/glew.h>

template<typename T>
class TD;

namespace {
    static_assert(sizeof(void*) == sizeof(void (*)(void)));
    template <typename... Args>
    class Outer {
    public:
        template <void(*F)(Args...)>
        //template <fptr F>
        //template <int i>
        //template <typename I>
        class RAII;
    };


    template <typename F, typename Tuple, size_t... Is>
    void call_fcn_with_tuple(F f, Tuple t, std::index_sequence<Is...>) {
        f(std::get<Is>(t)...);
    }

    template <typename F, typename... Args>
    void call_fcn_with_tuple(F f, std::tuple<Args...> tup) {
        //TD<decltype(std::make_index_sequence<2>())> asdf;
        call_fcn_with_tuple(f, tup, std::make_index_sequence<sizeof...(Args)>());
    }

    template<typename Ret, typename... Args>
    std::function<Ret(Args...)> tuple_to_function(std::tuple<Args...>) {
        return std::function<Ret(Args...)>{};
    }

    template<typename T>
    struct Wrapper {
        using value = T;
    };

    template<typename Ret, typename... Args>
    auto function_to_tuple(Wrapper<Ret(*)(Args...)>) {
        return Wrapper<std::tuple<Args...>>();
    }

    std::tuple functions = std::make_tuple(
        glViewport,
        glBindFramebuffer
    );

    template<typename...Functions>
    auto make_deques(std::tuple<Functions...>) {
        return std::make_tuple(std::deque<typename decltype(function_to_tuple(Wrapper<Functions>()))::value>()...);
    }

    static decltype(make_deques(functions)) stacks;

    void test() {

        //TD<decltype(stacks)> td;
        //get_asdf(std::make_tuple(glViewport));
        //tuple_to_function<int>(std::make_tuple(4,4,4));
        //call_fcn_with_tuple(glViewport, std::make_tuple(4,4,4,4));
    }

    //std::unordered_map<void(*)(int), std::deque<std::tuple<int>>> stacks;
    //template <typename ArgsTuple, decltype(tuple_to_function<void>(ArgsTuple{})) Func>
    template <typename FuncType, int func_id, typename... Args>
    class RAII {
        static_assert(std::is_same<FuncType, void(*)(Args...)>::value);
        using TupleType = std::tuple<Args...>;
        //using FuncType = void(*)(Args...);
        //std::deque<ArgsTuple> call_stack;
        public:
        RAII(TupleType call) {
            auto stack = std::get<func_id>(stacks);
            stack.push_back(call);
            call_fcn_with_tuple(std::get<func_id>(functions), call);
        }

        RAII(FuncType) {
            
        }
        
        ~RAII() {
            auto stack = std::get<func_id>(stacks);
            call_fcn_with_tuple(std::get<func_id>(functions), stack.back());
            stack.pop_back();
        }

        RAII(RAII const&) = delete;
        RAII& operator=(RAII const&) = delete;
    };

    template<int func_id, typename... Args>
    auto create_RAII(void(*func)(Args...)) {
        
        //TD<RAII<Args...>> asdfgh;
        //Outer<Args...>::RAII<nullptr> asdf;
        return RAII<decltype(func), func_id, Args...>(func);
    }

    template<int func_id>
    auto create_RAII() {
        return create_RAII<func_id>(std::get<func_id>(functions));
    }
}



//std::array<int, 10> aaasdf;
//std::array<int, (std::glViewport)%10> asdf;
using WithViewport = decltype(create_RAII<0>());

//class WithViewport : RAII{
//    static GLint x;
//    static GLint y;
//    static GLsizei width;
//    static GLsizei height;
//public:
//    WithViewport(GLint x, GLint y, GLsizei width, GLsizei height); 
//};
//
#endif
