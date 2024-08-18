#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <termios.h>

#include "game.h"
#include "misc.h"
#include "boolean.h"


int main(int argc, char* argv[])
{
    int isValidInput;
    int rows, columns;
    char** array2dMap = NULL;
    int* arrayCarTrackr = NULL;
   
    initRandom();
    isValidInput = valArgument(argc, argv);
  
    if(isValidInput) /* Executes if arguments given are successful */
    {
        /* Behind the scenes functions */
        rows = extractData(argv[1]) + 2;
        columns = extractData(argv[2]) + 2;
        array2dMap = create2dArray(rows, columns);
        arrayCarTrackr = createCarTrackrArr(rows);

        /* Initialise map */
        createMap(array2dMap, rows, columns);
        addObjects(array2dMap, arrayCarTrackr, rows, columns);
        printMap(array2dMap, rows, columns);
        
        playGame(array2dMap, arrayCarTrackr, rows, columns);

        
        free2dArray(array2dMap, rows);
        free(arrayCarTrackr);
    }   
    return 0;
}

















