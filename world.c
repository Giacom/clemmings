
#include "stdio.h"

#include "world.h"

WORLD active_world;


WORLD load_world(const char* filename) {
    ALLEGRO_BITMAP* sprite = al_load_bitmap(filename);
    if (!sprite) {
        printf("Error loading world: %s", filename);
        exit(1);
    }

    int width = al_get_bitmap_width(sprite);
    int height = al_get_bitmap_height(sprite);

    BLOCK_FLAG* collision_map = al_calloc(sizeof(collision_map), (width * height));

    WORLD world = (WORLD) { width, height, sprite, collision_map };
    update_collision_map(&world);
    return world;
}

void destroy_world(WORLD* world) {
    al_destroy_bitmap(world->sprite);
    al_free(world->collision_map);
}

void update_collision_map(WORLD* world) {
    al_lock_bitmap(world->sprite, ALLEGRO_LOCK_READONLY, al_get_bitmap_format(world->sprite));
    for (int x = 0; x < world->width; x++) {
        for (int y = 0; y < world->height; y++) {
            int index = GET_INDEX(world, x, y);
            unsigned char r, g, b, a;
            al_unmap_rgba(al_get_pixel(world->sprite, x, y), &r, &g, &b, &a);
            if (r != 0 && b != 0 && g != 0) {
                world->collision_map[index] |= WORLD_FLAG_COLLISION;
            } else {
                world->collision_map[index] &= ~WORLD_FLAG_COLLISION;
            }
        }
    }
    al_unlock_bitmap(world->sprite);
}

bool is_collision(WORLD* world, int x, int y) {
    return (get_collision_flag(world, x, y) & WORLD_FLAG_COLLISION) != 0;
}

BLOCK_FLAG get_collision_flag(WORLD* world, int x, int y) {
    if (DEBUG) {
        if (world->width <= x || world->height <= y) {
            return 0;
            //printf("Error, attempting to get collision flag that is outside world size.");
            //exit(1);
        }
    }

    int index = GET_INDEX(world, x, y);
    return world->collision_map[index];
}
