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

        // Returns the bitboard for the given piece.
        U64 getBitBoardForPiece(PieceType piece, PlayerColor color) const;

        // Returns the bitboard for the given coordinate.
        U64 coordinateToBitboard(Coordinate position) const;

        // Returns the occupancy bitboard for both colors.
        U64 getOccupancyBitboard() const;
        
        // Returns the occupancy bitboard for the given color.
        U64 getOccupancyBitboard(PlayerColor color) const;

        // Returns whether the given square is occupied by any piece.
        bool isSquareOccupied(const Coordinate& position) const;

        // Returns a tuple of two booleans, representing whether the player can castle kingside and queenside, respectively.
        std::tuple<bool, bool> canCastle(const PlayerColor color) const;

        void applyMove(const Coordinate& from, const Coordinate& to); // Change to use command pattern

        void undoMove(const Coordinate& from, const Coordinate& to); // Same as above

        // Places a piece on the board at the given position.
        void placePiece(const PieceType piece, const PlayerColor color, const Coordinate& position);

        // Clears the board of all pieces.
        void clearBoard();

        // Converts the current stored position to FEN format for exporting. Move this to GameController later.
        std::string toFEN();

    private:
        std::unordered_map<PieceType, U64> bitBoards[2];
        std::unordered_map<PieceType, char> pieceSymbols[2]; // Make this a public static member later. Maybe move to GameController?

        char enPassantTargetSquare[3] = "-";

        int halfMoveClock = 0;
        int fullMoveNumber = 1;

        bool castleRights[2][2] = {{true, true}, {true, true}}; // [white/black][kingside/queenside]
        bool whiteToMove;

};

#endif