#ifndef MOVEGENERATOR_HPP
#define MOVEGENERATOR_HPP

#include <stdexcept>
#include <vector>

#include "./ChessBoard.hpp"

typedef struct Coordinate // Typedef for a 2-integer coordinate. Also provides easy comparison.
{
    Coordinate(int x, int y) : coord{x, y} {}

    int& operator[](int i)
    {
        if (i < 0 || i >= 2) throw std::out_of_range("Index out of range");
        return coord[i];
    }

    int operator[](int i) const
    {
        if (i < 0 || i >= 2) throw std::out_of_range("Index out of range");
        return coord[i];
    }

    bool operator==(const Coordinate& other) const
    {
        return coord[0] == other.coord[0] && coord[1] == other.coord[1];
    }

    bool operator!=(const Coordinate& other) const
    {
        return !(*this == other);
    }

    int coord[2];
    
} Coordinate;

class MoveGenerator
{
    public: // All functions to generate legal moves for each piece, respectively.
        static std::vector<Coordinate> generatePawnMoves(const ChessBoard& board, const Coordinate& position);

        static std::vector<Coordinate> generateKnightMoves(const ChessBoard& board, const Coordinate& position);

        static std::vector<Coordinate> generateBishopMoves(const ChessBoard& board, const Coordinate& position);

        static std::vector<Coordinate> generateRookMoves(const ChessBoard& board, const Coordinate& position);

        static std::vector<Coordinate> generateQueenMoves(const ChessBoard& board, const Coordinate& position);

        static std::vector<Coordinate> generateKingMoves(const ChessBoard& board, const Coordinate& position);

        static std::vector<Coordinate> generateMoves(const ChessBoard& board, const Coordinate& position, ChessBoard::PieceType pieceType); // Generalized function that calls the appropriate piece generation function.

};

#endif