RELEASE_FLAGS = -O2 -D DEBUG=0
DEBUG_FLAGS = -g -D DEBUG=1
WARNING_FLAGS = -Wall -Wextra -Werror -Wpedantic -Wshadow -Wcast-qual -Wpointer-arith -Wstrict-prototypes -Wmissing-prototypes

LIB_FLAGS = $(shell pkg-config --cflags --libs allegro-5 allegro_main-5 allegro_image-5 allegro_font-5) -lm

HEADERS = game.h lemming.h world.h
SOURCE = main.c game.c lemming.c world.c
BINARY = lemmings

all:
	$(CC) $(DEBUG_FLAGS) $(WARNING_FLAGS) $(LIB_FLAGS) $(SOURCE) -o $(BINARY) 

release:
	$(CC) $(RELEASE_FLAGS) $(WARNING_FLAGS) $(LIB_FLAGS) $(SOURCE) -o $(BINARY)

run: all
	./$(BINARY)
