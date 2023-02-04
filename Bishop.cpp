// Bishop
//
// Author: Jason Dominguez
// Date: 2023-02-04

#include "Bishop.hpp"
#include "chessPieceUtils.hpp"

using chess::ChessPiece, chess::Bishop;

std::unique_ptr<ChessPiece> Bishop::clone() const {
    return std::move(
        std::make_unique<Bishop>(
            Bishop(this->color, this->id, this->hasMoved)
        )
    );
}

std::vector<int> Bishop::getLegalMoves(
    const int startPosition,
    const std::vector<std::unique_ptr<ChessPiece>>& chessBoard
) const {
    std::vector<int> legalNewPositions;
    findDiagMoves(
        this->color, startPosition, chessBoard, legalNewPositions
    );

    return legalNewPositions;
}
