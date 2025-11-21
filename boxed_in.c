/*
ENGGEN131 2024
C Project - Boxed In
Resource file - project2.c

You can use this program to test the functions that you write before grading them with CodeRunner
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define ROWS 10
#define COLS 10

#define SPACE 0
#define WALL 1
#define TARGET 2
#define BOX 3
#define BOX_ON_TARGET 4
#define PERSON 5
#define PERSON_ON_TARGET 6

// Function prototype declarations
void MakeBox(char *design, int width, int height);
void PrintRoom(int room[ROWS][COLS]);
void InitialiseRoom(int room[ROWS][COLS], char *layout);
void LocatePerson(int room[ROWS][COLS], int *row, int *col);
void MakeMove(int room[ROWS][COLS], char move, char *allMoves);
int CheckGameOver(int room[ROWS][COLS]);
void UndoMove(int room[ROWS][COLS], char *allMoves);

// When you have completed all of the functions for the project, place them here:

void MakeBox(char* design, int width, int height)
{
	if (width < 3 || height < 3) {
		int pos = 0;
		int i = 0, j = 0;
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				design[pos++] = '#';
			}
			design[pos++] = '\n';
		}
	}
	else {
		int pos = 0;
		int i = 0, j = 0, k = 0;
		while (i != width) {
			design[pos++] = '#';
			i++;
		}
		design[pos++] = '\n';

		for (i = 0; i < height - 2; i++) {
			for (j = 0; j < width; j++) {
				if (j == 0 || j == width - 1) {
					design[pos++] = '#';
				}
				else if (i == (height - 2) / 2 && j == (width - 1) / 2 && height % 2 == 1) {
					if (width % 2 == 1) {
						design[pos++] = 'X';
					}
					else {
						design[pos++] = 'X';
						design[pos++] = 'X';
						j++;
					}
				}
				else if ((i == (height - 2) / 2 && j == (width - 1) / 2 && height % 2 == 0) || (i == (height - 3) / 2 && j == (width - 1) / 2 && height % 2 == 0)) {
					if (width % 2 == 1) {
						design[pos++] = 'X';
					}
					else {
						design[pos++] = 'X';
						design[pos++] = 'X';
						j++;
					}
				}
				else {
					design[pos++] = ' ';
				}
			}
			design[pos++] = '\n';
		}

		while (k != width) {
			design[pos++] = '#';
			k++;
		}
		design[pos++] = '\n';
	}
}
void PrintRoom(int room[ROWS][COLS])
{
	int i = 0, j = 0;
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			if (room[i][j] == SPACE) {
				printf(" ");
			}
			else if (room[i][j] == WALL) {
				printf("#");
			}
			else if (room[i][j] == TARGET) {
				printf("*");
			}
			else if (room[i][j] == BOX) {
				printf("O");
			}
			else if (room[i][j] == BOX_ON_TARGET) {
				printf("@");
			}
			else if (room[i][j] == PERSON) {
				printf("X");
			}
			else if (room[i][j] == PERSON_ON_TARGET) {
				printf("X");
			}
		}
		printf("\n");
	}
}
void InitialiseRoom(int room[ROWS][COLS], char* layout)
{
	int i = 0, j = 0, k = 0;
	int len;
	len = strlen(layout);

	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			if (k < len) {
				if (layout[k] == '0') {
					room[i][j] = SPACE;
				}
				else if (layout[k] == '1') {
					room[i][j] = WALL;
				}
				else if (layout[k] == '2') {
					room[i][j] = TARGET;
				}
				else if (layout[k] == '3') {
					room[i][j] = BOX;
				}
				else if (layout[k] == '4') {
					room[i][j] = BOX_ON_TARGET;
				}
				else if (layout[k] == '5') {
					room[i][j] = PERSON;
				}
				else if (layout[k] == '6') {
					room[i][j] = PERSON_ON_TARGET;
				}
				else {
					room[i][j] = WALL;
				}
				k++;
			}
			else {
				room[i][j] = WALL;
			}
		}
	}
}
void LocatePerson(int room[ROWS][COLS], int* row, int* col)
{
	int i = 0, j = 0;

	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			if (room[i][j] == PERSON || room[i][j] == PERSON_ON_TARGET) {
				*row = i;
				*col = j;
			}
		}
	}
}
void MakeMove(int room[ROWS][COLS], char move, char* allMoves)
{
	int len;
	len = strlen(allMoves);
	if (move == 'z' && len > 0) {
		UndoMove(room, allMoves);
	}

	int x = 0, motion = 0;

	int row, col;
	LocatePerson(room, &row, &col);

	//Person moving with an empty space in direction
	if (move == 'w' && room[row - 1][col] == SPACE) {
		if (room[row][col] == PERSON) { //Person moving to empty space
			room[row][col] = SPACE;
			room[row - 1][col] = PERSON;
		}
		else {					//PERSON_ON_TARGET moving to empty space
			room[row][col] = TARGET;
			room[row - 1][col] = PERSON;
		}
		motion = 1;
	}
	else if (move == 'a' && room[row][col - 1] == SPACE) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row][col - 1] = PERSON;
		}
		else {
			room[row][col] = TARGET;
			room[row][col - 1] = PERSON;
		}
		motion = 1;
	}
	else if (move == 'd' && room[row][col + 1] == SPACE) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row][col + 1] = PERSON;
		}
		else {
			room[row][col] = TARGET;
			room[row][col + 1] = PERSON;
		}
		motion = 1;
	}
	else if (move == 's' && room[row + 1][col] == SPACE) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row + 1][col] = PERSON;
		}
		else {
			room[row][col] = TARGET;
			room[row + 1][col] = PERSON;
		}
		motion = 1;
	}

	//Person moving with a target in direction
	if (move == 'w' && room[row - 1][col] == TARGET) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE; //Empty space fills person position
			room[row - 1][col] = PERSON_ON_TARGET; //Person now identifies as person on target
		}
		else {
			room[row][col] = TARGET; //PERSON IS ON THE TARGET WITH TARGET IN DIRECTION
			room[row - 1][col] = PERSON_ON_TARGET;
		}
		motion = 1;
	}
	else if (move == 'a' && room[row][col - 1] == TARGET) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row][col - 1] = PERSON_ON_TARGET;
		}
		else {
			room[row][col] = TARGET;
			room[row][col - 1] = PERSON_ON_TARGET;
		}
		motion = 1;
	}
	else if (move == 'd' && room[row][col + 1] == TARGET) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row][col + 1] = PERSON_ON_TARGET;
		}
		else {
			room[row][col] = TARGET;
			room[row][col + 1] = PERSON_ON_TARGET;
		}
		motion = 1;
	}
	else if (move == 's' && room[row + 1][col] == TARGET) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row + 1][col] = PERSON_ON_TARGET;
		}
		else {
			room[row][col] = TARGET;
			room[row + 1][col] = PERSON_ON_TARGET;
		}
		motion = 1;
	}

	//Person and box next to each other moving to an empty space in direction
	if (move == 'w' && room[row - 1][col] == BOX && room[row - 2][col] == SPACE) {
		if (room[row][col] == PERSON) { //Person is not on a target next to a box
			room[row][col] = SPACE;
			room[row - 1][col] = PERSON;
			room[row - 2][col] = BOX;
		}
		else {					//PERSON_ON_TARGET next to a box
			room[row][col] = TARGET;
			room[row - 1][col] = PERSON;
			room[row - 2][col] = BOX;
		}
		motion = 2;
	}
	else if (move == 'a' && room[row][col - 1] == BOX && room[row][col - 2] == SPACE) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row][col - 1] = PERSON;
			room[row][col - 2] = BOX;
		}
		else {
			room[row][col] = TARGET;
			room[row][col - 1] = PERSON;
			room[row][col - 2] = BOX;
		}
		motion = 2;
	}
	else if (move == 'd' && room[row][col + 1] == BOX && room[row][col + 2] == SPACE) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row][col + 1] = PERSON;
			room[row][col + 2] = BOX;
		}
		else {
			room[row][col] = TARGET;
			room[row][col + 1] = PERSON;
			room[row][col + 2] = BOX;
		}
		motion = 2;
	}
	else if (move == 's' && room[row + 1][col] == BOX && room[row + 2][col] == SPACE) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row + 1][col] = PERSON;
			room[row + 2][col] = BOX;
		}
		else {
			room[row][col] = TARGET;
			room[row + 1][col] = PERSON;
			room[row + 2][col] = BOX;
		}
		motion = 2;
	}

	//Person and box next to each other moving with a target in direction 
	if (move == 'w' && room[row - 1][col] == BOX && room[row - 2][col] == TARGET) {
		if (room[row][col] == PERSON) { //Person is not on a target and pushes the box on a target
			room[row][col] = SPACE;
			room[row - 1][col] = PERSON;
			room[row - 2][col] = BOX_ON_TARGET;
		}
		else {					//PERSON_ON_TARGET pushes the box on a target
			room[row][col] = TARGET;
			room[row - 1][col] = PERSON;
			room[row - 2][col] = BOX_ON_TARGET;
		}
		motion = 2;
	}
	else if (move == 'a' && room[row][col - 1] == BOX && room[row][col - 2] == TARGET) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row][col - 1] = PERSON;
			room[row][col - 2] = BOX_ON_TARGET;
		}
		else {
			room[row][col] = TARGET;
			room[row][col - 1] = PERSON;
			room[row][col - 2] = BOX_ON_TARGET;
		}
		motion = 2;
	}
	else if (move == 'd' && room[row][col + 1] == BOX && room[row][col + 2] == TARGET) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row][col + 1] = PERSON;
			room[row][col + 2] = BOX_ON_TARGET;
		}
		else {
			room[row][col] = TARGET;
			room[row][col + 1] = PERSON;
			room[row][col + 2] = BOX_ON_TARGET;
		}
		motion = 2;
	}
	else if (move == 's' && room[row + 1][col] == BOX && room[row + 2][col] == TARGET) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row + 1][col] = PERSON;
			room[row + 2][col] = BOX_ON_TARGET;
		}
		else {
			room[row][col] = TARGET;
			room[row + 1][col] = PERSON;
			room[row + 2][col] = BOX_ON_TARGET;
		}
		motion = 2;
	}

	//Person moving box off a target
	if (move == 'w' && room[row - 1][col] == BOX_ON_TARGET && room[row - 2][col] == SPACE) {
		if (room[row][col] == PERSON) { //Person not on a target pushing a box off a target
			room[row][col] = SPACE;
			room[row - 1][col] = PERSON_ON_TARGET;
			room[row - 2][col] = BOX;
		}
		else { //Person on a target pushing a box off a target
			room[row][col] = TARGET;
			room[row - 1][col] = PERSON_ON_TARGET;
			room[row - 2][col] = BOX;
		}
		motion = 2;
	}
	else if (move == 'a' && room[row][col - 1] == BOX_ON_TARGET && room[row][col - 2] == SPACE) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row][col - 1] = PERSON_ON_TARGET;
			room[row][col - 2] = BOX;
		}
		else {
			room[row][col] = TARGET;
			room[row][col - 1] = PERSON_ON_TARGET;
			room[row][col - 2] = BOX;
		}
		motion = 2;
	}
	else if (move == 'd' && room[row][col + 1] == BOX_ON_TARGET && room[row][col + 2] == SPACE) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row][col + 1] = PERSON_ON_TARGET;
			room[row][col + 2] = BOX;
		}
		else {
			room[row][col] = TARGET;
			room[row][col + 1] = PERSON_ON_TARGET;
			room[row][col + 2] = BOX;
		}
		motion = 2;
	}
	else if (move == 's' && room[row + 1][col] == BOX_ON_TARGET && room[row + 2][col] == SPACE) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row + 1][col] = PERSON_ON_TARGET;
			room[row + 2][col] = BOX;
		}
		else {
			room[row][col] = TARGET;
			room[row + 1][col] = PERSON_ON_TARGET;
			room[row + 2][col] = BOX;
		}
		motion = 2;
	}

	//Person moving a box on target onto another target
	if (move == 'w' && room[row - 1][col] == BOX_ON_TARGET && room[row - 2][col] == TARGET) {
		if (room[row][col] == PERSON) { //Person not on a target pushing a box off a target
			room[row][col] = SPACE;
			room[row - 1][col] = PERSON_ON_TARGET;
			room[row - 2][col] = BOX_ON_TARGET;
		}
		else { //Person on a target pushing a box off a target
			room[row][col] = TARGET;
			room[row - 1][col] = PERSON_ON_TARGET;
			room[row - 2][col] = BOX_ON_TARGET;
		}
		motion = 2;
	}
	else if (move == 'a' && room[row][col - 1] == BOX_ON_TARGET && room[row][col - 2] == TARGET) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row][col - 1] = PERSON_ON_TARGET;
			room[row][col - 2] = BOX_ON_TARGET;
		}
		else {
			room[row][col] = TARGET;
			room[row][col - 1] = PERSON_ON_TARGET;
			room[row][col - 2] = BOX_ON_TARGET;
		}
		motion = 2;
	}
	else if (move == 'd' && room[row][col + 1] == BOX_ON_TARGET && room[row][col + 2] == TARGET) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row][col + 1] = PERSON_ON_TARGET;
			room[row][col + 2] = BOX_ON_TARGET;
		}
		else {
			room[row][col] = TARGET;
			room[row][col + 1] = PERSON_ON_TARGET;
			room[row][col + 2] = BOX_ON_TARGET;
		}
		motion = 2;
	}
	else if (move == 's' && room[row + 1][col] == BOX_ON_TARGET && room[row + 2][col] == TARGET) {
		if (room[row][col] == PERSON) {
			room[row][col] = SPACE;
			room[row + 1][col] = PERSON_ON_TARGET;
			room[row + 2][col] = BOX_ON_TARGET;
		}
		else {
			room[row][col] = TARGET;
			room[row + 1][col] = PERSON_ON_TARGET;
			room[row + 2][col] = BOX_ON_TARGET;
		}
		motion = 2;
	}

	//Records all movement and store in array
	if (motion == 1) {
		while (allMoves[x] != '\0') {
			x++;
		}
		allMoves[x++] = move;
		allMoves[x++] = '0';
	}
	else if (motion == 2) {
		while (allMoves[x] != '\0') {
			x++;
		}
		allMoves[x++] = move;
		allMoves[x++] = '1';
	}
}
int CheckGameOver(int room[ROWS][COLS])
{
	int stat = 0;
	int i = 0, j = 0;
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {

			if (room[i][j] == TARGET || room[i][j] == PERSON_ON_TARGET) {
				return 0;
			}
			else if (room[i][j] == BOX_ON_TARGET) {
				stat = 1;
			}
		}
	}
	return stat;
}
void UndoMove(int room[ROWS][COLS], char* allMoves)
{
	//Read previous input
	char input;
	char box;

	int i = 0, j = 0;
	while (allMoves[i] != '\0') {
		i++;
	}
	input = allMoves[i - 2];
	box = allMoves[i - 1];

	while (allMoves[j] != '\0') {
		j++;
	}
	allMoves[j - 2] = '\0';

	int row, col;
	LocatePerson(room, &row, &col);

	//Revert the change of person
	if (input == 'w' && box == '0') {
		MakeMove(room, 's', allMoves);
	}
	else if (input == 'a' && box == '0') {
		MakeMove(room, 'd', allMoves);
	}
	else if (input == 'd' && box == '0') {
		MakeMove(room, 'a', allMoves);
	}
	else if (input == 's' && box == '0') {
		MakeMove(room, 'w', allMoves);
	}
	else if (input == 'w' && box == '1') {
		if (room[row][col] == PERSON && room[row - 1][col] == BOX && room[row + 1][col] == SPACE) {
			room[row + 1][col] = PERSON;
			room[row][col] = BOX;
			room[row - 1][col] = SPACE;
		}
		else if (room[row][col] == PERSON && room[row - 1][col] == BOX_ON_TARGET && room[row + 1][col] == SPACE) {
			room[row + 1][col] = PERSON;
			room[row][col] = BOX;
			room[row - 1][col] = TARGET;
		}
		else if (room[row][col] == PERSON && room[row - 1][col] == BOX && room[row + 1][col] == TARGET) {
			room[row + 1][col] = PERSON_ON_TARGET;
			room[row][col] = BOX;
			room[row - 1][col] = SPACE;
		}
		else if (room[row][col] == PERSON && room[row - 1][col] == BOX_ON_TARGET && room[row + 1][col] == TARGET) {
			room[row + 1][col] = PERSON_ON_TARGET;
			room[row][col] = BOX;
			room[row - 1][col] = TARGET;
		}
		else if (room[row][col] == PERSON_ON_TARGET && room[row - 1][col] == BOX && room[row + 1][col] == SPACE) {
			room[row + 1][col] = PERSON;
			room[row][col] = BOX_ON_TARGET;
			room[row - 1][col] = SPACE;
		}
		else if (room[row][col] == PERSON_ON_TARGET && room[row - 1][col] == BOX && room[row + 1][col] == TARGET) {
			room[row + 1][col] = PERSON_ON_TARGET;
			room[row][col] = BOX_ON_TARGET;
			room[row - 1][col] = SPACE;
		}
		else if (room[row][col] == PERSON_ON_TARGET && room[row - 1][col] == BOX_ON_TARGET && room[row + 1][col] == SPACE) {
			room[row + 1][col] = PERSON;
			room[row][col] = BOX_ON_TARGET;
			room[row - 1][col] = TARGET;
		}
		else if (room[row][col] == PERSON_ON_TARGET && room[row - 1][col] == BOX_ON_TARGET && room[row + 1][col] == TARGET) {
			room[row + 1][col] = PERSON_ON_TARGET;
			room[row][col] = BOX_ON_TARGET;
			room[row - 1][col] = TARGET;
		}

	}
	else if (input == 'a' && box == '1') {
		if (room[row][col] == PERSON && room[row][col - 1] == BOX && room[row][col + 1] == SPACE) {
			room[row][col + 1] = PERSON;
			room[row][col] = BOX;
			room[row][col - 1] = SPACE;
		}
		else if (room[row][col] == PERSON && room[row][col - 1] == BOX_ON_TARGET && room[row][col + 1] == SPACE) {
			room[row][col + 1] = PERSON;
			room[row][col] = BOX;
			room[row][col - 1] = TARGET;
		}
		else if (room[row][col] == PERSON && room[row][col - 1] == BOX && room[row][col + 1] == TARGET) {
			room[row][col + 1] = PERSON_ON_TARGET;
			room[row][col] = BOX;
			room[row][col - 1] = SPACE;
		}
		else if (room[row][col] == PERSON && room[row][col - 1] == BOX_ON_TARGET && room[row][col + 1] == TARGET) {
			room[row][col + 1] = PERSON_ON_TARGET;
			room[row][col] = BOX;
			room[row][col - 1] = TARGET;
		}
		else if (room[row][col] == PERSON_ON_TARGET && room[row][col - 1] == BOX && room[row][col + 1] == SPACE) {
			room[row][col + 1] = PERSON;
			room[row][col] = BOX_ON_TARGET;
			room[row][col - 1] = SPACE;
		}
		else if (room[row][col] == PERSON_ON_TARGET && room[row][col - 1] == BOX && room[row][col + 1] == TARGET) {
			room[row][col + 1] = PERSON_ON_TARGET;
			room[row][col] = BOX_ON_TARGET;
			room[row][col - 1] = SPACE;
		}
		else if (room[row][col] == PERSON_ON_TARGET && room[row][col - 1] == BOX_ON_TARGET && room[row][col + 1] == SPACE) {
			room[row][col + 1] = PERSON;
			room[row][col] = BOX_ON_TARGET;
			room[row][col - 1] = TARGET;
		}
		else if (room[row][col] == PERSON_ON_TARGET && room[row][col - 1] == BOX_ON_TARGET && room[row][col + 1] == TARGET) {
			room[row][col + 1] = PERSON_ON_TARGET;
			room[row][col] = BOX_ON_TARGET;
			room[row][col - 1] = TARGET;
		}
	}
	else if (input == 'd' && box == '1') {
		if (room[row][col] == PERSON && room[row][col + 1] == BOX && room[row][col - 1] == SPACE) {
			room[row][col - 1] = PERSON;
			room[row][col] = BOX;
			room[row][col + 1] = SPACE;
		}
		else if (room[row][col] == PERSON && room[row][col + 1] == BOX_ON_TARGET && room[row][col - 1] == SPACE) {
			room[row][col - 1] = PERSON;
			room[row][col] = BOX;
			room[row][col + 1] = TARGET;
		}
		else if (room[row][col] == PERSON && room[row][col + 1] == BOX && room[row][col - 1] == TARGET) {
			room[row][col - 1] = PERSON_ON_TARGET;
			room[row][col] = BOX;
			room[row][col + 1] = SPACE;
		}
		else if (room[row][col] == PERSON && room[row][col + 1] == BOX_ON_TARGET && room[row][col - 1] == TARGET) {
			room[row][col - 1] = PERSON_ON_TARGET;
			room[row][col] = BOX;
			room[row][col + 1] = TARGET;
		}
		else if (room[row][col] == PERSON_ON_TARGET && room[row][col + 1] == BOX && room[row][col - 1] == SPACE) {
			room[row][col - 1] = PERSON;
			room[row][col] = BOX_ON_TARGET;
			room[row][col + 1] = SPACE;
		}
		else if (room[row][col] == PERSON_ON_TARGET && room[row][col + 1] == BOX && room[row][col - 1] == TARGET) {
			room[row][col - 1] = PERSON_ON_TARGET;
			room[row][col] = BOX_ON_TARGET;
			room[row][col + 1] = SPACE;
		}
		else if (room[row][col] == PERSON_ON_TARGET && room[row][col + 1] == BOX_ON_TARGET && room[row][col - 1] == SPACE) {
			room[row][col - 1] = PERSON;
			room[row][col] = BOX_ON_TARGET;
			room[row][col + 1] = TARGET;
		}
		else if (room[row][col] == PERSON_ON_TARGET && room[row][col + 1] == BOX_ON_TARGET && room[row][col - 1] == TARGET) {
			room[row][col - 1] = PERSON_ON_TARGET;
			room[row][col] = BOX_ON_TARGET;
			room[row][col + 1] = TARGET;
		}
	}
	else if (input == 's' && box == '1') {
		if (room[row][col] == PERSON && room[row + 1][col] == BOX && room[row - 1][col] == SPACE) {
			room[row - 1][col] = PERSON;
			room[row][col] = BOX;
			room[row + 1][col] = SPACE;
		}
		else if (room[row][col] == PERSON && room[row + 1][col] == BOX_ON_TARGET && room[row - 1][col] == SPACE) {
			room[row - 1][col] = PERSON;
			room[row][col] = BOX;
			room[row + 1][col] = TARGET;
		}
		else if (room[row][col] == PERSON && room[row + 1][col] == BOX && room[row - 1][col] == TARGET) {
			room[row - 1][col] = PERSON_ON_TARGET;
			room[row][col] = BOX;
			room[row + 1][col] = SPACE;
		}
		else if (room[row][col] == PERSON && room[row + 1][col] == BOX_ON_TARGET && room[row - 1][col] == TARGET) {
			room[row - 1][col] = PERSON_ON_TARGET;
			room[row][col] = BOX;
			room[row + 1][col] = TARGET;
		}
		else if (room[row][col] == PERSON_ON_TARGET && room[row + 1][col] == BOX && room[row - 1][col] == SPACE) {
			room[row - 1][col] = PERSON;
			room[row][col] = BOX_ON_TARGET;
			room[row + 1][col] = SPACE;
		}
		else if (room[row][col] == PERSON_ON_TARGET && room[row + 1][col] == BOX && room[row - 1][col] == TARGET) {
			room[row - 1][col] = PERSON_ON_TARGET;
			room[row][col] = BOX_ON_TARGET;
			room[row + 1][col] = SPACE;
		}
		else if (room[row][col] == PERSON_ON_TARGET && room[row + 1][col] == BOX_ON_TARGET && room[row - 1][col] == SPACE) {
			room[row - 1][col] = PERSON;
			room[row][col] = BOX_ON_TARGET;
			room[row + 1][col] = TARGET;
		}
		else if (room[row][col] == PERSON_ON_TARGET && room[row + 1][col] == BOX_ON_TARGET && room[row - 1][col] == TARGET) {
			room[row - 1][col] = PERSON_ON_TARGET;
			room[row][col] = BOX_ON_TARGET;
			room[row + 1][col] = TARGET;
		}
	}

	while (allMoves[j] != '\0') {
		j++;
	}
	allMoves[j - 2] = '\0';
}

/***********************************************************/
/***********************************************************/
/********* DO NOT MODIFY ANY CODE BELOW THIS POINT *********/
/***********************************************************/
/***********************************************************/

/* GetMove() returns the entered character. Invalid characters ignored */
char GetMove(void)
{
	char move;
	printf("\nEnter move: ");
	scanf("%c", &move);
	// Ignore any characters that are invalid
	while ((move != 'w') && (move != 'a') && (move != 's') && (move != 'd') && (move != 'z')) {
		scanf("%c", &move);
	}
	return move;
}

/* Boxed In Game */
int main(void)
{
	//EXAMPLE GAME 1
	//char layout[200] = "0011111000111005100010032011001002320100111043010000100011000011111000000000000000000000000000000000";
	//int room[ROWS][COLS] = { 0 };
	//char allMoves[1000] = { 0 };
	/*EXAMPLE GAME 2*/
	char layout[200] = "1111111111100000000110333000011030200001100025000110002000011030303001100000000110000000011111111111";
	int room[ROWS][COLS] = {0};
	char allMoves[1000]  = {0};

	printf("ENGGEN131 - C Project 2024\n");
	printf("                          ... presents ...\n");
	printf("   +------+  ____                    _   _____         _ \n");
	printf("  /      /| |  _ \\                  | | |_   _|       | |\n");
	printf(" +------+ | | |_) | _____  _____  __| |   | |  _ __   | |\n");
	printf(" |      | + |  _ < / _ \\ \\/ / _ \\/ _` |   | | | '_ \\  | |\n");
	printf(" |      |/  | |_) | (_) >  <  __/ (_| |  _| |_| | | | |_|\n");
	printf(" +------+   |____/ \\___/_/\\_\\___|\\__,_| |_____|_| |_| (_)\n");
	printf("\n");
	printf("\nMove the player (X) using the keys 'w', 'a', 's', 'd'\n");
	printf("Good luck!\n\n\n");

	/* Main game loop */
	InitialiseRoom(room, layout);
	PrintRoom(room);
	while (!CheckGameOver(room)) {
		MakeMove(room, GetMove(), allMoves);
		PrintRoom(room);
	}
	printf("\n\nCONGRATULATIONS!\nGame over!\n");
	printf("Moves: %s", allMoves);
	return 0;
}


