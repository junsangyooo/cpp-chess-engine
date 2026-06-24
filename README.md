# ♟ Chess Game — C++ OOP Project

A **chess game implemented from scratch in C++ — from A to Z**. It supports two display modes, CLI (terminal) and GUI (X11), allows human vs. human / human vs. computer / computer vs. computer matches, and implements all of chess's special rules including castling, en passant, and promotion.

The goal of this project was not merely to make a "working chess game," but to **internalize object-oriented design principles, design patterns, and C++ memory management (smart pointers / RAII) through a real, sizeable codebase**. The document below explains in detail "what was emphasized and with what structure it was built."

> Language/Environment: **C++14**, **Linux**, GUI via **X11 (Xlib)**. Built with `g++` + `make`.

---

## Table of Contents

1. [What Was Built — At a Glance](#1-what-was-built--at-a-glance)
2. [Focus 1 — MVC Architecture](#2-focus-1--mvc-architecture)
3. [Focus 2 — Three Design Patterns](#3-focus-2--three-design-patterns)
4. [Focus 3 — Memory Design (the trickiest part)](#4-focus-3--memory-design-the-trickiest-part)
5. [Coordinate Model — Position enum Encoding](#5-coordinate-model--position-enum-encoding)
6. [Implemented Features](#6-implemented-features)
7. [Computer AI — 5 Difficulty Levels](#7-computer-ai--5-difficulty-levels)
8. [Directory Structure](#8-directory-structure)
9. [Build & Run](#9-build--run)
10. [Command Reference](#10-command-reference)

---

## 1. What Was Built — At a Glance

| Item | Details |
|---|---|
| **Scale** | ~3,720 lines, ~25 classes (25 C++ headers / 24 implementation files) |
| **Output** | CLI (Unicode chess symbols) + GUI (X11 pixel drawing) **simultaneously** |
| **Match modes** | human vs human / human vs computer / computer vs computer |
| **Chess rules** | Legal moves for all 6 piece types, check / checkmate / stalemate, castling, en passant, pawn promotion, undo |
| **AI** | Difficulty Levels 1–5 (random → capture/check → evasion → negamax search → negamax + positional evaluation) |
| **Extras** | Custom setup mode, ScoreBoard, consecutive games |

The core design philosophy, as written in the document (`document/document.md`), is **high cohesion · low coupling · resilience to change**. To achieve this, the following three areas were the focus of the design.

---

## 2. Focus 1 — MVC Architecture

The backbone of this project is the **MVC (Model–View–Controller)** pattern. The three concerns of "game logic," "screen display," and "user input handling" are strictly separated so that **changing one side does not affect the others**.

```
                ┌──────────────────────────────────────────────┐
   user input   │                  main.cc                       │
   ───────────► │        (input parsing / game loop)             │
                └───────────────┬───────────────────────────────┘
                                │ delegate command
                                ▼
                  ┌──────────────────────────┐
                  │   Controller              │   move / undo / resign
                  │   controller.{h,cc}       │   pawnPromote / computerMove
                  └────────────┬──────────────┘
                               │ calls movePiece(...)
                               ▼
   ┌───────────────────────────────────────────────────────────┐
   │                       MODEL                                 │
   │  Chess ── center of game state & rules (chess.cc, 692 lines)│
   │   ├─ Board       8×8 grid, piece placement                 │
   │   ├─ Pieces      King/Queen/Rook/Bishop/Knight/Pawn/Empty  │
   │   ├─ Move        info for one move (from/to/captured/promo) │
   │   └─ ScoreBoard  score tracking                            │
   └───────────────────────────────┬───────────────────────────┘
                                    │ notifies on state change (Observer)
                                    ▼
              ┌───────────────────────────────────┐
              │              VIEW                   │
              │   Cli  ── terminal output (cli.cc) │
              │   Gui  ── X11 graphics (gui.cc)    │
              └───────────────────────────────────┘
```

| Role | Classes | Responsibility |
|---|---|---|
| **Model** | `Chess`, `Board`, `Piece`, `Move`, `ScoreBoard` | Game data and rules. **Knows nothing about the screen** |
| **View** | `Cli`, `Gui` (derived from `Observer`) | Only draws the board. **Knows nothing about logic** |
| **Controller** | `Controller` | Translates input into Model calls |

Thanks to this separation, for example, **you can completely replace the GUI representation without touching a single line of the game logic (`Chess`)**. To add a new display, you just create another class deriving from `Observer` and `attach` it.

---

## 3. Focus 2 — Three Design Patterns

The design patterns I learned were woven into the actual code.

### (1) Observer Pattern — Automatic Screen Refresh
`subject.h` / `observer.h`

`Chess` derives from `Subject`, and `Cli`/`Gui` derive from `Observer`. When the board state changes, `Chess` **notifies all registered displays at once**.

```cpp
// subject.cc — the Model doesn't need to know concretely which displays are attached
void Subject::drawBoard(...) {
    for (auto ob : observers) {   // for every registered Observer
        ob->drawBoard(...);        // notify "redraw"
    }
}
```

When `Chess::movePiece()` finishes and calls `drawBoard()` → the CLI and GUI both refresh automatically and **simultaneously**. Since the Model doesn't need to know about the View directly, coupling stays low.

### (2) Strategy Pattern — Swappable AI
`computer.h` + `level1.cc` ~ `level5.cc`

A single abstract interface, `Computer` (`virtual bool makeMove() = 0`), has difficulty-specific algorithms implemented as `LevelOne`~`LevelFive`, **swapped in at runtime**.

```cpp
// main.cc — inject a different strategy (algorithm) object depending on input
if (player1 == "computer3")
    computerOne = std::make_shared<LevelThree>(chess, true, board);
```

The game only knows the abstract type `Computer` and doesn't care which Level is actually running. To add a new difficulty, you just create a new subclass.

### (3) Inheritance + Polymorphism — Per-Piece Rule Separation
`pieces.h` + 7 piece classes

Each piece (`King`, `Queen`, `Rook`, `Bishop`, `Knight`, `Pawn`) derives from the abstract base `Piece`. **Even empty squares are `Empty` objects**, so every square on the board is handled through the same interface (`getPiece()`, `getFirstMove()`, `getValue()`, etc.).

```cpp
class Piece {                       // abstract base
    virtual char getPiece() const = 0;
    virtual bool getFirstMove() const { return false; }  // for castling
    virtual bool getEnPassant() const { return false; }  // for en passant
    virtual int  getValue() const { return 0; }          // for AI evaluation
    // ...
};
```

Each piece's unique attributes (whether a pawn has made its first move, a rook's/king's castling eligibility, etc.) are expressed via virtual functions, so common code is shared and only the differences are overridden.

---

## 4. Focus 3 — Memory Design (the trickiest part)

The part I paid the most attention to in this project was **memory management**. Instead of managing manually with `new`/`delete`, object lifetimes are designed to be managed automatically with **`std::shared_ptr` (smart pointers) and RAII**.

### The Board — a 2D Grid of Pointers
`board.h`

```cpp
class Board {
    std::shared_ptr<Piece> bd[8][8];   // each square is a 'pointer to a piece object'
};
```

Each square of the board is a pointer that **owns** a piece object. Moving a piece means **not copying the object, but moving the pointer**.

```cpp
// board.cc — a move is a pointer relocation
bd[new_row][new_col] = bd[org_row][org_col];   // move only the pointer,
remove(org_posn);                               // and clear the original square
```

### The Undo Stack — "Reviving Captured Pieces"
`chess.h` / `move.h`

This was the hardest design point. To implement undo, **a piece object that was already captured and removed must stay alive in memory**. For that:

```cpp
class Chess {
    std::vector<std::shared_ptr<Move>> moves;  // a stack recording every move
};

class Move {
    std::shared_ptr<Piece> captured;   // 'owns' the piece captured by this move
    std::shared_ptr<Piece> promoted;   // also 'owns' the pre-promotion piece
};
```

Because the `Move` object holds the captured piece via `shared_ptr`, the object isn't deallocated even after it disappears from the board. On `undo`, plugging that pointer back into the board **restores the dead piece exactly as it was**. Dedicated undo functions for castling, en passant, and promotion (`undoCastling`, `undoEnPassant`, `undoPromoted`) were also implemented.

### Ownership Graph

```
Controller ──owns──► Chess ──owns──► Board ──owns──► Piece[8][8]
                       │  └──owns──► ScoreBoard
                       │  └──owns──► vector<Move> ──owns──► captured Pieces
                       │
                       └──owns──► Cli / Gui (Observer)
                                    └─ holds a 'non-owning' reference to Chess (view→model, one-way observation)
```

Ownership is made explicit with `shared_ptr`, while **the View (Observer) is designed not to own the Model (Subject)**, so object lifetimes flow in a single direction.

---

## 5. Coordinate Model — Position enum Encoding
`position.h`

Chess squares are represented with a **meaningful enum** instead of raw `int`s or coordinate pairs, and a **base-10 encoding** is used to simplify row/column conversion.

```cpp
enum Position {
    a8 = 0,  b8, c8, ... h8,   //  0 ~  7  (8th rank)
    a7 = 10, b7, c7, ... h7,   // 10 ~ 17  (7th rank)
    ...
    a1 = 70, b1, c1, ... h1    // 70 ~ 77  (1st rank)
};
```

Because the rule is `value = row × 10 + col`:

```cpp
int row = posn / 10;   // row
int col = posn % 10;   // column
```

Anywhere in the code you can instantly get coordinates with `posn/10` and `posn%10`, so piece-move distance calculations (`±10` vertical, `±1` horizontal, `±9`/`±11` diagonal) are expressed in a single arithmetic line.

---

## 6. Implemented Features

- ✅ **Legal-move validation for all 6 piece types** — movement/capture rules per piece (`Chess::validKing`, `validQueen`, …)
- ✅ **Check / checkmate / stalemate** detection
- ✅ **Castling** (kingside/queenside, including eligibility & path-safety checks)
- ✅ **En passant**
- ✅ **Pawn promotion** (promote to any piece, with validation preventing promotion to an opponent's piece)
- ✅ **Undo** — restores even special moves exactly
- ✅ **Resign** and a **scoreboard** (win = 1 point, draw = 0.5 points)
- ✅ **Custom setup mode** — place an arbitrary position, then validate it (exactly one king, pawn placement, no check)
- ✅ **Consecutive games** — restart after a game ends

---

## 7. Computer AI — 5 Difficulty Levels

Five difficulty levels implemented via the Strategy pattern. All override `makeMove()` from the `Computer` interface. Levels 1–3 are **1-ply heuristics** (rule-based selection looking only one move ahead), while Levels 4–5 are **search-based** AIs that perform look-ahead.

| Level | Class | Strategy |
|---|---|---|
| **Level 1** | `LevelOne` | **Random** selection among legal moves |
| **Level 2** | `LevelTwo` | **Prefers captures and checks** (favors moves that capture an opponent's piece or give check) |
| **Level 3** | `LevelThree` | Level 2 + **avoids threatened pieces** (`underAttack` check) |
| **Level 4** | `LevelFour` | **Negamax + alpha-beta pruning (depth 2)** + material evaluation — looks ahead to the opponent's best reply |
| **Level 5** | `LevelFive` | **Negamax + alpha-beta (depth 3)** + material + a **piece-square table** (central control) + pawn-advancement evaluation — the strongest |

> **Design principle for Levels 4 & 5:** They use the standard chess-AI algorithm, **negamax (a minimax variant) + alpha-beta pruning**. The key point is that the engine was left entirely untouched — the hypothetical look-ahead is implemented by recursively wrapping the same `Board::move`/`undo` pattern that Levels 2 & 3 already used, legality is checked through the existing `Chess::validMove`, and only the final committed move goes through `Chess::movePiece`. The evaluation function sums each piece's `getValue()` (King 10 · Q 9 · R 5 · B/N 3 · P 1).

---

## 8. Directory Structure

```
chess/
├── README.md              # this document
├── document/
│   ├── document.md        # design report (intro · UML · design decisions · conclusion)
│   └── uml.png            # full class UML diagram
├── src/
│   ├── main.cc            # entry point: input parsing + game loop
│   ├── Makefile           # build script (g++, C++14, -lX11)
│   │
│   ├── chess.{h,cc}       # ★ Model core: rules · check · movement · undo
│   ├── board.{h,cc}       # 8×8 board (shared_ptr grid)
│   ├── move.{h,cc}        # info for one move
│   ├── scoreboard.{h,cc}  # scoreboard
│   ├── position.h         # square-coordinate enum
│   │
│   ├── pieces.{h,cc}      # abstract piece base
│   ├── king/queen/rook/bishop/knight/pawn.{h,cc}   # 6 piece types
│   ├── empty.{h,cc}       # empty-square object
│   │
│   ├── subject.{h,cc}     # Observer pattern: notifying subject
│   ├── observer.h         # Observer pattern: observer interface
│   ├── cli.{h,cc}         # View: terminal output
│   ├── gui.{h,cc}         # View: X11 graphics output
│   ├── window.{h,cc}      # X11 window wrapper
│   │
│   ├── controller.{h,cc}  # Controller
│   ├── computer.{h,cc}    # AI abstract base (Strategy)
│   └── level1~5.{h,cc}    # AI difficulty implementations (1-3: heuristics, 4-5: negamax search)
│
└── test/                  # scenario input files (*.in)
    ├── test1~3.in, check.in, stalemate.in,
    ├── castling.in, enpassant.in, pawnp.in, computer.in
```

### Class UML

![UML diagram](document/uml.png)

---

## 9. Build & Run

> The X11 (Xlib) development library is required (on Linux).

```bash
cd src
make            # produces the chess executable
./chess         # start the game (commands via standard input)
```

Run a test scenario:

```bash
./chess < ../test/test1.in
```

> **Note:** The GUI depends on X11, so an X11 environment (Linux or XQuartz) is required. All game features are fully usable with the CLI alone.

---

## 10. Command Reference

The game takes commands from standard input.

| Command | Description |
|---|---|
| `game <white> <black>` | Start a match. Each player is `human` or `computer1`~`computer5` |
| `move <from> <to>` | Move a piece (e.g. `move e2 e4`). For promotion, append the piece letter (e.g. `move e7 e8 Q`) |
| `move` | (computer's turn) the computer makes a move |
| `undo` | Undo the previous move |
| `resign` | Resign |
| `setup` | Enter custom-position setup mode |
| `+ <piece> <square>` | (setup) place a piece (e.g. `+ K e1`) |
| `- <square>` | (setup) remove a piece |
| `= <color>` | (setup) set the starting color (`White`/`Black`) |
| `done` | (setup) finish placement (if validation passes) |
| `exit` | Quit the program |

**Example — human vs. computer (Level 3):**
```
game human computer3
move e2 e4
move          # computer (black) replies
move g1 f3
move
...
```

---

## Design Summary

This project goes beyond a simple chess implementation; it is the result of **learning and applying the following at the scale of real code**:

- **The MVC pattern** separates logic, display, and control to create a structure resilient to change;
- **Three design patterns — Observer / Strategy / inheritance & polymorphism —** secure extensibility and reusability;
- **A `shared_ptr`-based memory design** safely handles complex object lifetimes (especially "preserving dead pieces" for undo) without manual memory management.
