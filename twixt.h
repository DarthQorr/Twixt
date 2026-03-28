#ifndef TWIXT_H
#define TWIXT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cell{
    int x;
    int y;
    int value;
    struct cell *next;
    struct cell *prev;
} cell;

extern int lis[29][29];

void initialise_environment(cell ** start);
void printline(cell **start);
int refer(int x, int y, cell *head);
void update(int x, int y, int change, cell **head);
int conditions(int x, int y, int col);
int mull_win_0(int x, int y, cell *head, int visited[29][29]);
int mull_win_1(int x, int y, cell *head, int visited[29][29]);

#endif