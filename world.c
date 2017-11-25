
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

    WORLD world = (WORLD) { width, height, sprite, collision_map, false };
    update_collision_map_from_bitmap(&world);
    return world;
}

void destroy_world(WORLD* world) {
    al_destroy_bitmap(world->sprite);
    al_free(world->collision_map);
}

void update_collision_map_from_bitmap(WORLD* world) {
    al_lock_bitmap(world->sprite, ALLEGRO_LOCK_READONLY, al_get_bitmap_format(world->sprite));
    for (int x = 0; x < world->width; x++) {
        for (int y = 0; y < world->height; y++) {
            int index = GET_INDEX(world, x, y);
            unsigned char r, g, b, a;
            al_unmap_rgba(al_get_pixel(world->sprite, x, y), &r, &g, &b, &a);
            if (r != 0 && g != 0 && b != 0 && a != 0) {
                world->collision_map[index] |= WORLD_FLAG_COLLISION;
            } else {
                world->collision_map[index] &= ~WORLD_FLAG_COLLISION;
            }
        }
    }
    al_unlock_bitmap(world->sprite);
}

void update_bitmap_from_collision_map(WORLD *world) {
    if (!world->is_collision_dirty) {
        return;
    }
    world->is_collision_dirty = false;

    ALLEGRO_COLOR blank = al_map_rgba(0, 0, 0, 0);


    ALLEGRO_BITMAP* prev_bitmap = al_get_target_bitmap();
    al_set_target_bitmap(world->sprite);

    al_lock_bitmap(world->sprite, ALLEGRO_PIXEL_FORMAT_ANY, 0);

    // TODO: Use a buffer of regions to update; instead of looping through the whole world
    for (int x = 0; x < world->width; x++) {
        for (int y = 0; y < world->height; y++) {
            int index = GET_INDEX(world, x, y);
            if ((world->collision_map[index] & WORLD_FLAG_COLLISION) == false) {
                al_put_pixel(x, y, blank);
            }
        }
    }
    al_unlock_bitmap(world->sprite);
    al_set_target_bitmap(prev_bitmap);
}

bool is_collision(WORLD* world, int x, int y) {
    return (get_collision_flag(world, x, y) & WORLD_FLAG_COLLISION) != 0;
}

bool is_in_world_bounds(WORLD* world, int x, int y) {
    return world->width > x && world->height > y && x >= 0 && y >= 0;
}

BLOCK_FLAG get_collision_flag(WORLD* world, int x, int y) {
    if (!is_in_world_bounds(world, x, y)) {
        return 0;
    }

    int index = GET_INDEX(world, x, y);
    return world->collision_map[index];
}

void destruct_collision(WORLD* world, int x, int y, int x_range, int y_range) {
    for (int w_y = y; w_y < y + y_range; w_y++) {
        for (int w_x = x; w_x < x + x_range; w_x++) {
            if (is_in_world_bounds(world, w_x, w_y)) {
                int index = GET_INDEX(world, w_x, w_y);
                world->collision_map[index] &= ~WORLD_FLAG_COLLISION;
            }
        }
    }
    world->is_collision_dirty = true;
}
