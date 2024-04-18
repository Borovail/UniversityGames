#include "../include/Ship.h" 

#include <ncurses.h>
#include <math.h>

void initialize_ship(Ship* ship){

   ship->boxCollider.x = COLS / 2;
    ship->boxCollider.y = LINES - 2;
    ship->boxCollider.height = SHIP_LENGTH;
    ship->boxCollider.width = SHIP_WIDTH;
    ship->hp=3;
}




void update_ship(Ship* ship,int input,int speed,double deltaTime,int dynamicCols,int dynamicRows) {
    // Управление кораблем с клавиатуры
    switch (input) {
        case KEY_LEFT: ship->boxCollider.x =(ship->boxCollider.x > 0)  ? ship->boxCollider.x - (speed * deltaTime) : dynamicCols - 1;
        break;
    
        case KEY_RIGHT: ship->boxCollider.x =(ship->boxCollider.x < COLS - 1) ? ship->boxCollider.x +  (speed* deltaTime) : 0;
        break;
        
        case KEY_UP: ship->boxCollider.y =   (ship->boxCollider.y > 0) ? ship->boxCollider.y - (speed* deltaTime) : dynamicRows - 1; 
        break;
      
        case KEY_DOWN: ship->boxCollider.y = (ship->boxCollider.y < LINES - 1) ? ship->boxCollider.y + (speed* deltaTime) : 0;
         break;
    }
}


void draw_ship(Ship* ship){

//   // Отрисовка корабля
    // mvprintw((int)round(ship->boxCollider.y), (int)round(ship->boxCollider.x), "|+|-|+|");

    int y=(int)round(ship->boxCollider.y);
    int x=(int)round(ship->boxCollider.x);

    if(ship->getDamage){

 attron(COLOR_PAIR(4));
mvprintw(y, x, "      ==   ");
    mvprintw(y + 1, x, "  :  :++:  :");

    mvprintw(y + 2, x, ":*:+ +**+ +:*:");
    mvprintw(y + 3, x, "  #-++==++-#");

    mvprintw(y + 4, x, " .   :++:   .");
    attroff(COLOR_PAIR(4));

        ship->getDamage=false;
    }
    else{

    

    mvprintw(y, x, "      ==   ");
 attron(COLOR_PAIR(4));
    mvprintw(y + 1, x, "  :  :++:  :");
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(2));
    mvprintw(y + 2, x, ":*:+ +**+ +:*:");
    mvprintw(y + 3, x, "  #-++==++-#");

    mvprintw(y + 4, x, " .   :++:   .");
    attroff(COLOR_PAIR(2));

    }
    
}
