#include "cli.h"
#include <iostream>

void Cli::drawBoard(std::string value, int posn1, int posn2, int posn3, int posn4) {
    char piece;
    for (int i = 0; i < 8; ++i) {
        std::cout << 8 - i << " ";
        for (int j = 0; j <8;  ++j) {
            int posn = i*10 + j;
            piece = chess->charAt(Position(posn));
            if (piece == ' ') {
                std::cout << "█";
            } else if (piece == '-') {
                std::cout << "▒";
            } else if (piece == 'P') {
                std::cout << "♟";
            } else if (piece == 'p') {
                std::cout << "♙";
            } else if (piece == 'R') {
                std::cout << "♜";
            } else if (piece == 'r') {
                std::cout << "♖";
            } else if (piece == 'N') {
                std::cout << "♞";
            } else if (piece == 'n') {
                std::cout << "♘";
            } else if (piece == 'B') {
                std::cout << "♝";
            } else if (piece == 'b') {
                std::cout << "♗";
            } else if (piece == 'Q') {
                std::cout << "♛";
            } else if (piece == 'q') {
                std::cout << "♕";
            } else if (piece == 'K') {
                std::cout << "♚";
            } else if (piece == 'k') {
                std::cout << "♔";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "  abcdefgh" << std::endl;
    if (value != "") {
        std::cout << value << std::endl;
    }
}

void Cli::notify() {
    char piece;
    for (int i = 0; i < 8; ++i) {
        std::cout << 8 - i << " ";
        for (int j = 0; j <8;  ++j) {
            int posn = i*10 + j;
            piece = chess->charAt(Position(posn));
            if (piece == ' ') {
                std::cout << "█";
            } else if (piece == '-') {
                std::cout << "▒";
            } else if (piece == 'P') {
                std::cout << "♟";
            } else if (piece == 'p') {
                std::cout << "♙";
            } else if (piece == 'R') {
                std::cout << "♜";
            } else if (piece == 'r') {
                std::cout << "♖";
            } else if (piece == 'N') {
                std::cout << "♞";
            } else if (piece == 'n') {
                std::cout << "♘";
            } else if (piece == 'B') {
                std::cout << "♝";
            } else if (piece == 'b') {
                std::cout << "♗";
            } else if (piece == 'Q') {
                std::cout << "♛";
            } else if (piece == 'q') {
                std::cout << "♕";
            } else if (piece == 'K') {
                std::cout << "♚";
            } else if (piece == 'k') {
                std::cout << "♔";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "  abcdefgh" << std::endl;
}

Cli::Cli(std::shared_ptr<Chess> chess): chess{chess.get()} {
    notify();
}

Cli::~Cli() {
    // Non-owning observer: nothing to release. (Previously this dereferenced a
    // nulled pointer via chess->detach, and the shared_ptr cycle meant the
    // destructor never even ran.)
    chess = nullptr;
}
