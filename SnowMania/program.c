#define _POSIX_C_SOURCE 200201L
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "Objects.h"
#include <ctype.h>
#include <math.h>

void draw_player();
void draw_snowflake();
void draw_giant_snowflake();
void draw_giant_rock();
void draw_rock();
void draw_positive_buster();
void draw_negative_buster();

void select_level(int argc, char *argv[]);

bool start_game(int point_to_win, bool is_giant_rock, bool is_giant_snowflake, bool *unlock_next_level);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    select_level(argc, argv);
    endwin();
    return 0;
}
void select_level(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Too few arguments\n");
        printf("Available commands:\n");
        printf("./program level [number]\n");
        printf("./program create levels [count]\n");
        return;
    }

    int level = 0;

    if (strcmp(argv[1], "level") == 0)
    {
        level = atoi(argv[2]);

        if (level < 1 || level > 20)
        {
            printf("Number must be in range from 1 to 20 \n");
            return;
        }
    }
    else if (strcmp(argv[1], "create") == 0)
    {
        if (strcmp(argv[2], "levels") == 0)
        {
            int level_count = atoi(argv[3]);

            if (level_count > 0 && level_count < 21)
            {
                int previous_points = -1;
                for (int i = 1; i <= level_count; i++)
                {
                    char file_name[30];
                    sprintf(file_name, "level%d.txt", i);
                    FILE *file = fopen(file_name, "w+");

                    int unlocked = 0;
                    int giant_rocks = 0, giant_snow_flakes = 0, points_to_win = 0;

                    giant_rocks = rand() % (int)round(level_count / i);
                    giant_snow_flakes = rand() % i;
                    points_to_win = i * 10 + i - rand() % (i * 5 + 1);

                    while (points_to_win <= previous_points)
                    {
                        points_to_win += rand() % 10;
                    }

                    if (i == 1)
                        unlocked = 1;

                    fprintf(file, "Need points to win:%d,Unclocked:%d,Is giant rocks:%d,Is giant snowflakes:%d",
                            points_to_win,
                            unlocked,
                            (giant_rocks % 3 == 0 && giant_rocks % 2 == 0) ? 1 : 0,
                            (giant_snow_flakes % 3 == 0 && giant_snow_flakes % 2 == 0) ? 1 : 0);
                    fclose(file);

                    previous_points = points_to_win;
                }

            }
            else
            {
                printf("Currently you can create only from 1 to 20 levels\n");
                return;
            }
        }
        else
        {
            printf("Unknown command:\n");
            printf("Did you mean :\n");
            printf("./program create levels [count]\n");
            return;
        }
        return;
    }
    else
    {
        printf("Unknown command:\n");
        printf("Available commands:\n");
        printf("./program level [number]\n");
        printf("./program create levels [count]\n");
        return;
    }

    bool restart_game = false;

    do
    {
        char file_name[30];                       // Увеличенный размер для безопасности
        sprintf(file_name, "level%d.txt", level); // Используйте sprintf для формирования имени файла

        FILE *file = fopen(file_name, "r");
        if (file)
        {
            char stats[500];
            int point_to_win = 0;
            bool unlock_next_level;
            int is_level_unlocked, is_giant_snowflake, is_giant_rock;
            fscanf(file, "Need points to win:%d,Unclocked:%d,Is giant rocks:%d,Is giant snowflakes:%d", &point_to_win, &is_level_unlocked, &is_giant_rock, &is_giant_snowflake);
            fclose(file);


            if (!is_level_unlocked)
            {
                printf("Level is locked\n");
                printf("You need to pass the previous levels first\n");
                return;
            }

            restart_game = start_game(point_to_win, is_giant_rock, is_giant_snowflake, &unlock_next_level);

            if (level != 20 && unlock_next_level)
            {
                char name_file[30];     
                level++;                          // Увеличенный размер для безопасности
                sprintf(name_file, "%s%d.txt", argv[1], level); // Используйте sprintf для формирования имени файла

                file = fopen(name_file, "r+");
                if (file)
                {
                    fseek(file, 32, SEEK_SET);
                    fprintf(file, "%d", 1);
                    fclose(file);
                }

            }
            else
            {
                printf("File not found\n");
                return;
            }
        }
        else
        {
            printf("Level not found\n");
            return;
        }

    } while (restart_game);
}

int snow_flake_y = 5;
int player_x = 20;
double timer = 0;
double effect_timer = 0;
double timer_finish = 1;
double timer_start = 0;
double timer_seconds = 0.1;
bool is_right;

const int giant_snow_flakes_count=3,snowflakes_cout=5,rocks_count=5,giant_rocks_count=3,positive_busters_count=3,negative_busters_count=3;


object player[1];
object giant_snow_flakes[3];
object snowflakes[5];
object rocks[5];
object giant_rocks[3];

object giant_snow_flakes_second_wave[3];
object snowflakes_second_wave[5];
object rocks_second_wave[5];
object giant_rocks_second_wave[3];

object negativ_busters[3];
object positive_busters[3];

char* art1[] =   {"   _==_  _ \n",
                  " _,(\",)|_|\n",
                  "  \\/. \\-|\n",
                  "__( :  )|_\n\n" };

    char* art2[] = {"     __    \n",
                  "   _|==|_  \n",
                  "    ('')___/\n",
                  ">--(`^^')\n",
                  "  (`^'^'^')\n",
                  "  `======`\n" };


bool start_game(int point_to_win, bool is_giant_rock, bool is_giant_snowflake, bool *unlock_next_level)
{

    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE); // Включаем поддержку клавиатуры
    // set implicit modes
    cbreak();
    // getch() will be non-blocking
    nodelay(stdscr, TRUE);
    start_color();

    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);

    init_array();

    spawn_objects(player, 1, 0,  0 ,3, 5, true);
    player->x = COLS / 2;
    player[0].speed = 1;
    spawn_objects(giant_snow_flakes, giant_rocks_count, 5, 1, 5, 10, is_giant_snowflake);
    spawn_objects(snowflakes, snowflakes_cout, 3, 1,  3, 5, true);
    spawn_objects(rocks, rocks_count, -3, 1,  3, 3, true);
    spawn_objects(giant_rocks, giant_rocks_count, -5, 1,  3, 5, is_giant_rock);

    spawn_objects(giant_snow_flakes_second_wave, giant_rocks_count, 5, 1,  5, 10, is_giant_snowflake);
    spawn_objects(snowflakes_second_wave, snowflakes_cout, 3, 1,  3, 5, true);
    spawn_objects(rocks_second_wave, rocks_count, -3, 1, 3, 3, true);
    spawn_objects(giant_rocks_second_wave, giant_rocks_count, -5, 1,  3, 5, is_giant_rock);

    spawn_objects(negativ_busters, negative_busters_count, 0, 0,  1, 1, true);
    spawn_objects(positive_busters, positive_busters_count, 0, 2,  1, 1, true);

    while (true)
    {
        int ch = getch();
        clear();

        if (effect_timer >= timer_finish)
        {
            player[0].speed = 1;
            effect_timer = timer_start;
        }

        if (ch == KEY_LEFT && player_x > 0)
        { // Исправлено условие
            player[0].x -= player[0].speed;
            if(player[0].x <1){
                player[0].x =COLS-1;
            }
            is_right = false;
        }

        if (ch == KEY_RIGHT && player_x < COLS - 1)
        { // Исправлено условие
            player[0].x += player[0].speed;
             if(player[0].x >COLS-1){
                player[0].x =1;
            }
            is_right = true;
        }

        if (timer > timer_finish)
        {
            move_objects(giant_snow_flakes, 3);
            move_objects(snowflakes, 5);
            move_objects(rocks, 5);
            move_objects(giant_rocks, 3);
            move_objects(positive_busters, 3);
            move_objects(negativ_busters, 3);
            timer = timer_start;
        }
        if (timer >= timer_finish / 2)
        {
            move_objects(giant_snow_flakes_second_wave, 3);
            move_objects(snowflakes_second_wave, 5);
            move_objects(rocks_second_wave, 5);
            move_objects(giant_rocks_second_wave, 3);
        }

        collide(player, giant_snow_flakes, 3);

        collide(player, snowflakes, 5);
        collide(player, rocks, 5);
        collide(player, giant_rocks, 3);
        collide(player, positive_busters, 3);
        collide(player, negativ_busters, 3);


        for (size_t i = 0; i < sizeof(art1)/sizeof(art1[0]); i++)
        {
        mvprintw(LINES/1.1+i,COLS/6,"%s",art1[i]);
        }
        

        // mvprintw(LINES/2,COLS-5,"%s", art2);


        draw_objects(player, 1, draw_player);

        draw_objects(giant_snow_flakes, 3, draw_giant_snowflake);
        draw_objects(snowflakes, 5, draw_snowflake);

        draw_objects(rocks, 5, draw_rock);
        draw_objects(giant_rocks, 3, draw_rock);
        draw_objects(negativ_busters, 3, draw_negative_buster);
        draw_objects(positive_busters, 3, draw_positive_buster);

        mvprintw(LINES - 1, COLS / 1.25, "Points needed you win: %d", point_to_win);
        mvprintw(LINES - 2, COLS / 1.25, "Your points: %d", player[0].points);

        refresh();
        napms(15);
        timer += timer_seconds;
        effect_timer += 0.005;

        if (player[0].points >= point_to_win)
        {
            *unlock_next_level = true;

            clear();

            mvprintw(LINES / 2, COLS / 2, "You won! Next level unlocked");
            mvprintw(LINES / 2 + 1, COLS / 2, "Do you want go to next level?  Press y/e | yes or exit");

            int answer;
            do
            {
                answer = getch();

                napms(20);
            } while (tolower(answer) != 'y' && tolower(answer) != 'e');

            if (answer == 'y')
                return true;
            else
                return false;
        }
    }
}

void draw_player(int x, int y)
{
    attron(COLOR_PAIR(2));
    if (is_right)
    {

        mvprintw(y - 3, x, "( 0_0)");
        mvprintw(y - 2, x, "(/ )/");
        mvprintw(y - 1, x, "/︶\\");
    }
    else
    {

        mvprintw(y - 3, x, "(0_0 )");
        mvprintw(y - 2, x, " ୧( ୧)");
        mvprintw(y - 1, x, "  /︶\\");
    }
    attroff(COLOR_PAIR(2));
}

void draw_snowflake(int x, int y)
{
    attron(COLOR_PAIR(1));

    mvprintw(y - 3, x, " * ");
    mvprintw(y - 2, x, "* *");
    mvprintw(y - 1, x, " * ");
    attroff(COLOR_PAIR(1));
}

void draw_giant_snowflake(int x, int y)
{
    attron(COLOR_PAIR(1));

    mvprintw(y - 3, x, "*   *");
    mvprintw(y - 2, x, "  *  ");
    mvprintw(y - 1, x, "*   *");
    attroff(COLOR_PAIR(1));
}

void draw_giant_rock(int x, int y)
{
    mvprintw(y - 3, x, "#####");
    mvprintw(y - 2, x, "#@@@#");
    mvprintw(y - 1, x, "#####");
}

void draw_rock(int x, int y)
{
    mvprintw(y - 3, x, " #");
    mvprintw(y - 2, x, "#@#");
    mvprintw(y - 1, x, " #");
}

void draw_positive_buster(int x, int y)
{
    attron(COLOR_PAIR(2));
    
    mvprintw(y , x, ">>>");
    attroff(COLOR_PAIR(2));

}

void draw_negative_buster(int x, int y)
{
    attron(COLOR_PAIR(3));
    mvprintw(y , x, "<<<");
    attroff(COLOR_PAIR(3));

}




