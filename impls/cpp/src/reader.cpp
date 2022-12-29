#include <regex>
#include "../headers/reader.hpp"
#include "../headers/tokenizer.hpp"

mal::Reader::Reader(std::vector<std::string> const &tokens) : 
    m_tokens(tokens), m_current(0) { }

mal::Reader::Reader(mal::Reader const &other) : 
    m_tokens(other.m_tokens),
    m_current(other.m_current) { }

mal::Reader&
mal::Reader::operator=(Reader const &other) {
    if ( this == &other )
        return *this;
    m_tokens = other.m_tokens;
    m_current = other.m_current;
    return *this;
}

std::optional<std::string>
mal::Reader::next() {
    if ( m_current >= m_tokens.size() )
        return {};
    return m_tokens[m_current++];
}

std::optional<std::string>
mal::Reader::peek() {
    if ( m_current >= m_tokens.size() )
        return {};
    return m_tokens[m_current];
}

mal::Type*
mal::read_str(std::string const &input) {
    Reader reader(tokenize(input));

    return read_form(reader);
}

std::vector<std::string>
mal::tokenize(std::string const &input) {
    return Tokenizer{input}.tokenize();
}

mal::Type*
mal::read_form(Reader &reader) {
    auto token = reader.peek();

    if ( *token == "(" )
        return read_list(reader);
    else if ( *token == "[" )
        return read_vector(reader);
    else if ( *token == "{" )
        return read_map(reader);
    return read_atom(reader);
}

mal::Type*
mal::read_list(Reader &reader) {
    auto token = reader.next();
    auto *list = new List();

    while (auto token = reader.peek()) {
        if (*token == ")") {
            reader.next();
            return list;
        }
        list->add(read_form(reader));
    }
    delete list;
    throw new ReaderMissingClosingException(")");
}

mal::Type*
mal::read_vector(Reader &reader) {
    auto token = reader.next();
    auto *vec = new Vector();

    while (auto token = reader.peek()) {
        if (*token == "]") {
            reader.next();
            return vec;
        }
        vec->add(read_form(reader));
    }
    delete vec;
    throw new ReaderMissingClosingException("]");
}

mal::Type*
mal::read_map(Reader &reader) {
    auto token = reader.next();
    auto *map = new Map();
    Type *key, *val;

    while (auto token = reader.peek()) {
        if (*token == "}") {
            reader.next();
            return map;
        }
        key = read_form(reader);
        token = reader.peek();
        if (*token == "}") {
            reader.next();
            throw new ReaderException("map must contains an even number of forms");
        }
        val = read_form(reader);
        map->add(key, val);
    }
    delete map;
    throw new ReaderMissingClosingException("}");
}

mal::Type*
mal::read_atom(Reader &reader) {
    auto token = reader.next();

    if (!token) {
        throw new ReaderUnexpectedEOFException();
    }
    if (is_nil(*token))
        return new Nil();
    else if (is_string(*token))
        return new String(*token);
    else if (is_boolean(*token))
        return new Boolean(*token);
    else if (is_integer(*token))
        return new Integer(*token);
    else if (is_keyword(*token))
        return new Keyword(*token);
    return new Symbol(*token);
}

// Type predicate

/**
 * Returns true if the value is an integer, otherwise false.
 * An integer is defined as : [+|-][0-9]+
 */
bool
mal::is_integer(std::string const &value) {
    return std::regex_match(value, std::regex{"^[-|\\+]?\\d+$"});
}


/**
 * Returns true if the value is nil, otherwise false.
 * A nil value is defined as : nil
 */
bool
mal::is_nil(std::string const &value) {
    return value == "nil";
}

/**
 * Returns true if the value is a keyword, otherwise false.
 * A keyword is defined as : :[[a-Z]|[0-9]]+
 */
bool
mal::is_keyword(std::string const &value) {
    return std::regex_match(value, std::regex{"^:[\\w|\\d]+$"});
}

/**
 * Returns true if the value is a boolean, otherwise false.
 * A boolean is defined as : true|false
 */
bool
mal::is_boolean(std::string const &value) {
    return value == "true" || value == "false";
}

/**
 * Returns true if the value is a string, otherwise false.
 * If the strings is not valid, an exception of type
 * ReaderMissingClosingException is thrown.
 * A string is defined as : ".*"
 */
bool
mal::is_string(std::string const &value) {
    std::regex is_str_re{"^\".*\"$"};
    std::regex left_unbalance_re{"^[^\"]*\"$"};
    std::regex right_unbalance_re{"^\"[^\"]*$"};
    
    if (std::regex_match(value, left_unbalance_re))
        throw new ReaderMissingClosingException("\"");
    if (std::regex_match(value, right_unbalance_re))
        throw new ReaderMissingClosingException("\"");
    return std::regex_match(value, is_str_re);
}

// Reader exceptions

mal::ReaderException::ReaderException() :
    m_msg("") { }

mal::ReaderException::ReaderException(std::string const &msg) :
    m_msg("reader: " + msg) { }

char const*
mal::ReaderException::what() const throw() {
    if (m_msg.empty())
        return "reader: exception";
    return m_msg.c_str();
}

char const*
mal::ReaderUnexpectedEOFException::what() const throw() {
    return "reader: unexpected EOF while reading";
}

char const*
mal::ReaderUnknownTypeException::what() const throw() {
    return "reader: unknown type";
}

mal::ReaderMissingClosingException::ReaderMissingClosingException(std::string const &mismatch) :
    mal::ReaderException(), m_mismatch("") 
{
    m_mismatch = "reader: missing closing '" + mismatch + "'";
}

char const*
mal::ReaderMissingClosingException::what() const throw() {
    return m_mismatch.c_str();
}
