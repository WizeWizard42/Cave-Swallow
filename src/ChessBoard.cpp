#include <sstream>

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

std::string ChessBoard::toFEN() {
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
