#pragma once

#include <functional>
#include <unordered_map>
#include "types.hpp"
#include "function.hpp"

namespace mal
{
    using env_t = std::unordered_map<std::string, Type*>;
    // TODO: use a type table ? See the type implementation of SICP.
    static const env_t repl_env = {
        {
            "+",
            new Function([](List *args) {
                mal::assert_arity(args, 2);
                Mal_ARGS_IT(args);
                Mal_ARG(Integer*, x);
                Mal_ARG(Integer*, y);

                return x->add(y);
            })
        },
        {
            "-",
            new Function([](List *args) {
                mal::assert_arity(args, 2);
                Mal_ARGS_IT(args);
                Mal_ARG(Integer*, x);
                Mal_ARG(Integer*, y);

                return x->sub(y);
            })
        },
        {
            "*",
            new Function([](List *args) {
                mal::assert_arity(args, 2);
                Mal_ARGS_IT(args);
                Mal_ARG(Integer*, x);
                Mal_ARG(Integer*, y);

                return x->mult(y);
            })
        },
        {
            "/",
            new Function([](List *args) {
                mal::assert_arity(args, 2);
                Mal_ARGS_IT(args);
                Mal_ARG(Integer*, x);
                Mal_ARG(Integer*, y);

                return x->div(y);
            })
        }
    };
}
