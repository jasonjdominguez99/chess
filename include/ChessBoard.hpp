// ChessBoard
//
// Author: Jason Dominguez
// Date: 2023-02-05

#ifndef ChessBoard_H
#define ChessBoard_H

#include "ChessPiece.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace chess {
    enum moveType {standard, enPassant, castling};

    std::vector<std::unique_ptr<ChessPiece>> initBoard(
        std::vector<std::unique_ptr<ChessPiece>> board
    );

    class ChessBoard
    {
    static inline const int numRanks = 8, numFiles = 8;

    private:
        std::vector<std::unique_ptr<ChessPiece>> board;

    public:
        ChessBoard();
        ChessBoard(const ChessBoard& boardToCopy);
        ChessBoard(const std::vector<std::unique_ptr<ChessPiece>>& boardToCopy);

        ~ChessBoard() {};

        std::vector<std::unique_ptr<ChessPiece>> get() const;

        void movePiece(int startPos, int endPos);
        void movePiece(int startPos, int endPos, moveType move);

        std::unique_ptr<ChessPiece> operator[](int idx) const;
        std::unique_ptr<ChessPiece>& operator[](int idx);

        void reset();

        friend std::ostream& operator<<(
            std::ostream& output, const ChessBoard& board
        );
        friend int boardPosToIdx(const std::string& pos);
        friend std::string idxToBoardPos(int posIdx);
        friend void checkValidBoardIdx(int idx);
    };  
}

#endif
