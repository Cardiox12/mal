#include <iostream>
#include "headers/linenoise.hpp"

char const *HIST_PATH = ".history.txt";

void config_linenoise() {
    linenoise::SetMultiLine(true);
    linenoise::LoadHistory(HIST_PATH);
}

std::string READ(std::string const &input) {
    return input;
}

std::string EVAL(std::string const &input) {
    return input;
}

std::string PRINT(std::string const &input) {
    return input;
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
        std::cout << rep(line) << "\n";
        linenoise::AddHistory(line.c_str());
    }
    linenoise::SaveHistory(HIST_PATH);
}