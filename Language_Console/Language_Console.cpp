// Language_Console.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "compiler.h"
#include "token.h"
#include "parser.h"
#include "iostream"
#include "templ.hpp"

int main() {
	//compile_file("try.txt");
    TOKEN_T* token = new(struct TOKEN_STRUCT);
    std::string nam = "joe";
    char* nam_ptr = &nam[0];
    token->value = nam_ptr;
    int itype = 5;
    token->types = static_cast<TOKEN_STRUCT::type>(itype);
    //Make_Tree(store);
    
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
