#include <ncurses.h>
#include <stdlib.h>

#include "Objects.h"

static spawn_position positions[50];

int size;
void init_array()
{

    size = COLS / 15;

    for (size_t i = 0; i < size; i++)
    {
        positions[i].x = (i + 1) * 15;
        positions[i].y = rand() % LINES/2;
    }
}

void draw_objects(object *objects, int objects_count, void (*func)(int x, int y))
{
    for (size_t i = 0; i < objects_count; i++)
    {
        if (objects[i].isPresent)
        {
            func(objects[i].x, objects[i].y);
        }
    }
}

void move_objects(object *objects, int objects_count)
{
    for (int i = 0; i < objects_count; i++)
    {
        if (objects[i].isPresent)
        {

            objects[i].y += 1;

            if (objects[i].y > LINES + 3)
            {
                if (objects[i].spawn_pos != NULL)
                    objects[i].spawn_pos->isTaken = false;

                respawn_object(&objects[i]);
            }
        }
    }
}

void spawn_objects(object *objects, int objects_count, int points,int effect,  int height, int width, bool isPresent)
{

    for (size_t i = 0; i < objects_count; i++)
    {
        objects[i].isPresent = isPresent;
        objects[i].height = height;
        objects[i].width = width;
        objects[i].points = points;
        objects[i].effect = effect;

        if (objects_count == 1)
        {
            objects[i].y = LINES - 1;
        }
        else
        {
            respawn_object(&objects[i]);
        }
    }
}

void respawn_object(object *object)
{
    object->y = 0;

    int index = rand() % size;
    if (!positions[index].isTaken)
    {
        object->spawn_pos = &positions[index];
        object->spawn_pos->isTaken = true; // Пометить позицию как занятую
        object->y = object->spawn_pos->y;
        object->x = object->spawn_pos->x;
    }
}

void collide(object *player, object *objects, int objects_count)
{

    for (int i = 0; i < objects_count; i++)
    {
        if (objects[i].isPresent)
            if (player[0].x + player[0].width >= objects[i].x && player[0].x <= objects[i].x + objects[i].width && player[0].y + player[0].height >= objects[i].y && player[0].y <= objects[i].y + objects[i].height)
            {
                if (player[0].points + objects[i].points >= 0)
                {
                    player[0].points += objects[i].points;
                }

                     player->speed = objects[i].effect;
            
                objects[i].y = LINES + 100;
            }
    }
}
