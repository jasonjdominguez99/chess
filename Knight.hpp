// Knight
//
// Author: Jason Dominguez
// Date: 2023-02-04

#include "ChessPiece.hpp"

#ifndef Knight_H
#define Knight_H

namespace chess
{
    class Knight final : public ChessPiece
    {
    private:
        static const int bigJump = 2;
        static const int smallJump = 1;

    public:
        Knight(pieceColor color, int id)
            : ChessPiece(color, id, 'N') {}

        Knight(pieceColor color, int id, bool moved)
            : ChessPiece(color, id, 'N', moved) {}

        virtual ~Knight() = default;

        std::unique_ptr<ChessPiece> clone() const override;

        std::vector<int> getLegalMoves(
            const int startPosition,
            const std::vector<std::unique_ptr<ChessPiece>>& chessBoard
        ) const override;
    };
}

#endif
