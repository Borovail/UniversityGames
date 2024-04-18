#include <math.h>
#include <ncurses.h>
#include "Colliders.h"


#define MACHINE_GUN_BULLET_HEIGHT 1
#define MACHINE_GUN_BULLET_WIDTH 2

typedef struct 
{
    bool isActive;
    double damage;
BoxCollider boxCollider;

}MachineGunBullet;

void fire_machine_gun_bullets(MachineGunBullet* bullets ,int bullet_count,int x_pos,int y_pos);
void update_bullets_machine_bullets(MachineGunBullet* bullets , int bullet_count,int bullet_speed,double deltaTime);
void draw_machine_gun_bullets(MachineGunBullet* bullets,int bullets_count);
void initialize_machine_gun_bullets(MachineGunBullet* bullets,int bullet_count);
