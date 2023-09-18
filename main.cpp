#include <iostream>

#include "include/ChessBoard.hpp"

int main(int argc, char* argv[])
{
    ChessBoard game;

    std::cout << game.toFEN() << std::endl;

    return 0;
}