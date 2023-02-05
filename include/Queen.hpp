// Queen
//
// Author: Jason Dominguez
// Date: 2023-02-04

#include "ChessPiece.hpp"

#ifndef Queen_H
#define Queen_H

namespace chess
{
    class Queen final : public ChessPiece
    {  
    public:
        Queen(pieceColor color, int id)
            : ChessPiece(color, id, 'Q') {}

        Queen(pieceColor color, int id, bool moved)
            : ChessPiece(color, id, 'Q', moved) {}

        virtual ~Queen() = default;

        std::unique_ptr<ChessPiece> clone() const override;

        std::vector<int> getLegalMoves(
            const int startPosition,
            const std::vector<std::unique_ptr<ChessPiece>>& chessBoard
        ) const override;
    };
}

#endif
