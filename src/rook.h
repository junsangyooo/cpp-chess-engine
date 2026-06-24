#ifndef _ROOK_H_
#define _ROOK_H_
#include "pieces.h"

class Rook : public Piece {
    char piece;
    bool firstMove = true;
    bool promoted = false;
    int whenPromoted = -1;
    int whenFirstMove = -1;
    const int value = 5;
public:
    Rook(char piece);
    ~Rook();
public:
    char getPiece() const override {return piece;}
    bool getFirstMove() const override {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
    bool getPromoted() const override {return promoted;}
    void setPromoted(bool value) override {promoted = value;}
    void setWhenPromoted(int value) override {whenPromoted = value;}
    int getWhenPromoted() override {return whenPromoted;}
    void setWhenFirstMove(int value) override {whenFirstMove = value;}
    int getWhenFirstMove() override {return whenFirstMove;}
    int getValue() const override {return value;}
};

#endif
