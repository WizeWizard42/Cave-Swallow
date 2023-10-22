#include <stdexcept>
#include <iostream>

#include "../include/MoveGenerator.hpp"

std::vector<Coordinate> MoveGenerator::generatePawnMoves(const ChessBoard& board, const Coordinate& position)
{
    std::cout << "TODO: Implement pawn move generation" << std::endl;
    return std::vector<Coordinate> { Coordinate(0, 0) };
};

std::vector<Coordinate> MoveGenerator::generateKnightMoves(const ChessBoard& board, const Coordinate& position)
{
    std::cout << "TODO: Implement knight move generation" << std::endl;
    return std::vector<Coordinate> { Coordinate(0, 0) };
};

std::vector<Coordinate> MoveGenerator::generateBishopMoves(const ChessBoard& board, const Coordinate& position)
{
    std::cout << "TODO: Implement bishop move generation" << std::endl;
    return std::vector<Coordinate> { Coordinate(0, 0) };
};

std::vector<Coordinate> MoveGenerator::generateRookMoves(const ChessBoard& board, const Coordinate& position)
{
    std::cout << "TODO: Implement rook move generation" << std::endl;
    return std::vector<Coordinate> { Coordinate(0, 0) };
};

std::vector<Coordinate> MoveGenerator::generateQueenMoves(const ChessBoard& board, const Coordinate& position)
{
    std::cout << "TODO: Implement queen move generation" << std::endl;
    return std::vector<Coordinate> { Coordinate(0, 0) };
};

std::vector<Coordinate> MoveGenerator::generateKingMoves(const ChessBoard& board, const Coordinate& position)
{
    std::cout << "TODO: Implement king move generation" << std::endl;
    return std::vector<Coordinate> { Coordinate(0, 0) };
};

std::vector<Coordinate> MoveGenerator::generateMoves(const ChessBoard& board, const Coordinate& position, ChessBoard::PieceType pieceType)
{
    switch (pieceType)
    {
        case ChessBoard::PAWN:
            return MoveGenerator::generatePawnMoves(board, position);
        case ChessBoard::KNIGHT:
            return MoveGenerator::generateKnightMoves(board, position);
        case ChessBoard::BISHOP:
            return MoveGenerator::generateBishopMoves(board, position);
        case ChessBoard::ROOK:
            return MoveGenerator::generateRookMoves(board, position);
        case ChessBoard::QUEEN:
            return MoveGenerator::generateQueenMoves(board, position);
        case ChessBoard::KING:
            return MoveGenerator::generateKingMoves(board, position);
        default:
            throw std::invalid_argument("Unknown piece type");
    }
};
