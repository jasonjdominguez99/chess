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
    std::string colorToString(const pieceColor& color);
    pieceColor stringToColor(const std::string& color);
    pieceColor oppositeColor(const pieceColor& color);

    class chessPiece
    {
    protected:
        pieceColor color;
        int id;
        char symbol;
        bool hasMoved;
        bool enPassantPossible;

    public:
        chessPiece(pieceColor col, int pieceId, char pieceSymbol)
        : chessPiece(col, pieceId, pieceSymbol, false, false) {}

        chessPiece(pieceColor col, int pieceId, char pieceSymbol, bool moved)
        : chessPiece(col, pieceId, pieceSymbol, moved, false) {}
        
        chessPiece(pieceColor col, int pieceId, char pieceSymbol, bool moved, bool enPassant)
        : color{col}, id{pieceId}, symbol{pieceSymbol},
          hasMoved{moved}, enPassantPossible{enPassant} {}
        
        virtual ~chessPiece() = default;

        pieceColor getColor() const { return color; }
        int getId() const { return id; }
        char getSymbol() const { return symbol; }
        bool hasMoved() const { return hasMoved; }
        void hasBeenMoved() { hasMoved = true; }
        bool isEnPassantPossible() const { return enPassantPossible; }
        void setEnPassant(const bool& enPassant) { enPassantPossible = enPassant; }
        
        virtual std::unique_ptr<chessPiece> clone() const = 0;
        virtual std::vector<int> getValidMoves(
            const int& startPosition, 
            const std::vector<std::unique_ptr<chessPiece>>& chessBoard
        ) = 0;

        friend std::ostream& operator<<(std::ostream &output, const chessPiece& piece);
    };
}

#endif
