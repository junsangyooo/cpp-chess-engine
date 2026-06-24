#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include <memory>
#include "scoreboard.h"
#include "pieces.h"
#include "board.h"
#include "subject.h"
#include "chess.h"
#include "observer.h"
#include "gui.h"
#include "cli.h"
#include "controller.h"
#include "computer.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "level5.h"

enum Position;

Position strToPosn(std::string str) {
    if (str == "a8") {return Position(a8);}
    else if (str == "b8") {return Position(b8);}
    else if (str == "c8") {return Position(c8);}
    else if (str == "d8") {return Position(d8);}
    else if (str == "e8") {return Position(e8);}
    else if (str == "f8") {return Position(f8);}
    else if (str == "g8") {return Position(g8);}
    else if (str == "h8") {return Position(h8);}
    else if (str == "a7") {return Position(a7);}
    else if (str == "b7") {return Position(b7);}
    else if (str == "c7") {return Position(c7);}
    else if (str == "d7") {return Position(d7);}
    else if (str == "e7") {return Position(e7);}
    else if (str == "f7") {return Position(f7);}
    else if (str == "g7") {return Position(g7);}
    else if (str == "h7") {return Position(h7);}
    else if (str == "a6") {return Position(a6);}
    else if (str == "b6") {return Position(b6);}
    else if (str == "c6") {return Position(c6);}
    else if (str == "d6") {return Position(d6);}
    else if (str == "e6") {return Position(e6);}
    else if (str == "f6") {return Position(f6);}
    else if (str == "g6") {return Position(g6);}
    else if (str == "h6") {return Position(h6);}
    else if (str == "a5") {return Position(a5);}
    else if (str == "b5") {return Position(b5);}
    else if (str == "c5") {return Position(c5);}
    else if (str == "d5") {return Position(d5);}
    else if (str == "e5") {return Position(e5);}
    else if (str == "f5") {return Position(f5);}
    else if (str == "g5") {return Position(g5);}
    else if (str == "h5") {return Position(h5);}
    else if (str == "a4") {return Position(a4);}
    else if (str == "b4") {return Position(b4);}
    else if (str == "c4") {return Position(c4);}
    else if (str == "d4") {return Position(d4);}
    else if (str == "e4") {return Position(e4);}
    else if (str == "f4") {return Position(f4);}
    else if (str == "g4") {return Position(g4);}
    else if (str == "h4") {return Position(h4);}
    else if (str == "a3") {return Position(a3);}
    else if (str == "b3") {return Position(b3);}
    else if (str == "c3") {return Position(c3);}
    else if (str == "d3") {return Position(d3);}
    else if (str == "e3") {return Position(e3);}
    else if (str == "f3") {return Position(f3);}
    else if (str == "g3") {return Position(g3);}
    else if (str == "h3") {return Position(h3);}
    else if (str == "a2") {return Position(a2);}
    else if (str == "b2") {return Position(b2);}
    else if (str == "c2") {return Position(c2);}
    else if (str == "d2") {return Position(d2);}
    else if (str == "e2") {return Position(e2);}
    else if (str == "f2") {return Position(f2);}
    else if (str == "g2") {return Position(g2);}
    else if (str == "h2") {return Position(h2);}
    else if (str == "a1") {return Position(a1);}
    else if (str == "b1") {return Position(b1);}
    else if (str == "c1") {return Position(c1);}
    else if (str == "d1") {return Position(d1);}
    else if (str == "e1") {return Position(e1);}
    else if (str == "f1") {return Position(f1);}
    else if (str == "g1") {return Position(g1);}
    else if (str == "h1") {return Position(h1);}
    else {throw std::out_of_range {"Invalid position!"};}
}


bool newGame() {
    std::cout << "Game has ended. Do you want to play again? (yes/no)" << std::endl;
    std::string response;
    std::cin >> response;
    if (response == "yes") {return true;}
    else if (response == "no") { return false;}
    else {throw std::out_of_range {"Invalid response!"};}
}


bool validPiece(char piece) {
    if (piece == 'p' || piece == 'P' || piece == 'k' || piece == 'K' || piece == 'q' || piece == 'Q' || piece == 'r' || piece == 'R' ||piece == 'b' || piece == 'B' || piece == 'n' || piece == 'N') {
        return true;
    }
    return false;
}

int main() {
    std::shared_ptr<ScoreBoard> sb;
    std::string command;
    bool whiteTurn = true;
    std::shared_ptr<Board> board;
    std::shared_ptr<Chess> chess;
    std::shared_ptr<Controller> control;
    std::shared_ptr<Cli> textBoard;
    std::shared_ptr<Gui> graphicBoard;
    bool boardExist = false;
    while (std::cin >> command) {
        if (command == "exit") {
            break;
        }
        if (!boardExist) {
            whiteTurn = true;
            sb = std::make_shared<ScoreBoard>(0.0, 0.0);
            board = std::make_shared<Board>();
            chess = std::make_shared<Chess>(board, sb);
            control = std::make_shared<Controller>(chess);
            textBoard = std::make_shared<Cli>(chess);
            graphicBoard = std::make_shared<Gui>(chess);
            chess->attach(textBoard);
            chess->attach(graphicBoard);
            boardExist = true;
        }
        if (command == "exit") {
            break;
        } else if (command == "game"){
            std::string player1;
            std::string player2;
            std::cin >> player1 >> player2;
            bool player1IsComputer = false;
            bool player2IsComputer = false;
            std::shared_ptr<Computer> computerOne;
            std::shared_ptr<Computer> computerTwo;
            if (player1 == "computer1") {
                player1IsComputer = true;
                computerOne = std::make_shared<LevelOne>(chess, true, board);
            } else if (player1 == "computer2") {
                player1IsComputer = true;
                computerOne = std::make_shared<LevelTwo>(chess, true, board);
            } else if (player1 == "computer3") {
                player1IsComputer = true;
                computerOne = std::make_shared<LevelThree>(chess, true, board);
            } else if (player1 == "computer4") {
                player1IsComputer = true;
                computerOne = std::make_shared<LevelFour>(chess, true, board);
            } else if (player1 == "computer5") {
                player1IsComputer = true;
                computerOne = std::make_shared<LevelFive>(chess, true, board);
            }
            if (player1IsComputer){
                control->setComputerWhite(computerOne);
            }
            
            if (player2 == "computer1") {
                player2IsComputer = true;
                computerTwo = std::make_shared<LevelOne>(chess, false, board);
            } else if (player2 == "computer2") {
                player2IsComputer = true;
                computerTwo = std::make_shared<LevelTwo>(chess, false, board);
            } else if (player2 == "computer3") {
                player2IsComputer = true;
                computerTwo = std::make_shared<LevelThree>(chess, false, board);
            } else if (player2 == "computer4") {
                player2IsComputer = true;
                computerTwo = std::make_shared<LevelFour>(chess, false, board);
            } else if (player2 == "computer5") {
                player2IsComputer = true;
                computerTwo = std::make_shared<LevelFive>(chess, false, board);
            }
            if (player2IsComputer) {
                control->setComputerBlack(computerTwo);
            }

            std::string cmd;
            bool gameEnd = false;
            bool restart = false;
            bool error = false;
            while(!gameEnd) {
                if (restart) {
                    board = std::make_shared<Board>();
                    chess = std::make_shared<Chess>(board, sb);
                    control = std::make_shared<Controller>(chess);
                    textBoard = std::make_shared<Cli>(chess);
                    graphicBoard = std::make_shared<Gui>(chess);
                    chess->attach(textBoard);
                    chess->attach(graphicBoard);
                    if (player1IsComputer) {
                        control->setComputerWhite(computerOne);
                    }
                    if (player2IsComputer) {
                        control->setComputerBlack(computerTwo);
                    }
                    whiteTurn = true;
                    restart = false;
                }
                if (whiteTurn && !error) {
                    std::cout << "\n\n---WHITE TURN---" << std::endl;
                } else if (!error) {
                    std::cout << "\n\n---BLACK TURN---" << std::endl;
                }
                
                error = false;
                std::cin >> cmd;
                if (std::cin.eof()) {
                    gameEnd = true;
                    restart = false;
                    continue;
                } else if (cmd == "resign") {
                    control->resign(whiteTurn);
                    if (whiteTurn) {
                        sb->addToBlack(1);
                        std::cout << "Black wins!" << std::endl;
                    }
                    else {
                        sb->addToWhite(1);
                        std::cout << "White wins!" << std::endl;
                    }
                    gameEnd = true;
                } else if (cmd == "move") {
                    if (whiteTurn && player1IsComputer) {
                        gameEnd = control->computerMove(whiteTurn);
                    } else if (!whiteTurn && player2IsComputer) {
                        gameEnd = control->computerMove(whiteTurn);
                    } else {
                        std::string posn1;
                        std::string posn2;
                        Position firstPosn;
                        Position secondPosn;
                        std::cin >> posn1 >> posn2;
                        try {firstPosn = strToPosn(posn1);}
                        catch(std::out_of_range &e) {
                            std::cerr << e.what() << std::endl;
                            error = true;
                            continue;
                        }
                        try {secondPosn = strToPosn(posn2);}
                        catch(std::out_of_range &e) {
                            std::cerr << e.what() << std::endl;
                            error = true;
                            continue;
                        }

                        char piece = board->charAt(firstPosn);
                        //Check Pawn Promotion
                        char promoted;
                        if ((piece == 'p' && 60 <= firstPosn && firstPosn <= 67) || (piece == 'P' && 10 <= firstPosn && firstPosn <= 17)) {
                            std::cin >> promoted;
                            if (promoted != 'r' && promoted != 'R' && promoted != 'n' && promoted != 'N' && promoted != 'b' && promoted != 'B' && promoted != 'q' && promoted != 'Q') {
                                std::cerr << "Please provide a valid piece." << std::endl;
                                error = true;
                                continue;
                            } else if (piece == 'p' && 'A' <= promoted && promoted <= 'Z') {
                                std::cerr << "You cannot promote to the opponent's piece." << std::endl;
                                error = true;
                                continue;
                            } else if (piece == 'P' && 'a' <= promoted && promoted <= 'z') {
                                std::cerr << "You cannot promote to the opponent's piece." << std::endl;
                                error = true;
                                continue;
                            }
                            try {gameEnd = control->pawnPromote(firstPosn, secondPosn, whiteTurn, promoted);}
                            catch (std::out_of_range &e) {
                                std::cerr << e.what() << std::endl;
                                error = true;
                                continue;
                            }
                        } else {
                            try {gameEnd = control->move(firstPosn, secondPosn, whiteTurn);}
                            catch (std::out_of_range &e) {
                                std::cerr << e.what() << std::endl;
                                error = true;
                                continue;
                            }
                        }
                    }
                    whiteTurn = !whiteTurn;
                } else if (cmd == "undo") {
                    try{control->undo();}
                    catch (std::out_of_range &e) {
                        std::cerr << e.what() << std::endl;
                        continue;
                    }
                    whiteTurn = !whiteTurn;
                } else {
                    std::cerr << "Please provide a valid command." << std::endl;
                    error = true;
                    continue;
                }
                bool response = false;
                if (gameEnd) {
                    while(!response) {
                        try {
                            restart = newGame();
                            response = true;    
                        }
                        catch (std::out_of_range &e) {
                            std::cerr << e.what() << std::endl;
                        }
                    }
                    gameEnd = !restart;
                }
            }
            std::cout << "Final Score:" << std::endl;
            if (player1IsComputer || player1 == "human") {
                std::cout << "White: " << sb->getWhite() << std::endl;
            } else {
                std::cout << player1 << ": " << sb->getWhite() << std::endl;
            }
            if (player2IsComputer || player2 == "human") {
                std::cout << "Black: " << sb->getBlack() << std::endl;
            } else {
                std::cout << player2 << ": " << sb->getBlack() << std::endl;
            }
            boardExist = false;
        } else if (command == "setup") {
            std::string cmd;
            int changedPosn;
            while (std::cin >> cmd) {
                if (cmd == "done") {
                    int whiteKing = 0;
                    int blackKing = 0;
                    bool check = control->check();
                    if (check) {
                        std::cerr << "King should be not in check!!!" << std::endl;
                        continue;
                    }
                    bool validPawn = true;
                    for(int i = 0; i < 8; ++i) {
                        for (int j = 0; j < 8; ++j) {
                            char piece = board->charAt(Position(10*i +j));
                            if ((i == 0 || i == 7) && (piece == 'p' || piece == 'P')) {
                                validPawn = false;
                            }
                            if (piece == 'k') {blackKing++;}
                            else if (piece == 'K') {whiteKing++;}
                        }
                    }
                    
                    if (!validPawn) {
                        std::cerr << "Pawn cannot start on the first or last row!!!" << std::endl;
                        continue;
                    }
                    if (whiteKing != 1 || blackKing != 1) {
                        std::cerr << "Each side can only have one King!!!" << std::endl;
                        continue;
                    }
                    break;
                } else if (cmd == "+") {
                    char piece;
                    std::string position;
                    std::cin >> piece >> position;
                    Position posn;
                    try {posn = strToPosn(position);}
                    catch (std::out_of_range &e) {
                        std::cerr << e.what() << std::endl;
                        continue;
                    }
                    if (!validPiece(piece)) {
                        std::cerr << "Please provide a valid piece." << std::endl;
                        continue;
                    } 
                    board->replace(piece, posn);
                    changedPosn = ((posn / 10) * 10) + (posn % 10);
                    control->display(changedPosn);
                } else if (cmd == "-") {
                    std::string position;
                    std::cin >> position;
                    Position posn;
                    try {posn = strToPosn(position);}
                    catch (std::out_of_range &e) {
                        std::cerr << e.what() << std::endl;
                        continue;
                    }
                    if (board->charAt(posn) != ' ' && board->charAt(posn) != '-') {
                        board->remove(posn);
                        changedPosn = ((posn / 10) * 10) + (posn % 10);
                        control->display(changedPosn);
                    } else {continue;}
                } else if (cmd == "=") {
                    std::string colour;
                    std::cin >> colour;
                    if (colour == "White") {whiteTurn = true;}
                    else if (colour == "Black") {whiteTurn = false;}
                    else {
                        std::cerr << "Invalid colour!" << std::endl;
                        continue;
                    }
                } else {
                    std::cerr << "Please provide a valid command." << std::endl;
                    continue;
                }
            }
        } else {
            std::cerr << "Please provide a valid command." << std::endl;
            continue;
        }
    }
}
