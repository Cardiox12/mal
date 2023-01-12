#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <exception>

namespace mal
{
    enum class TypeTag {
        LIST,
        VECTOR,
        MAP,
        SYMBOL,
        INTEGER,
        NIL,
        KEYWORD,
        BOOLEAN,
        STRING,
        FUNCTION
    };

    const std::unordered_map<TypeTag, const char*> G_TYPE_NAME = {
        {TypeTag::LIST,     "list"},
        {TypeTag::VECTOR,   "vector"},
        {TypeTag::MAP,      "map"},
        {TypeTag::SYMBOL,   "symbol"},
        {TypeTag::INTEGER,  "integer"},
        {TypeTag::NIL,      "nil"},
        {TypeTag::KEYWORD,  "keyword"},
        {TypeTag::BOOLEAN,  "boolean"},
        {TypeTag::STRING,   "string"},
    };

    class Type {
        TypeTag m_tag;
    protected:
        Type(TypeTag tag);
    public:
        virtual ~Type() = default;

        virtual std::string repr() const = 0;
        bool is(TypeTag tag) const;
        TypeTag tag() const;
    };

    // Sequence type
    class List : public Type {
        std::vector<Type*> m_list;
    public:
        List();
        List(std::vector<Type*> const &list);
        virtual ~List();

        void add(Type *type);
        virtual std::string repr() const;
        std::vector<Type*> const &value() const;

        List *rest() const;
    };

    class Vector : public Type {
        std::vector<Type*> m_vec;
    public:
        Vector();
        virtual ~Vector();

        void add(Type *type);
        std::vector<Type*> const &value() const;
        virtual std::string repr() const;
    };

    class Map : public Type {
        std::unordered_map<Type*, Type*> m_map;
    public:
        Map();
        virtual ~Map();

        void add(Type *key, Type *val);
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
        std::string const &value() const;
    };

    class Integer : public Type {
        int m_value;
    public:
        Integer(int value);
        Integer(std::string const &value);
        virtual ~Integer() = default;

        int value() const;
        virtual std::string repr() const;
        Integer *add(Integer *x) const;
        Integer *sub(Integer *x) const;
        Integer *div(Integer *x) const;
        Integer *mult(Integer *x) const;
    };

    class Boolean : public Type {
        bool m_value{ false };
    public:
        Boolean(bool value);
        Boolean(std::string const &value);
        virtual ~Boolean() = default;

        virtual std::string repr() const;
    };

    class String : public Type {
        std::string m_value;
    public:
        String(std::string const &value);
        virtual ~String() = default;

        virtual std::string repr() const;
    };

    // Type exceptions

    class TypeException : public std::exception {
        std::string m_msg;
    public:
        TypeException(std::string const &msg);
        virtual char const *what() const throw();
    };

    // Type assert
    std::string get_type_name(TypeTag tag);

    /**
     * TypeAssert
     * TypeAssert object check for types that doesn't match the attribute `tag'.
     * If one of the type doesn't match the type tag `tag' attribute, an exception
     * of type `TypeException' is thrown.
     */
    class TypeAssert {
        TypeTag m_tag;
    public:
        TypeAssert(TypeTag tag);

        template<class... Args>
        void operator()(Type *got, Args... args) {
            if (!got->is(m_tag)) {
                throw new TypeException{ 
                    "expected type '" + get_type_name(m_tag) + "' but got type '" + get_type_name(got->tag()) + "'"
                };
            }
            this->operator()(args...);
        }
    private:
        // Default case 
        void operator()();
    };

    bool assert_types(Type*);

    /**
     * assert_types
     * assert_types function check type `t' against the tags passed in parameter.
     * If the type doesn't match one of the tags in parameter, the function will
     * throw an exception of type `TypeException'.
     */
    template<class... Tags>
    bool assert_types(Type *t, TypeTag tag, Tags... tags) {
        if (t->is(tag))
            return true;
        if (!assert_types(t, tags...)) {
            throw new TypeException{ 
                "expected type '" + get_type_name(tag) + "' but got type '" + get_type_name(t->tag()) + "'"
            };
        }
        return true;
    }

    static TypeAssert assert_int(TypeTag::INTEGER);
    static TypeAssert assert_list(TypeTag::LIST);
    static TypeAssert assert_vector(TypeTag::VECTOR);
    static TypeAssert assert_map(TypeTag::MAP);
    static TypeAssert assert_symbol(TypeTag::SYMBOL);
    static TypeAssert assert_nil(TypeTag::NIL);
    static TypeAssert assert_keyword(TypeTag::KEYWORD);
    static TypeAssert assert_boolean(TypeTag::BOOLEAN);
    static TypeAssert assert_string(TypeTag::STRING);
}
