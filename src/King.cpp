// King
//
// Author: Jason Dominguez
// Date: 2023-02-04

#include "King.hpp"
#include "ChessPieceUtils.hpp"

using chess::ChessPiece, chess::King;

std::unique_ptr<ChessPiece> King::clone() const {
    return std::move(
        std::make_unique<King>(
            King(this->color, this->id, this->hasMoved)
        )
    );
}

std::vector<int> King::getLegalMoves(
    const int startPosition,
    const std::vector<std::unique_ptr<ChessPiece>>& chessBoard
) const {
    std::vector<int> legalNewPositions;
    findHorizAndVertMoves(
        this->color, startPosition, chessBoard, legalNewPositions,
        this->maxMoveDist, this->maxMoveDist
    );
    findDiagMoves(
        this->color, startPosition, chessBoard, legalNewPositions,
        this->maxMoveDist, this->maxMoveDist
    );

    // Kingside castling (castling with closest rook to king)
    if (!this->hasMoved) {
        if (chessBoard[startPosition + 3]
            && chessBoard[startPosition + 3]->getSymbol() == 'R'
            && !chessBoard[startPosition + 3]->hasBeenMoved()
        ) {
            if (!chessBoard[startPosition + 1]
                && !chessBoard[startPosition + 2]
            ) {
                legalNewPositions.push_back(startPosition + 2);
            }
        }
    }
    // Queenside castling (castling with rook furthest from king)
    if (!this->hasMoved) {
        if (chessBoard[startPosition - 4]
            && chessBoard[startPosition - 4]->getSymbol() == 'R' &&
            !chessBoard[startPosition - 4]->hasBeenMoved()
        ) {
            if (!chessBoard[startPosition - 1]
                && !chessBoard[startPosition - 2]
                && !chessBoard[startPosition - 3]
            ) {
                legalNewPositions.push_back(startPosition - 2);
            }
        }
    }
    
    return legalNewPositions;
}
