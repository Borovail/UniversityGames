#include "../include/Arts.h"
#include "../include/Paintings.h"
#include <ncurses.h>
#include <string.h>

//Not implemented but had a great prospect  to make a game intro with animations


void draw_alien(int *row, int *position, int *border)
{
    int center = COLS / 6 - strlen(alien1[0]) / 2;
    int max_rows = sizeof(alien1) / sizeof(alien1[0]);

    if (*row == max_rows - 1) {
        return;
    }

    if (*row == -1) {
        *row = 0;
    }

    if (*position < LINES) { // Проверка, чтобы не выйти за границы экрана
        mvprintw((*position)+1, center, "%s", alien1[0]);
        mvprintw((*position)--, center, "%s", alien1[*row]);
    }

    if (*position == *border) {
        (*border)++;
        *position = LINES - 1; // Сброс позиции в нижнюю часть экрана
        (*row)++;
    }
}



void draw_alien2(int *row, int *position, int *border)
{
    int center =( COLS / 1.2 - strlen(alien2[0]) / 2)+5;
    int max_rows = sizeof(alien2) / sizeof(alien2[0]);

    if (*row == 0)
    {
        return;
    }

    if (*row == -1)
    {
        *row = max_rows - 1;
    }

    if (*position > 0)
        mvprintw((*position) - 1, center, "%s", alien2[0]);

    mvprintw((*position)++, center, "%s", alien2[*row]);

    if (*position == *border)
    {
        (*border)--;
        *position = 0;
        (*row)--;
    }
}

bool draw_rocket()
{

    int center = COLS / 2 - strlen(rocket[0]) / 2;
    int num_rows = sizeof(rocket) / sizeof(rocket[0]);

    int target = num_rows;
    for (int row_count = num_rows - 1; row_count >= 1; row_count--)
    {

        for (int y = 1; y <= target; y++)
        {
             if(skip_animation())
            return 0;

            mvprintw(y, center, "%s", rocket[row_count]);
            refresh();
            usleep(1 * 1000);

            // clear
            mvprintw(y, center, "%s", rocket[0]);
        }

        mvprintw(target, center, "%s", rocket[row_count]);

        target--;
    }

    return 1;
}

void draw_game_logo()
{

    int center = COLS / 2 - strlen(game_intro[0]) / 2;
    int num_rows = sizeof(game_intro) / sizeof(game_intro[0]);

    int target = LINES;

    for (int row_count = num_rows - 1; row_count >= 0; row_count--) {
        for (int y = 1; y <= target; y++) {
            if(skip_animation())
            return;
                    attron(COLOR_PAIR(4));

                mvprintw(y, center , "%s", game_intro[row_count]);
                attroff(COLOR_PAIR(4));

            refresh();
            usleep(1 * 10000);

            // Очищаем строку перед следующей отрисовкой
             mvprintw(y, center , "%s", game_intro[0]);
        }
        for (size_t i = 0; i < strlen(game_intro[row_count]); i++) {
            int color_pair=4;
      
                if(game_intro[row_count][i] == '%'){
                   color_pair = 2;
                }
                 else if(game_intro[row_count][i] != '@' ){
                   color_pair = 3;

                 }

                attron(COLOR_PAIR(color_pair));
               mvprintw(target, center+i, "%c", game_intro[row_count][i]);
                attroff(COLOR_PAIR(color_pair));
            }
        target--;
    }

    usleep(10 * 100000); // Более разумное время задержки
}






void draw_meteorite(int *row, int *position, int *border)
{
    int center = COLS / 7 - strlen(meteorite[0]) / 2;
    int max_rows = sizeof(meteorite) / sizeof(meteorite[0]);

    if (*row == 0)
    {
        return;
    }

    if (*row == -1)
    {
        *row = max_rows - 1;
    }

    if (*position >= 1)
        mvprintw((*position) - 1, center, "%s", meteorite[0]);

    mvprintw((*position)++, center, "%s", meteorite[(*row)]);

    if (*position == *border)
    {
        (*border)--;
        *position = 0;
        (*row)--;
    }
}



void draw_meteorite_from_down(int *row, int *position, int *border)
{
    int center = (COLS/1.2  - strlen(meteorite[0]) / 2)+4;
    int max_rows = sizeof(meteorite) / sizeof(meteorite[0]);

    if (*row == max_rows - 1)
    {
        return;
    }

    if (*row == -1)
    {
        *row = 0;
    }

    if (*position < LINES){
        mvprintw((*position) + 1, center, "%s", meteorite[0]);
    }
    mvprintw((*position)--, center, "%s", meteorite[(*row)]);

    if (*position == *border)
    {
        (*border)++;
        *position = LINES - 1;
        (*row)++;
    }
}




void draw_game_intro()
{
        mvprintw(LINES-(LINES-1), COLS-48, "To skip intro you can press: 'Escape' or 'q/Q'");
     


    if(draw_rocket()==false)
        return;
    

    int meteorite_pos = 0, meteorite_row = -1, meteorite_border = LINES / 2.3;
    int meteorite_pos2 = LINES -1, meteorite_row2 = -1, meteorite_border2 =LINES /1.8;
    int alien_pos = LINES-1, alien_row = -1, alien_border = LINES/2.2;
    int alien_pos2 = 0, alien_row2 = -1, alien_border2 = LINES/2.3;


    int counter = 10000;

    while (counter != 0)
    {
          if(skip_animation())
            break;

        draw_alien(&alien_row, &alien_pos, &alien_border);
        draw_meteorite(&meteorite_row,&meteorite_pos,&meteorite_border );
        draw_alien2(&alien_row2,&alien_pos2,&alien_border2);
        draw_meteorite_from_down(&meteorite_row2,&meteorite_pos2,&meteorite_border2 );

        refresh();
        usleep(10000); // небольшая задержка
        counter--;
        mvprintw(LINES-(LINES-1), COLS-48, "To skip intro you can press: 'Escape' or 'q/Q'");

    }

    usleep(10 * 1000000); // небольшая задержка
}

bool skip_animation()
{
    int input = getch();

    if (input == 'Q' || input == 'q' || input == 27)
    {
        
        clear();
         mvprintw(LINES/2, COLS/2, "SKIP ANIMATION");
        refresh();
        return true;
    }

    return false;
}
