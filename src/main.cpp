#include <iostream>
#include <sstream>
#include <fstream>
#include <optional>
#include <vector>

#include "tokenization.hpp"


//return token as asm
std::string tokenToAsm(const std::vector<Token>& tokens)
{
    std::stringstream output;
    output << "global _start\n_start:\n";
    for (int i = 0; i < tokens.size(); ++i)
    {
        const Token& token = tokens.at(i);
        if (token.type == TokenType::exit)
        {
            if (i + 1 < tokens.size() && tokens.at(i + 1).type == TokenType::init_lit)
            {
                if (i + 2 < tokens.size() && tokens.at(i +2).type == TokenType::semi)
                {
                    output << "   mov rax, 60\n";
                    output << "   mov rdi, " << tokens.at(i + 1).value.value() << std::endl;
                    output << "   syscall";
                }
            }
        }
    }
    return output.str();
}

int main(int argc, char* argv[]) {
    //Expect one arg after the program name
    if (argc != 2)
    {
        std::cerr << "Invalid Usage. Valid Usage is..." << std::endl;
        std::cerr << "nitro <input.ni>" << std::endl;
        return EXIT_FAILURE;
    }


    //Read the entire string file - test.ni
    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(argv[1], std::ios::in);
        if (!input) {
            std::cerr << "Error: Could not open file " << argv[1] << std::endl;
            return EXIT_FAILURE;
        }
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    Tokenizer tokenizer(std::move(contents));
    std::vector<Token> tokens = tokenizer.tokenize();
    {
         std::fstream file("output.asm", std::ios::out);
         file << tokenToAsm(tokens);
    }

    //system commands in WIN
    system("wsl nasm -felf64 output.asm -o output.o");
    system("wsl ld output.o -o output");

    return EXIT_SUCCESS;
}