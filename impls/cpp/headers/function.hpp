#pragma once

#include "types.hpp"
#include <iterator>
#include <functional>

#define Mal_ARGS_IT(mal_args)                           \
    auto mal_args_begin_ = mal_args->value().begin();   \
    auto mal_args_end_ = mal_args->value().end();


#define Mal_ARG(type, name)                             \
    if (mal_args_begin_ == mal_args_end_) {             \
        throw new std::exception{};                     \
    }                                                   \
    type name = static_cast<type>(*mal_args_begin_++);

#define Mal_VAR(type, name, val) type name = static_cast<type>(val)

namespace mal
{
    typedef std::function<Type*(List*)> function_t;

    /**
     * Function
     * Function object represent a function type.
     * The Function object wrap the function given in argument.
     */
    class Function : public Type {
        function_t m_func;
    public:
        Function(function_t func);
        Type *operator()(List *args);

        std::string repr() const override;
    };

    /**
     * assert_arity
     * assert_arity check that the @arg size is equal to @arg args size.
     * If the arity isn't equal, an exception is thrown.
     * 
     */
    void assert_arity(List *args, size_t size);

    /**
     * assert_arity
     * assert_airty check that @arg args is in the arity range 
     * between @arg start and @arg stop.
     */
    void assert_arity(List *args, size_t start, size_t stop);

    class ArityException : public std::exception {
        std::string m_message;
    public:
        ArityException(size_t arity);
        char const *what() const throw() override;
    };
}
