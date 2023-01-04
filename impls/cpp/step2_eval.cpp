#include <iostream>
#include "headers/linenoise.hpp"
#include "headers/tokenizer.hpp"
#include "headers/reader.hpp"
#include "headers/printer.hpp"
#include "headers/env.hpp"

char const *HIST_PATH = ".history.txt";

void config_linenoise() {
    linenoise::SetMultiLine(true);
    linenoise::LoadHistory(HIST_PATH);
}

mal::Type *EVAL(mal::Type *ast, mal::env_t &env);

mal::Type*
eval_ast(mal::Type *ast, mal::env_t &env) {

    if (ast->is(mal::TypeTag::SYMBOL)) {
        Mal_VAR(mal::Symbol*, symbol, ast);
        auto value = mal::get_env(env, symbol->value());

        if (!value)
            throw new mal::EnvNotFoundException(symbol->value());
        return *value;
    } 
    else if (ast->is(mal::TypeTag::LIST)) {
        Mal_VAR(mal::List*, list, ast);
        mal::List *new_list = new mal::List();

        for ( auto val : list->value() ){
            new_list->add(EVAL(val, env));
        }
        return new_list;
    }
    return ast;
}

mal::Type *READ(std::string const &input) {
    return mal::read_str(input);
}

mal::Type *EVAL(mal::Type *ast, mal::env_t &env) {
    if (!ast->is(mal::TypeTag::LIST)) {
        return eval_ast(ast, env);
    }
    mal::List *list = static_cast<mal::List*>(ast);

    if (list->value().empty()) {
           return ast;
    }
    Mal_VAR(mal::List*, result, eval_ast(ast, env));
    Mal_VAR(mal::Function*, fn, result->value().front());
    Mal_VAR(mal::List*, args, result);
    
    return (*fn)(args->rest());
}

std::string PRINT(mal::Type *type) {
    auto repr = mal::pr_str(type);
    
    delete type;
    return repr;
}

std::string rep(std::string const &input) {
    auto ast = READ(input);
    ast = EVAL(ast, mal::repl_env);

    return PRINT(ast);
}

int main() {
    std::string line;

    config_linenoise();
    while (true) {
        if (linenoise::Readline("user> ", line))
            break;
        try {
            std::cout << rep(line) << "\n";
        } catch (std::exception *e) {
            std::cout << e->what() << std::endl;
        }
        linenoise::AddHistory(line.c_str());
    }
    linenoise::SaveHistory(HIST_PATH);
}