#ifndef FileManager_H
#define FileManager_H
#include "GameState.h"
#include <stdbool.h>


void printHelp();
void serializeGameState(const GameState *state, char *buffer);
void deserializeGameState(const char *buffer, GameState *state);
void createFile(const char *fileName);
void save_game(GameState *game_state, char *filePath);
bool open_game(GameState *game_state, char *filePath);
int proccessUserInput(int argc, char *argv[],GameState* gameState ,char* file_path);
char*  make_correct_file_format(int argc,char *argv[]);
#endif // FileManager_H

