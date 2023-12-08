#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include <cstdint>

#include <unordered_map>
#include <string>
#include <tuple>

#include "./Coordinate.hpp"

typedef uint64_t U64;

// A chess board. Uses bitboards to store the position of pieces in an 8x8 board.
class ChessBoard
{
    public:
        enum PieceType
        {
            EMPTY = -1,
            PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
        };

        enum PlayerColor
        {
            NONE = -1,
            WHITE, BLACK
        };

        ChessBoard();

        // Returns the piece at the given position.
        std::tuple<PlayerColor, PieceType> getPieceAt(const Coordinate& position) const;
        std::tuple<PlayerColor, PieceType> getPieceAt(const Coordinate& position, const PlayerColor color) const;

        U64 getBitBoardForPiece(PieceType piece, PlayerColor color) const;

        U64 coordinateToBitboard(Coordinate position) const;

        U64 getOccupancyBitboard() const;
        
        U64 getOccupancyBitboard(PlayerColor color) const;

        bool isSquareOccupied(const Coordinate& position) const;

        void applyMove(const Coordinate& from, const Coordinate& to);

        void undoMove(const Coordinate& from, const Coordinate& to);

        void placePiece(const PieceType piece, const PlayerColor color, const Coordinate& position);

        void clearBoard();

        // Converts the current stored position to FEN format for exporting.
        std::string toFEN();

    private:
        std::unordered_map<PieceType, U64> bitBoards[2];
        std::unordered_map<PieceType, char> pieceSymbols[2];

        bool whiteToMove;

};

#endif