#include "../include/Monster.h" 
#include <math.h>
#include <ncurses.h>
#include <stdlib.h>

int generate_correct_position(Monster* monsters,int monster_count,int cols);

void initialize_monsters(Monster* monsters,int monster_count){
 for (int i = 0; i < monster_count; i++) {
     monsters[i].isActive=false;
            monsters[i].boxCollider.height = MONSTER_HEIGHT;             
            monsters[i].boxCollider.width =MONSTER_WIDTH;                        
 }
}



void update_monsters(Monster* monsters,int monster_count,int rows,int speed,double deltaTime) {
    for (int i = 0; i < monster_count; i++) {

        if (monsters[i].isActive) {
            monsters[i].boxCollider.y+=speed*deltaTime;
            if (monsters[i].boxCollider.y >= rows) {
                monsters[i].isActive = false; 
            }
        }
        
    }
}

void spawn_monsters(Monster* monsters,int monster_count,int cols) {
    for (int i = 0; i < monster_count; i++) {
        if (!monsters[i].isActive) {
            monsters[i].boxCollider.x =generate_correct_position(monsters, monster_count, cols); 
            monsters[i].boxCollider.y =0; 

             monsters[i].coin = true ? rand()%5==3 : false;
            monsters[i].isActive = true;
            monsters[i].getDamage = false;
           monsters[i].hp=400;
            break;
        }
    }
}

int generate_correct_position(Monster* monsters,int monster_count,int cols){
  int position =rand()%cols;

  for (size_t i = 0; i < monster_count; i++)
  {
   if (!monsters[i].isActive) {
    while ((int)round(monsters->boxCollider.x)==position)
    {
      position =rand()%cols;
    }
    
   }
  }
  
return position;
}


void draw_monsters(Monster* monsters,int monster_count) {
    for (int i = 0; i < monster_count; i++) {


        if (monsters[i].isActive) {
            
if(monsters[i].getDamage)
{
attron(COLOR_PAIR(1));
            mvprintw((int)round(monsters[i].boxCollider.y), (int)round(monsters[i].boxCollider.x), "  :. .: ");
            mvprintw((int)round(monsters[i].boxCollider.y)+1, (int)round(monsters[i].boxCollider.x), "_+%@@@%+_");
            mvprintw((int)round(monsters[i].boxCollider.y)+2, (int)round(monsters[i].boxCollider.x), " .*****.");

            
monsters[i].getDamage=false;
attroff(COLOR_PAIR(1));
}
else{
attron(COLOR_PAIR(1));

      mvprintw((int)round(monsters[i].boxCollider.y), (int)round(monsters[i].boxCollider.x), "  :. .: ");
attroff(COLOR_PAIR(1));

            mvprintw((int)round(monsters[i].boxCollider.y)+1, (int)round(monsters[i].boxCollider.x), "_+%@@@%+_");
            mvprintw((int)round(monsters[i].boxCollider.y)+2, (int)round(monsters[i].boxCollider.x), " .*****.");
}
        }
       
    }
}


void monster_death_animation(int x,int y){

  mvprintw(y,x,"|   +  ");
  mvprintw(y+1,x,"  #_ ");
  mvprintw(y+2,x," +  -  ");
  mvprintw(y+3,x," _    ");

}
