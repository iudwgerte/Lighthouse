CC = g++
LIBS = -lpthread
SRC = src/*.cpp
EXE = Lighthouse

WFLAGS = -std=c++17 -Wall -Wextra -Wshadow -pedantic
CFLAGS = -O3 -DNDEBUG $(WFLAGS) -flto -march=native
DFLAGS = -O0 $(WFLAGS) -fsanitize=address -fsanitize=undefined

all:
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(EXE)

debug:
	$(CC) $(DFLAGS) $(SRC) $(LIBS) -o $(EXE)
