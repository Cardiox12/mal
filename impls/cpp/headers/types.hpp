#pragma once

#include <string>
#include <vector>

namespace mal
{
    enum class TypeTag {
        LIST,
        VECTOR,
        SYMBOL,
        INTEGER,
        NIL,
        KEYWORD,
        BOOLEAN,
    };

    class Type {
        TypeTag m_tag;
    protected:
        Type(TypeTag tag);
    public:
        virtual ~Type() = default;

        virtual std::string repr() const = 0;
        bool is(TypeTag tag) const;
    };

    // Sequence type
    class List : public Type {
        std::vector<Type*> m_list;
    public:
        List();
        virtual ~List();

        void add(Type *type);
        virtual std::string repr() const;
    };

    class Vector : public Type {
        std::vector<Type*> m_vec;
    public:
        Vector();
        virtual ~Vector();

        void add(Type *type);
        virtual std::string repr() const;
    };

    // Scalars

    struct Nil : public Type {
        Nil();
        virtual ~Nil() = default;

        virtual std::string repr() const;
    };

    class Keyword : public Type {
        std::string m_keyword;
    public:
        Keyword(std::string const &keyword);
        virtual ~Keyword() = default;

        virtual std::string repr() const;
    };

    
    class Symbol : public Type {
        std::string m_symbol;
    public:
        Symbol(std::string const &symbol);
        virtual ~Symbol() = default;

        virtual std::string repr() const;
    };

    class Integer : public Type {
        int m_value;
    public:
        Integer(int value);
        Integer(std::string const &value);
        virtual ~Integer() = default;

        virtual std::string repr() const;
    };

    class Boolean : public Type {
        bool m_value{ false };
    public:
        Boolean(bool value);
        Boolean(std::string const &value);
        virtual ~Boolean() = default;

        virtual std::string repr() const;
    };
}

