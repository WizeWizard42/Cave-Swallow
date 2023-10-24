#include <stdexcept>
#include <iostream>

#include "../include/MoveGenerator.hpp"

namespace MoveGenerator
{
    std::vector<Coordinate>generatePawnMoves(const ChessBoard& board, const Coordinate& position)
    {
        std::cout << "TODO: Implement pawn move generation" << std::endl;
        return std::vector<Coordinate> { Coordinate(0, 0) };
    };

    std::vector<Coordinate> generateKnightMoves(const ChessBoard& board, const Coordinate& position)
    {
        std::cout << "TODO: Implement knight move generation" << std::endl;
        return std::vector<Coordinate> { Coordinate(0, 0) };
    };

    std::vector<Coordinate> generateBishopMoves(const ChessBoard& board, const Coordinate& position)
    {
        std::cout << "TODO: Implement bishop move generation" << std::endl;
        return std::vector<Coordinate> { Coordinate(0, 0) };
    };

    std::vector<Coordinate> generateRookMoves(const ChessBoard& board, const Coordinate& position)
    {
        std::cout << "TODO: Implement rook move generation" << std::endl;
        return std::vector<Coordinate> { Coordinate(0, 0) };
    };

    std::vector<Coordinate> generateQueenMoves(const ChessBoard& board, const Coordinate& position)
    {
        std::cout << "TODO: Implement queen move generation" << std::endl;
        return std::vector<Coordinate> { Coordinate(0, 0) };
    };

    std::vector<Coordinate> generateKingMoves(const ChessBoard& board, const Coordinate& position)
    {
        std::cout << "TODO: Implement king move generation" << std::endl;
        return std::vector<Coordinate> { Coordinate(0, 0) };
    };

    std::vector<Coordinate> generateMoves(const ChessBoard& board, const Coordinate& position, ChessBoard::PieceType pieceType)
    {
        switch (pieceType)
        {
            case ChessBoard::PAWN:
                return generatePawnMoves(board, position);
            case ChessBoard::KNIGHT:
                return generateKnightMoves(board, position);
            case ChessBoard::BISHOP:
                return generateBishopMoves(board, position);
            case ChessBoard::ROOK:
                return generateRookMoves(board, position);
            case ChessBoard::QUEEN:
                return generateQueenMoves(board, position);
            case ChessBoard::KING:
                return generateKingMoves(board, position);
            default:
                throw std::invalid_argument("Unknown piece type");
        }
    };
};


