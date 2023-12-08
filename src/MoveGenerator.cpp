#include <stdexcept>
#include <iostream>

#include "../include/MoveGenerator.hpp"

namespace MoveGenerator
{
    const U64 SECOND_RANK = 0xFF00ULL;
    const U64 SEVENTH_RANK = 0x00FF000000000000ULL;
    const U64 A_FILE = 0x0101010101010101ULL;
    const U64 H_FILE = 0x8080808080808080ULL;

    U64 generateHorizontalMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        U64 occupied = board.getOccupancyBitboard();
        U64 friendlyOccupied = board.getOccupancyBitboard(color);
        U64 pieceBoard = board.coordinateToBitboard(position);
        U64 rankMask = 0xFFULL << (position[1] * 8); // Generate mask for the rank of the piece

        // Generate ray to the left and right
        U64 moveMask = ((occupied - 2 * pieceBoard) ^ (reverseBoard(reverseBoard(occupied) - 2 * reverseBoard(pieceBoard)))) & rankMask;

        // Exclude friendly occupied squares
        moveMask &= ~friendlyOccupied;

        return moveMask;
    };

    U64 generateVerticalMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        U64 occupied = board.getOccupancyBitboard();
        U64 friendlyOccupied = board.getOccupancyBitboard(color);
        U64 pieceBoard = board.coordinateToBitboard(position);
        U64 fileMask = 0x0101010101010101ULL << position[0]; // Generate mask for the file of the piece

        // Generate ray upward
        U64 upwardRay = occupied - (pieceBoard << 8);
        upwardRay = upwardRay ^ reverseBoard(reverseBoard(occupied) - (reverseBoard(pieceBoard) << 8));

        // Generate ray downward
        U64 downwardRay = reverseBoard(reverseBoard(occupied) - (reverseBoard(pieceBoard) >> 8));
        downwardRay = downwardRay ^ (occupied - (pieceBoard >> 8));

        U64 moveMask = ((upwardRay | downwardRay) & fileMask) & ~friendlyOccupied;

        return moveMask;
    };

    U64 generateDiagonalMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        U64 occupied = board.getOccupancyBitboard();
        U64 friendlyOccupied = board.getOccupancyBitboard(color);
        U64 pieceBoard = board.coordinateToBitboard(position);
        U64 diagonalMask = createDiagonalMask(position);

        // Generate diagonal rays
        U64 upRightRay = occupied - (pieceBoard << 9);
        upRightRay = upRightRay ^ reverseBoard(reverseBoard(occupied) - (reverseBoard(pieceBoard) << 9));

        U64 upLeftRay = occupied - (pieceBoard << 7);
        upLeftRay = upLeftRay ^ reverseBoard(reverseBoard(occupied) - (reverseBoard(pieceBoard) << 7));

        U64 downRightRay = reverseBoard(reverseBoard(occupied) - (reverseBoard(pieceBoard) >> 7));
        downRightRay = downRightRay ^ (occupied - (pieceBoard >> 7));

        U64 downLeftRay = reverseBoard(reverseBoard(occupied) - (reverseBoard(pieceBoard) >> 9));
        downLeftRay = downLeftRay ^ (occupied - (pieceBoard >> 9));

        // Combine rays and apply diagonal mask
        U64 moveMask = (upRightRay | upLeftRay | downRightRay | downLeftRay) & diagonalMask;
        moveMask &= ~friendlyOccupied;

        return moveMask;
    };

    U64 generatePawnMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        U64 occupied = board.getOccupancyBitboard();
        U64 friendlyOccupied = board.getOccupancyBitboard(color);
        U64 pieceBoard = board.coordinateToBitboard(position);
        U64 moveMask;

        if (color == ChessBoard::WHITE)
        {
            // Generate single and double pawn pushes
            moveMask = (pieceBoard << 8) & ~occupied | ((pieceBoard & SECOND_RANK) << 16) & ~(occupied | (occupied << 8));

            // Generate captures if there is a piece to capture, preventing wraparound
            moveMask |= (pieceBoard << 7) & occupied & ~friendlyOccupied & ~H_FILE;
            moveMask |= (pieceBoard << 9) & occupied & ~friendlyOccupied & ~A_FILE;
        }
        else if (color == ChessBoard::BLACK)
        {
            // Generate single and double pawn pushes
            moveMask = (pieceBoard >> 8) & ~occupied | ((pieceBoard & SEVENTH_RANK) >> 16) & ~(occupied | (occupied >> 8));

            // Generate captures if there is a piece to capture, preventing wraparound
            moveMask |= (pieceBoard >> 7) & occupied & ~friendlyOccupied & ~A_FILE;
            moveMask |= (pieceBoard >> 9) & occupied & ~friendlyOccupied & ~H_FILE;
        }

        return moveMask;
    };

    U64 generateKnightMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        std::cout << "TODO: Implement knight move generation" << std::endl;
        return 0;
    };

    U64 generateBishopMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        return generateDiagonalMoves(board, position, color);
    };

    U64 generateRookMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        return generateHorizontalMoves(board, position, color) | generateVerticalMoves(board, position, color);
    };

    U64 generateQueenMoves(const ChessBoard& board, const Coordinate& position, const ChessBoard::PlayerColor& color)
    {
        return (generateHorizontalMoves(board, position, color)
                | generateVerticalMoves(board, position, color)
                | generateDiagonalMoves(board, position, color));
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

    U64 createDiagonalMask(const Coordinate& position) {
        const U64 mainDiagonal = 0x8040201008040201ULL;
        const U64 antiDiagonal = 0x0102040810204080ULL;
        
        int file = position[0];
        int rank = position[1];
        int a1h8DiagonalShift = rank - file;
        int h1a8DiagonalShift = rank + file - 7;

        U64 a1h8Diagonal = (a1h8DiagonalShift > 0) ? (mainDiagonal << (8 * a1h8DiagonalShift))
                                                : (mainDiagonal >> (-8 * a1h8DiagonalShift));
        U64 h1a8Diagonal = (h1a8DiagonalShift > 0) ? (antiDiagonal << (8 * h1a8DiagonalShift))
                                                : (antiDiagonal >> (-8 * h1a8DiagonalShift));

        return a1h8Diagonal | h1a8Diagonal;
}
};


