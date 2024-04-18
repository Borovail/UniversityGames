# variables
CC=gcc
CFLAGS=-std=c11 -Wall -Iinclude `sdl2-config --cflags`
LDLIBS=`sdl2-config --libs` -lm -lcurses 
EXECUTABLE=SnowMania
OBJ=program.o LevelsControl.o Objects.o

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(OBJ) $(LDLIBS) -o $(EXECUTABLE)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@




clean:
	rm -f src/*.o *.o 