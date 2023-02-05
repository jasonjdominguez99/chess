// Bishop
//
// Author: Jason Dominguez
// Date: 2023-02-04

#include "ChessPiece.hpp"

#ifndef Bishop_H
#define Bishop_H

namespace chess
{
    class Bishop final : public ChessPiece
    {  
    public:
        Bishop(pieceColor color, int id)
            : ChessPiece(color, id, 'B') {}

        Bishop(pieceColor color, int id, bool moved)
            : ChessPiece(color, id, 'B', moved) {}

        virtual ~Bishop() = default;

        std::unique_ptr<ChessPiece> clone() const override;

        std::vector<int> getLegalMoves(
            const int startPosition,
            const std::vector<std::unique_ptr<ChessPiece>>& chessBoard
        ) const override;
    };
}

#endif
