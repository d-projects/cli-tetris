CXX = g++
CXXFLAGS = -g -Wall -MMD
OBJECTS = Command.o GameController.o Block.o Board.o View.o TextView.o LevelStrategy.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean:
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}