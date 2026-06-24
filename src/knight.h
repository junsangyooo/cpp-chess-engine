#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "pieces.h"

class Knight : public Piece {
    char piece;
    bool promoted = false;
    int whenPromoted = -1;
    const int value = 3;
public:
    Knight(char piece);
    ~Knight();
public:
    char getPiece() const override {return piece;}
    bool getPromoted() const override {return promoted;}
    void setPromoted(bool value) override {promoted = value;}
    void setWhenPromoted(int value) override {whenPromoted = value;}
    int getWhenPromoted() override {return whenPromoted;}
    int getValue() const override {return value;}
};

#endif
