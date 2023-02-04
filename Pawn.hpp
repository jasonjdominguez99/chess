// Pawn
//
// Author: Jason Dominguez
// Date: 2023-02-04

#include "ChessPiece.hpp"

#ifndef Pawn_H
#define Pawn_H

namespace chess
{
    class Pawn final : public ChessPiece
    {  
    public:
        Pawn(pieceColor color, int id)
            : ChessPiece(color, id, 'p') {}

        Pawn(pieceColor color, int id, bool moved)
            : ChessPiece(color, id, 'p', moved) {}

        Pawn(pieceColor color, int id, bool moved, bool enPass)
            : ChessPiece(color, id, 'p', moved, enPass) {}

        virtual ~Pawn() = default;

        std::unique_ptr<ChessPiece> clone() const override;

        std::vector<int> getLegalMoves(
            const int startPosition,
            const std::vector<std::unique_ptr<ChessPiece>>& chessBoard
        ) const override;
    };
}

#endif
