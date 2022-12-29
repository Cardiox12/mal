#pragma once

#include <string>
#include <vector>
#include <exception>
#include <optional>
#include <regex>

class Tokenizer {
public:
    class UnbalanceException : public std::exception {
        std::string m_message;  
    public:
        UnbalanceException(size_t pos);
        virtual char const *what() const throw();
    };
private:
    std::regex const    SYNTAX_RE{"[\\s,]*(~@|[\\[\\]{}()'`~^@]|\"(?:\\.|[^\\\"])*\"?|;.*|[^\\s\\[\\]{}('\"`,;)]*)"};
    std::string const   &m_input;
    size_t              m_start;
    size_t              m_current;
public:
    Tokenizer(std::string const &input);
    Tokenizer(Tokenizer const &other);
    Tokenizer &operator=(Tokenizer const &other);

    std::vector<std::string> tokenize() const;
    static inline std::string trim(std::string s);
    static inline std::string ltrim(std::string s);
    static inline std::string rtrim(std::string s);
};