// Rook
//
// Author: Jason Dominguez
// Date: 2023-02-04

#include "Rook.hpp"
#include "chessPieceUtils.hpp"

namespace chess
{
    std::unique_ptr<ChessPiece> Rook::clone() const {
        return std::move(
            std::make_unique<Rook>(
                Rook(this->color, this->id, this->hasMoved)
            )
        );
    }

    std::vector<int> Rook::getLegalMoves(
        const int startPosition,
        const std::vector<std::unique_ptr<ChessPiece>>& chessBoard
    ) const {
        std::vector<int> legalNewPositions;

        findHorizAndVertMoves(
            this->color, startPosition, chessBoard, legalNewPositions
        );

        return legalNewPositions;
    }
}
