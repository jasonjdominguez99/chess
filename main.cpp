#include <iostream>
#include "Pawn.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"

using chess::Pawn, chess::pieceColor;
using chess::Queen;
using chess::Rook;
using chess::Bishop;

int main() {
    std::cout << "hello jase!" << std::endl;

    Pawn pawn(pieceColor::white, 1);
    std::cout << pawn << std::endl;

    Queen queen(pieceColor::black, 1);
    std::cout << queen << std::endl;

    Rook rook(pieceColor::white, 1);
    std::cout << rook << std::endl;

    Bishop bishop(pieceColor::black, 1);
    std::cout << bishop << std::endl;

    return 0;
}