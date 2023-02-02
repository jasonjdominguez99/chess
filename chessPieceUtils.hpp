// chessPieceUtils
//
// Author: Jason Dominguez
// Date: 2023-02-02

#include "chessPiece.hpp"

#ifndef chessPieceUtils_H
#define chessPieceUtils_H

namespace chess
{
    std::string colorToString(const pieceColor& color);
    pieceColor stringToColor(const std::string& color);
    pieceColor oppositeColor(const pieceColor& color);


    struct movesInfo {
        std::vector<int> startPositions;
        std::vector<std::vector<int>> movesPerPiece;
        std::vector<int> allMoves;
    };

    movesInfo getAllLegalMoves(
        const pieceColor& color,
        const std::vector<std::unique_ptr<chessPiece>>& board
    );

    void findHorizAndVertMoves(
        pieceColor color,
        std::vector<int>& validNewPositions,
        int startCol, int startRow,
        const std::vector<std::unique_ptr<chessPiece>>& board
    );
                                                
    void findDiagMoves(pieceColor color,
                       std::vector<int>& validNewPositions, 
                       int startCol, int startRow,
                       const std::vector<std::unique_ptr<chessPiece>>& board);
}

#endif
