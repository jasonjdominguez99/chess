// ChessBoard
//
// Author: Jason Dominguez
// Date: 2023-02-05

#include "ChessBoard.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include <stdexcept>

using chess::ChessPiece, chess::ChessBoard;

ChessBoard::ChessBoard() {
    board = initBoard(std::move(board));
}

ChessBoard::ChessBoard(const ChessBoard& boardToCopy) {
    // Perform deep copy of all chess piece pointers
    // in chess board to copies chess board vector
    for (const auto& piece : boardToCopy.board) {
        if (!piece) {
            board.push_back(std::unique_ptr<ChessPiece>(nullptr));
        } else {
            board.push_back(piece->clone());
        }
    }
}

ChessBoard::ChessBoard(
    const std::vector<std::unique_ptr<ChessPiece>>& boardToCopy
    ) {
    // Perform deep copy of all chess piece pointers
    // in chess board to copies chess board vector
    for (const auto& piece : boardToCopy) {
        if (!piece) {
            board.push_back(std::unique_ptr<ChessPiece>(nullptr));
        } else {
            board.push_back(piece->clone());
        }
    }
}

std::vector<std::unique_ptr<ChessPiece>> ChessBoard::get() const {
    std::vector<std::unique_ptr<ChessPiece>> bCopy;
    for (int i = 0; i < numFiles*numRanks; i++) {
        if (!board[i]) {
            bCopy.push_back(std::unique_ptr<ChessPiece>{nullptr});
        } else {
            bCopy.push_back(board[i]->clone());
        }
    }
    return std::move(bCopy);
}

void ChessBoard::movePiece(int startPos, int endPos) {
    int forward = startPos + numFiles;
    int backward = startPos - numFiles;

    if (board[startPos]->getSymbol() == 'p'
        && !board[endPos]
        && (endPos == forward + 1 || endPos == forward - 1))
    {
        // En passant move upwards
        board[endPos] = std::move(board[endPos - 8]);
    }
    else if (board[startPos]->getSymbol() == 'p'
             && !board[endPos]
             && (endPos == backward + 1 || endPos == backward - 1))
    {
        // En passant move down
        board[endPos] = std::move(board[endPos + 8]);
    }
    board[endPos] = std::move(board[startPos]);
    board[endPos]->beenMoved();
}

void ChessBoard::movePiece(int startPos, int endPos, moveType move) {
    switch (move)
    {
    case standard:
        board[endPos] = std::move(board[startPos]);
        break;

    case enPassant:
        // Piece which was captured en passant but not landed on, must be
        // removed from board so first move piece to be captured back,
        // then capture as normal
        {
            int forward = startPos + numFiles;
            int backward = startPos - numFiles;

            if (endPos == forward + 1 || endPos == forward - 1) {
                board[endPos] = std::move(board[endPos - numFiles]);

            } else if (endPos == backward + 1 || endPos == backward - 1) {
                board[endPos] = std::move(board[endPos + numFiles]);

            } else {
                throw std::invalid_argument(
                    "Error: Invalid en passant capture"
                );
            }
        }

        board[endPos] = std::move(board[startPos]);
        break;

    case castling:
        // Move rook
        if (board[startPos]->getSymbol() == 'K' && endPos > startPos)
        {
            board[endPos - 1] = std::move(board[startPos + 3]);
        }
        else if (board[startPos]->getSymbol() == 'K' && endPos < startPos)
        {
            board[endPos + 1] = std::move(board[startPos - 4]);
        }
        else
        {
            throw std::invalid_argument("Error: Invalid castling move");
        }

        board[endPos] = std::move(board[startPos]); // Move king as normal
        break;
    
    default:
        throw std::invalid_argument("Error: Invalid move type");
        break;
    }
}

void ChessBoard::reset() {
    board.clear();
    board = initBoard(std::move(board));
}

namespace chess
{
    std::vector<std::unique_ptr<ChessPiece>> initBoard(
        std::vector<std::unique_ptr<ChessPiece>> board
    ) {
        using chess::Pawn, chess::Rook, chess::Knight,
              chess::Bishop, chess::Queen, chess::King,
              std::make_unique;
        
        const int ranks = 8;
        const int files = 8;

        // Initialize white pieces on chess board
        // starting from bottom left to top right
        board.push_back(make_unique<Rook>(Rook(white, 0)));
        board.push_back(make_unique<Knight>(Knight(white, 1)));
        board.push_back(make_unique<Bishop>(Bishop(white, 2)));
        board.push_back(make_unique<Queen>(Queen(white, 3)));
        board.push_back(make_unique<King>(King(white, 4)));
        board.push_back(make_unique<Bishop>(Bishop(white, 5)));
        board.push_back(make_unique<Knight>(Knight(white, 6)));
        board.push_back(make_unique<Rook>(Rook(white, 7)));

        for (int i = 1*files; i < 2*files ; i++) {
            board.push_back(make_unique<Pawn>(Pawn(white, i)));
        }

        // Initialize unoccupied chess board squares
        // rows 3,4,5,6 (array elements 16-48)
        for (int i = 2*files; i < (ranks - 2)*files ; i++) {
            board.push_back(std::unique_ptr<ChessPiece>{nullptr}); 
        }

        // Initialize black pieces on chess board
        for (int i = (ranks - 2)*files; i < (ranks - 1)*files ; i++) {
            board.push_back(make_unique<Pawn>(Pawn(black, i)));
        }
        
        int id = (ranks - 1)*files;
        board.push_back(make_unique<Rook>(Rook(black, id + 0)));
        board.push_back(make_unique<Knight>(Knight(black, id + 1)));
        board.push_back(make_unique<Bishop>(Bishop(black, id + 2)));
        board.push_back(make_unique<Queen>(Queen(black, id + 3)));
        board.push_back(make_unique<King>(King(black, id + 4)));
        board.push_back(make_unique<Bishop>(Bishop(black, id + 5)));
        board.push_back(make_unique<Knight>(Knight(black, id + 6)));
        board.push_back(make_unique<Rook>(Rook(black, id + 7)));

        return std::move(board);
    }

    std::unique_ptr<ChessPiece> ChessBoard::operator[](int idx) const {
        int numSquares = numFiles*numRanks;
        if (!(idx >= 0 && idx < numSquares)) {
            throw std::out_of_range("Board index out of range");
        }

        if (board[idx]) {
            return std::move(board[idx]->clone());
        } else {
            return std::move(std::unique_ptr<ChessPiece>(nullptr));
        }
    }

    std::unique_ptr<ChessPiece>& ChessBoard::operator[](int idx) {
        int numSquares = numFiles*numRanks;
        if (!(idx >= 0 && idx < numSquares)) {
            throw std::out_of_range("Board index out of range");
        }
        return board[idx];
    }

    std::ostream& operator<<(std::ostream& output, const ChessBoard& b) {
        output << std::endl 
               << "     a   b   c   d   e   f   g   h" << std::endl;
        output << "  -----------------------------------" << std::endl;
        for (int fileIdx = ChessBoard::numFiles - 1; fileIdx >= 0 ; fileIdx--) {
            output << fileIdx + 1 << " ||";
            for (int rankIdx = 0; rankIdx < ChessBoard::numRanks; rankIdx++) {
                int posIdx = fileIdx*ChessBoard::numFiles + rankIdx;
                if (rankIdx < ChessBoard::numRanks - 1) {
                    if (b.board[posIdx]) {
                        output << " " << *b.board[posIdx] << " |";
                    }
                    else {
                        output << "   |";
                    }
                } else {
                    if (b.board[posIdx]) {
                        output << " " << *b.board[posIdx] << " || "
                               << fileIdx + 1 << std::endl;
                    } else {
                        output << "   || " << fileIdx + 1 << std::endl;
                    }
                }
            }
            output << "  -----------------------------------" << std::endl;
        }
        output << "     a   b   c   d   e   f   g   h" << std::endl;

        return output;
    }

    int boardPosToIdx(const std::string& pos) {
        const char file = pos[0];
        const size_t rankNumIdx = 1;
        int rank = std::stoi(std::string(&pos[1])) - 1;

        if (rank < 0 || rank >= 8) {
            throw std::out_of_range("Rank out of range");
        }

        int fileNum;
        switch (file)
        {
        case 'a':
            fileNum = 0;
            break;
        case 'b':
            fileNum = 1;
            break;
        case 'c':
            fileNum = 2;
            break;
        case 'd':
            fileNum = 3;
            break;
        case 'e':
            fileNum = 4;
            break;
        case 'f':
            fileNum = 5;
            break;
        case 'g':
            fileNum = 6;
            break;
        case 'h':
            fileNum = 7;
            break;
        
        default:
            throw std::out_of_range("File out of range");
        }

        return rank*ChessBoard::numFiles + fileNum;
    }

    std::string idxToBoardPos(int posIdx) {
        int rankNum = posIdx/ChessBoard::numFiles + 1;
        int fileNum = posIdx%ChessBoard::numFiles + 1;

        if (rankNum < 1 || rankNum > 8) {
            throw std::out_of_range("Rank out of range");
        }

        std::string rank = std::to_string(rankNum);

        std::string file;
        switch (fileNum)
        {
        case 1:
            file = "a";
            break;
        case 2:
            file = "b";
            break;
        case 3:
            file = "c";
            break;
        case 4:
            file = "d";
            break;
        case 5:
            file = "e";
            break;
        case 6:
            file = "f";
            break;
        case 7:
            file = "g";
            break;
        case 8:
            file = "h";
            break;
        
        default:
            throw std::out_of_range("File out of range");
        }

        return file + rank;
    }
}
