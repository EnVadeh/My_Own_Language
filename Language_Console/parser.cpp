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




void InputArray::MakeArray(TOKEN_COUNTER_STRUCT* store) {
	//for some reason the array is starting to fill from 48
	store->counter = 0; //to start the loop
	while (store->counter < store->max_token) {
		TOKEN_T* token = token_current(store); //temp token
		//these make tokens: //also right now i'm assuming that brackets and paranthesis are also operators
		switch (token->types) {
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
			AST_O * ast_o = new(struct AST_OPERATOR);
			ast_o = make_node<AST_OPERATOR>(store, token, ast_o);
			this->InArray[ast_o->position].ast_o = ast_o;
			break;
		case 0:
			AST_V * ast_v = new(struct AST_VARIABLE);
			ast_v = make_node<AST_VARIABLE>(store, token, ast_v);
			this->InArray[ast_v->position].ast_v = ast_v;
		case 1:
			AST_N * ast_n = new(struct AST_NUMERAL);
			ast_n = make_node<AST_NUMERAL>(store, token, ast_n);
			this->InArray[ast_n->position].ast_n = ast_n;
			break;

		default: std::cout << "The token type can't be parsed";
			break;
		}
		store->counter++;
	}
	AST_E* ast_e = new(struct AST_ENDOFARRAY);
	this->InArray[store->counter].ast_e->position = store->counter; //end of array token
}




//this will check grammars and check for input and output array using the inptr and outptr
void MakeThroughGrammar() {
	int x = 0;
}; 

//use select case/switch while compiling to create ast depending ont he token value

//void main() {
//	AST_OPERATOR* ast_o = init_operator_node();
//	ASTree* tree = Make_Tree(nullptr, nullptr, ast_o, nullptr);
//}


//This does work, just don't call it main function cause the ain fucniton si at languale_console.,cpp