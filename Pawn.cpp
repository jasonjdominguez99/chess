// Pawn
//
// Author: Jason Dominguez
// Date: 2023-02-04

#include "Pawn.hpp"
#include "chessPieceUtils.hpp"

using chess::ChessPiece, chess::Pawn;

std::unique_ptr<ChessPiece> Pawn::clone() const {
    return std::move(
        std::make_unique<Pawn>(
            Pawn(this->color, this->id, this->hasMoved, this->enPassant)
        )
    );
}

std::vector<int> Pawn::getLegalMoves(
    const int startPosition,
    const std::vector<std::unique_ptr<ChessPiece>>& chessBoard
) const {
    const auto [startCol, startRow] = positionToColAndRow(startPosition);
        
    // White pieces will move up the board (positive increment in position)
    // black pieces will move down (negative increment of position)
    int move = this->color == white ? 1 : -1;
        
    std::vector<int> legalNewPositions;
    int pos{};

    // Check if pawn can move forward by 1
    if (startRow + move < numRanks) {
        pos = startPosition + move*numFiles;
        if (!chessBoard[pos]) {
            legalNewPositions.push_back(pos);
        }
    }
    // Check if pawn can move forward by 2 (if pawn's first move)
    if (!this->hasMoved) {
        if (startRow + 2*move < numRanks) {
            pos = startPosition + move*numFiles;
            if (!chessBoard[pos + numFiles] && !chessBoard[pos]) {
                legalNewPositions.push_back(pos + numFiles);
            }
        }
    }
    // Check if diagonal moves are possible
    // (if attacking opposite color piece or if en passant is possible)
    // NOTE: getting the en passant condition and capture condition
    //       should be converted to function as it it repeated
    if (startRow + move < numRanks && startCol + move < numFiles) {
        pos = startPosition + move;
        bool enPassantCondition = (
            chessBoard[pos]
            && chessBoard[pos]->getColor() != this->color
            && chessBoard[pos]->getSymbol() == 'p'
            && chessBoard[pos]->isEnPassantPossible()
        );
        pos = startPosition + (8*move + move);
        bool captureCondition = (
            chessBoard[pos] 
            && chessBoard[pos]->getColor() != this->color
        );

        if (enPassantCondition || captureCondition) {
            legalNewPositions.push_back(pos);
        }
    }
    if (startRow + move < numRanks && startCol - move >= 0) {
        pos = startPosition - move;
        bool enPassantCondition = (
            chessBoard[pos]
            && chessBoard[pos]->getColor() != this->color
            && chessBoard[pos]->getSymbol() == 'p'
            && chessBoard[pos]->isEnPassantPossible()
        );
        pos = startPosition + (8*move - move);
        bool captureCondition = (
            chessBoard[pos] 
            && chessBoard[pos]->getColor() != this->color
        );

        if (enPassantCondition || captureCondition) {
            legalNewPositions.push_back(pos);
        }
    }

    return legalNewPositions;
}
