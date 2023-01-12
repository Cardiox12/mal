#include "../headers/types.hpp"
#include <format>

#include <iostream>

// Type

mal::Type::Type(mal::TypeTag tag) :
    m_tag(tag) { }

bool
mal::Type::is(mal::TypeTag tag) const {
    return m_tag == tag;
}

mal::TypeTag
mal::Type::tag() const {
    return m_tag;
}

// Type List

mal::List::List() : 
    mal::Type(TypeTag::LIST), m_list() { }

mal::List::List(std::vector<mal::Type*> const &list) :
    mal::Type(TypeTag::LIST), m_list(list) { }

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

std::vector<mal::Type*> const&
mal::List::value() const {
    return m_list;
}

mal::List*
mal::List::rest() const {
    return new List(
        std::vector<Type*>(m_list.begin() + 1, m_list.end())
    );
}

// Type vector

mal::Vector::Vector() : 
    mal::Type(TypeTag::VECTOR), m_vec() { }

mal::Vector::~Vector() {
    // TODO: delete items or not ?
    for ( auto* item : m_vec ) {
        delete item;
    }
}

std::vector<mal::Type*> const&
mal::Vector::value() const {
    return m_vec;
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

// Type Map

mal::Map::Map() :
    mal::Type(mal::TypeTag::MAP), m_map() { }

mal::Map::~Map() {
    // TODO: delete items or not ?
}

void
mal::Map::add(Type *key, Type *val) {
    m_map.insert(std::make_pair(key, val));
}

std::unordered_map<mal::Type*, mal::Type*> const&
mal::Map::value() const {
    return m_map;
}

std::string
mal::Map::repr() const {
    std::string s = "{";
    size_t index = 1;

    for (auto const &[k, v] : m_map){
        s += k->repr() + " " + v->repr();
        if (index++ < m_map.size())
            s += " ";
    }
    return s + "}";
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

std::string const&
mal::Symbol::value() const {
    return m_symbol;
}

// Type number

mal::Integer::Integer(int value) :
    mal::Type(mal::TypeTag::INTEGER), m_value(value) { }

mal::Integer::Integer(std::string const &value) :
    mal::Type(mal::TypeTag::INTEGER), m_value(std::stoi(value)) { }

int
mal::Integer::value() const {
    return m_value;
}

std::string
mal::Integer::repr() const {
    return std::to_string(m_value);
}

mal::Integer*
mal::Integer::add(Integer *x) const {
    return new Integer(m_value + x->m_value);
}

mal::Integer*
mal::Integer::sub(Integer *x) const {
    return new Integer(m_value - x->m_value);
}

mal::Integer*
mal::Integer::div(Integer *x) const {
    return new Integer(m_value / x->m_value);
}

mal::Integer*
mal::Integer::mult(Integer *x) const {
    return new Integer(m_value * x->m_value);
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

// Type exceptions

mal::TypeException::TypeException(std::string const &msg) :
    m_msg("type: " + msg) { }

char const*
mal::TypeException::what() const throw() {
    return m_msg.c_str();
}

// Type assert

std::string
mal::get_type_name(mal::TypeTag tag) {
    auto it = G_TYPE_NAME.find(tag);

    if (it != G_TYPE_NAME.end())
        return it->second;
    return "";
}

bool
mal::assert_types(mal::Type*) {
    return false;
}

mal::TypeAssert::TypeAssert(mal::TypeTag tag) : m_tag(tag) { }

void mal::TypeAssert::operator()() { }
