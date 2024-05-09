#include <iostream>
#include "token.h"
#include "compiler.h"
#include <fstream>
#include <string>

std::string readfile(const char* filename) {
    std::ifstream file(filename, std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Could not read file: " << filename << std::endl;
        return "";
    }
    std::string buffer;
    std::string line;

    while (std::getline(file, line)) {
        buffer += line + '\n';
    }
    file.close();
    return buffer;
}


void compile(char* src) {
    LEXER_L* lexer = init_lexer(src);
    TOKEN_T* tok = nullptr;

    while ((tok = lexer_next_token(lexer)) != nullptr) {
        if (tok->types == TOKEN_STRUCT::TOKEN_EOF) {
            delete tok;
            break;
        }
        store_tokens(tok);
        std::cout << "the token represents: [" << tok->value << "]" << " and its token is: [" << tok->types << "] " << std::endl;
        delete tok;
    }
}

void compile_file(const char* filename) {
    std::string src_name = readfile(filename);
    char* src = &src_name[0];
    compile(src);
}
