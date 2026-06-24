# ♟ Chess Game — C++ OOP Project

C++로 **A부터 Z까지 직접 구현한 체스 게임**입니다. CLI(터미널)와 GUI(X11) 두 가지 화면을 지원하고, 사람 대 사람·사람 대 컴퓨터·컴퓨터 대 컴퓨터 대전이 가능하며, 캐슬링·앙파상·프로모션 같은 체스의 특수 규칙까지 모두 구현했습니다.

이 프로젝트의 목적은 단순히 "돌아가는 체스"를 만드는 것이 아니라, **객체지향 설계 원칙과 디자인 패턴, 그리고 C++의 메모리 관리(스마트 포인터/RAII)를 실제 규모 있는 코드로 체득하는 것**이었습니다. 아래 문서는 "무엇을 중점으로 어떤 구조로 만들었는가"를 자세히 설명합니다.

> 언어/환경: **C++14**, **Linux**, GUI는 **X11(Xlib)**. 빌드는 `g++` + `make`.

---

## 목차

1. [무엇을 만들었나 — 한눈에](#1-무엇을-만들었나--한눈에)
2. [중점 1 — MVC 아키텍처](#2-중점-1--mvc-아키텍처)
3. [중점 2 — 세 가지 디자인 패턴](#3-중점-2--세-가지-디자인-패턴)
4. [중점 3 — 메모리 설계 (가장 까다로웠던 부분)](#4-중점-3--메모리-설계-가장-까다로웠던-부분)
5. [좌표 모델 — Position enum 인코딩](#5-좌표-모델--position-enum-인코딩)
6. [구현한 기능](#6-구현한-기능)
7. [컴퓨터 AI — 난이도 4단계](#7-컴퓨터-ai--난이도-4단계)
8. [디렉토리 구조](#8-디렉토리-구조)
9. [빌드 및 실행](#9-빌드-및-실행)
10. [명령어 레퍼런스](#10-명령어-레퍼런스)

---

## 1. 무엇을 만들었나 — 한눈에

| 항목 | 내용 |
|---|---|
| **규모** | 약 3,400줄, 클래스 25개 (C++ 헤더 24 / 구현 23) |
| **출력 방식** | CLI(유니코드 체스 기호) + GUI(X11 픽셀 드로잉) **동시** 출력 |
| **대전 모드** | human vs human / human vs computer / computer vs computer |
| **체스 규칙** | 6종 기물의 합법수, 체크·체크메이트·스테일메이트, 캐슬링, 앙파상, 폰 프로모션, undo |
| **AI** | 난이도 Level 1~4 (랜덤 → 캡처/체크 선호 → 회피 → 종합) |
| **부가 기능** | 커스텀 setup 모드, 점수판(ScoreBoard), 연속 대국 |

핵심 설계 철학은 문서(`document/document.md`)에 적은 대로 **높은 응집도(high cohesion) · 낮은 결합도(low coupling) · 변경 내성(resilience to change)** 입니다. 이를 위해 아래 세 가지를 중점적으로 설계했습니다.

---

## 2. 중점 1 — MVC 아키텍처

이 프로젝트의 뼈대는 **MVC(Model–View–Controller)** 패턴입니다. "게임 로직", "화면 표시", "사용자 입력 처리"라는 세 가지 관심사를 철저히 분리해서, **한쪽을 바꿔도 다른 쪽이 영향받지 않도록** 만들었습니다.

```
                ┌──────────────────────────────────────────────┐
   사용자 입력  │                  main.cc                       │
   ───────────► │           (입력 파싱 / 게임 루프)               │
                └───────────────┬───────────────────────────────┘
                                │ 명령 위임
                                ▼
                  ┌──────────────────────────┐
                  │   Controller  (제어자)    │   move / undo / resign
                  │   controller.{h,cc}       │   pawnPromote / computerMove
                  └────────────┬──────────────┘
                               │ movePiece(...) 호출
                               ▼
   ┌───────────────────────────────────────────────────────────┐
   │                       MODEL                                 │
   │  Chess ── 게임 상태·규칙의 중심 (chess.cc, 690줄)            │
   │   ├─ Board       8×8 격자, 기물 배치                        │
   │   ├─ Piece들     King/Queen/Rook/Bishop/Knight/Pawn/Empty  │
   │   ├─ Move        한 수의 정보 (출발/도착/잡힌 기물/프로모션) │
   │   └─ ScoreBoard  점수 기록                                  │
   └───────────────────────────────┬───────────────────────────┘
                                    │ 상태가 바뀌면 통지 (Observer)
                                    ▼
              ┌───────────────────────────────────┐
              │              VIEW                   │
              │   Cli  ── 터미널 출력 (cli.cc)      │
              │   Gui  ── X11 그래픽 출력 (gui.cc)  │
              └───────────────────────────────────┘
```

| 역할 | 담당 클래스 | 책임 |
|---|---|---|
| **Model** | `Chess`, `Board`, `Piece`, `Move`, `ScoreBoard` | 게임 데이터와 규칙. **화면을 전혀 모름** |
| **View** | `Cli`, `Gui` (`Observer` 파생) | 보드를 그리기만 함. **로직을 모름** |
| **Controller** | `Controller` | 입력을 Model 호출로 번역 |

이 분리 덕분에, 예를 들어 **GUI 표현을 통째로 바꿔도 게임 로직(`Chess`)은 한 줄도 건드릴 필요가 없습니다.** 새 화면을 추가하고 싶으면 `Observer`를 상속한 클래스를 하나 더 만들어 `attach`만 하면 됩니다.

---

## 3. 중점 2 — 세 가지 디자인 패턴

배운 디자인 패턴을 실제로 코드에 녹였습니다.

### (1) Observer 패턴 — 화면 자동 갱신
`subject.h` / `observer.h`

`Chess`는 `Subject`를 상속하고, `Cli`/`Gui`는 `Observer`를 상속합니다. 보드 상태가 바뀌면 `Chess`가 등록된 모든 화면에 **한 번에 통지**합니다.

```cpp
// subject.cc — Model은 어떤 화면이 붙어있는지 구체적으로 몰라도 됨
void Subject::drawBoard(...) {
    for (auto ob : observers) {   // 등록된 모든 Observer에게
        ob->drawBoard(...);        // "다시 그려라" 통지
    }
}
```

`Chess::movePiece()`가 끝날 때 `drawBoard()`를 호출하면 → CLI와 GUI가 **동시에** 자동으로 갱신됩니다. Model이 View를 직접 알 필요가 없으므로 결합도가 낮습니다.

### (2) Strategy 패턴 — 교체 가능한 AI
`computer.h` + `level1.cc` ~ `level4.cc`

`Computer`라는 추상 인터페이스(`virtual bool makeMove() = 0`) 하나에, 난이도별 알고리즘을 `LevelOne`~`LevelFour`로 구현해 **런타임에 갈아끼웁니다.**

```cpp
// main.cc — 입력에 따라 다른 전략(알고리즘) 객체를 주입
if (player1 == "computer3")
    computerOne = std::make_shared<LevelThree>(chess, true, board);
```

게임은 `Computer`라는 추상 타입만 알고, 실제로 Level 몇이 동작하는지는 신경 쓰지 않습니다. 새 난이도를 추가하려면 새 subclass만 만들면 됩니다.

### (3) 상속 + 다형성 — 기물의 규칙 분리
`pieces.h` + 7종 기물 클래스

`Piece` 추상 base에서 각 기물(`King`, `Queen`, `Rook`, `Bishop`, `Knight`, `Pawn`)이 파생됩니다. **빈 칸까지 `Empty` 객체**로 두어, 보드의 모든 칸을 동일한 인터페이스(`getPiece()`, `getFirstMove()`, `getValue()` 등)로 다룹니다.

```cpp
class Piece {                       // 추상 base
    virtual char getPiece() const = 0;
    virtual bool getFirstMove() const { return false; }  // 캐슬링용
    virtual bool getEnPassant() const { return false; }  // 앙파상용
    virtual int  getValue() const { return 0; }          // AI 평가용
    // ...
};
```

각 기물별 고유 속성(폰의 첫 이동 여부, 룩/킹의 캐슬링 자격 등)을 가상 함수로 표현해, 공통 코드는 공유하고 차이만 override합니다.

---

## 4. 중점 3 — 메모리 설계 (가장 까다로웠던 부분)

이 프로젝트에서 가장 신경 쓴 부분이 **메모리 관리**입니다. `new`/`delete`로 수동 관리하는 대신, **`std::shared_ptr`(스마트 포인터)와 RAII**로 객체 수명을 자동 관리하도록 설계했습니다.

### 보드 — 포인터의 2차원 격자
`board.h`

```cpp
class Board {
    std::shared_ptr<Piece> bd[8][8];   // 각 칸이 '기물 객체를 가리키는 포인터'
};
```

보드의 각 칸은 기물 객체를 **소유하는 포인터**입니다. 기물을 옮긴다는 것은 **객체를 복사하는 게 아니라 포인터를 옮기는 것**입니다.

```cpp
// board.cc — 이동은 포인터 재배치
bd[new_row][new_col] = bd[org_row][org_col];   // 포인터만 옮기고
remove(org_posn);                               // 원래 칸은 빈 칸으로
```

### Undo 스택 — "잡힌 기물을 되살리기"
`chess.h` / `move.h`

가장 어려웠던 설계 포인트입니다. 무르기(undo)를 구현하려면 **이미 잡혀 사라진 기물 객체가 메모리에 살아있어야** 합니다. 이를 위해:

```cpp
class Chess {
    std::vector<std::shared_ptr<Move>> moves;  // 모든 수를 기록한 스택
};

class Move {
    std::shared_ptr<Piece> captured;   // 이 수에서 잡힌 기물을 '소유'
    std::shared_ptr<Piece> promoted;   // 프로모션 전 기물도 '소유'
};
```

`Move` 객체가 잡힌 기물을 `shared_ptr`로 들고 있기 때문에, 보드에서 사라져도 객체는 해제되지 않습니다. `undo` 시 그 포인터를 보드에 다시 꽂으면 **죽었던 기물이 정확히 그대로 복원**됩니다. 캐슬링·앙파상·프로모션 각각에 대한 전용 undo 함수(`undoCastling`, `undoEnPassant`, `undoPromoted`)도 구현했습니다.

### 소유권 그래프

```
Controller ──owns──► Chess ──owns──► Board ──owns──► Piece[8][8]
                       │  └──owns──► ScoreBoard
                       │  └──owns──► vector<Move> ──owns──► 잡힌 Piece들
                       │
                       └──owns──► Cli / Gui (Observer)
                                    └─ Chess를 '비소유' 참조 (화면→모델 단방향 관찰)
```

`shared_ptr`로 소유권을 명확히 하되, **화면(Observer)은 모델(Subject)을 소유하지 않도록** 설계해 객체 수명이 한 방향으로 흐르게 했습니다.

---

## 5. 좌표 모델 — Position enum 인코딩
`position.h`

체스 칸을 `int`나 좌표쌍 대신 **의미가 드러나는 enum**으로 표현하고, **10진수 인코딩**을 써서 행/열 변환을 단순화했습니다.

```cpp
enum Position {
    a8 = 0,  b8, c8, ... h8,   //  0 ~  7  (8번째 행)
    a7 = 10, b7, c7, ... h7,   // 10 ~ 17  (7번째 행)
    ...
    a1 = 70, b1, c1, ... h1    // 70 ~ 77  (1번째 행)
};
```

`value = row × 10 + col` 규칙이라:

```cpp
int row = posn / 10;   // 행
int col = posn % 10;   // 열
```

코드 어디서나 `posn/10`, `posn%10`으로 즉시 좌표를 얻을 수 있어, 기물 이동 거리 계산(`±10` 수직, `±1` 수평, `±9`/`±11` 대각)이 산술 한 줄로 표현됩니다.

---

## 6. 구현한 기능

- ✅ **6종 기물의 합법수 판정** — 각 기물의 이동/캡처 규칙 (`Chess::validKing`, `validQueen`, …)
- ✅ **체크 / 체크메이트 / 스테일메이트** 판정
- ✅ **캐슬링** (킹사이드/퀸사이드, 자격·경로 안전성 검사 포함)
- ✅ **앙파상** (en passant)
- ✅ **폰 프로모션** (원하는 기물로 승격, 상대 기물로 승격 방지 검증)
- ✅ **무르기(undo)** — 특수 수까지 정확히 복원
- ✅ **resign(기권)** 및 **점수판** (승 1점, 무승부 0.5점)
- ✅ **커스텀 setup 모드** — 임의 국면 배치 후 유효성 검사(킹 1개, 폰 위치, 체크 여부)
- ✅ **연속 대국** — 게임 종료 후 재시작

---

## 7. 컴퓨터 AI — 난이도 4단계

Strategy 패턴으로 구현된 4개 난이도. 모두 `Computer` 인터페이스의 `makeMove()`를 override합니다.

| 레벨 | 클래스 | 전략 |
|---|---|---|
| **Level 1** | `LevelOne` | 합법수 중 **무작위** 선택 |
| **Level 2** | `LevelTwo` | **캡처와 체크를 선호** (상대 기물을 잡거나 체크를 거는 수 우선) |
| **Level 3** | `LevelThree` | Level 2 + **위협받는 기물 회피** (`underAttack` 판정) |
| **Level 4** | `LevelFour` | 위 요소들을 **종합**한 가장 강한 수 선택 |

---

## 8. 디렉토리 구조

```
chess/
├── README.md              # 이 문서
├── document/
│   ├── document.md        # 설계 보고서 (소개·UML·설계 결정·결론)
│   └── uml.png            # 전체 클래스 UML 다이어그램
├── src/
│   ├── main.cc            # 진입점: 입력 파싱 + 게임 루프
│   ├── Makefile           # 빌드 스크립트 (g++, C++14, -lX11)
│   │
│   ├── chess.{h,cc}       # ★ Model 중심: 규칙·체크·이동·undo
│   ├── board.{h,cc}       # 8×8 보드 (shared_ptr 격자)
│   ├── move.{h,cc}        # 한 수의 정보
│   ├── scoreboard.{h,cc}  # 점수판
│   ├── position.h         # 칸 좌표 enum
│   │
│   ├── pieces.{h,cc}      # 기물 추상 base
│   ├── king/queen/rook/bishop/knight/pawn.{h,cc}   # 6종 기물
│   ├── empty.{h,cc}       # 빈 칸 객체
│   │
│   ├── subject.{h,cc}     # Observer 패턴: 통지 주체
│   ├── observer.h         # Observer 패턴: 관찰자 인터페이스
│   ├── cli.{h,cc}         # View: 터미널 출력
│   ├── gui.{h,cc}         # View: X11 그래픽 출력
│   ├── window.{h,cc}      # X11 윈도우 래퍼
│   │
│   ├── controller.{h,cc}  # Controller
│   ├── computer.{h,cc}    # AI 추상 base (Strategy)
│   └── level1~4.{h,cc}    # AI 난이도 구현
│
└── test/                  # 시나리오 입력 파일 (*.in)
    ├── test1~3.in, check.in, stalemate.in,
    ├── castling.in, enpassant.in, pawnp.in, computer.in
```

### 클래스 UML

![UML 다이어그램](document/uml.png)

---

## 9. 빌드 및 실행

> X11(Xlib) 개발 라이브러리가 필요합니다 (Linux 기준).

```bash
cd src
make            # chess 실행 파일 생성
./chess         # 게임 시작 (표준 입력으로 명령)
```

테스트 시나리오 실행:

```bash
./chess < ../test/test1.in
```

> **참고:** GUI는 X11에 의존하므로 X11 환경(Linux 또는 XQuartz)이 필요합니다. CLI만으로도 게임의 모든 기능을 사용할 수 있습니다.

---

## 10. 명령어 레퍼런스

게임은 표준 입력으로 명령을 받습니다.

| 명령 | 설명 |
|---|---|
| `game <백> <흑>` | 대국 시작. 플레이어는 `human` 또는 `computer1`~`computer4` |
| `move <출발> <도착>` | 기물 이동 (예: `move e2 e4`). 프로모션 시 기물 문자 추가 (예: `move e7 e8 Q`) |
| `move` | (컴퓨터 차례) 컴퓨터가 수를 둠 |
| `undo` | 직전 수 무르기 |
| `resign` | 기권 |
| `setup` | 커스텀 국면 배치 모드 진입 |
| `+ <기물> <칸>` | (setup) 기물 배치 (예: `+ K e1`) |
| `- <칸>` | (setup) 기물 제거 |
| `= <색>` | (setup) 시작 색 지정 (`White`/`Black`) |
| `done` | (setup) 배치 완료 (유효성 검사 통과 시) |
| `exit` | 프로그램 종료 |

**예시 — 사람 대 컴퓨터(Level 3):**
```
game human computer3
move e2 e4
move          # 컴퓨터(흑)가 응수
move g1 f3
move
...
```

---

## 설계 요약

이 프로젝트는 단순한 체스 구현을 넘어, 다음을 **실제 코드 규모로 학습·적용**한 결과물입니다.

- **MVC 패턴**으로 로직·화면·제어를 분리해 변경에 강한 구조를 만들고,
- **Observer / Strategy / 상속·다형성** 세 가지 디자인 패턴으로 확장성과 재사용성을 확보했으며,
- **`shared_ptr` 기반 메모리 설계**로 수동 메모리 관리 없이 복잡한 객체 수명(특히 undo를 위한 "죽은 기물 보존")을 안전하게 다뤘습니다.
