RELEASE_FLAGS = -O2
DEBUG_FLAGS = -g

LIB_FLAGS = $(shell pkg-config --cflags --libs allegro-5.0 allegro_main-5.0 allegro_image-5.0 allegro_font-5.0) -lm

HEADERS = game.h
SOURCE = main.c game.c
BINARY = lemmings

all:
	$(CC) $(DEBUG_FLAGS) $(LIB_FLAGS) $(SOURCE) -o $(BINARY) 

release:
	$(CC) $(RELEASE_FLAGS) $(LIB_FLAGS) $(SOURCE) -o $(BINARY)

run: all
	./$(BINARY)
