#ifndef _CLI_H_
#define _CLI_H_
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
//#include "position.h"

enum Position;

class Cli: public Observer {
    // Non-owning pointer to the subject: the Observer must NOT keep the Chess
    // model alive, otherwise Chess (Subject) <-> Cli form a shared_ptr cycle
    // that never gets freed. Chess outlives its observers, so a raw pointer is safe.
    Chess* chess;
public:
    Cli(std::shared_ptr<Chess> chess);
    void drawBoard(std::string value = "", int posn1 = -1, int posn2 = -1, int posn3 = -1, int posn4 = -1) override;
    void notify() override;
    ~Cli();
};

#endif
