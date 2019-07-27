#ifndef SRC_RENDERING_RAII_H
#define SRC_RENDERING_RAII_H

#include <functional>
#include <deque>
#include <memory>
#include <GL/glew.h>
#include <assert.h>
#include "raii_functions.h"

//template<typename T>
//class TD;

namespace {
    // Warning: only append to this list.
    // Indexes are hard-coded elsewhere.
    static std::tuple functions = std::make_tuple(
        glViewport,
        gl_bind_framebuffer,
        gl_set_enabled<GL_DEPTH_TEST>,
        glPolygonMode,
        glClearColor,
        gl_set_enabled<GL_SCISSOR_TEST>,
        gl_set_enabled<GL_COLOR_LOGIC_OP>,
        glLogicOp
    );

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

        static auto& get_stack() {
            return std::get<func_id>(global::gl_call_stacks);
        }

        public:
        RAII(Args... names) {
            auto call = std::make_tuple(names...);
            auto& stack = get_stack();
            assert(stack.size() != 0); // No default specified
            stack.push_back(call);
            call_fcn_with_tuple(std::get<func_id>(functions), call);
        }

        static void set_default(Args... names) {
            auto call = std::make_tuple(names...);
            auto& stack = get_stack();
            if (stack.size() == 0) {
                stack.push_back(call);
                call_fcn_with_tuple(std::get<func_id>(functions), call);
            } else {
                stack[0] = call;
            }
        }

        ~RAII() {
            auto& stack = get_stack();
            assert(stack.size() >= 2); // No default value given
            stack.pop_back();
            if (!stack.empty())
                call_fcn_with_tuple(std::get<func_id>(functions), stack.back());
        }

        RAII(RAII const&) = delete;
        RAII& operator=(RAII const&) = delete;
    };

    template<int func_id, typename... Args>
    constexpr auto create_RAII(void(*func)(Args...)) {
        return Wrapper<RAII<decltype(func), func_id, Args...>>();
    }

    template<int func_id>
    using raii_type = typename decltype(create_RAII<func_id>(std::get<func_id>(functions)))::value;
}

using WithViewport = raii_type<0>;
using WithBindFramebuffer = raii_type<1>;
using WithDepthTestEnabled = raii_type<2>;
using WithPolygonMode = raii_type<3>;
using WithClearColor = raii_type<4>;
using WithScissorTestEnabled = raii_type<5>;
using WithColorLogicOpEnabled = raii_type<6>;
using WithLogicOp = raii_type<7>;

void set_raii_defaults();

#endif
