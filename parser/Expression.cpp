//
// Created by brage on 8. okt 2023.
//

#include <iostream>
#include "Expression.h"

void Expression::print() {
    recursivePrint("", "", "");
}

void Expression::recursivePrint(std::string string, std::string prefix, std::string childPrefix) {
    string += prefix + std::to_string(static_cast<int>(token->type)) + "\n";
    std::cout << string;

    if(this->left != nullptr) {
        std::cout << "left:" << static_cast<int>(this->left->token->type) << std::endl;
    }
    if(this->right != nullptr) {
        std::cout << "right:" << static_cast<int>(this->right->token->type) << std::endl;
    }
    /*if(this->left != nullptr) {
        this->left->recursivePrint(string, childPrefix + "left:   ", childPrefix + "|    ");
    }
    if(this->right != nullptr) {
        this->right->recursivePrint(string, childPrefix + "right:  ", childPrefix + "  ");
    }*/
}
