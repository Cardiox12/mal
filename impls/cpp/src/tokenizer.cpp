#include "../headers/tokenizer.hpp"

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
    m_start = other.m_start;
    m_current = other.m_current;
    return *this;
}

std::vector<std::string>
Tokenizer::tokenize() const {
    std::vector<std::string> tokens;
    std::sregex_iterator begin{ m_input.begin(), m_input.end(), SYNTAX_RE };
    std::sregex_iterator end{};

    for ( auto it = begin ; it != end ; ++it ) {
        tokens.push_back(Tokenizer::trim(it->str()));
    }
    return tokens;
}

std::string
Tokenizer::trim(std::string s) {
    return Tokenizer::rtrim(Tokenizer::ltrim(s));
}

std::string
Tokenizer::ltrim(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](auto c){
        return !std::isspace(c);
    }));
    return s;
}

std::string
Tokenizer::rtrim(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](auto c){
        return !std::isspace(c);
    }).base(), s.end());
    return s;
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