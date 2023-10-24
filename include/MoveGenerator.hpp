#ifndef MOVEGENERATOR_HPP
#define MOVEGENERATOR_HPP

#include <stdexcept>
#include <vector>

#include "./ChessBoard.hpp"
#include "./Coordinate.hpp"
namespace MoveGenerator
{
    // All functions to generate legal moves for each piece, respectively.
    std::vector<Coordinate> generatePawnMoves(const ChessBoard& board, const Coordinate& position);

    std::vector<Coordinate> generateKnightMoves(const ChessBoard& board, const Coordinate& position);

    std::vector<Coordinate> generateBishopMoves(const ChessBoard& board, const Coordinate& position);

    std::vector<Coordinate> generateRookMoves(const ChessBoard& board, const Coordinate& position);

    std::vector<Coordinate> generateQueenMoves(const ChessBoard& board, const Coordinate& position);

    std::vector<Coordinate> generateKingMoves(const ChessBoard& board, const Coordinate& position);

    std::vector<Coordinate> generateMoves(const ChessBoard& board, const Coordinate& position, ChessBoard::PieceType pieceType); // Generalized function that calls the appropriate piece generation function.

};

#endif