#include <iostream>
#include "headers/linenoise.hpp"
#include "headers/tokenizer.hpp"
#include "headers/reader.hpp"
#include "headers/printer.hpp"

char const *HIST_PATH = ".history.txt";

void config_linenoise() {
    linenoise::SetMultiLine(true);
    linenoise::LoadHistory(HIST_PATH);
}

mal::Type *READ(std::string const &input) {
    return mal::read_str(input);
}

mal::Type *EVAL(mal::Type *type) {
    return type;
}

std::string PRINT(mal::Type *type) {
    auto repr = mal::pr_str(type);
    
    delete type;
    return repr;
}

std::string rep(std::string const &input) {
    return PRINT(EVAL(READ(input)));
}

int main() {
    std::string line;

    config_linenoise();
    while (true) {
        if (linenoise::Readline("user> ", line))
            break;
        try {
            std::cout << rep(line) << "\n";
        } catch (mal::ReaderException *e) {
            std::cout << e->what() << std::endl;
        }
        linenoise::AddHistory(line.c_str());
    }
    linenoise::SaveHistory(HIST_PATH);
}