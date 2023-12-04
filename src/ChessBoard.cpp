#include <sstream>
#include <iostream>

#include "../include/ChessBoard.hpp"

ChessBoard::ChessBoard()
{
    bitBoards[WHITE][PAWN] = 0xFF00;
    bitBoards[WHITE][KNIGHT] = 0x42;
    bitBoards[WHITE][BISHOP] = 0x24;
    bitBoards[WHITE][ROOK] = 0x81;
    bitBoards[WHITE][QUEEN] = 0x08;
    bitBoards[WHITE][KING] = 0x10;

    bitBoards[BLACK][PAWN] = 0xFF000000000000;
    bitBoards[BLACK][KNIGHT] = 0x4200000000000000;
    bitBoards[BLACK][BISHOP] = 0x2400000000000000;
    bitBoards[BLACK][ROOK] = 0x8100000000000000;
    bitBoards[BLACK][QUEEN] = 0x0800000000000000;
    bitBoards[BLACK][KING] = 0x1000000000000000;

    pieceSymbols[WHITE][PAWN] = 'P';
    pieceSymbols[WHITE][KNIGHT] = 'N';
    pieceSymbols[WHITE][BISHOP] = 'B';
    pieceSymbols[WHITE][ROOK] = 'R';
    pieceSymbols[WHITE][QUEEN] = 'Q';
    pieceSymbols[WHITE][KING] = 'K';

    pieceSymbols[BLACK][PAWN] = 'p';
    pieceSymbols[BLACK][KNIGHT] = 'n';
    pieceSymbols[BLACK][BISHOP] = 'b';
    pieceSymbols[BLACK][ROOK] = 'r';
    pieceSymbols[BLACK][QUEEN] = 'q';
    pieceSymbols[BLACK][KING] = 'k';

    whiteToMove = true;

};

std::tuple<ChessBoard::PlayerColor, ChessBoard::PieceType> ChessBoard::getPieceAt(const Coordinate& position) const
{
    int index = position[0] + 8 * position[1];
    for (int color = WHITE; color <= BLACK; ++color)
    {
        for (int piece = PAWN; piece <= KING; ++piece)
        {
            if (bitBoards[color].at(static_cast<PieceType>(piece)) & (1ULL << index))
            {
                return {static_cast<PlayerColor>(color), static_cast<PieceType>(piece)};
            }
        }
    }
    return {NONE, EMPTY};
};

U64 ChessBoard::getBitBoardForPiece(PieceType piece, PlayerColor color) const
{
    return bitBoards[color].at(piece);
};

U64 ChessBoard::getOccupancyBitboard() const
{
    return this->getOccupancyBitboard(WHITE) | this->getOccupancyBitboard(BLACK);
};

U64 ChessBoard::getOccupancyBitboard(PlayerColor color) const
{
    U64 occupancy = 0;

    for (int type = PAWN; type <= KING; ++type)
    {
        occupancy |= getBitBoardForPiece(static_cast<PieceType>(type), color);
    }

    return occupancy;
};

U64 ChessBoard::coordinateToBitboard(Coordinate position) const
{
    if (position[0] < 0 || position[0] > 7 || position[1] < 0 || position[1] > 7) {
        return 0; // Return 0 if the coordinates are out of bounds
    }

    return 1ULL << ((position[1] * 8) + position[0]);
};

bool ChessBoard::isSquareOccupied(const Coordinate& position) const
{
    return (this->getOccupancyBitboard() & this->coordinateToBitboard(position));
};

void ChessBoard::applyMove(const Coordinate& from, const Coordinate& to)
{
    std::cout << "TODO: Implement move logic" << std::endl;
};

void ChessBoard::undoMove(const Coordinate& from, const Coordinate& to)
{
    std::cout << "TODO: Implement reverse move logic" << std::endl;
};

void ChessBoard::placePiece(const ChessBoard::PieceType piece, const ChessBoard::PlayerColor color, const Coordinate& position)
{
    if (!(this->isSquareOccupied(position)))
    {
        this->bitBoards[color][piece] |= this->coordinateToBitboard(position);
        return;
    }

    std::cerr << "Position (" << position[0] << ", " << position[1] << ") is already occupied." << std::endl;
}

void ChessBoard::clearBoard()
{
    for (int i = WHITE; i <= BLACK; ++i)
    {
        for (int j = PAWN; j <= KING; ++j)
        {
            this->bitBoards[i][static_cast<PieceType>(j)] = 0ULL;
        }
    }
}

std::string ChessBoard::toFEN()
{
    std::ostringstream fen;

    for (int rank = 7; rank >= 0; rank--)
    {
        int emptySquares = 0;
        for (int file = 0; file < 8; file++)
        {
            char pieceChar = ' ';
            for (int color = 0; color < 2; color++)
            {
                for (int piece = PAWN; piece <= KING; piece++)
                {
                    if ((bitBoards[color][static_cast<PieceType>(piece)] >> (file + (rank * 8))) & 1) // Bit shift to check the appropriate bit in the board.
                    {
                        pieceChar = pieceSymbols[color][static_cast<PieceType>(piece)];
                        break;
                    }
                }
                if (pieceChar != ' ')
                    break;
            }
            if (pieceChar == ' ')
            {
                ++emptySquares;
            }
            else 
            {
                if (emptySquares > 0)
                {
                    fen << emptySquares;
                    emptySquares = 0;
                }
                fen << pieceChar;
            }
        }

        if (emptySquares > 0) {
            fen << emptySquares;
        }

        if (rank > 0) {
            fen << '/';
        }
    }

    // Rest of FEN information (active color, castling rights, en passant, etc.)

    if (whiteToMove)
    {
        fen << " w";
    }
    else
    {
        fen << " b";
    }

    fen << " - - 0 1"; 

    return fen.str();
}
