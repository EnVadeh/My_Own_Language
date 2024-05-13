#pragma once
#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include "token.h"

// need to have these strucsts include actual tokens man..
// after thinking, i don't thikn I need it because I'm not comparing token values to the grammar... just the type, which is an int
struct AST_FUNCTION{
	std::string name;  // name of the function also do I use std string of vector<char>?
	int tok;
	int position;  // position of node; 
};

struct AST_NUMERAL {
	int value;  //type cast the string to int later
	int tok = 1;  //nums can only be int
	int position;  // position of node; 
};

struct AST_OPERATOR {
	char op;
	int tok;  //opeartors will have diferent value for each type of operator
	int position;  // position of node; 
};

struct AST_VARIABLE {
	std::string name; //name of the variMable
	int tok = 0; //variable names are just ids
	int position;  // position of node; 
};

struct AST_ENDOFARRAY {
	int tok = 69; //placeholder number
	int position;
};


typedef AST_FUNCTION AST_F;
typedef AST_NUMERAL AST_N;
typedef AST_OPERATOR AST_O;
typedef AST_VARIABLE AST_V;
typedef AST_ENDOFARRAY AST_E;

//right now it's a apointer, so only one can exist.. need to change this... nope dont' need to change. cause making new pointers eachiteration
union TOKEN_ARRAY {  //not making a tree anymore. just an input field
	AST_F* ast_f;    //will copmare this to another union of grammar?
	AST_N* ast_n;
	AST_O* ast_o;
	AST_V* ast_v;
	AST_E* ast_e;
};

typedef TOKEN_ARRAY TokArray;
 //no need of stack, just check with other union
class InputArray {
public:
	TokArray InArray[50];
	int inptr;
	void MakeArray(TOKEN_COUNTER_STRUCT* store);
};

class OutputArray {
public:
	TokArray OutArray[50];
	int outptr;
	
};

void MakeThroughGrammar();
//when making grammar, save a previous state whenever grammar is called in the output array to make sure I can backtrack

//this is confusing:: Shoudl I create an ast as I lex? I guess I should wait for nextline and create an ast for that..
// for this I need to change thej compiler.cpp function
// new plan! Store tokens for each line only, and then reset the counter after the line's over?
TOKEN_T* token_prev(TOKEN_COUNTER_STRUCT* store);
TOKEN_T* token_current(TOKEN_COUNTER_STRUCT* store);
TOKEN_T* token_next(TOKEN_COUNTER_STRUCT* store);
int node_pos(TOKEN_COUNTER_STRUCT* store, TOKEN_T* tok);


#endif