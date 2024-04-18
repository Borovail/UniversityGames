#include <stdbool.h>
#include "GameState.h"

void init_game(GameState* gameState);
void init_ncurses();
bool update_game();
void draw();
bool end_game();
void draw_logo();
void shut_down(GameState* gameState);
void draw_UI();