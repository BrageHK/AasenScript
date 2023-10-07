#include <iostream>
#include <fstream>
#include <string>
#include "enums/TokenEnum.h"
#include "lexer/Lexer.h"

void runFile(const char* path) {
    std::cout << path << std::endl;
    std::ifstream file(path);
    std::string programText;
    if(file.is_open()) {
        std::string line;
        while(getline(file, line)) {
            programText.append(line);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
    std::cout << programText << std::endl;
}

void runPrompt() {
    std::cout << "Norlang, et proggerpåk med forferdelig (!bra) syntax!!!" << std::endl;
    int lineNumber = 1;
    for(;;) {
        std::cout << ">> ";
        std::string line;
        getline(std::cin, line);
        if(line == "exit") {
            break;
        }
        Lexer lexer(line);
        for(const auto& token : lexer.generateTokens(lineNumber++)) {
            std::cout << "[" << static_cast<int>(token.type) << ", " << token.value << "]" <<  std::endl;
        }

    }
}

int main(int argc, char* argv[]) {
    if(argc > 2) {
        std::cout << "Only one argument is supported!" << std::endl;
        return -1;
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }

    return 0;
}

