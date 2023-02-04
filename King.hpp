// King
//
// Author: Jason Dominguez
// Date: 2023-02-04

#include "ChessPiece.hpp"

#ifndef King_H
#define King_H

namespace chess
{
    class King final : public ChessPiece
    {
    private:
        static const int maxMoveDist = 1;

    public:
        King(pieceColor color, int id)
            : ChessPiece(color, id, 'Q') {}

        King(pieceColor color, int id, bool moved)
            : ChessPiece(color, id, 'Q', moved) {}

        virtual ~King() = default;

        std::unique_ptr<ChessPiece> clone() const override;

        std::vector<int> getLegalMoves(
            const int startPosition,
            const std::vector<std::unique_ptr<ChessPiece>>& chessBoard
        ) const override;
    };
}

#endif
