#ifndef SRC_RENDERING_RAII_H
#define SRC_RENDERING_RAII_H

#include <functional>
#include <deque>
#include <memory>
#include <GL/glew.h>
#include <assert.h>

//template<typename T>
//class TD;

namespace {
    template <typename F, typename Tuple, size_t... Is>
    void call_fcn_with_tuple(F f, Tuple t, std::index_sequence<Is...>) {
        f(std::get<Is>(t)...);
    }

    template <typename F, typename... Args>
    void call_fcn_with_tuple(F f, std::tuple<Args...> tup) {
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

    static std::tuple functions = std::make_tuple(
        glViewport,
        glBindFramebuffer
    );

    template<typename...Functions>
    auto make_deques(std::tuple<Functions...>) {
        return std::make_tuple(std::deque<typename decltype(function_to_tuple(Wrapper<Functions>()))::value>()...);
    }
}

// This must be in a named namespace because it is extern.
namespace global {
    extern decltype(make_deques(functions)) gl_call_stacks;
}

namespace  {
    //void test() {
        //TD<decltype(stacks)> td;
        //get_asdf(std::make_tuple(glViewport));
        //tuple_to_function<int>(std::make_tuple(4,4,4));
        //call_fcn_with_tuple(glViewport, std::make_tuple(4,4,4,4));
    //}

    template <typename FuncType, int func_id, typename... Args>
    class RAII {
        static_assert(std::is_same_v<FuncType, void(*)(Args...)>);
        static_assert(std::is_same_v<
                FuncType,
                std::remove_reference_t<decltype(std::get<func_id>(functions))>>, "Wrong function signature");
        using TupleType = std::tuple<Args...>;
        public:
        RAII(Args... names) {
            auto call = std::make_tuple(names...);
            auto stack = std::get<func_id>(global::gl_call_stacks);
            stack.push_back(call);
            call_fcn_with_tuple(std::get<func_id>(functions), call);
        }

        RAII() {
            
        }
        
        ~RAII() {
            auto stack = std::get<func_id>(global::gl_call_stacks);
            stack.pop_back();
            assert(!stack.empty());
            call_fcn_with_tuple(std::get<func_id>(functions), stack.back());
        }

        RAII(RAII const&) = delete;
        RAII& operator=(RAII const&) = delete;
    };

    template<int func_id, typename... Args>
    auto create_RAII(void(*func)(Args...)) {
        return RAII<decltype(func), func_id, Args...>();
    }

    template<int func_id>
    auto create_RAII() {
        return create_RAII<func_id>(std::get<func_id>(functions));
    }
}

using WithViewport = decltype(create_RAII<0>());
using WithBoundFramebuffer = decltype(create_RAII<1>());

#endif
