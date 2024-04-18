#include "../include/ColilsionManager.h"
#include <ncurses.h>

bool checkCollision(BoxCollider *collider1, BoxCollider *collider2)
{
    if ((collider1->x < collider2->x + collider2->width &&
         collider1->x + collider1->width > collider2->x) &&
        (collider1->y < collider2->y + collider2->height &&
         collider1->y + collider1->height > collider2->y))
    {
        return true;
    }
    return false;
}

void proccesCollisionsForMonstersWithMachineBullets(Monster *monsters, int monsters_count, MachineGunBullet *bullets, int bullets_count, int *score, int *coins)
{

    for (int i = 0; i < monsters_count; i++)
    {
        ////only if it are active
        if (monsters[i].isActive)
        {
            /////go throw all machine_gun_bullets
            for (int j = 0; j < bullets_count; j++)
            {
                ////only if it are active
                if (bullets[i].isActive)
                {
                    ////check if any bullet collide with monster
                    if (checkCollision(&monsters[i].boxCollider, &bullets[j].boxCollider))
                    {
                        monsters[i].hp -= bullets[j].damage;
                        monsters[i].getDamage=true;
                        if (monsters[i].hp <= 0)
                        {
                            monsters[i].isActive = false;
                            (*score)++;
                            (*coins) += monsters[i].coin;
                        }

                        ////deactivate  monster and bullet
                        bullets[j].isActive = false;
                        break;
                    }
                }
            }
        }
    }
}

void proccesCollisionsForMonstersWithLazerBullets(Monster *monsters, int monsters_count, LazerBullet *bullets, int bullets_count, int *score, int *coins)
{

    for (int i = 0; i < monsters_count; i++)
    {
        ////only if it are active
        if (monsters[i].isActive)
        {
            /////go throw all machine_gun_bullets
            for (int j = 0; j < bullets_count; j++)
            {
                ////only if it are active
                if (bullets[i].isActive)
                {
                    ////check if any bullet collide with monster
                    if (checkCollision(&monsters[i].boxCollider, &bullets[j].firstRay))
                    {

                        monsters[i].hp -= bullets[j].damage;
                        monsters[i].getDamage = true;

                        if (monsters[i].hp <= 0)
                        {
                            monsters[i].isActive = false;
                            (*score)++;
                            (*coins) += monsters[i].coin;
                        }

                        ////deactivate  monster and bullet
                        bullets[j].isActive = false;
                        break;
                    }

                    ////check if any bullet collide with monster
                    if (checkCollision(&monsters[i].boxCollider, &bullets[j].secondRay))
                    {
                        monsters[i].hp -= bullets[j].damage;
                        monsters[i].getDamage = true;
                        if (monsters[i].hp <= 0)
                        {
                            monsters[i].isActive = false;
                            (*score)++;
                            (*coins) += monsters[i].coin;
                        }

                        ////deactivate  monster and bullet
                        bullets[j].isActive = false;
                        break;
                    }
                }
            }
        }
    }

    attroff(COLOR_PAIR(4));
}

void proccesCollisionsWithShip(Ship *ship, Monster *monsters, int monsters_count)
{

    for (int i = 0; i < monsters_count; i++)
    {
        if (monsters[i].isActive)
        {
            ////check if any monster collide with ship
            if (checkCollision(&ship->boxCollider, &monsters[i].boxCollider))
            {

                ship->hp -= 1;
                    ////paint ship in red like taking damage
                    ship->getDamage=true;
                

                monsters[i].isActive = false;
                break;
            }
        }
    }
}
