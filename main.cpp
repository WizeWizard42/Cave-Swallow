#include <iostream>

#include "include/ChessBoard.hpp"
#include "include/MoveGenerator.hpp"

int main(int argc, char* argv[])
{
    ChessBoard game;

    std::cout << game.toFEN() << std::endl;

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            std::cout << game.getPieceAt(Coordinate(x, y)) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}