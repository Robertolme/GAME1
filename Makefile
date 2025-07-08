CC=gcc
CFLAGS=-Wall -std=c99
LIBS=-lraylib -lm -ldl -lpthread -lGL -lrt -lX11

SRC=src/main.c src/player.c src/enemy.c src/map.c
OUT=rpg

all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LIBS)
