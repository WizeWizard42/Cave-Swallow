#include <iostream>

#include "include/ChessBoard.hpp"
#include "include/MoveGenerator.hpp"

void printBitboard(U64 bitboard) {

    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            std::cout << ((bitboard & (1ULL << square)) ? '1' : '0');
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}



void testHorizontalMoves(const ChessBoard& board, const Coordinate& position, ChessBoard::PlayerColor color) {

    std::cout << "Testing horizontal moves from position (" << position[0] << ", " << position[1] << ") for color " << (color == ChessBoard::WHITE ? "White" : "Black") << ":" << std::endl;
    U64 moves = MoveGenerator::generateHorizontalMoves(board, position, color);
    printBitboard(moves);

}

void testVerticalMoves(const ChessBoard& board, const Coordinate& position, ChessBoard::PlayerColor color) {

    std::cout << "Testing vertical moves from position (" << position[0] << ", " << position[1] << ") for color " << (color == ChessBoard::WHITE ? "White" : "Black") << ":" << std::endl;
    U64 moves = MoveGenerator::generateVerticalMoves(board, position, color);
    printBitboard(moves);

}

void testDiagonalMoves(const ChessBoard& board, const Coordinate& position, ChessBoard::PlayerColor color) {

    std::cout << "Testing diagonal moves from position (" << position[0] << ", " << position[1] << ") for color " << (color == ChessBoard::WHITE ? "White" : "Black") << ":" << std::endl;
    U64 moves = MoveGenerator::generateDiagonalMoves(board, position, color);
    printBitboard(moves);

}



int main() {

    ChessBoard board;

    Coordinate position;

    ChessBoard::PlayerColor color;

    board.clearBoard();



    // Test 1: Empty board

    std::cout << "Test 1: Empty board\\n";

    position = Coordinate(4, 4); // E5

    color = ChessBoard::WHITE;

    board.placePiece(ChessBoard::ROOK, color, position);

    testDiagonalMoves(board, position, color);



    // Test 2: Board with pieces blocking horizontally

    std::cout << "Test 2: Board with pieces blocking vertically\\n";

    board.placePiece(ChessBoard::ROOK, ChessBoard::WHITE, Coordinate(4, 6)); // E7

    board.placePiece(ChessBoard::ROOK, ChessBoard::BLACK, Coordinate(4, 3)); // E4

    position = Coordinate(4, 4); // E5

    color = ChessBoard::WHITE;

    testVerticalMoves(board, position, color);



    // Test 3: Edge case - piece at the edge of the board

    std::cout << "Test 3: Edge case - piece at the edge of the board\\n";

    board.clearBoard();

    position = Coordinate(0, 4); // A5

    testHorizontalMoves(board, position, color);



    // Test 4: Piece surrounded by friendly pieces

    std::cout << "Test 4: Piece surrounded by friendly pieces\\n";

    board.clearBoard();

    board.placePiece(ChessBoard::ROOK, ChessBoard::WHITE, Coordinate(3, 4)); // E4

    board.placePiece(ChessBoard::ROOK, ChessBoard::WHITE, Coordinate(5, 4)); // E6

    position = Coordinate(4, 4); // E5

    testHorizontalMoves(board, position, color);



    return 0;

}
