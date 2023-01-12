#pragma once

#include <functional>
#include <unordered_map>
#include <optional>
#include <exception>
#include "types.hpp"
#include "function.hpp"
// TODO: remove, debug purpose only
#include <iostream>

namespace mal
{
    using env_t = std::unordered_map<std::string, Type*>;
    // TODO: use a type table ? See the type implementation of SICP.
    // table is good for coercion, etc...
    static env_t repl_env = {
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
                auto const argsize = mal::assert_arity(args, 1, 2);
                Mal_ARGS_IT(args);
                Mal_ARG(Integer*, x);
                if (argsize == 1)
                    return new Integer(-x->value());
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

    std::optional<Type*> get_env(env_t &env, std::string const &key);
    void set_env(env_t &env, std::string const &key, Type *value);

    class EnvException : public std::exception {
        std::string m_msg;
    public:
        EnvException(std::string const &msg);
        char const *what() const throw() override;
    };

    struct EnvNotFoundException : public EnvException {
        EnvNotFoundException(std::string const &key);
        char const *what() const throw() override;
    };
}
