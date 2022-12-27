#include "tokenizer.hpp"

Tokenizer::Tokenizer(std::string const &input) : 
    m_input(input), 
    m_start(0),
    m_current(0) { }

Tokenizer::Tokenizer(Tokenizer const &other) :
    m_input(other.m_input), 
    m_start(other.m_start),
    m_current(other.m_current) { }

Tokenizer&
Tokenizer::operator=(Tokenizer const &other) {
    if ( this == &other )
        return *this;
    m_input = other.m_input;
    m_start = other.m_start;
    m_current = other.m_current;
    return *this;
}

std::string
Tokenizer::get_single_token() {
    return std::string(1, m_input[m_current++]);
}

std::optional<std::string>
Tokenizer::next() {
    while ( !is_end() ){
        char c = m_input[m_current];
        m_start = m_current;
        switch (c)
        {
            // Whitespaces or commas
            case '\t': break; case '\n': break; case '\v': break; 
            case '\f': break; case '\r': break; case ',': break;
            case ' ': break;

            // Single character
            case '[': return get_single_token(); case ']': return get_single_token();
            case '(': return get_single_token(); case ')': return get_single_token();
            case '{': return get_single_token(); case '}': return get_single_token();
            case '`': return get_single_token(); case '@': return get_single_token(); 
            case '^': return get_single_token(); case '\'': return get_single_token();
            case '~':
                advance();
                // Try to match `~@`
                if (match('@')) {
                    advance();
                    return get_token();
                }
                return get_single_token();
            
            // Double quote
            case '"':
                advance();
                while (!is_end() && !match('"')){
                    if (m_current + 1 < m_input.size() && match('\\') && m_input[m_current + 1] == '"')
                        m_current += 2;
                    else
                        advance();
                }
                if ( !match('"') )
                    throw new UnbalanceException(m_start);
                advance();
                return get_token();

            // Comment
            case ';':
                advance();
                while (!is_end() && !match('\n'))
                    advance();
                return get_token();

            default:
                if (is_non_special(c)) {
                    while (!is_end() && is_non_special(peek()))
                        advance();
                    return get_token();
                }
        }
        advance();
    }
    return {};
}

std::string
Tokenizer::get_token() const {
    return m_input.substr(m_start, m_current - m_start);
}

bool
Tokenizer::is_end() const {
    return m_current >= m_input.size();
}

void
Tokenizer::advance() {
    ++m_current;
}

char
Tokenizer::peek() const {
    return m_input[m_current];
}

bool
Tokenizer::match(char c) const {
    return m_input[m_current] == c;
}

bool
Tokenizer::is_non_special(char c) const {
    std::string special_charset = "\n\t\f\v {}('\"`,;)";

    return special_charset.find(c) == std::string::npos;
}

// Exceptions
Tokenizer::UnbalanceException::UnbalanceException(size_t pos)
    : m_message()
{
    m_message = "Unbalance expression at char " + std::to_string(pos);
}

char const*
Tokenizer::UnbalanceException::what() const throw() {
    return m_message.c_str();
}