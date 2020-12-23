CC = g++
LD = g++

CFLAGS = -c -pedantic-errors -std=c++14 -Wall
LFLAGS = -pedantic-errors -Wall

OBJS = main.o Model.o View.o Controller.o Ship.o Utility.o
PROG = battleship

default: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -o $(PROG)

main.o: main.cpp Controller.h
	$(CC) $(CFLAGS) main.cpp

Model.o: Model.cpp Model.h 
	$(CC) $(CFLAGS) Model.cpp

View.o: View.cpp View.h
	$(CC) $(CFLAGS) View.cpp

Controller.o: Controller.cpp Controller.h 
	$(CC) $(CFLAGS) Controller.cpp

Ship.o: Ship.cpp Ship.h
	$(CC) $(CFLAGS) Ship.cpp

Utility.o: Utility.cpp Utility.h
	$(CC) $(CFLAGS) Utility.cpp

clean:
	rm -f *.o

real_clean:
	rm -f *.o
	rm -f *exe
