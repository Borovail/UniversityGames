#include <math.h>
#include <ncurses.h>
#include "Colliders.h"

#define LAZER_BULLET_LENGTH 1
#define LAZER_BULLET_WIDTH 1

typedef struct 
{
    bool isActive;
   double damage;
BoxCollider firstRay;
BoxCollider secondRay;

}LazerBullet;


void fire_lazer_gun_bullets(LazerBullet* bullets ,int bullet_count,int x_pos,int y_pos);
void update_bullets_lazer_bullets(LazerBullet* bullets , int bullet_count,int bullet_speed,double deltaTime) ;
void draw_lazer_bullets(LazerBullet* bullets,int bullets_count);
void initialize_lazer_gun_bullets(LazerBullet* bullets,int bullet_count);