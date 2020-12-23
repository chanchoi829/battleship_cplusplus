CC = g++
LD = g++

CFLAGS = -c -pedantic-errors -std=c++14 -Wall
LFLAGS = -pedantic-errors -Wall

OBJS = main.o Game.o Utility.o
PROG = battleship

default: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -o $(PROG)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Game.o: Game.cpp Game.h 
	$(CC) $(CFLAGS) Game.cpp

Utility.o: Utility.cpp Utility.h
	$(CC) $(CFLAGS) Utility.cpp

clean:
	rm -f *.o

real_clean:
	rm -f *.o
	rm -f *exe
