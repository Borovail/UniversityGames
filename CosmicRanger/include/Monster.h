#ifndef Monster_H
#define Monster_H
#include "Colliders.h"
#include <stdbool.h>


typedef struct {
   bool isActive;
   double hp;
   bool coin;
   bool getDamage;
    BoxCollider boxCollider;
    
} Monster;

#define MONSTER_HEIGHT 3
#define MONSTER_WIDTH 6
void initialize_monsters(Monster* monsters,int monster_count);
void update_monsters(Monster* monsters,int monster_count,int rows,int speed,double deltaTime);
void draw_monsters(Monster* monsters,int monster_count);
void spawn_monsters(Monster* monsters,int monster_count,int cols);
void monster_death_animation(int x,int y);
#endif // Monster_H
