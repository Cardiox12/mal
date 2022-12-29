#include "../headers/printer.hpp"

std::string
mal::pr_str(mal::Type *type) {
#ifdef DEBUG
    std::string type_tag;

    if (type->is(TypeTag::LIST))
        type_tag = "list";
    else if (type->is(TypeTag::SYMBOL))
        type_tag = "symbol";
    else if (type->is(TypeTag::INTEGER))
        type_tag = "integer";
    else if (type->is(TypeTag::NIL))
        type_tag = "nil";
    else if (type->is(TypeTag::KEYWORD))
        type_tag = "keyword";
    else if (type->is(TypeTag::BOOLEAN))
        type_tag = "boolean";
    else if (type->is(TypeTag::VECTOR))
        type_tag = "vector";
    else if (type->is(TypeTag::STRING))
        type_tag = "string";
    else if (type->is(TypeTag::MAP))
        type_tag = "map";
    return "[" + type_tag + "] " + type->repr();
#else
    return type->repr();
#endif
}
