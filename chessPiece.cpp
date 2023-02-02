// chessPiece
//
// Author: Jason Dominguez
// Date: 2023-02-02

#include <iostream>
#include <sstream>
#include "chessPiece.hpp"

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
    
    std::ostream& operator<<(std::ostream& output, const chessPiece& piece) {
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
