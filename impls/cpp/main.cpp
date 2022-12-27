#include "tokenizer.hpp"
#include <iostream>

int main() {
    std::string input = "(* 1 2 3123987 \n\n\n(+ 1 2))+ 1 22 []{}()'`~^@  ~@  \"Hello, je suis tony\" ; Je suis un commentaire";
    Tokenizer tokenizer(input);

    while (auto token = tokenizer.next()) {
        std::cout << "Token: |" << token.value() << "|" << std::endl;
    }
}