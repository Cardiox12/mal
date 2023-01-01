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

mal::Type*
eval_ast(mal::Type *ast, mal::env_t const &env) {
    switch (ast->tag())
    {
    case mal::TypeTag::SYMBOL: {
        Mal_VAR(mal::Symbol*, symbol, ast);

        auto it = env.find(symbol->value());

        if ( it == env.end() )
            return ast;
        return it->second;
    }
    case mal::TypeTag::LIST:
        break;
    }
    return ast;
}

mal::Type *READ(std::string const &input) {
    return mal::read_str(input);
}

mal::Type *EVAL(mal::Type *ast, mal::env_t const &env) {
    if (!ast->is(mal::TypeTag::LIST)) {
        return eval_ast(ast, env);
    }
    mal::List *list = static_cast<mal::List*>(ast);

    if (list->value().empty()) {
           return ast;
    }
    return eval_ast(ast, env);
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