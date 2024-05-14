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
		case 11: {
			AST_O* ast_o = new(struct AST_OPERATOR);
			ast_o = make_node<AST_OPERATOR>(store, token, ast_o);
			this->InArray[ast_o->position].TokU.ast_o = ast_o;
			this->InArray[ast_o->position].discriminator = TokArray::AST_OP;
			break; }
		case 0: {
			AST_V* ast_v = new(struct AST_VARIABLE);
			ast_v = make_node<AST_VARIABLE>(store, token, ast_v);
			this->InArray[ast_v->position].TokU.ast_v = ast_v; 
			this->InArray[ast_v->position].discriminator = TokArray::AST_VAR;
			break;
		}
		case 1: {
			AST_N* ast_n = new(struct AST_NUMERAL);
			ast_n = make_node<AST_NUMERAL>(store, token, ast_n);
			this->InArray[ast_n->position].TokU.ast_n = ast_n;
			this->InArray[ast_n->position].discriminator = TokArray::AST_NUM;
			break; 
		}
		default: std::cout << "The token type can't be parsed";
			break;
		}
		store->counter++;
	}
	AST_E* ast_e = new(struct AST_ENDOFARRAY);
	this->InArray[store->counter].TokU.ast_e->position = store->counter; //end of array token
}

int OutputArray::PeekFunction(InputArray& InObj, int index) {
	int type = InObj.InArray[index].discriminator;
	return type;
}
//array sould looik like this: [0]ast_ex, [1]ast_o->7(;), [2]ast_e
//also only call this once
void OutputArray::Grammar_rule_0(InputArray& InObj) {
	InObj.inptr = 0;
	outptr = 0;
	AST_EX* ast_ex = new(struct AST_EXPRESSION);
	ast_ex->position = 0;
	OutArray[ast_ex->position].TokU.ast_ex = ast_ex;
	AST_O* ast_o = new(struct AST_OPERATOR);
	ast_o->tok = 7;
	ast_o->position = 1;
	OutArray[ast_o->position].TokU.ast_o = ast_o;
	AST_E* ast_e = new(struct AST_ENDOFARRAY);
	ast_e->position = 2;
	OutArray[ast_e->position].TokU.ast_e = ast_e;
}
 //probably should've used a template function but I remembered it too late
void OutputArray::PushArray(int push_times) {
	int type = this->OutArray[outptr + 1].discriminator;
	switch (type) {
	case 0: { //numeral on the right
		AST_N* ast_n = new(struct AST_NUMERAL);
		ast_n = this->OutArray[outptr + 1].TokU.ast_n;
		ast_n->position++;
		this->OutArray[outptr + push_times].TokU.ast_n = ast_n;
		delete this->OutArray[outptr + 1].TokU.ast_n;
		break;
	}
	case 1: {  //operator on the right
		AST_O* ast_o = new(struct AST_OPERATOR);
		ast_o = this->OutArray[outptr + 1].TokU.ast_o;
		ast_o->position++;
		this->OutArray[outptr + push_times].TokU.ast_o = ast_o;
		delete this->OutArray[outptr + 1].TokU.ast_o;
		break; }
	case 2: { //variable on the right
		AST_V* ast_v = new(struct AST_VARIABLE);
		ast_v = this->OutArray[outptr + 1].TokU.ast_v;
		ast_v->position++;
		this->OutArray[outptr + push_times].TokU.ast_v = ast_v;
		delete this->OutArray[outptr + 1].TokU.ast_v;
		break;
	}
	case 3: { //end on the right
		AST_E* ast_e = new(struct AST_ENDOFARRAY);
		ast_e = this->OutArray[outptr + 1].TokU.ast_e;
		ast_e->position++;
		this->OutArray[outptr + push_times].TokU.ast_e = ast_e;
		delete this->OutArray[outptr + 1].TokU.ast_e;
		break;
	}
	case 4: { //factor on the right
		AST_F* ast_f = new(struct AST_FACTOR);
		ast_f = this->OutArray[outptr + 1].TokU.ast_f;
		ast_f->position++;
		this->OutArray[outptr + push_times].TokU.ast_f = ast_f;
		delete this->OutArray[outptr + 1].TokU.ast_f;
		break;
	}
	case 5: { //expression on the right
		AST_EX* ast_ex = new(struct AST_EXPRESSION);
		ast_ex = this->OutArray[outptr + 1].TokU.ast_ex;
		ast_ex->position++;
		this->OutArray[outptr + push_times].TokU.ast_ex = ast_ex;
		delete this->OutArray[outptr + 1].TokU.ast_ex;
		break;
	}
	case 6: { //term on the right
		AST_T* ast_t = new(struct AST_TERM);
		ast_t = this->OutArray[outptr + 1].TokU.ast_t;
		ast_t->position++;
		this->OutArray[outptr + push_times].TokU.ast_t = ast_t;
		delete this->OutArray[outptr + 1].TokU.ast_t;
		break;
	}
	default: std::cout << "Parser error, discriminator is bugging out! " << std::endl;
		break;
	}

}
//each function calls another function but before that chceks if inptrobj = outptrobj and if it is then increment it
void OutputArray::Grammar_rule_1(InputArray& InObj) { 
	int type = PeekFunction(InObj, outptr+1);
	switch (type) {
	case 0: //there's another num???
		std::cout << "Parse error, expected an operator between 2 numbers" << std::endl;
		return;
		break;
	case 1: {
		if ((InObj.InArray[outptr + 1].TokU.ast_o->tok) == 8) {  //addition
			delete OutArray[outptr].TokU.ast_ex;
			AST_T* ast_t1 = new(struct AST_TERM);
			ast_t1->position = outptr;
			OutArray[ast_t1->position].TokU.ast_t = ast_t1;
			PushArray(3); //push the array forward by 3
			AST_O* ast_o = new(struct AST_OPERATOR);
			ast_o->position = outptr + 1;
			ast_o->tok = 8;
			OutArray[ast_o->position].TokU.ast_o = ast_o;
			AST_T* ast_t2 = new(struct AST_TERM);
			ast_t2->position = outptr + 2;
			OutArray[ast_t2->position].TokU.ast_t = ast_t2;
		}
		else if((InObj.InArray[outptr + 1].TokU.ast_o->tok) == 2) {  //equals
			delete OutArray[outptr].TokU.ast_ex;
			AST_F* ast_f1 = new(struct AST_FACTOR);
			ast_f1->position = outptr;
			OutArray[ast_f1->position].TokU.ast_f = ast_f1;
			PushArray(3); //push the array forward by 3
			AST_O* ast_o = new(struct AST_OPERATOR);
			ast_o->position = outptr + 1;
			ast_o->tok = 2;
			OutArray[ast_o->position].TokU.ast_o = ast_o;
			AST_F* ast_f2 = new(struct AST_FACTOR);
			ast_f2->position = outptr + 2;
			OutArray[ast_f2->position].TokU.ast_f = ast_f2;
		}
		else if ((InObj.InArray[outptr + 1].TokU.ast_o->tok) == 9) {  //addition
			delete OutArray[outptr].TokU.ast_ex;
			AST_T* ast_t1 = new(struct AST_TERM);
			ast_t1->position = outptr;
			OutArray[ast_t1->position].TokU.ast_t = ast_t1;
			PushArray(3); //push the array forward by 3
			AST_O* ast_o = new(struct AST_OPERATOR);
			ast_o->position = outptr + 1;
			ast_o->tok = 9;
			OutArray[ast_o->position].TokU.ast_o = ast_o;
			AST_T* ast_t2 = new(struct AST_TERM);
			ast_t2->position = outptr + 2;
			OutArray[ast_t2->position].TokU.ast_t = ast_t2;
		}
		else {
			//check what type and grammar rule
		}
		break;
	}
	case 2:
		std::cout << "Parse error, expected an operator between 2 numbers" << std::endl;
		return;
		break;
	}
}

//this will check grammars and check for input and output array using the inptr and outptr
//remember peek funciton to "predict" some sort
void MakeThroughGrammar() {
	int x = 0;
}; 
void Grammar_rule_0() {
}

//use select case/switch while compiling to create ast depending ont he token value

//void main() {
//	AST_OPERATOR* ast_o = init_operator_node();
//	ASTree* tree = Make_Tree(nullptr, nullptr, ast_o, nullptr);
//}


//This does work, just don't call it main function cause the ain fucniton si at languale_console.,cpp