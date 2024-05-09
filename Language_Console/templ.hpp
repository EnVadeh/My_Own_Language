#pragma once
#include "token.h"
#include <iostream>
template <typename Node_Type>
Node_Type* make_node(TOKEN_T* token) {
	Node_Type* node = new Node_Type();
	node->token = token->types;
	node->position = node_pos(token);
	if constexpr (std::is_same_v<Node_Type, AST_OPERATOR>) {
		//node->op = token->value;
		std::cout << "This is an operator node";
	}
	else if constexpr (std::is_same_v<Node_Type, AST_FUNCTION>) {
		//node->name = "node function";
	}
	else if constexpr (std::is_same_v<Node_Type, AST_NUMERAL>){
		//node->value = token->value;
	}
	//else if constexpr (std::is_same_v<Node_Type, AST_VARIABLE>) {}
	return node;
}