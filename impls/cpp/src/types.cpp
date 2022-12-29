#include "../headers/types.hpp"
#include <format>

// Type

mal::Type::Type(mal::TypeTag tag) :
    m_tag(tag) { }

bool
mal::Type::is(mal::TypeTag tag) const {
    return m_tag == tag;
}

// Type List

mal::List::List() : 
    mal::Type(TypeTag::LIST), m_list() { }

mal::List::~List() {
    for ( auto* item : m_list ) {
        delete item;
    }
}

void
mal::List::add(Type *type) {
    m_list.push_back(type);
}

std::string
mal::List::repr() const {
    std::string acc = "(";

    for (size_t index = 0 ; index < m_list.size() ; ++index ) {
        acc += m_list[index]->repr();
        if ((index + 1) < m_list.size())
            acc += " ";
    }
    return acc + ")";
}

// Type vector

mal::Vector::Vector() : 
    mal::Type(TypeTag::VECTOR), m_vec() { }

mal::Vector::~Vector() {
    for ( auto* item : m_vec ) {
        delete item;
    }
}

void
mal::Vector::add(Type *type) {
    m_vec.push_back(type);
}

std::string
mal::Vector::repr() const {
    std::string acc = "[";

    for (size_t index = 0 ; index < m_vec.size() ; ++index ) {
        acc += m_vec[index]->repr();
        if ((index + 1) < m_vec.size())
            acc += " ";
    }
    return acc + "]";
}


// Type Scalar

// Type nil
mal::Nil::Nil() : mal::Type(TypeTag::NIL) { }

std::string
mal::Nil::repr() const {
    return "nil";
}

// Type keyword

mal::Keyword::Keyword(std::string const &keyword) :
    mal::Type(mal::TypeTag::KEYWORD), m_keyword(keyword) { }

std::string
mal::Keyword::repr() const {
    // TODO: add prefix ':' ?
    return m_keyword;
}

// Type symbol

mal::Symbol::Symbol(std::string const &symbol) :
    mal::Type(mal::TypeTag::SYMBOL), m_symbol(symbol) { }

std::string
mal::Symbol::repr() const {
    return m_symbol;
}

// Type number

mal::Integer::Integer(int value) :
    mal::Type(mal::TypeTag::INTEGER), m_value(value) { }

mal::Integer::Integer(std::string const &value) :
    mal::Type(mal::TypeTag::INTEGER), m_value(std::stoi(value)) { }

std::string
mal::Integer::repr() const {
    return std::to_string(m_value);
}

// Type boolean

mal::Boolean::Boolean(bool value) :
    mal::Type(mal::TypeTag::BOOLEAN), m_value(value) { }

mal::Boolean::Boolean(std::string const &value) :
    mal::Type(mal::TypeTag::BOOLEAN), m_value(false) 
{
    // TODO: manage cast error
    if (value == "true" )
        m_value = true;
    else if (value == "false")
        m_value = false;
}

std::string
mal::Boolean::repr() const {
    return (m_value) ? "true" : "false";
}

// Type string

mal::String::String(std::string const &value) :
    mal::Type(mal::TypeTag::STRING), m_value(value) { }

std::string
mal::String::repr() const {
    return m_value;
}