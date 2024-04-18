#include "../include/FileManager.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printHelp()
{
    printf("Manual:\n");
    printf("./CosmicRanger open [file_name] - open game file\n");
    printf("./CosmicRanger create [file_name] - create new game file\n");
    printf("./CosmicRanger help - show help manual\n");
}

void serializeGameState(const GameState *state, char *buffer)
{
    sprintf(buffer, "Max score: %d,Coins: %d", state->max_score, state->coins);

}

void deserializeGameState(const char *buffer, GameState *state)
{
    sscanf(buffer, "Max score: %d,Coins: %d", &state->max_score, &state->coins);
}


void createFile(const char *fileName)
{
    FILE *file = fopen(fileName, "w");

    if (file != NULL)
    {
        printf("File %s was succesfully created\n", fileName);
    }
    else
    {
        printf("Error: failed to create file: %s \n", fileName);
    }
}

void save_game(GameState *game_state, char *filePath)
{

    FILE *file = fopen(filePath, "w");
    if (file)
    {

        char buffer[500];

        serializeGameState(game_state, buffer);

        fputs(buffer, file);

        printf("Game saved saccusfully in file: %s\n", filePath);

        fclose(file);
    }
    else
    {
        printf("Error:file: %s not found, saving was unsuccesfull\n", filePath);
    }

   
}

bool open_game(GameState *game_state, char *filePath)
{
    FILE *file = fopen(filePath, "r");

    if (file)
    {

        char buffer[500];


        if (fgets(buffer, sizeof(buffer), file) != NULL)
        {

            deserializeGameState(buffer, game_state);
        }

        fclose(file);

        return true;
    }
    else
    {
        printf("File '%s' not found. You can create it with command './CosmicRanger create [file name]'.\n", filePath);
        return false;
    }
}

int proccessUserInput(int argc, char *argv[],GameState* gameState ,char* file_path)
{
  
if(file_path==NULL) return 0;

    if (strcmp(argv[1], "help") == 0)
    {
        printHelp();
        return 0;
    }
    else if (strcmp(argv[1], "create") == 0)
    {
        if (argc < 3)
        {
            printf("Error: file name missing.\n");
            return 0;
        }
       createFile(file_path);
       return  0 ;
     
    }
    else if (strcmp(argv[1], "open") == 0)
    {
        if (argc < 3)
        {
            printf("Error: file name missing.\n");
            return 0;
        }

      return open_game(gameState,file_path);
        
    }

return 0;
}

char*  make_correct_file_format(int argc,char *argv[]){

  if (argc < 3)
    {
        printf("Error: too few arguments.\n");
        printHelp();
        return NULL;
    }


char *extension = ".txt";
    int length = strlen(argv[2]) + strlen(extension) + 1;

    char *result = malloc(length);

    if (result == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return NULL;
    }

    strcpy(result, argv[2]); 
    strcat(result, extension); 

    return result;
}

