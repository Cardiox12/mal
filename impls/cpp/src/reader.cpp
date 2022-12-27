#include "reader.hpp"
#include "tokenizer.hpp"

Reader::Reader(std::vector<std::string> const &tokens) : 
    m_tokens(tokens), m_current(0) { }

Reader::Reader(Reader const &other) : 
    m_tokens(other.m_tokens),
    m_current(other.m_current) { }

Reader&
Reader::operator=(Reader const &other) {
    if ( this == &other )
        return *this;
    m_tokens = other.m_tokens;
    m_current = other.m_current;
    return *this;
}

std::optional<std::string>
Reader::next() {
    if ( m_current >= m_tokens.size() )
        return {};
    return m_tokens[m_current++];
}

std::optional<std::string>
Reader::peek() {
    if ( m_current >= m_tokens.size() )
        return {};
    return m_tokens[m_current];
}

void
read_str(std::string const &input) {
    Reader reader(tokenize(input));

    read_form(reader);
}

std::vector<std::string>
tokenize(std::string const &input) {
    Tokenizer tokenizer(input);
    std::vector<std::string> tokens;

    while (auto token = tokenizer.next()) {
        tokens.push_back(token.value());
    }
    return tokens;
}

void
read_form(Reader &reader) {

}