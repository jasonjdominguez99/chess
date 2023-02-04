// chessPieceUtils
//
// Author: Jason Dominguez
// Date: 2023-02-02

#include "chessPiece.hpp"

#ifndef chessPieceUtils_H
#define chessPieceUtils_H

namespace chess
{
    static inline const int numRanks = 8, numFiles = 8;

    std::string colorToString(pieceColor color);
    pieceColor stringToColor(const std::string& color);
    pieceColor oppositeColor(pieceColor color);

    void copyBoard(
        const std::vector<std::unique_ptr<chessPiece>>& board,
        std::vector<std::unique_ptr<chessPiece>>& bCopy
    );

    struct movesInfo {
        std::vector<int> startPositions;
        std::vector<std::vector<int>> movesPerPiece;
        std::vector<int> allMoves;
    };

    movesInfo getAllLegalMoves(
        pieceColor color,
        const std::vector<std::unique_ptr<chessPiece>>& board
    );

    bool addMoveIfValid(
        int position,
        pieceColor color,
        const std::vector<std::unique_ptr<chessPiece>>& board,
        std::vector<int>& outValidNewPositions
    );

    void findHorizAndVertMoves(
        pieceColor color,
        int startCol, int startRow,
        const std::vector<std::unique_ptr<chessPiece>>& board,
        std::vector<int>& outValidNewPositions,
        int maxHorizDist = numFiles, int maxVertDist = numRanks
    );

    void findDiagMoves(
        pieceColor color,
        int startCol, int startRow,
        const std::vector<std::unique_ptr<chessPiece>>& board,
        std::vector<int>& outValidNewPositions,
        int maxHorizDist = numFiles, int maxVertDist = numRanks
    );
}

#endif
