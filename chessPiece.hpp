// ChessPiece
//
// Author: Jason Dominguez
// Date: 2023-02-02

#include <string>
#include <vector>
#include <memory>

#ifndef ChessPiece_H
#define ChessPiece_H

namespace chess
{
    enum pieceColor {white, black};

    class ChessPiece
    {
    protected:
        pieceColor color;
        int id;
        char symbol;
        bool hasMoved;
        bool enPassant;

    public:
        ChessPiece(pieceColor col, int pId, char pieceSymbol)
        : ChessPiece(col, pId, pieceSymbol, false, false) {}

        ChessPiece(pieceColor col, int pId, char piece, bool moved)
        : ChessPiece(col, pId, piece, moved, false) {}
        
        ChessPiece(pieceColor col, int pId, char piece, bool moved, bool enPass)
        : color{col}, id{pId}, symbol{piece},
          hasMoved{moved}, enPassant{enPass} {}
        
        virtual ~ChessPiece() = default;

        pieceColor getColor() const { return color; }
        int getId() const { return id; }
        char getSymbol() const { return symbol; }
        bool hasMoved() const { return hasMoved; }
        void hasBeenMoved() { hasMoved = true; }
        bool isEnPassantPossible() const { return enPassant; }
        void setEnPassant(const bool& enPass) { enPassant = enPass; }
        
        virtual std::unique_ptr<ChessPiece> clone() const = 0;
        virtual std::vector<int> getValidMoves(
            const int& startPosition, 
            const std::vector<std::unique_ptr<ChessPiece>>& chessBoard
        ) = 0;

        friend std::ostream& operator<<(
            std::ostream &output, const ChessPiece& piece
        );
    };
}

#endif
