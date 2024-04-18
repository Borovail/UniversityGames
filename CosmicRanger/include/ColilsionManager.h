
#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H
#include "Monster.h"
#include "LazerBullet.h"
#include "MachineGunBullet.h"
#include "Ship.h"
#include "Colliders.h"



/// @brief Checks collisions between  two objects
/// @param collider1 
/// @param collider2 
/// @return true if any object in any way cross or collide any other object with collider
bool checkCollision(BoxCollider* collider1, BoxCollider* collider2);

void proccesCollisionsForMonstersWithLazerBullets(Monster* monsters,int monsters_count,LazerBullet* bullets,int bullets_count,int* score,int* coins);
void proccesCollisionsForMonstersWithMachineBullets(Monster* monsters,int monsters_count,MachineGunBullet* bullets,int bullets_count,int* score,int* coins);

void proccesCollisionsWithShip(Ship* ship,Monster* monsters,int monsters_count);

#endif // COLLISION_MANAGER_H
