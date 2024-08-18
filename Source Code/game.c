#include <stdio.h>
#include <stdlib.h>

#include "misc.h"
#include "boolean.h"
#include "game.h"


/* This function runs the main process of the game wear the player can interact with it */
void playGame(char** array2d, int* arrayCarTrackr, int numRows, int numCols)
{
    int gameOver = FALSE;
    char input;
    int rowLoc = 1, colLoc = 1; /* Keeps track of player row and column location*/
    char initPosChar = ' ';

    do
    {
        input = getUserInput(array2d, &rowLoc, &colLoc);
        updateTraffic(array2d, arrayCarTrackr, numRows, numCols);
        gameOver = updatePlayer(array2d, &rowLoc, &colLoc, gameOver, input, &initPosChar);
        
        printMap(array2d, numRows, numCols);
    }while(!gameOver); 

        /* Determines if program was terminated due to loss or win*/
        if(array2d[numRows-2][numCols-2] == 'P')
        {
            printf("\nYou win!\n");
        }
        else
        {
            printf("\nYou lose. You got hit by a car!\n");
        }
}


/* This function updates the players movements and returns whether the player crashed into a car
 or reached the goal*/
int updatePlayer(char** array2d, int* rowLoc, int* colLoc, int gameOver , char input, char* initPosChar)
{
    int newRow = *rowLoc;
    int newCol = *colLoc;

    /* Stores car character to replace players original position when player moves */
    /* This helps with the jumping over car feature */
    if(array2d[*rowLoc][*colLoc] == '<')
    {
        *initPosChar = '<';
    }
    if(array2d[*rowLoc][*colLoc] == '>')
    {
        *initPosChar = '>';
    }

    /* Replaces players current position with character that belongs there as part of the map */
    array2d[*rowLoc][*colLoc] = *initPosChar;

    switch(input) 
    {
        case 'w':
            newRow = *rowLoc - 1;
            break;
        case 'a':
            newCol = *colLoc - 1;
            break;
        case 's':
            newRow = *rowLoc + 1;
            break;
        case 'd':
            newCol = *colLoc + 1;
            break;
    }

    if((array2d[newRow][newCol] == '<') || (array2d[newRow][newCol] == '>')) 
    {
        gameOver = TRUE;
    }

    if(array2d[newRow][newCol] == 'G') 
    {
        gameOver = TRUE;
    }

    /* Move the player*/
    *initPosChar = array2d[newRow][newCol]; /* Stores char of the location player is about to move to so it can replace it again later*/
    array2d[newRow][newCol] = 'P';  

    /* Update tracker for players location */
    *rowLoc = newRow;
    *colLoc = newCol;

    return gameOver; 
}


/* This function updates every car movement on the map */
void updateTraffic(char** array2d, int* arrayCarTrackr, int numRows, int numCols)
{
    int i;
    int carNum = 0;
    int arrayCol;

    for(i = 2; i < (numRows-1); i+=2)
    {
        arrayCol = arrayCarTrackr[carNum]; /* retrieves and stores column number of car */
        
        if(array2d[i][arrayCol] == '<')
        {
            arrayCarTrackr[carNum] = arrayCol - 1; /*stores new position of car in location tracking array*/
            array2d[i][arrayCarTrackr[carNum]] = '<'; /* Moves the car left by one*/
            array2d[i][arrayCarTrackr[carNum] + 1] = '.'; /*replaces last position of car with road char*/

            if(arrayCarTrackr[carNum] == 1)/* If car reaches the leftmost boundary*/
            { 
                array2d[i][arrayCarTrackr[carNum]] = '>';
            }   
        }

        if(array2d[i][arrayCol] == '>')
        {
            arrayCarTrackr[carNum] = arrayCol + 1; /*stores new position of car in location tracking array*/
            array2d[i][arrayCarTrackr[carNum]] = '>'; /* Moves the car right by one*/
            array2d[i][arrayCarTrackr[carNum] - 1] = '.'; /*replaces last position of car with road char*/

            if(arrayCarTrackr[carNum] == (numCols - 2))/* If car reaches the rightmost boundary*/
            { 
                array2d[i][arrayCarTrackr[carNum]] = '<';
            } 
        }
        carNum = carNum + 1; /* Increment to next car to perform the loop on */         
    }
}


/* This function displays the 2d array of the map and all its contents to the terminal clearing all
content of the terminal before */
void printMap(char** array2d, int numRows, int numCols)
{
    int i, j;

    system("clear");

    for(i = 0; i < numRows; i++)
    {
        for(j = 0; j < numCols; j++) 
        {
            printf(" %c", array2d[i][j]);
        }
        printf("\n");
    }

    printf("Press w to move up\n");
    printf("Press s to move down\n");
    printf("Press a to move left\n");
    printf("Press d to move right\n");
}


/* This function adds a certain number of cars to the map depending on given arguments */
void addTraffic(char** array2d, int* arrayCarTrackr, int numRows, int numCols)
{
    int i, carCounter = 0, randLocation, randDirection; 

    for(i = 1; i < numRows - 2; i++){
        if((i % 2) == 0) {

            randLocation = randomUCP(1, numCols - 2); /*returns a column in the row the car should begin in*/
            randDirection = randomUCP(0, 1); /*returns 0 represents < or 1 represents >*/
            arrayCarTrackr[carCounter] = randLocation; /*stores the location of each car*/
            

            if(randDirection == 0 && randLocation != 1){ /*pointing left and not on boundary*/
                array2d[i][randLocation] = '<';
            }
            else if(randDirection == 1 && randLocation != (numCols - 2)){ /*pointing right and not on boundary*/
                array2d[i][randLocation] = '>';
            }
            else if(randDirection == 0 && randLocation == 1){ /*pointing left and on boundary*/
                array2d[i][randLocation] = '>';
            }
            else if(randDirection == 1 && randLocation == (numCols - 2)){ /*pointing right and on boundary*/
                array2d[i][randLocation] = '<';
            }

            carCounter = carCounter + 1;
        }        
    }
}


/* This function creates the boarders of the map only depending on how many rows and columsn 
are given as arguments */
void createMap(char** array2d, int numRows, int numCols)
{
    int i, j;

    /*Creates border and fills interior with spaces (might put in function of its own)*/
    for(i = 0; i < numRows; i++){
        for(j = 0; j < numCols; j++){
            if(i == 0 || i == numRows - 1 || j == 0 || j == numCols - 1) {
                array2d[i][j] = '*';
            } else {
                array2d[i][j] = ' ';
            }
        }
    }   
}


/* This function adds all contents in the 2d array map */
void addObjects(char** array2d, int* arrayCarTrackr, int numRows, int numCols){
    /*adds roads*/
    addRoads(array2d, numRows, numCols);

    /*adds goal*/
    addCharacters(array2d, numRows - 2, numCols - 2, 'G');

    /*adds person*/
    addCharacters(array2d, 1, 1, 'P');

    /*adds traffic*/
    addTraffic(array2d, arrayCarTrackr, numRows, numCols);
}


/* This function adds roads only to the map */
void addRoads(char** array2d, int numRows, int numCols){
    int i, j;

    for(i = 1; i < numRows - 2; i++)
    {
        for(j = 1; j < numCols - 1; j++)
        {
            if((i % 2) == 0) 
            {
                array2d[i][j] = '.';
            } 
        }
    } 
}


/* This function adds characters to the map */
void addCharacters(char** array2d, int row, int col, char obj)
{
    array2d[row][col] = obj;
}


/* This function makes sure the correct number of rows and columns are given in order for 
the game to operate properly */
int valArgument(int argc, char* argv[])
{
    int status;

    /*validate number of arguements*/
    if(argc != 3)
    {
        printf("Error, must be 3 arguments!");
        status = FALSE;
    }

    /*validate rows*/
    else if((atoi(argv[1]) < 3) || ((atoi(argv[1]) % 2) == 0))
    {
        printf("Error, enter an odd value and minimum of 3 rows for argument 1!");
        status = FALSE;
    }

    /*validate columns*/
    else if(atoi(argv[2]) < 5)
    {
        printf("Error, enter a minimum of 5 columns for argument 2!");
        status = FALSE;
    }
    else
    {
        status = TRUE;    
    }

    return status;
}


/* This function converts character string to integer value */
int extractData(char* string)
{
    return atoi(string);
}


/* This function creates a 2d array dynamically */
char** create2dArray(int numRows, int numCols)
{
    int i;
    char** array2d = (char**)malloc(numRows * sizeof(char*));

    for(i = 0; i < numRows; i++) {
        array2d[i] = (char*)malloc(numCols * sizeof(char));
    }
    return array2d;
}


/* This function creates an array dynamically for car tracker*/
int* createCarTrackrArr(int numRows)
{
    int numCars;
    int* arrayCarTrackr;
    /*calculates number of cars thats going to be added and creates array to store each cars location*/
    numCars = ((numRows-1) - 1) / 2; 
    arrayCarTrackr = (int*) malloc (numCars * sizeof(int));
    return arrayCarTrackr;
}


/* This function frees 2d array */
void free2dArray(char** array, int numRows)
{
    int i;
    for (i = 0; i < numRows; i++) {
        free(array[i]);
    }
    free(array);
}


/* This function gets input from user and validates it*/
char getUserInput(char** array2d, int* rowLoc, int* colLoc)
{
    char ch;
    int valid = FALSE;

    while(valid == FALSE)
    {
    disableBuffer();
    scanf(" %c", &ch);
    enableBuffer();
    valid = validateInput(array2d, ch, valid, rowLoc, colLoc);
    }
    return ch;
}


/* This function makes sure only w, a, s or d is accepted and prevents player
from moving past the boundary of the map */
int validateInput(char** array2d, char input, int valid, int* rowLoc, int* colLoc)
{
    int newRow = *rowLoc;
    int newCol = *colLoc;
    valid = TRUE;

    switch(input) 
    {
        case 'w':
            newRow = *rowLoc - 1;
            break;
        case 'a':
            newCol = *colLoc - 1;
            break;
        case 's':
            newRow = *rowLoc + 1;
            break;
        case 'd':
            newCol = *colLoc + 1;
            break;
    }

    if((input != 'w') && (input != 'a') && (input != 's') && (input != 'd')){
        valid = FALSE;
    }

    /* Check if the move is within boundaries and not a wall */
    if (array2d[newRow][newCol] == '*') {
        valid = FALSE;
    }
    return valid;
}
