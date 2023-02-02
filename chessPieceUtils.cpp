// chessPieceUtils
//
// Author: Jason Dominguez
// Date: 2023-02-02

#include "chessPieceUtils.hpp"

namespace chess
{
    std::string colorToString(const pieceColor& color) {
        return color == white ? "white" : "black";
    }

    pieceColor stringToColor(const std::string& color) {
        return color == "white" || color == "White" ? white : black;
    }

    pieceColor oppositeColor(const pieceColor& color) {
        return color == white ? black : white;
    }

    void copyBoard(
        const std::vector<std::unique_ptr<chessPiece>>& board,
        std::vector<std::unique_ptr<chessPiece>>& bCopy
    ) {
        // Create temp copy of board
        std::vector<std::unique_ptr<chessPiece>> bCopy(board.size());
        for (int i = 0; i < bCopy.size(); i++) {
            if (board[i]) {
                bCopy[i] = std::unique_ptr<chessPiece>(
                    board[i]->clone()
                );
            } else {
                bCopy[i] = std::unique_ptr<chessPiece>{nullptr};
            }
        }
    }

    movesInfo getAllLegalMoves(
        const pieceColor& color,
        const std::vector<std::unique_ptr<chessPiece>>& board
    ) {
        // Want to return possible positions of pieces to move,
        // possible moves for each of these pieces and all possible moves
        std::vector<int> legalStartPositions;
        std::vector<std::vector<int>> legalMovesPerPiece;
        std::vector<int> allLegalMoves;

        int pos = 0;
        for (const auto& piece : board) {
            if (piece && piece->getColor() == color) {
                std::vector<int> legalMoves;

                // std::vector<std::unique_ptr<chessPiece>> bCopy;
                // copyBoard(board, bCopy);
                // legalMoves = piece->getValidMoves(
                //     pos, std::move(bCopy)
                // );
                legalMoves = piece->getValidMoves(pos, board);

                legalStartPositions.push_back(pos);
                legalMovesPerPiece.push_back(legalMoves);
                allLegalMoves.insert(
                    std::end(allLegalMoves),
                    std::begin(legalMoves),
                    std::end(legalMoves)
                );

                pos++;
            }
        }

        return {
            legalStartPositions,
            legalMovesPerPiece,
            allLegalMoves
        };
    }
}