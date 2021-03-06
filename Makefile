CC = g++

CFLAGS = -pedantic-errors -Wall -g

OBJS = main.o Computer.o Display.o Engine.o Grid.o Player.o Ship.o
PROG = battleship

default: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG) -pthread -lX11 -L/usr/lib -ljpeg -lpng -ltiff

main.o: main.cpp Engine.h
	$(CC) $(CFLAGS) -c main.cpp

Computer.o: Computer.cpp Computer.h Engine.h Ship.h
	$(CC) $(CFLAGS) -c Computer.cpp

Display.o: Display.cpp Display.h Engine.h Grid.h Ship.h
	$(CC) $(CFLAGS) -c Display.cpp

Engine.o: Engine.cpp Engine.h Computer.h Display.h Grid.h Player.h Ship.h
	$(CC) $(CFLAGS) -c Engine.cpp

Grid.o: Grid.cpp Grid.h Ship.h
	$(CC) $(CFLAGS) -c Grid.cpp

Player.o: Player.cpp Player.h Engine.h Ship.h
	$(CC) $(CFLAGS) -c Player.cpp

Ship.o: Ship.cpp Ship.h
	$(CC) $(CFLAGS) -c Ship.cpp

clean:
	rm -f *.o

real_clean:
	rm -f *.o
	rm -f *exe
