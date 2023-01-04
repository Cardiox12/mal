#include "../headers/function.hpp"

// Type Function

mal::Function::Function(mal::function_t func) :
    mal::Type(mal::TypeTag::FUNCTION), m_func(func) { }

mal::Type*
mal::Function::operator()(mal::List *args) {
    return m_func(args);
}

std::string
mal::Function::repr() const {
    return "func";
}

// Arity

size_t
mal::assert_arity(mal::List *args, size_t size) {
    auto const argsize = args->value().size();
    if (argsize != size) {
        throw new ArityException(size);
    }
    return argsize;
}

size_t
mal::assert_arity(mal::List *args, size_t start, size_t stop) {
    auto const argsize = args->value().size();

    if (argsize < start || argsize > stop) {
        throw new ArityException(start);
    }
    return argsize;
}

// Exception

mal::ArityException::ArityException(size_t arity) :
    m_message("bad function arity, " + std::to_string(arity) + " arguments expected") { }

char const*
mal::ArityException::what() const throw() {
    return m_message.c_str();
}