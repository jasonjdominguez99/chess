// Queen
//
// Author: Jason Dominguez
// Date: 2023-02-04

#include "Queen.hpp"
#include "chessPieceUtils.hpp"

namespace chess
{
    std::unique_ptr<ChessPiece> Queen::clone() const {
        return std::move(
            std::make_unique<Queen>(
                Queen(this->color, this->id, this->hasMoved)
            )
        );
    }

    std::vector<int> Queen::getLegalMoves(
        const int startPosition,
        const std::vector<std::unique_ptr<ChessPiece>>& chessBoard
    ) const {
        std::vector<int> legalNewPositions;
        findHorizAndVertMoves(
            this->color, startPosition, chessBoard, legalNewPositions
        );
        findDiagMoves(
            this->color, startPosition, chessBoard, legalNewPositions
        );

        return legalNewPositions;
    }
}
