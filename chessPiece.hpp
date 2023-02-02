// chessPiece
//
// Author: Jason Dominguez
// Date: 2023-02-02

#include <string>
#include <vector>
#include <memory>

#ifndef chessPiece_H
#define chessPiece_H

namespace chess
{
    enum pieceColor {white, black};

    class chessPiece
    {
    protected:
        pieceColor color;
        int id;
        char symbol;
        bool hasMoved;
        bool enPassant;

    public:
        chessPiece(pieceColor col, int pId, char pieceSymbol)
        : chessPiece(col, pId, pieceSymbol, false, false) {}

        chessPiece(pieceColor col, int pId, char piece, bool moved)
        : chessPiece(col, pId, piece, moved, false) {}
        
        chessPiece(pieceColor col, int pId, char piece, bool moved, bool enPass)
        : color{col}, id{pId}, symbol{piece},
          hasMoved{moved}, enPassant{enPass} {}
        
        virtual ~chessPiece() = default;

        pieceColor getColor() const { return color; }
        int getId() const { return id; }
        char getSymbol() const { return symbol; }
        bool hasMoved() const { return hasMoved; }
        void hasBeenMoved() { hasMoved = true; }
        bool isEnPassantPossible() const { return enPassant; }
        void setEnPassant(const bool& enPass) { enPassant = enPass; }
        
        virtual std::unique_ptr<chessPiece> clone() const = 0;
        virtual std::vector<int> getValidMoves(
            const int& startPosition, 
            const std::vector<std::unique_ptr<chessPiece>>& chessBoard
        ) = 0;

        friend std::ostream& operator<<(
            std::ostream &output, const chessPiece& piece
        );
    };
}

#endif
