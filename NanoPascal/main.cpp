#include <iostream>
#include <fstream>
#include "parser.h"

int main(int argc, char *argv[]){
    /* int mn = std::stoul("0xff",nullptr,16); */

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
        std::cerr << "Cannot open '" << argv[1] << "'\n";
        return 1;
    }

    Lexer lexer(input);
    Parser parser(lexer);

    try
    {
        parser.parse();
    }
    catch(const std::string& e)
    {
        std::cerr << e << '\n';
    }
    

    return EXIT_SUCCESS;
}