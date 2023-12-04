#ifndef MOVEGENERATOR_HPP
#define MOVEGENERATOR_HPP

#include <stdexcept>
#include <vector>

#include "./ChessBoard.hpp"
#include "./Coordinate.hpp"
namespace MoveGenerator
{
    U64 generateHorizontalMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color);

    U64 generateVerticalMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color);

    U64 generateDiagonalMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color);

    // All functions to generate legal moves for each piece, respectively.
    U64 generatePawnMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color);

    U64 generateKnightMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color);

    U64 generateBishopMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color);

    U64 generateRookMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color);

    U64 generateQueenMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color);

    U64 generateKingMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color);

    U64 generateMoves(const ChessBoard& board, const Coordinate& position, std::tuple<ChessBoard::PlayerColor, ChessBoard::PieceType> piece); // Generalized function that calls the appropriate piece generation function.

    U64 reverseBoard(U64 n);

    U64 createDiagonalMask(const Coordinate& position);
};

#endif