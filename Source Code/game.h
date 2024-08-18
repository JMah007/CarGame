#ifndef GAME_H
#define GAME_H

void playGame(char** array2d, int* arrayCarTrackr, int numRows, int numCols);
int updatePlayer(char** array2d, int* rowLoc, int* colLoc, int gameOver , char input, char* initPosChar);
void updateTraffic(char** array2d, int* arrayCarTrackr, int numRows, int numCols);
void printMap(char** array2d, int numRows, int numCols);
void addTraffic(char** array2d, int* arrayCarTrackr, int numRows, int numCols);
void createMap(char** array2d, int numRows, int numCols);
void addObjects(char** array2d, int* arrayCarTrackr, int numRows, int numCols);
void addRoads(char** array2d, int numRows, int numCols);
void addCharacters(char** array2d, int row, int col, char obj);
int extractData(char* arg);
int valArgument(int argc, char* argv[]);
char** create2dArray(int numRows, int numCols);
int* createCarTrackrArr(int numRows);
void free2dArray(char** array, int numRows);
char getUserInput(char** array2d, int* rowLoc, int* colLoc);
int validateInput(char** array2d, char input, int valid, int* rowLoc, int* colLoc);

#endif