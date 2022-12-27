#pragma once

#include <string>
#include <vector>
#include <exception>
#include <optional>

class Tokenizer {
public:
    class UnbalanceException : public std::exception {
        std::string m_message;  
    public:
        UnbalanceException(size_t pos);
        virtual char const *what() const throw();
    };
private:
    std::string const   &m_input;
    size_t              m_start;
    size_t              m_current;
public:
    Tokenizer(std::string const &input);
    Tokenizer(Tokenizer const &other);
    Tokenizer &operator=(Tokenizer const &other);

    std::optional<std::string> next();
    bool is_non_special(char c) const;
private:
    std::string get_single_token();
    std::string get_token() const;
    char peek() const;
    void advance();
    bool is_end() const;
    bool match(char c) const;
};