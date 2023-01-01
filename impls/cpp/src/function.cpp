#include "function.hpp"

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

void
mal::assert_arity(mal::List *args, size_t size) {
    if (args->value().size() != size) {
        throw new ArityException(size);
    }
}

void
mal::assert_arity(mal::List *args, size_t start, size_t stop) {
    auto size = args->value().size();

    if (size < start || size > stop) {
        throw new ArityException(start);
    }
}

// Exception

mal::ArityException::ArityException(size_t arity) :
    m_message("bad function arity, " + std::to_string(arity) + " arguments expected") { }

char const*
mal::ArityException::what() const throw() {
    return m_message.c_str();
}