#ifndef SHIP_H
#define SHIP_H

#include "Colliders.h"
#include <stdbool.h>


#define SHIP_LENGTH 5
#define SHIP_WIDTH 16




typedef struct {
   bool isActive;
   int hp;
    BoxCollider boxCollider;
   bool getDamage;
} Ship;


void update_ship(Ship* ship,int input,int speed,double deltaTime,int dymanicCols,int dynamicRows);
void draw_ship(Ship* ship);
void initialize_ship(Ship* ship);

#endif // SHIP_H
