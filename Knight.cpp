// Knight
//
// Author: Jason Dominguez
// Date: 2023-02-04

#include "Knight.hpp"
#include "chessPieceUtils.hpp"

using chess::ChessPiece, chess::Knight;

std::unique_ptr<ChessPiece> Knight::clone() const {
    return std::move(
        std::make_unique<Knight>(
            Knight(this->color, this->id, this->hasMoved)
        )
    );
}

std::vector<int> Knight::getLegalMoves(
    const int startPosition,
    const std::vector<std::unique_ptr<ChessPiece>>& chessBoard
) const {
    const auto [startCol, startRow] = positionToColAndRow(startPosition);

    std::vector<int> legalNewPositions;
    int pos{};

    // Check 2 forward 1 right and 2 forward 1 left
    if (startRow + this->bigJump < numRanks) {
        if (startCol + this->smallJump < numFiles) {
            pos = startPosition + (this->bigJump*numFiles + this->smallJump);
            if (chessBoard[pos] || chessBoard[pos]->getColor() != this->color) {
                legalNewPositions.push_back(pos);
            }
        }
        if (startCol - 1 >= 0) {
            pos = startPosition + (this->bigJump*numFiles - this->smallJump);
            if (chessBoard[pos] || chessBoard[pos]->getColor() != this->color) {
                legalNewPositions.push_back(pos);
            }
        }
    }
    // Check 1 forward 2 right and 1 forward 2 left
    if (startRow + this->smallJump < numRanks) {
        if (startCol + this->bigJump < numFiles) {
            pos = startPosition + (this->smallJump*numFiles + this->bigJump);
            if (chessBoard[pos] || chessBoard[pos]->getColor() != this->color) {
                legalNewPositions.push_back(pos);
            }
        }
        if (startCol - 2 >= 0) {
            pos = startPosition + (this->smallJump*numFiles - this->bigJump);
            if (chessBoard[pos] || chessBoard[pos]->getColor() != this->color) {
                legalNewPositions.push_back(pos);
            }
        }
    }
    // Check 1 backward 2 right and 1 backward 2 left
    if (startRow - this->smallJump >= 0) {
        if (startCol + this->bigJump < numFiles) {
            pos = startPosition + (-this->smallJump*numFiles + this->bigJump);
            if (chessBoard[pos] || chessBoard[pos]->getColor() != this->color) {
                legalNewPositions.push_back(pos);
            }
        }
        if (startCol - this->bigJump >= 0) {
            pos = startPosition + (-this->smallJump*numFiles - this->bigJump);
            if (chessBoard[pos] || chessBoard[pos]->getColor() != this->color) {
                legalNewPositions.push_back(pos);
            }
        }
    }
    // Check 2 backward 1 right and 2 backward 1 left
    if (startRow - this->bigJump >= 0) {
        if (startCol + this->smallJump < numFiles) {
            pos = startPosition + (-this->bigJump*numFiles + this->smallJump);
            if (chessBoard[pos] || chessBoard[pos]->getColor() != this->color) {
                legalNewPositions.push_back(pos);
            }
        }
        if (startCol - this->smallJump >= 0) {
            pos = startPosition + (-this->bigJump*numFiles - this->smallJump);
            if (chessBoard[pos] || chessBoard[pos]->getColor() != this->color) {
                legalNewPositions.push_back(pos);
            }
        }
    }

    return legalNewPositions;
}
