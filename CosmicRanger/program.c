#include "include/Engine.h"
#include "include/FileManager.h"
#include "include/Paintings.h"
#include <unistd.h>  // Для sleep в Unix/Linux
#include <stdlib.h>
#include <ncurses.h>
//important because of usleep()
#define _DEFAULT_SOURCE




///////что сделать сразу
// игровое лого разукрасить как на картинка
//// разукрасить игру
///сделать смерть корабля конец игры






int main(int argc, char *argv[]){

  char* file_path = make_correct_file_format( argc, argv);

GameState gameState;

if(proccessUserInput(argc,argv,&gameState,file_path)==0){
    return 0;
}

 init_ncurses();


//  draw_game_intro();

 while (true)
 {
  
 
 draw_game_logo();
 

 init_game(&gameState);
 

  while ( update_game());

if(end_game(&gameState)){
  break;
}
   clear();
    nodelay(stdscr, TRUE);

 }

 shut_down(&gameState);

 save_game(&gameState,file_path);

 free(file_path);

return 0;
  
}


