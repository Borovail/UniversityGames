#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


#include "Colliders.h"

typedef struct 
{
     void (*processCollision)(GameObject* self, GameObject* other, int* score);
     bool isActive;
     BoxCollider boxCollider;

}GameObject;


#endif // GAME_OBJECT_H