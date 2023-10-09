//
// Created by brage on 10. okt 2023.
//

#include "error.h"

void error::throwError(Token token, std::string message) {
    //std::cout << "Error at line " << token.line << ": " << message << std::endl;
    exit(1);
}
