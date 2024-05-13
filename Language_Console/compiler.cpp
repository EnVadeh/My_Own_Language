#include <iostream>
#include "token.h"
#include "compiler.h"
#include <fstream>
#include <string>
#include "parser.h"
#include "templ.hpp"

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

// fix the loop so that it works a line at a time, so until semicolon
//maybe a prbolem is that the array has only pointers to the same tok
void compile(char* src) {
    LEXER_L* lexer = init_lexer(src);
    TOKEN_T* tok = nullptr;
    TOKEN_COUNTER_STRUCT* token_store = store_token();
    int line_start = 0;
    int line_end = 0;
    while (true) {
        token_store->counter = 0;
        token_store->max_token = 0;
        while (src[line_end] != ';' && src[line_end] != '\0') {   //we finding out where each line ends.. right now this is pretty expensive, try finding out a novel recursive loop or something
            line_end++;
        }
        lexer->i = line_start; //starting for eachh line
        lexer->c = src[line_start];
        while (lexer->i < line_end) {
            tok = lexer_next_token(lexer);
            if (tok != nullptr) {
                {
                    std::cout << "the token represents: [" << tok->value << "]" << " and its token is: [" << tok->types << "] " << std::endl;
                    store_add(tok, token_store);
                delete tok;
                }
            }
        }
        if (((tok = lexer_next_token(lexer)) != nullptr) && (tok->types == TOKEN_STRUCT::TOKEN_SCOLON)) {
            std::cout << "the token represents: [" << tok->value << "]" << " and its token is: [" << tok->types << "] " << std::endl;
            store_add(tok, token_store);
            delete tok;
        
        }
        std::cout << "Final store: " << token_store->max_token<< std::endl;
        //ASTree* tree = Make_Tree(token_store);
        //make tree now here ->

        if (src[line_end] == '\0') {
            break;
        }
        line_start = line_end + 1;
        line_end = line_start;
    }

    /*while (((tok = lexer_next_token(lexer)) != nullptr) && (tok->types != TOKEN_STRUCT::TOKEN_SCOLON) ) {
        if (tok != nullptr) {
            store_add(tok, token_store);      
            std::cout << "the token represents: [" << tok->value << "]" << " and its token is: [" << tok->types << "] " << std::endl;
            delete tok;
        }
    }*/
}

void compile_file(const char* filename) {
    std::string src_name = readfile(filename);
    char* src = &src_name[0];
    compile(src);
}
