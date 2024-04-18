
#include "../include/EnterMenuManager.h"

#include <ncurses.h>
#include <unistd.h>  // Для sleep()




void draw_animated_button(int starty,int startx){
    // Отрисовка границ кнопки
    for (int j = 0; j < BUTTON_HEIGHT; j++) {
        for (int i = 0; i < BUTTON_WIDTH; i++) {
           
                mvprintw(starty + j, startx + i, "");
            
        }
    }
}




void handle_button_click(){

 int startx = (COLS - BUTTON_WIDTH) / 2;  // Вычисление начальных координат кнопки
    int starty = (LINES - BUTTON_HEIGHT) / 2;

        draw_animated_button(starty,startx);  // Отрисовка кнопки с анимацией
        refresh();

int x=0,y=0,side=0;
bool isWindowPainted=false;



 while (true) {
    
//  if(!isWindowPainted)
// draw_symbols(&side,&x,&y) ;
 
// if(side==4){
// isWindowPainted=true;
// side=0;

// }

//  if(isWindowPainted){
//   draw_animated_symbol(&side,&x,&y);
//  }


        refresh();
        int ch = getch();
        if (ch == KEY_MOUSE) {
             MEVENT event;
 if (getmouse(&event) == OK) {
                if ((event.x < startx + BUTTON_WIDTH &&
         startx + BUTTON_WIDTH > event.x) &&
        (event.y < starty + BUTTON_HEIGHT &&
         starty + BUTTON_HEIGHT > event.y))
    {
mvprintw(LINES/2,COLS/2,"CLik");
        
    }
            }
            

        }
        napms(20);  // Задержка для анимации
    }
}




void draw_symbols(int* side,int* x,int*y){



if(*side==0){
    if((*x)+1<COLS-2){
        (*x)++;
    }else{
        (*side)++;
    }
}

if(*side==1){
    if((*y)+1<LINES-1){
        (*y)++;
    }else{
        (*side)++;
    }
}

if(*side==2){
    if((*x)-1>0){
        (*x)--;
    }else{
        (*side)++;
    }
}


if(*side==3){
    if((*y)-1>0){
        (*y)--;
    }else{
        (*side)++;
    }
}



mvprintw(*y,*x,"o");

}

void draw_animated_symbol(int* side,int* x,int*y){



if(*side==0){
    if((*x)+1<COLS-2){
        mvprintw(*y,*x,"o");
        (*x)++;
    }else{
        (*side)++;
    }
}

if(*side==1){
    if((*y)+1<LINES-1){
        mvprintw(*y,*x,"o");
        (*y)++;
    }else{
        (*side)++;
    }
}

if(*side==2){
    if((*x)-1>0){
        mvprintw(*y,*x,"o");
        (*x)--;
    }else{
        (*side)++;
    }
}


if(*side==3){
    if((*y)-1>0){
        mvprintw(*y,*x,"o");
        (*y)--;
    }else{
        (*side)++;
    }
}



mvprintw(*y,*x,"#");

}





