//
// Created by brage on 8. okt 2023.
//

#include <iostream>
#include "Expression.h"

void Expression::print() {
    recursivePrint("", "", "");
}

void Expression::recursivePrint(std::string string, std::string prefix, std::string childPrefix) {
    string += prefix + std::to_string(static_cast<int>(Operator)) + "\n";
    std::cout << string;
    if(!this->Left) {;
        this->Left->recursivePrint(string, childPrefix + "Left:   ", childPrefix + "|    ");
    }
    if(!this->Right) {
        this->Right->recursivePrint(string, childPrefix + "Right:  ", childPrefix + "  ");
    }
}
