#include "../include/Engine.h"
#include "../include/ColilsionManager.h"
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
Ship ship;
MachineGunBullet machine_gun_bullets[5];
LazerBullet lazer_gun_bullets[10];
Monster monsters[5];

struct timespec lastFrameTime;
double deltaTime;
double difficulty=0;


int DynamicCOLS = 0;
int DynamicROWS = 0;

int machine_gun_bullets_count = 5;
int lazer_gun_bullets_count = 10;
int monsters_count = 5;


int monster_speed=5;
int machine_gun_bullet_speed=35;
int  lazer_bullet_speed=50;
int  ship_speed=100;


int killsScore = 0;
double distance =0;
int score=0;
int coins=5;




bool update_game()
{

    getmaxyx(stdscr, DynamicROWS, DynamicCOLS); // Получить текущие размеры экрана
    int input = getch();

    if (input == 'q')
        return false;

    if (input == ' ')
        fire_lazer_gun_bullets(lazer_gun_bullets, lazer_gun_bullets_count, ship.boxCollider.x, ship.boxCollider.y);

    fire_machine_gun_bullets(machine_gun_bullets, machine_gun_bullets_count, ship.boxCollider.x, ship.boxCollider.y);

    struct timespec currentFrameTime;
    clock_gettime(CLOCK_MONOTONIC, &currentFrameTime);
    deltaTime = (currentFrameTime.tv_sec - lastFrameTime.tv_sec) +
                (currentFrameTime.tv_nsec - lastFrameTime.tv_nsec) / 1000000000.0;

    spawn_monsters(monsters, monsters_count, DynamicCOLS);

deltaTime+=difficulty;


    ////update functions

    update_ship(&ship, input,ship_speed, deltaTime,DynamicCOLS,DynamicROWS);
    update_bullets_machine_bullets(machine_gun_bullets, machine_gun_bullets_count, machine_gun_bullet_speed, deltaTime);
    update_bullets_lazer_bullets(lazer_gun_bullets, lazer_gun_bullets_count, lazer_bullet_speed, deltaTime);
    update_monsters(monsters, monsters_count, LINES, monster_speed, deltaTime);

    ////update functions




////collision functions
       
    proccesCollisionsForMonstersWithMachineBullets(monsters,monsters_count,machine_gun_bullets,machine_gun_bullets_count,&killsScore,&coins);
 proccesCollisionsForMonstersWithLazerBullets(monsters,monsters_count,lazer_gun_bullets,lazer_gun_bullets_count,&killsScore,&coins); 
 proccesCollisionsWithShip(&ship,monsters,monsters_count);

////collision functions
  

    if(ship.hp<=0){
        
        return false;
    }


    draw();
    draw_UI();

    lastFrameTime = currentFrameTime;

    distance+=deltaTime;

    napms(20); // Задержка на 20 миллисекунд

    difficulty+=0.000002;

    return true;
}




void draw()
{
    clear();

    draw_monsters(monsters, monsters_count);
    
    draw_ship(&ship);

    draw_machine_gun_bullets(machine_gun_bullets, machine_gun_bullets_count);

    draw_lazer_bullets(lazer_gun_bullets, lazer_gun_bullets_count);

    draw_UI();


    // mvprintw(LINES/2-1,COLS/2,"\tdelta: %f",deltaTime);
    // mvprintw(LINES/2,COLS/2,"\tdifficulty: %f",difficulty);


    refresh();
}

void draw_UI(){
    mvprintw(LINES-6,COLS-1,"\tYou hp: %d ",ship.hp);
    mvprintw(LINES-5,COLS-1,"\tYour coins: %d",coins);
    mvprintw(LINES-4,COLS-1,"\tYou killed: %d monsters",killsScore);
    mvprintw(LINES-3,COLS-1,"\tYour record is %d distance",score);;
    mvprintw(LINES-2,COLS-1,"\tYou reached %d distance",(int)round(distance));

}








void init_game(GameState* gameState){
 srand(time(NULL));

   coins = gameState->coins;
   score = gameState->max_score;
distance=0;
killsScore=0;

   initialize_ship(&ship);
   initialize_lazer_gun_bullets(lazer_gun_bullets ,lazer_gun_bullets_count);
   initialize_machine_gun_bullets(machine_gun_bullets,machine_gun_bullets_count );
   initialize_monsters(monsters,monsters_count);
    
    clock_gettime(CLOCK_MONOTONIC, &lastFrameTime);
}


void init_ncurses(){
 initscr();
    noecho();
    curs_set(FALSE);
    //   mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    // printf("\033[?1003h\n"); // Включить отслеживание движения мыши
    
    keypad(stdscr, TRUE); // Включаем поддержку клавиатуры
    // set implicit modes
    cbreak();
    // getch() will be non-blocking
    nodelay(stdscr, TRUE);
    start_color();
    
     init_color(23,32,32,32);// RGB gray
                                                
           // color sets
        init_pair(2, COLOR_BLUE, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
        init_pair(4, 23, COLOR_BLACK);

        init_pair(1, COLOR_RED, COLOR_BLACK);


        
}


void shut_down(GameState* gameState){


gameState->coins = coins;
gameState->max_score = (int)round(distance)>gameState->max_score ? (int)round(distance)   : gameState->max_score;
  endwin();

}



bool end_game(GameState* gameState){
    gameState->coins = coins;
gameState->max_score = (int)round(distance)>gameState->max_score ? (int)round(distance)   : gameState->max_score;
    clear();

    nodelay(stdscr, FALSE);
    mvprintw(LINES/2,COLS/3,"%s\n","You lose, wanna start again? Enter y/n  (yes or no)");

    refresh();
    while (true)
    {
        
   char input  =getch();

   if(tolower(input)=='y'){
    return false;
   }
    else if(tolower(input)=='n'){
    return true;
   }
  
 


    }

    return false;
    
}