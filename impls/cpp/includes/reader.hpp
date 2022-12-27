#pragma once

#include <string>
#include <vector>
#include <optional>

class Reader {
    std::vector<std::string>    m_tokens;
    size_t                      m_current;
public:
    Reader(std::vector<std::string> const &tokens);
    Reader(Reader const &other);
    Reader &operator=(Reader const &other);

    std::optional<std::string> next();
    std::optional<std::string> peek();
};

std::vector<std::string> tokenize(std::string const &input);
void read_str(std::string const &input);
void read_form(Reader &reader);