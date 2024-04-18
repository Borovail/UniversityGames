#include "../include/MachineGunBullet.h" 


void initialize_machine_gun_bullets(MachineGunBullet* bullets,int bullet_count){
    // Инициализация пуль
    for (int i = 0; i < bullet_count; i++)
    {
        bullets[i].isActive = false;
        bullets[i].boxCollider.height = MACHINE_GUN_BULLET_HEIGHT;
        bullets[i].boxCollider.width = MACHINE_GUN_BULLET_WIDTH;
        bullets[i].damage=5;

    }
}




void fire_machine_gun_bullets(MachineGunBullet* bullets ,int bullet_count,int x_pos,int y_pos) {
    for (int i = 0; i < bullet_count; i++) {
        if (!bullets[i].isActive) {
            bullets[i].boxCollider.x = x_pos+6;
            bullets[i].boxCollider.y = y_pos;
            bullets[i].isActive = true;
            break;
        }
    }
}





void update_bullets_machine_bullets(MachineGunBullet* bullets , int bullet_count,int bullet_speed,double deltaTime) {
    for (int i = 0; i < bullet_count; i++) {
        if (bullets[i].isActive) {
            bullets[i].boxCollider.y-=bullet_speed*deltaTime;
            if (bullets[i].boxCollider.y < 0) {
                bullets[i].isActive = false;
            }
        }
    }
}


void draw_machine_gun_bullets(MachineGunBullet* bullets,int bullets_count){
    // // Отрисовка пуль
    // for (int i = 0; i < bullets_count; i++) {
    //     if (bullets[i].active) {
    //         mvprintw((int)round(bullets[i].boxCollider.y), (int)round(bullets[i].boxCollider.x)+3, "*");
    //     }
    // }


     // Отрисовка пуль
    for (int i = 0; i < bullets_count; i++) {
        if (bullets[i].isActive) {
            mvprintw((int)round(bullets[i].boxCollider.y), (int)round(bullets[i].boxCollider.x), "==");
        }
    }
}
