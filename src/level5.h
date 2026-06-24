#ifndef _LEVEL_FIVE_H_
#define _LEVEL_FIVE_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <vector>
#include <memory>
#include <random>
#include <stdlib.h>
#include "computer.h"
#include "pieces.h"
#include "board.h"
#include "position.h"
#include "move.h"


// Level 5: the strongest AI. Same negamax + alpha-beta engine-free approach as
// Level 4, but searches one ply deeper and uses a richer evaluation
// (material + piece-square positional bonus + pawn advancement), so it plays
// noticeably stronger than Level 4.
class LevelFive : public Computer{
    std::shared_ptr<Chess> chess;
    bool whiteSide;
    std::shared_ptr<Board> board;
    std::vector<std::shared_ptr<Move>> generateMoves(bool side);
    int evaluate(bool side);
    int negamax(int depth, int alpha, int beta, bool side);
public:
    LevelFive(std::shared_ptr<Chess> chess, bool side, std::shared_ptr<Board> bd);
    ~LevelFive();
    bool makeMove() override;
};

#endif
