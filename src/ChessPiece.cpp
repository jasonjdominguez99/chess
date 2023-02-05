// ChessPiece
//
// Author: Jason Dominguez
// Date: 2023-02-02

#include <iostream>
#include <sstream>
#include "ChessPiece.hpp"

namespace chess
{
    std::ostream& operator<<(std::ostream& output, const ChessPiece& piece) {
        // Display chess piece symbol using ANSI to make
        // symbols bold and for black pieces gray
        std::stringstream ansiSymbol;

        ansiSymbol << "\u001b[1m";
        if (piece.color == black) ansiSymbol << "\u001b[30m";
        ansiSymbol << piece.symbol << "\u001b[0m";
        output << ansiSymbol.str();

        return output;
    }
}
