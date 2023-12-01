#include <stdexcept>
#include <iostream>

#include "../include/MoveGenerator.hpp"

namespace MoveGenerator
{
    U64 generateHorizontalMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        U64 occupied = board.getOccupancyBitboard();
        U64 friendlyOccupied = board.getOccupancyBitboard(color);
        U64 pieceBoard = board.coordinateToBitboard(position);
        U64 moveMask;

        // Generate ray to the left
        U64 leftRay = (occupied - 2 * pieceBoard) ^ occupied;
        
        // Generate ray to the right
        U64 rightRay = reverseBoard(reverseBoard(occupied) - 2 * reverseBoard(pieceBoard)) ^ reverseBoard(occupied);

        // Combine left and right rays
        moveMask = leftRay | rightRay;

        // Remove original piece position and positions beyond roadblocks
        moveMask &= ~friendlyOccupied;
        moveMask &= ~(moveMask - 2 * pieceBoard);

        return moveMask;
    };

    U64 generateVerticalMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        return 0;
    };

    U64 generateDiagonalMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        return 0;
    };

    U64 generatePawnMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        std::cout << "TODO: Implement pawn move generation" << std::endl;
        return 0;
    };

    U64 generateKnightMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        std::cout << "TODO: Implement knight move generation" << std::endl;
        return 0;
    };

    U64 generateBishopMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        std::cout << "TODO: Implement bishop move generation" << std::endl;
        return 0;
    };

    U64 generateRookMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        std::cout << "TODO: Implement rook move generation" << std::endl;
        return 0;
    };

    U64 generateQueenMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        std::cout << "TODO: Implement queen move generation" << std::endl;
        return 0;
    };

    U64 generateKingMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        std::cout << "TODO: Implement king move generation" << std::endl;
        return 0;
    };

    U64 generateMoves(const ChessBoard& board, const Coordinate& position, std::tuple<ChessBoard::PlayerColor, ChessBoard::PieceType> piece)
    {
        switch (std::get<1>(piece))
        {
            case ChessBoard::PAWN:
                return generatePawnMoves(board, position, std::get<0>(piece));
            case ChessBoard::KNIGHT:
                return generateKnightMoves(board, position, std::get<0>(piece));
            case ChessBoard::BISHOP:
                return generateBishopMoves(board, position, std::get<0>(piece));
            case ChessBoard::ROOK:
                return generateRookMoves(board, position, std::get<0>(piece));
            case ChessBoard::QUEEN:
                return generateQueenMoves(board, position, std::get<0>(piece));
            case ChessBoard::KING:
                return generateKingMoves(board, position, std::get<0>(piece));
            default:
                throw std::invalid_argument("Unknown piece type");
        }
    };

    U64 reverseBoard(U64 n)
    {
        n = ((n >> 1) & 0x5555555555555555ULL) | ((n & 0x5555555555555555ULL) << 1);
        n = ((n >> 2) & 0x3333333333333333ULL) | ((n & 0x3333333333333333ULL) << 2);
        n = ((n >> 4) & 0x0F0F0F0F0F0F0F0FULL) | ((n & 0x0F0F0F0F0F0F0F0FULL) << 4);
        n = ((n >> 8) & 0x00FF00FF00FF00FFULL) | ((n & 0x00FF00FF00FF00FFULL) << 8);
        n = ((n >> 16) & 0x0000FFFF0000FFFFULL) | ((n & 0x0000FFFF0000FFFFULL) << 16);
        n = (n >> 32) | (n << 32);
        return n;
    };
};


