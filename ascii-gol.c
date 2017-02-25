#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#define ROWS 34
#define COLS 119
#define SPACE 32 

char neighbors(char gi[][COLS], int i, int j){
    int vizinho = 0;
	int dead = 0;
    if(gi[i-1][j-1] == ' ')
        dead++;
	else if(gi[i-1][j-1]> vizinho)
		vizinho = gi[i-1][j-1];
    if(gi[i-1][j] == ' ')
        dead++;
	else if(gi[i-1][j]> vizinho)
		vizinho = gi[i-1][j];
    if(gi[i-1][j+1] == ' ')
        dead++;
	else if(gi[i+1][j+1]> vizinho)
		vizinho = gi[i+1][j+1];
    if(gi[i][j-1] == ' ')
        dead++;
	else if(gi[i][j-1]> vizinho)
		vizinho = gi[i][j-1];
    if(gi[i][j+1] == ' ')
        dead++;
	else if(gi[i][j+1]> vizinho)
		vizinho = gi[i][j+1];
    if(gi[i+1][j-1] == ' ')
        dead++;
	else if(gi[i+1][j-1]> vizinho)
		vizinho = gi[i+1][j-1];
    if(gi[i+1][j] == ' ')
        dead++;
	else if(gi[i+1][j]> vizinho)
		vizinho = gi[i+1][j];
    if(gi[i+1][j+1] == ' ')
        dead++;
	else if(gi[i+1][j+1]> vizinho)
		vizinho = gi[i+1][j+1];
//da rulez
	if (dead > 6) //less than two live neighbors. dies.
		vizinho = SPACE;
    else if(dead < 5) //more than three live neighbors. dies. or stay dead.
		vizinho = SPACE;
    else if(gi[i][j] == SPACE && dead == 6)//dead and two neighbors. stay dead
		vizinho = SPACE;
    else if(gi[i][j] != SPACE && (dead == 6 || dead == 5)) //alive and well
		vizinho = gi[i][j];
    return vizinho; //last condition, dead and three neighbors. rule 5
}

void nextgen(char prev[][COLS]){
    //here
	int i, j; 
	int nex[ROWS][COLS];
    for(j = 0; j < ROWS; j++){
        for(i = 0; i < COLS; i++){
            nex[j][i] = SPACE;
        }
    }
    for(j = 1; j < ROWS-1; j++){
        for(i = 1; i < COLS-1; i++){
			nex[j][i] = neighbors(prev, j, i); // what's this supposed to do? why ==? no idea lol 
            // it writes the letter of the new generation in this cell.
        }
    }

    for(j = 0; j < ROWS; j++){
        for(i = 0; i < COLS; i++){
			prev[j][i] = nex[j][i];
        }
    }
}

int main(int argc, char** argv){
    int i, j, test;
    FILE * input;
    input = fopen(argv[1], "r");
    if(!input)
        printf("no file!");
    char grid[ROWS][COLS];
    printf("%c", grid[40][40]);
    for(j = 0; j < ROWS; j++){
        for(i = 0; i < COLS; i++){
            grid[j][i] = SPACE;
        }
    }

    for(j = 1; j < ROWS-1; j++){
        for(i = 1; i < COLS-1; i++){
            fscanf(input, "%c", &grid[j][i]);
            printf("%c", grid[j][i]);
			if(grid[j][i] == '\n'){ 
                i = 0;
                break;
            }
        }
       printf("\n");
        
    }

    int k;
    for(k = 0; k < 875; k++){
        nextgen(grid);
        for(j = 0; j < ROWS; j++){
            for(i = 0; i < COLS; i++){
                printf("%c", grid[j][i]);
            }

            printf("\n");
        }
        usleep(41000);
        system("clear");
    } 

    FILE *output = fopen("output.txt", "w"); 
    for(j = 0; j < ROWS; j++){
        for(i = 0; i < COLS; i++){
            fprintf(output,"%c", grid[j][i]);
        }

        fprintf(output, "\n");
    }
    return 0;
}
