#include <time.h>
#include <termios.h>
#include <stdlib.h>

void disableBuffer(){
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

void enableBuffer(){
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag |= (ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

void initRandom(){
    srand(time(NULL));
}

int randomUCP(int low, int high){
    int number = -1;

    if(low <= high){
        number = (rand() % (high-low+1)) + low;
    }

    return number;
}