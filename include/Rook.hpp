// Rook
//
// Author: Jason Dominguez
// Date: 2023-02-04

#include "ChessPiece.hpp"

#ifndef Rook_H
#define Rook_H

namespace chess
{
    class Rook final : public ChessPiece
    {  
    public:
        Rook(pieceColor color, int id)
            : ChessPiece(color, id, 'R') {}

        Rook(pieceColor color, int id, bool moved)
            : ChessPiece(color, id, 'R', moved) {}

        virtual ~Rook() = default;

        std::unique_ptr<ChessPiece> clone() const override;

        std::vector<int> getLegalMoves(
            const int startPosition,
            const std::vector<std::unique_ptr<ChessPiece>>& chessBoard
        ) const override;
    };
}

#endif
