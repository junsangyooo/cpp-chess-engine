#include "gui.h"

void Gui::drawKing(int col, int row, char piece) {
    int colour;
    if (piece == 'K') {
        colour = xw.White;
    } else {colour = xw.Black;}
    xw.fillRectangle(col*30+15, row*30+2, 2, 2, colour);
    xw.fillRectangle(col*30+13, row*30+4, 6, 2, colour);
    xw.fillRectangle(col*30+15, row*30+6, 2, 3, colour);
    xw.fillRectangle(col*30+11, row*30+8, 2, 1, colour);
    xw.fillRectangle(col*30+19, row*30+8, 2, 1, colour);
    xw.fillRectangle(col*30+9, row*30+9, 14, 1, colour);
    xw.fillRectangle(col*30+7, row*30+10, 18, 1, colour);
    xw.fillRectangle(col*30+6, row*30+11, 20, 2, colour);
    xw.fillRectangle(col*30+5, row*30+13, 22, 3, colour);
    xw.fillRectangle(col*30+6, row*30+16, 20, 1, colour);
    xw.fillRectangle(col*30+7, row*30+17, 18, 1, colour);
    xw.fillRectangle(col*30+9, row*30+18, 14, 1, colour);
    xw.fillRectangle(col*30+10, row*30+19, 12, 1, colour);
    xw.fillRectangle(col*30+12, row*30+20, 8, 1, colour);
    xw.fillRectangle(col*30+10, row*30+21, 12, 1, colour);
    xw.fillRectangle(col*30+7, row*30+22, 18, 3, colour);
}
void Gui::drawQueen(int col, int row, char piece) {
    int colour;
    if (piece == 'Q') {
        colour = xw.White;
    } else {colour = xw.Black;}
    xw.fillRectangle(col*30+15, row*30+5, 2, 3, colour);
    xw.fillRectangle(col*30+14, row*30+8, 4, 2, colour);
    xw.fillRectangle(col*30+3, row*30+9, 2, 1, colour);
    xw.fillRectangle(col*30+27, row*30+9, 2, 1, colour);
    xw.fillRectangle(col*30+4, row*30+10, 2, 1, colour);
    xw.fillRectangle(col*30+26, row*30+10, 2, 1, colour);
    xw.fillRectangle(col*30+13, row*30+10, 6, 1, colour);
    xw.fillRectangle(col*30+4, row*30+11, 3, 1, colour);
    xw.fillRectangle(col*30+25, row*30+11, 3, 1, colour);
    xw.fillRectangle(col*30+12, row*30+11, 8, 1, colour);
    xw.fillRectangle(col*30+5, row*30+12, 5, 1, colour);
    xw.fillRectangle(col*30+22, row*30+12, 5, 1, colour);
    xw.fillRectangle(col*30+11, row*30+12, 10, 1, colour);
    xw.fillRectangle(col*30+5, row*30+13, 22, 1, colour);
    xw.fillRectangle(col*30+6, row*30+14, 20, 2, colour);
    xw.fillRectangle(col*30+7, row*30+16, 18, 2, colour);
    xw.fillRectangle(col*30+8, row*30+18, 16, 1, colour);
    xw.fillRectangle(col*30+9, row*30+19, 14, 1, colour);
    xw.fillRectangle(col*30+10, row*30+20, 12, 1, colour);
    xw.fillRectangle(col*30+8, row*30+21, 16, 1, colour);
    xw.fillRectangle(col*30+7, row*30+22, 18, 3, colour);
}
void Gui::drawRook(int col, int row, char piece) {
    int colour;
    if (piece == 'R') {
        colour = xw.White;
    } else {colour = xw.Black;}
    xw.fillRectangle(col*30+6, row*30+6, 5, 4, colour);
    xw.fillRectangle(col*30+14, row*30+6, 4, 4, colour);
    xw.fillRectangle(col*30+21, row*30+6, 5, 4, colour);
    xw.fillRectangle(col*30+6, row*30+10, 20, 4, colour);
    xw.fillRectangle(col*30+11, row*30+14, 10, 8, colour);
    xw.fillRectangle(col*30+7, row*30+22, 18, 3, colour);
}
void Gui::drawBishop(int col, int row, char piece) {
    int colour;
    if (piece == 'B') {
        colour = xw.White;
    } else {colour = xw.Black;}
    xw.fillRectangle(col*30+15, row*30+4, 2, 2, colour);
    xw.fillRectangle(col*30+14, row*30+6, 4, 1, colour);
    xw.fillRectangle(col*30+13, row*30+7, 6, 1, colour);
    xw.fillRectangle(col*30+12, row*30+8, 6, 1, colour);
    xw.fillRectangle(col*30+11, row*30+9, 6, 1, colour);
    xw.fillRectangle(col*30+20, row*30+9, 1, 1, colour);
    xw.fillRectangle(col*30+10, row*30+10, 6, 1, colour);
    xw.fillRectangle(col*30+19, row*30+10, 3, 1, colour);
    xw.fillRectangle(col*30+9, row*30+11, 6, 1, colour);
    xw.fillRectangle(col*30+18, row*30+11, 5, 1, colour);
    xw.fillRectangle(col*30+8, row*30+12, 6, 1, colour);
    xw.fillRectangle(col*30+17, row*30+12, 7, 1, colour);
    xw.fillRectangle(col*30+7, row*30+13, 6, 1, colour);
    xw.fillRectangle(col*30+16, row*30+13, 9, 1, colour);
    xw.fillRectangle(col*30+6, row*30+14, 8, 1, colour);
    xw.fillRectangle(col*30+15, row*30+14, 12, 1, colour);
    xw.fillRectangle(col*30+6, row*30+15, 20, 1, colour);
    xw.fillRectangle(col*30+7, row*30+16, 18, 1, colour);
    xw.fillRectangle(col*30+8, row*30+17, 16, 1, colour);
    xw.fillRectangle(col*30+9, row*30+18, 14, 1, colour);
    xw.fillRectangle(col*30+10, row*30+19, 12, 1, colour);
    xw.fillRectangle(col*30+11, row*30+20, 10, 1, colour);
    xw.fillRectangle(col*30+10, row*30+21, 12, 1, colour);
    xw.fillRectangle(col*30+7, row*30+22, 18, 3, colour);
}
void Gui::drawKnight(int col, int row, char piece) {
    int colour;
    if (piece == 'N') {
        colour = xw.White;
    } else {colour = xw.Black;}
    xw.fillRectangle(col*30+11, row*30+5, 2, 1, colour);
    xw.fillRectangle(col*30+14, row*30+5, 2, 1, colour);
    xw.fillRectangle(col*30+12, row*30+6, 6, 1, colour);
    xw.fillRectangle(col*30+13, row*30+7, 7, 1, colour);
    xw.fillRectangle(col*30+12, row*30+8, 8, 1, colour);
    xw.fillRectangle(col*30+11, row*30+9, 2, 1, colour);
    xw.fillRectangle(col*30+14, row*30+9, 7, 1, colour);
    xw.fillRectangle(col*30+10, row*30+10, 11, 1, colour);
    xw.fillRectangle(col*30+9, row*30+11, 12, 1, colour);
    xw.fillRectangle(col*30+8, row*30+12, 14, 1, colour);
    xw.fillRectangle(col*30+7, row*30+13, 15, 1, colour);
    xw.fillRectangle(col*30+7, row*30+14, 7, 1, colour);
    xw.fillRectangle(col*30+16, row*30+14, 7, 1, colour);
    xw.fillRectangle(col*30+8, row*30+15, 4, 1, colour);
    xw.fillRectangle(col*30+15, row*30+15, 8, 1, colour);
    xw.fillRectangle(col*30+9, row*30+16, 2, 1, colour);
    xw.fillRectangle(col*30+14, row*30+16, 9, 1, colour);
    xw.fillRectangle(col*30+13, row*30+17, 10, 1, colour);
    xw.fillRectangle(col*30+12, row*30+18, 11, 1, colour);
    xw.fillRectangle(col*30+11, row*30+19, 12, 1, colour);
    xw.fillRectangle(col*30+10, row*30+20, 13, 1, colour);
    xw.fillRectangle(col*30+9, row*30+21, 14, 1, colour);
    xw.fillRectangle(col*30+7, row*30+22, 18, 3, colour);
}
void Gui::drawPawn(int col, int row, char piece) {
    int colour;
    if (piece == 'P') {
        colour = xw.White;
    } else {colour = xw.Black;}
    xw.fillRectangle(col*30+15, row*30+6, 2, 1, colour);
    xw.fillRectangle(col*30+14, row*30+7, 4, 1, colour);
    xw.fillRectangle(col*30+13, row*30+8, 6, 1, colour);
    xw.fillRectangle(col*30+14, row*30+9, 4, 1, colour);
    xw.fillRectangle(col*30+15, row*30+10, 2, 1, colour);
    xw.fillRectangle(col*30+12, row*30+11, 8, 1, colour);
    xw.fillRectangle(col*30+14, row*30+12, 4, 2, colour);
    xw.fillRectangle(col*30+15, row*30+14, 2, 1, colour);
    xw.fillRectangle(col*30+14, row*30+15, 4, 2, colour);
    xw.fillRectangle(col*30+13, row*30+17, 6, 2, colour);
    xw.fillRectangle(col*30+12, row*30+19, 8, 2, colour);
    xw.fillRectangle(col*30+10, row*30+21, 12, 1, colour);
    xw.fillRectangle(col*30+9, row*30+22, 14, 1, colour);
    xw.fillRectangle(col*30+7, row*30+23, 18, 2, colour);
}

void Gui::drawBoard(std::string value, int posn1, int posn2, int posn3, int posn4) {
    char piece;
    if (posn1 != -1) {
        int row = posn1 / 10;
        int col = posn1 % 10;
        piece = chess->charAt(Position(posn1));
        if ((row + col) % 2 == 0) {
            xw.fillRectangle(col*30, row*30, 30, 30, xw.Orange);
        } else {
            xw.fillRectangle(col*30, row*30, 30, 30, xw.Brown);
        }
        if (piece == 'k' || piece =='K'){
            drawKing(col, row, piece);
        } else if (piece == 'q' || piece == 'Q') {
            drawQueen(col, row, piece);
        } else if (piece == 'r' || piece == 'R'){
            drawRook(col, row, piece);
        } else if (piece == 'b' || piece == 'B') {
            drawBishop(col, row, piece);
        } else if (piece == 'n' || piece == 'N') {
            drawKnight(col, row, piece);
        } else if (piece == 'p' || piece == 'P') {
            drawPawn(col, row, piece);
        }
    }
    if (posn2 != -1) {
        int row = posn2 / 10;
        int col = posn2 % 10;
        piece = chess->charAt(Position(posn2));
        if ((row + col) % 2 == 0) {
            xw.fillRectangle(col*30, row*30, 30, 30, xw.Orange);
        } else {
            xw.fillRectangle(col*30, row*30, 30, 30, xw.Brown);
        }
        if (piece == 'k' || piece =='K'){
            drawKing(col, row, piece);
        } else if (piece == 'q' || piece == 'Q') {
            drawQueen(col, row, piece);
        } else if (piece == 'r' || piece == 'R'){
            drawRook(col, row, piece);
        } else if (piece == 'b' || piece == 'B') {
            drawBishop(col, row, piece);
        } else if (piece == 'n' || piece == 'N') {
            drawKnight(col, row, piece);
        } else if (piece == 'p' || piece == 'P') {
            drawPawn(col, row, piece);
        }
    }
    if (posn3 != -1) {
        int row = posn3 / 10;
        int col = posn3 % 10;
        piece = chess->charAt(Position(posn3));
        if ((row + col) % 2 == 0) {
            xw.fillRectangle(col*30, row*30, 30, 30, xw.Orange);
        } else {
            xw.fillRectangle(col*30, row*30, 30, 30, xw.Brown);
        }
        if (piece == 'k' || piece =='K'){
            drawKing(col, row, piece);
        } else if (piece == 'q' || piece == 'Q') {
            drawQueen(col, row, piece);
        } else if (piece == 'r' || piece == 'R'){
            drawRook(col, row, piece);
        } else if (piece == 'b' || piece == 'B') {
            drawBishop(col, row, piece);
        } else if (piece == 'n' || piece == 'N') {
            drawKnight(col, row, piece);
        } else if (piece == 'p' || piece == 'P') {
            drawPawn(col, row, piece);
        }
    }
    if (posn4 != -1) {
        int row = posn4 / 10;
        int col = posn4 % 10;
        piece = chess->charAt(Position(posn4));
        if ((row + col) % 2 == 0) {
            xw.fillRectangle(col*30, row*30, 30, 30, xw.Orange);
        } else {
            xw.fillRectangle(col*30, row*30, 30, 30, xw.Brown);
        }
        if (piece == 'k' || piece =='K'){
            drawKing(col, row, piece);
        } else if (piece == 'q' || piece == 'Q') {
            drawQueen(col, row, piece);
        } else if (piece == 'r' || piece == 'R'){
            drawRook(col, row, piece);
        } else if (piece == 'b' || piece == 'B') {
            drawBishop(col, row, piece);
        } else if (piece == 'n' || piece == 'N') {
            drawKnight(col, row, piece);
        } else if (piece == 'p' || piece == 'P') {
            drawPawn(col, row, piece);
        }
    }
    xw.fillRectangle(0, 240, 240, 40, xw.White);
    if (value != "") {
        xw.drawString(30, 270, value);
    }
}

void Gui::notify() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j <8;  ++j) {
            int posn = i*10 + j;
            char piece = chess->charAt(Position(posn));
            if ((i + j) % 2 == 0) {
                xw.fillRectangle(j*30, i*30, 30, 30, xw.Orange);
            } else {
                xw.fillRectangle(j*30, i*30, 30, 30, xw.Brown);
            }
            if (piece == 'k' || piece =='K'){
                drawKing(j, i, piece);
            } else if (piece == 'q' || piece == 'Q') {
                drawQueen(j, i, piece);
            } else if (piece == 'r' || piece == 'R'){
                drawRook(j, i, piece);
            } else if (piece == 'b' || piece == 'B') {
                drawBishop(j ,i, piece);
            } else if (piece == 'n' || piece == 'N') {
                drawKnight(j ,i, piece);
            } else if (piece == 'p' || piece == 'P'){
                 drawPawn(j, i, piece);
            }
        }
    }
     /*for (int i = 0; i < 8; ++i) {
        for (int j = 0; j <8;  ++j) {
            int posn = i*10 + j;
            char piece = chess->charAt(Position(posn));
            if ((i + j) % 2 == 0) {
                xw.fillRectangle(j*30, i*30, 30, 30, xw.Orange);
            } else {
                xw.fillRectangle(j*30, i*30, 30, 30, xw.Brown);
            }
            if (piece == ' ' || piece == '-') {continue;}
            else {
                std::string tmp(1, piece);
                xw.drawString(j*30 + 10, i*30 + 15, tmp);
            }
        }
    }*/
   
}

Gui::Gui(std::shared_ptr<Chess> chess): chess{chess.get()}, xw{240, 280} {
    notify();
}



Gui::~Gui() {
    // Non-owning observer: nothing to release (see Cli::~Cli).
    chess = nullptr;
}
