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
    // if ( first == "{" )
        // TODO: manage hashmap
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
    throw new ReadMissingClosingException(")");
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
    throw new ReadMissingClosingException("]");
}

mal::Type*
mal::read_atom(Reader &reader) {
    auto token = reader.next();

    if (!token) {
        throw new ReaderUnexpectedEOFException();
    }
    if (is_nil(*token))
        return new Nil();
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

// Reader exceptions

char const*
mal::ReaderException::what() const throw() {
    return "reader: exception";
}

char const*
mal::ReaderUnexpectedEOFException::what() const throw() {
    return "reader: unexpected EOF while reading";
}

char const*
mal::ReaderUnknownTypeException::what() const throw() {
    return "reader: unknown type";
}

mal::ReadMissingClosingException::ReadMissingClosingException(std::string const &mismatch) :
    mal::ReaderException(), m_mismatch("") 
{
    m_mismatch = "reader: missing closing '" + mismatch + "'";
}

char const*
mal::ReadMissingClosingException::what() const throw() {
    return m_mismatch.c_str();
}
