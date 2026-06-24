CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
EXEC = chess
OBJECTS =  board.o pieces.o king.o queen.o rook.o bishop.o knight.o pawn.o empty.o move.o cli.o gui.o window.o scoreboard.o subject.o chess.o controller.o main.o computer.o level1.o level2.o level3.o level4.o level5.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}