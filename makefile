ALESTI_TRABALHO = app
CFLAGS = -c -std=c++11

all:									${ALESTI_TRABALHO}

${ALESTI_TRABALHO}:						main.o wordTree.o charNode.o
										g++ main.o wordTree.o charNode.o -o ${ALESTI_TRABALHO}

main.o:									main.cpp
										g++ ${CFLAGS} main.cpp

wordTree.o:								wordTree.cpp wordTree.hpp
										g++ ${CFLAGS} wordTree.cpp

charNode.o:								charNode.cpp charNode.hpp
										g++ ${CFLAGS} charNode.cpp

run:									${ALESTI_TRABALHO}
										./${ALESTI_TRABALHO}

clean:									
										rm -f main.o ${ALESTI_TRABALHO}