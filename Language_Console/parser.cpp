#include "parser.h"
#include "token.h"
#include "iostream"
#include "templ.hpp"

//think of how to call these functions
//also remember to deal with nullptrs. 
//possible problem with the max and counter is that only the first member of the array's "max" is being changed.
// thas why I created it as a static
//also another problem, possibly is that I will delete the tokens and the store every line, i wonder what's gonna happen in the future..

//the prev/current/next token is just copying the adress of the token
TOKEN_T* token_prev(TOKEN_COUNTER_STRUCT* store) {
	if ((store->counter) < 0) {
		return nullptr;
	}
	else {
		TOKEN_T* prev_token = &store[(store->counter) - 1].token;
		return prev_token;
	}
}

TOKEN_T* token_current(TOKEN_COUNTER_STRUCT* store) {
		TOKEN_T* current_token = &store[(store->counter) + 1].token;
		return current_token;
}

TOKEN_T* token_next(TOKEN_COUNTER_STRUCT* store) {
	if ((store->counter) > (store->max_token)) {
		return nullptr;
	}
	else {
		TOKEN_T* next_token = &store[(store->counter) + 1].token;
		return next_token;
	}
}

int node_pos(TOKEN_COUNTER_STRUCT* store, TOKEN_T* tok) {
	//each token has to check for the token before it and after it before putting it somewhere right? This is where grammar rules are supposed to be implemented I guess.
	TOKEN_T* prev_token = token_prev(store);
	TOKEN_T* current_token = tok;
	TOKEN_T* next_token = token_next(store);
	//code here to determine position.. not determined yet
	return 0;
}
ASTree* Make_Tree(TOKEN_COUNTER_STRUCT* store) {
	ASTree* Tree_A = new ASTree[100]; //for some reason the array is starting to fill from 48
	store->counter = 0; //to start the loop
	while (store->counter<store->max_token) {
		TOKEN_T* tok = token_current(store);
		
		//initalising these outside the switch case for less error
		AST_OPERATOR* ast_o;
		AST_VARIABLE* ast_v;
		AST_NUMERAL* ast_n;
	//these make tokens: //also right now i'm assuming that brackets and paranthesis are also operators
		switch (tok->types) {
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
			ast_o = make_node<AST_OPERATOR>(store, tok);
			break;
		case 0:
			ast_v = make_node<AST_VARIABLE>(store, tok);
			break;
		case 1:
			ast_n = make_node<AST_NUMERAL>(store, tok);
			break;

		default: std::cout << "The token type can't be parsed";
		}
		store->counter++;
	}

	return Tree_A;
}


//AST_OPERATOR* init_operator_node(TOKEN_T* token) {
//	AST_OPERATOR* ast_o = new(struct AST_OPERATOR);
//	ast_o->op = token->value;
//	ast_o->token = token->types;
//	ast_o->position = '0';
//	return ast_o;
//}
//AST_FUNCTION* init_function_node(TOKEN_T* token) {
//	AST_FUNCTION* ast_f = new(struct AST_FUNCTION);
//	ast_f->name = "node function";
//	ast_f->token = '0';
//	ast_f->position = '0';
//	return ast_f;
//}
//AST_NUMERAL* init_numeral_node(TOKEN_T* token) {
//	AST_NUMERAL* ast_n = new(struct AST_NUMERAL);
//	//ast_n->value = static_cast<asn_value>(token->value); //change tokenizer for numbers.
//	ast_n->token = '0';
//	ast_n->position = '0';
//	return ast_n;
//}
//AST_VARIABLE* init_variable_node(TOKEN_T* token) {
//	AST_VARIABLE* ast_v = new(struct AST_VARIABLE);
//	ast_v->name = "name";
//	ast_v->token = '0';
//	ast_v->position = '0';
//	return ast_v;
//}

//use select case/switch while compiling to create ast depending ont he token value
//change the position later using grammar rules

//void main() {
//	AST_OPERATOR* ast_o = init_operator_node();
//	ASTree* tree = Make_Tree(nullptr, nullptr, ast_o, nullptr);
//}


//This does work, just don't call it main function cause the ain fucniton si at languale_console.,cpp