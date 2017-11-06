#ifndef WORLD_H
#define WORLD_H

#include "allegro5/allegro.h"

#define WORLD_FLAG_COLLISION (1 << 2)
#define WORLD_FLAG_DEATH (2 << 2)
#define GET_INDEX(WORLD, X, Y) ((Y * WORLD->width) + X)


typedef uint8_t BLOCK_FLAG;

typedef struct {
    int width;
    int height;
    ALLEGRO_BITMAP* sprite;
    BLOCK_FLAG* collision_map;
} WORLD;

extern WORLD active_world;

WORLD load_world(const char* filename);
void destroy_world(WORLD* world);
void update_collision_map(WORLD* world);
bool is_collision(WORLD* world, int x, int y);
BLOCK_FLAG get_collision_flag(WORLD* world, int x, int y);

#endif // WORLD_H
