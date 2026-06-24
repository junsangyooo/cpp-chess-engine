#include "level5.h"

// Level 5 AI: the strongest computer player. Negamax with alpha-beta pruning
// (engine untouched — all look-ahead via Board::move/undo), searching one ply
// deeper than Level 4 and scoring positions with material + a piece-square
// table (rewards central control) + pawn advancement. Captures are searched
// first (move ordering) to make the alpha-beta cutoffs more effective so the
// deeper search stays fast enough.

static const int SEARCH_DEPTH = 3;
static const int MATE_SCORE = 1000000;

// Central-control bonus per square (symmetric for both colors). Center squares
// are worth more than the edges/corners.
static const int PST[8][8] = {
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 2, 2, 1, 1, 0},
    {1, 1, 2, 3, 3, 2, 1, 1},
    {1, 2, 3, 4, 4, 3, 2, 1},
    {1, 2, 3, 4, 4, 3, 2, 1},
    {1, 1, 2, 3, 3, 2, 1, 1},
    {0, 1, 1, 2, 2, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
};

LevelFive::LevelFive(std::shared_ptr<Chess> chess, bool side, std::shared_ptr<Board> bd): chess{chess}, whiteSide{side}, board{bd} {}

LevelFive::~LevelFive() {
    chess = nullptr;
    board = nullptr;
}

// Legal moves for `side`, captures first (better alpha-beta move ordering).
std::vector<std::shared_ptr<Move>> LevelFive::generateMoves(bool side) {
    std::vector<std::shared_ptr<Move>> captures;
    std::vector<std::shared_ptr<Move>> quiets;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Position org = Position(i * 10 + j);
            char pc = board->charAt(org);
            if (side && !('A' <= pc && pc <= 'Z')) continue;
            if (!side && !('a' <= pc && pc <= 'z')) continue;
            for (int r = 0; r < 8; ++r) {
                for (int c = 0; c < 8; ++c) {
                    Position dst = Position(r * 10 + c);
                    auto probe = std::make_shared<Move>(org, dst);
                    if (!chess->validMove(probe, side)) continue;
                    auto m = std::make_shared<Move>(org, dst);
                    char tgt = board->charAt(dst);
                    if (tgt != ' ' && tgt != '-') {
                        m->setCaptured(board->getPiece(dst));
                        captures.emplace_back(m);
                    } else {
                        quiets.emplace_back(m);
                    }
                }
            }
        }
    }
    captures.insert(captures.end(), quiets.begin(), quiets.end());
    return captures;
}

// Material + positional score from `side`'s point of view.
int LevelFive::evaluate(bool side) {
    int score = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Position p = Position(i * 10 + j);
            char c = board->charAt(p);
            if (c == ' ' || c == '-') continue;
            int v = board->getValue(p) * 10; // scale material above positional terms
            int positional = PST[i][j];
            if (c == 'P') positional += (7 - i);      // white pawns advance upward (row 0)
            else if (c == 'p') positional += i;        // black pawns advance downward (row 7)
            if ('A' <= c && c <= 'Z') score += v + positional;
            else score -= v + positional;
        }
    }
    return side ? score : -score;
}

int LevelFive::negamax(int depth, int alpha, int beta, bool side) {
    if (depth == 0) return evaluate(side);

    std::vector<std::shared_ptr<Move>> moves = generateMoves(side);
    if (moves.empty()) {
        bool inCheck = side ? (chess->whiteInCheck() != "")
                            : (chess->blackInCheck() != "");
        if (inCheck) return -MATE_SCORE - depth;
        return 0;
    }

    int best = -MATE_SCORE * 2;
    for (auto &m : moves) {
        board->move(m);
        int val = -negamax(depth - 1, -beta, -alpha, !side);
        board->undo(m);
        if (val > best) best = val;
        if (best > alpha) alpha = best;
        if (alpha >= beta) break;
    }
    return best;
}

bool LevelFive::makeMove() {
    std::vector<std::shared_ptr<Move>> moves = generateMoves(whiteSide);
    if (moves.empty()) return false;

    std::shared_ptr<Move> best = moves.front();
    int bestVal = -MATE_SCORE * 2;
    int alpha = -MATE_SCORE * 2;
    int beta = MATE_SCORE * 2;
    for (auto &m : moves) {
        board->move(m);
        int val = -negamax(SEARCH_DEPTH - 1, -beta, -alpha, !whiteSide);
        board->undo(m);
        if (val > bestVal) {
            bestVal = val;
            best = m;
        }
        if (bestVal > alpha) alpha = bestVal;
    }

    Position org = best->getOrg();
    Position dst = best->getNew();
    char pc = board->charAt(org);
    char promote = '.';
    if (pc == 'P' && dst <= 7) promote = 'Q';
    else if (pc == 'p' && dst >= 70) promote = 'q';

    auto realMove = std::make_shared<Move>(org, dst);
    return chess->movePiece(realMove, whiteSide, promote);
}
