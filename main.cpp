#include <iostream>
#include <fstream>

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

void testKnightMoves(const ChessBoard& board, const Coordinate& position, ChessBoard::PlayerColor color) {

    std::cout << "Testing knight moves from position (" << position[0] << ", " << position[1] << ") for color " << (color == ChessBoard::WHITE ? "White" : "Black") << ":" << std::endl;
    U64 moves = MoveGenerator::generateKnightMoves(board, position, color);
    printBitboard(moves);
}

void testPawnMoves(const ChessBoard& board, const Coordinate& position, ChessBoard::PlayerColor color) {

    std::cout << "Testing pawn moves from position (" << position[0] << ", " << position[1] << ") for color " << (color == ChessBoard::WHITE ? "White" : "Black") << ":" << std::endl;
    U64 moves = MoveGenerator::generatePawnMoves(board, position, color);
    printBitboard(moves);

}



int main() {

    ChessBoard board;
    Coordinate position;
    
    // Test Pawn Moves
    board.clearBoard();
    position.setCoord(4, 1); // e2
    board.placePiece(ChessBoard::PAWN, ChessBoard::WHITE, position);
    U64 pawnMoves = MoveGenerator::generatePawnMoves(board, position, ChessBoard::WHITE);
    std::cout << "Pawn moves from e2:\n";
    printBitboard(pawnMoves);

    // Test Knight Moves
    board.clearBoard();
    position.setCoord(1, 0); // b1
    board.placePiece(ChessBoard::KNIGHT, ChessBoard::WHITE, position);
    U64 knightMoves = MoveGenerator::generateKnightMoves(board, position, ChessBoard::WHITE);
    std::cout << "Knight moves from b1:\n";
    printBitboard(knightMoves);

    // Test Bishop Moves
    board.clearBoard();
    position.setCoord(2, 3); // c4
    board.placePiece(ChessBoard::BISHOP, ChessBoard::WHITE, position);
    U64 bishopMoves = MoveGenerator::generateBishopMoves(board, position, ChessBoard::WHITE);
    std::cout << "Bishop moves from c4:\n";
    printBitboard(bishopMoves);

    // Test Rook Moves
    board.clearBoard();
    position.setCoord(4, 4); // e5
    board.placePiece(ChessBoard::ROOK, ChessBoard::WHITE, position);
    U64 rookMoves = MoveGenerator::generateRookMoves(board, position, ChessBoard::WHITE);
    std::cout << "Rook moves from e5:\n";
    printBitboard(rookMoves);

    // Test Queen Moves
    board.clearBoard();
    position.setCoord(4, 4); // e5
    board.placePiece(ChessBoard::QUEEN, ChessBoard::WHITE, position);
    U64 queenMoves = MoveGenerator::generateQueenMoves(board, position, ChessBoard::WHITE);
    std::cout << "Queen moves from e5:\n";
    printBitboard(queenMoves);

    // Test King Moves
    board.clearBoard();
    position.setCoord(6, 1); // g2
    board.placePiece(ChessBoard::KING, ChessBoard::WHITE, position);
    U64 kingMoves = MoveGenerator::generateKingMoves(board, position, ChessBoard::WHITE);
    std::cout << "King moves from g2:\n";
    printBitboard(kingMoves);


    // Test 1: Empty board

    std::cout << "Test 1: Empty board\\n";

    board.clearBoard();

    position.setCoord(4, 2); // E3

    board.placePiece(ChessBoard::PAWN, ChessBoard::WHITE, position);

    testPawnMoves(board, position, ChessBoard::WHITE);



    // Test 2: Board with pieces blocking horizontally

    std::cout << "Test 2: Board with pieces blocking vertically\\n";

    board.placePiece(ChessBoard::ROOK, ChessBoard::WHITE, Coordinate(4, 6)); // E7

    board.placePiece(ChessBoard::ROOK, ChessBoard::BLACK, Coordinate(4, 3)); // E4

    position.setCoord(4, 4); // E5

    testVerticalMoves(board, position, ChessBoard::WHITE);



    // Test 3: Edge case - piece at the edge of the board

    std::cout << "Test 3: Edge case - piece at the edge of the board\\n";

    board.clearBoard();

    position.setCoord(0, 4); // A5

    testHorizontalMoves(board, position, ChessBoard::WHITE);



    // Test 4: Piece surrounded by friendly pieces

    std::cout << "Test 4: Piece surrounded by friendly pieces\\n";

    board.clearBoard();

    board.placePiece(ChessBoard::ROOK, ChessBoard::WHITE, Coordinate(3, 4)); // E4

    board.placePiece(ChessBoard::ROOK, ChessBoard::WHITE, Coordinate(5, 4)); // E6

    position.setCoord(4, 4); // E5

    testHorizontalMoves(board, position, ChessBoard::WHITE);

    // Populate the board with multiple pieces

    board.placePiece(ChessBoard::ROOK, ChessBoard::WHITE, Coordinate(4, 6)); // E7
    board.placePiece(ChessBoard::PAWN, ChessBoard::BLACK, Coordinate(4, 3)); // E4
    board.placePiece(ChessBoard::KNIGHT, ChessBoard::BLACK, Coordinate(1, 1)); // D5
    board.placePiece(ChessBoard::KING, ChessBoard::BLACK, Coordinate(6, 5)); // G6
    board.placePiece(ChessBoard::KING, ChessBoard::WHITE, Coordinate(2, 5)); // C6

    // Print current FEN string to terminal
    std::cout << board.toFEN() << std::endl;

    // Write current FEN string to file
    std::ofstream file;
    file.open("test.fen");
    file << board.toFEN();
    file.close();

    return 0;

}
