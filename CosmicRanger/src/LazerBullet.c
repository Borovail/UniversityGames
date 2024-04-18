#include "../include/LazerBullet.h" 

void initialize_lazer_gun_bullets(LazerBullet* bullets,int bullet_count){
// Инициализация пуль
    for (int i = 0; i < bullet_count; i++)
    {
        bullets[i].isActive = false;
        bullets[i].firstRay.height = LAZER_BULLET_LENGTH;
        bullets[i].firstRay.width = LAZER_BULLET_WIDTH;
        bullets[i].secondRay.height = LAZER_BULLET_LENGTH;
        bullets[i].secondRay.width = LAZER_BULLET_WIDTH;
        bullets[i].damage = 10;

    }

}


void fire_lazer_gun_bullets(LazerBullet* bullets ,int bullet_count,int x_pos,int y_pos) {
    for (int i = 0; i < bullet_count; i++) {
        if (!bullets[i].isActive) {
            bullets[i].firstRay.x = x_pos+1;
            bullets[i].firstRay.y = y_pos+i-6;
              bullets[i].secondRay.x = x_pos+12;
            bullets[i].secondRay.y = y_pos+i-6;
            bullets[i].isActive = true;
        }
    }
}



void update_bullets_lazer_bullets(LazerBullet* bullets , int bullet_count,int bullet_speed,double deltaTime) {
    for (int i = 0; i < bullet_count; i++) {
        if (bullets[i].isActive) {
            bullets[i].firstRay.y-=bullet_speed*deltaTime;
            bullets[i].secondRay.y-=bullet_speed*deltaTime;
            if (bullets[i].firstRay.y < 0 || bullets[i].secondRay.y < 0) {
                bullets[i].isActive = false;
            }
        }
    }
}


void draw_lazer_bullets(LazerBullet* bullets,int bullets_count){
    // Отрисовка пуль
    for (int i = 0; i < bullets_count; i++) {
        if (bullets[i].isActive) {
                  attron(COLOR_PAIR(2));
            mvprintw((int)round(bullets[i].firstRay.y),(int)round( bullets[i].firstRay.x), "|");
            mvprintw((int)round(bullets[i].secondRay.y), (int)round(bullets[i].secondRay.x), "|");
                  attroff(COLOR_PAIR(2));

        }
    }
}