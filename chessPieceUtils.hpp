// ChessPieceUtils
//
// Author: Jason Dominguez
// Date: 2023-02-02

#include "ChessPiece.hpp"

#ifndef ChessPieceUtils_H
#define ChessPieceUtils_H

namespace chess
{
    static inline const int numRanks = 8, numFiles = 8;

    std::string colorToString(pieceColor color);
    pieceColor stringToColor(const std::string& color);
    pieceColor oppositeColor(pieceColor color);

    void copyBoard(
        const std::vector<std::unique_ptr<ChessPiece>>& board,
        std::vector<std::unique_ptr<ChessPiece>>& bCopy
    );

    struct movesInfo {
        std::vector<int> startPositions;
        std::vector<std::vector<int>> movesPerPiece;
        std::vector<int> allMoves;
    };

    movesInfo getAllLegalMoves(
        pieceColor color,
        const std::vector<std::unique_ptr<ChessPiece>>& board
    );

    bool addMoveIfValid(
        int position,
        pieceColor color,
        const std::vector<std::unique_ptr<ChessPiece>>& board,
        std::vector<int>& outValidNewPositions
    );

    void findHorizAndVertMoves(
        const pieceColor color,
        const int startPos,
        const std::vector<std::unique_ptr<ChessPiece>>& board,
        std::vector<int>& outValidNewPositions,
        const int maxHorizDist = numFiles,
        const int maxVertDist = numRanks
    );

    void findDiagMoves(
        const pieceColor color,
        const int startPos,
        const std::vector<std::unique_ptr<ChessPiece>>& board,
        std::vector<int>& outValidNewPositions,
        const int maxHorizDist = numFiles,
        const int maxVertDist = numRanks
    );
}

#endif
