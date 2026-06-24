#ifndef _GUI_H_
#define _GUI_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <vector>
#include <memory>
#include "observer.h"
#include "chess.h"
#include "window.h"
//#include "position.h"

enum Position;

class Gui: public Observer {
    // Non-owning pointer to the subject (see Cli for the cycle-avoidance rationale).
    Chess* chess;
    Xwindow xw;
    void drawKing(int col, int row, char piece);
    void drawQueen(int col, int row, char piece);
    void drawRook(int col, int row, char piece);
    void drawBishop(int col, int row, char piece);
    void drawKnight(int col, int row, char piece);
    void drawPawn(int col, int row, char piece);
public:
    Gui(std::shared_ptr<Chess> chess);
    void drawBoard(std::string value = "", int posn1 = -1, int posn2 = -1, int posn3 = -1, int posn4 = -1) override;
    void notify() override;
    ~Gui();
};

#endif
