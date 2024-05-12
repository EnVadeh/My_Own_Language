#pragma once
#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include "token.h"

struct AST_FUNCTION{
	std::string name;  // name of the function also do I use std string of vector<char>?
	int token;
	int position;  // position of node; 
};

struct AST_NUMERAL {
	int value;  //type cast the string to int later
	int token;
	int position;  // position of node; 
};

struct AST_OPERATOR {
	char op;
	int token;
	int position;  // position of node; 
};

struct AST_VARIABLE{
	std::string name; //name of the variMable
	int token;
	int position;  // position of node; 
};

typedef AST_FUNCTION AST_F;
typedef AST_NUMERAL AST_N;
typedef AST_OPERATOR AST_O;
typedef AST_VARIABLE AST_V;

//right now it's a apointer, so only one can exist.. need to change this
union AST {
	AST_F* ast_f;
	AST_N* ast_n;
	AST_O* ast_o;
	AST_V* ast_v;
};

typedef AST ASTree;

//this is confusing:: Shoudl I create an ast as I lex? I guess I should wait for nextline and create an ast for that..
// for this I need to change thej compiler.cpp function
// new plan! Store tokens for each line only, and then reset the counter after the line's over?
TOKEN_T* token_prev(TOKEN_COUNTER_STRUCT* store);
TOKEN_T* token_current(TOKEN_COUNTER_STRUCT* store);
TOKEN_T* token_next(TOKEN_COUNTER_STRUCT* store);
int node_pos(TOKEN_COUNTER_STRUCT* store, TOKEN_T* tok);

ASTree* Make_Tree(TOKEN_COUNTER_STRUCT* store);
//AST_OPERATOR* init_operator_node(TOKEN_T* token);
//AST_FUNCTION* init_function_node(TOKEN_T* token);
//AST_NUMERAL* init_numeral_node(TOKEN_T* token);
//AST_VARIABLE* init_variable_node(TOKEN_T* token);

#endif