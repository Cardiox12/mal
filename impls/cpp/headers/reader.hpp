#pragma once

#include <string>
#include <vector>
#include <optional>
#include <exception>
#include <algorithm>
#include "types.hpp"

// TODO: remove, debug purpose only
#include <iostream>

namespace mal {
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
    mal::Type *read_str(std::string const &input);
    mal::Type *read_form(Reader &reader);
    mal::Type *read_atom(Reader &reader);
    // TOOD: Refactor and federate all sequence type into one with subtypes ?
    mal::Type *read_list(Reader &reader);
    mal::Type *read_vector(Reader &reader);

    // Type predicate

    bool is_integer(std::string const &value);
    bool is_nil(std::string const &value);
    bool is_keyword(std::string const &value);
    bool is_boolean(std::string const &value);

    // Reader exceptions

    struct ReaderException : public std::exception {
        virtual char const *what() const throw();
    };

    struct ReaderUnexpectedEOFException : public ReaderException {
        virtual char const *what() const throw();
    };

    struct ReaderUnknownTypeException : public ReaderException {
        virtual char const *what() const throw();
    };

    class ReadMissingClosingException : public ReaderException {
        std::string m_mismatch;
    public:
        ReadMissingClosingException(std::string const &mismatch);
        virtual ~ReadMissingClosingException() = default;
        virtual char const *what() const throw();
    };
}
