#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include <cstdint>

#include <unordered_map>
#include <string>

typedef uint64_t U64;

// A chess board. Uses bitboards to store the position of pieces in an 8x8 board.
class ChessBoard
{
    public:
        enum PieceType
        {
            PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
        };

        enum PlayerColor
        {
            WHITE, BLACK
        };

        ChessBoard();

        // Converts the current stored position to FEN format for exporting.
        std::string toFEN();

        friend class MoveGenerator;

    private:
        std::unordered_map<PieceType, U64> bitBoards[2];
        std::unordered_map<PieceType, char> pieceSymbols[2];

        bool whiteToMove;

};

#endif