#pragma once
#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include "token.h"

// need to have these strucsts include actual tokens man..
// after thinking, i don't thikn I need it because I'm not comparing token values to the grammar... just the type, which is an int
//each token has this position index so it can self assign to the outputarray


struct AST_NUMERAL {
	int tok = 1;  //nums can only be int
	int position;  // position of node; 
};

struct AST_OPERATOR {
	int tok;  //opeartors will have diferent value for each type of operator
	int position;  // position of node; 
};

struct AST_VARIABLE {
	int tok = 0; //variable names are just ids
	int position;  // position of node; 
};

struct AST_ENDOFARRAY {
	int tok = 69; //placeholder number
	int position;
};

struct AST_FACTOR{ 
	int tok = 70;
	int position;  // position of node; 
};

struct AST_EXPRESSION {
	int tok = 71;
	int position;
};

struct AST_TERM {
	int tok = 72;
	int position;
};


typedef AST_NUMERAL AST_N;
typedef AST_OPERATOR AST_O;
typedef AST_VARIABLE AST_V;
typedef AST_ENDOFARRAY AST_E;
typedef AST_FACTOR AST_F;
typedef AST_EXPRESSION AST_EX;
typedef AST_TERM AST_T;


//right now it's a apointer, so only one can exist.. need to change this... nope dont' need to change. cause making new pointers eachiteration
union TOKEN_UNION {  //not making a tree anymore. just an input field
	AST_N* ast_n;
	AST_O* ast_o;
	AST_V* ast_v;
	AST_E* ast_e;
	AST_F* ast_f;   
	AST_EX* ast_ex;
	AST_T* ast_t;
};
typedef TOKEN_UNION TokU;

//I could use std::variant for tagged unions, its a moder cpp feature
//remind to use that in other producsts or in here if I have time to learn it
struct TOKEN_ARRAY {
	TOKEN_UNION TokU;
	enum discriminator{
		AST_NUM,
		AST_OP,
		AST_VAR,
		AST_END,
		AST_FACT,
		AST_EXPR,
		AST_TERM
	}
	discriminator;
};
typedef TOKEN_ARRAY TokArray;

struct AST {
	TokArray* lhs;
	TokArray* root;
	TokArray* rhs;
};

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

	int PeekFunction(InputArray& InObj, int index);

	//right nwo plan is for each function to call the other function
	void PushArray(int push_times);

// rule 0 : start -> expression;

	void Grammar_rule_0(InputArray& InObj);
//rule 1 : expression -> term(+term)* | term(-term)* | factor "=" factor

	void Grammar_rule_1(InputArray& InObj);

//rule 2 : term -> factor(xfactor)* | factor(/factor)*
	void Grammar_rule_2(InputArray& InObj);

	//rule 3 : factor -> expression | variable | number
	void Grammar_rule_3(InputArray& InObj);
};


// with variables i want ot check if it exists at all..
// also i want to check for the semicolon first and foremost


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