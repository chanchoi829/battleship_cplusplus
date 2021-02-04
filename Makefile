CC = g++
LD = g++

CFLAGS = -c -pedantic-errors -std=c++14 -Wall
LFLAGS = -pedantic-errors -Wall

OBJS = main.o Computer.o Display.o Engine.o Grid.o Player.o Ship.o Utility.o
PROG = battleship

default: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -pthread -o $(PROG)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Computer.o: Computer.cpp Computer.h
	$(CC) $(CFLAGS) Computer.cpp

Display.o: Display.cpp Display.h
	$(CC) $(CFLAGS) Display.cpp

Engine.o: Engine.cpp Engine.h 
	$(CC) $(CFLAGS) Engine.cpp

Grid.o: Grid.cpp Grid.h
	$(CC) $(CFLAGS) Grid.cpp

Player.o: Player.cpp Player.h
	$(CC) $(CFLAGS) Player.cpp

Ship.o: Ship.cpp Ship.h
	$(CC) $(CFLAGS) Ship.cpp

Utility.o: Utility.cpp Utility.h
	$(CC) $(CFLAGS) Utility.cpp

clean:
	rm -f *.o

real_clean:
	rm -f *.o
	rm -f *exe
