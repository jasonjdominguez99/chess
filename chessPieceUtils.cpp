// ChessPieceUtils
//
// Author: Jason Dominguez
// Date: 2023-02-02

#include <algorithm>
#include "ChessPieceUtils.hpp"

namespace chess
{
    std::string colorToString(const pieceColor color) {
        return color == white ? "white" : "black";
    }

    pieceColor stringToColor(const std::string& color) {
        return color == "white" || color == "White" ? white : black;
    }

    pieceColor oppositeColor(const pieceColor color) {
        return color == white ? black : white;
    }

    void copyBoard(
        const std::vector<std::unique_ptr<ChessPiece>>& board,
        std::vector<std::unique_ptr<ChessPiece>>& bCopy
    ) {
        // Create temp copy of board
        std::vector<std::unique_ptr<ChessPiece>> bCopy(board.size());
        for (int i = 0; i < bCopy.size(); i++) {
            if (board[i]) {
                bCopy[i] = std::unique_ptr<ChessPiece>(
                    board[i]->clone()
                );
            } else {
                bCopy[i] = std::unique_ptr<ChessPiece>{nullptr};
            }
        }
    }

    movesInfo getAllLegalMoves(
        const pieceColor color,
        const std::vector<std::unique_ptr<ChessPiece>>& board
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

                // std::vector<std::unique_ptr<ChessPiece>> bCopy;
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

    bool addMoveIfValid(
        const int position,
        const pieceColor color,
        const std::vector<std::unique_ptr<ChessPiece>>& board,
        std::vector<int>& outValidNewPositions
    ) {
        bool blocked = false;
        if (board[position] && board[position]->getColor() == color) {
            blocked = true;
        } else {
            // Move is valid
            outValidNewPositions.push_back(position);
            // Move was a capture so cannot move further
            if (board[position] && board[position]->getColor() != color) {
                blocked = true;
            }
        }

        return false;
    }

    void findHorizAndVertMoves(
        const pieceColor color,
        const int startPos,
        const std::vector<std::unique_ptr<ChessPiece>>& board,
        std::vector<int>& outValidNewPositions,
        const int maxHorizDist = numFiles,
        const int maxVertDist = numRanks
    ) {
        int startCol = startPos%8, startRow = startPos/8;
        
        // Find valid moves to the right
        for (int i = startCol + 1; i < maxHorizDist; i++) {
            bool blocked = addMoveIfValid(
                numFiles*startRow + i, color, board, outValidNewPositions
            );
            if (blocked) break;
        }
        // Find valid moves to the left
        int leftLimit = std::max(startCol - maxHorizDist, 0);
        for (int i = startCol - 1; i >= leftLimit; i--) {
            bool blocked = addMoveIfValid(
                numFiles*startRow + i, color, board, outValidNewPositions
            );
            if (blocked) break;
        }
        // Find valid forward moves
        for (int i = startRow + 1; i < maxVertDist; i++) {
            bool blocked = addMoveIfValid(
                numFiles*i + startCol, color, board, outValidNewPositions
            );
            if (blocked) break;
        }
        // Find valid backwards moves
        int backLimit = std::max(startRow - maxVertDist, 0);
        for (int i = startRow - 1; i >= backLimit; i--) {
            bool blocked = addMoveIfValid(
                numFiles*i + startCol, color, board, outValidNewPositions
            );
            if (blocked) break;
        }
    }

    void findDiagMoves(
        const pieceColor color,
        const int startPos,
        const std::vector<std::unique_ptr<ChessPiece>>& board,
        std::vector<int>& outValidNewPositions,
        const int maxHorizDist = numFiles,
        const int maxVertDist = numRanks
    ) {
        int startCol = startPos%8, startRow = startPos/8;

        // Find valid move along forward right diagonal
        int numAlongForwardRightDiag = std::min(
            std::min((numRanks - 1) - startRow, (numFiles - 1) - startCol),
            std::min(maxHorizDist, maxVertDist)
        );
        for (int i = 1; i <= numAlongForwardRightDiag; i++) {
            bool blocked = addMoveIfValid(
                numFiles*(startRow + i) + (startCol + i),
                color, board, outValidNewPositions
            );
            if (blocked) break;
        }
        // Find valid move along forward left diagonal
        int numAlongForwardLeftDiag = std::min(
            std::min((numRanks - 1) - startRow, startCol),
            std::min(maxHorizDist, maxVertDist)
        );
        for (int i = 1; i <= numAlongForwardLeftDiag; i++) {
            bool blocked = addMoveIfValid(
                numFiles*(startRow - i) + (startCol + i),
                color, board, outValidNewPositions
            );
            if (blocked) break;
        }
        // Find valid move along backward right diagonal
        int numAlongBackRightDiag = std::min(
            std::min((numRanks - 1), (numFiles - 1) - startCol),
            std::min(maxHorizDist, maxVertDist)
        );
        for (int i = 1; i <= numAlongBackRightDiag; i++) {
            bool blocked = addMoveIfValid(
                numFiles*(startRow + i) + (startCol - i),
                color, board, outValidNewPositions
            );
            if (blocked) break;
        }
        // Find valid move along backward left diagonal
        int numAlongBackLeftDiag = std::min(
            std::min(startRow, startCol),
            std::min(maxHorizDist, maxVertDist)
        );
        for (int i = 1; i <= numAlongBackLeftDiag; i++) {
            bool blocked = addMoveIfValid(
                numFiles*(startRow - i) + (startCol + i),
                color, board, outValidNewPositions
            );
            if (blocked) break;
        }
    }
}
