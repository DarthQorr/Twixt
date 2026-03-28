#include "twixt.h"

int lis[29][29] = {};

// 0 = Empty, 1 = Barrier2, 2 = Barrier1, 3 = Red player, 4 = Blue player
char *arr[7] = {".  ", "b  ","r  ","x  ","o  ","\n", "   "};

void build_environment(int ch, int steps, int x, int y, cell ** start){
    int c = 0;
    if(*start == NULL){
        c = 1;
        cell *newcell = malloc(sizeof(cell));
        newcell -> value = ch;
        newcell -> next = NULL;
        newcell -> prev = NULL;
        newcell -> x = x;
        newcell -> y = y;
        x++;

        *start = newcell;
    }
    cell *temp = *start;

    while(temp -> next != NULL){
        temp = temp -> next;
    }

    for(int i = 0; i < steps - c; i++){
        cell *newcell = malloc(sizeof(cell));
        newcell -> value = ch;
        newcell -> next = NULL;
        newcell -> prev = temp;
        newcell -> x = x;
        newcell -> y = y;
        x++;

        temp -> next = newcell;
        temp = newcell;
    }
}

void printline(cell **start){
    printf("0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27\n");
    cell *temp = *start;

    if(temp == NULL){
        printf("Null\n");
        return;
    }

    while(temp != NULL){
        printf("%s",arr[temp -> value]);
        if(temp -> next != NULL && temp -> next -> value == 5 && (temp -> y == 0 || temp -> y == 27))printf("    %d", temp -> y);
        else if(temp -> next != NULL && temp -> next -> value == 5)printf(" %d", temp -> y);
        temp = temp -> next;
    }
}

void initialise_environment(cell ** start){
    cell * head = *start;
    
    build_environment(6, 1, 0, 0, &head); build_environment(0,26,1,0,&head);build_environment(5,1,28,0,&head); 
    build_environment(0,1,0,1,&head);build_environment(1,1,1,1,&head);build_environment(2,24,2,1,&head);build_environment(2,1,26,1,&head);build_environment(0,1,27,1,&head);build_environment(5,1,28,1,&head);
    
    for(int y = 2; y < 26;y++){
        build_environment(0,1,0,y,&head); build_environment(1,1,1,y,&head);build_environment(0,24,2,y,&head);build_environment(1,1,26,y,&head); build_environment(0,1,27,y,&head);build_environment(5,1,28,y,&head);
    }

    build_environment(0,1,0,26,&head); build_environment(2,1,1,26,&head);build_environment(2,24,2,26,&head);build_environment(1,1,26,26,&head);build_environment(0,1,27,26,&head);build_environment(5,1,27,26,&head);
    build_environment(6, 1, 0, 27,&head);build_environment(0,26,1,27,&head);build_environment(5,1,27,27,&head);

    *start = head;
}

int refer(int x, int y, cell *head){
    cell *temp = head;
    while(temp != NULL){
        if(temp -> x == x && temp -> y == y){
            return temp -> value;
        }
        temp = temp -> next;
    }
    return -1;
}

void update(int x, int y, int change, cell **head){
    cell * temp = *head;
    while(temp != NULL){
        if(temp -> x == x && temp -> y == y){
            temp -> value = change;
            return;
        }
        temp = temp -> next;
    }
    printf("Cell not found!\n");
}

int conditions(int x, int y, int col){
    if(x < 0 || x > 27 || y < 0 || y > 27) return 0;

    if ((x == 0 && y == 0) || (x == 27 && y == 0) || (x == 0 && y == 27) || (x == 27 && y == 27)) return 0;
    if ((x == 1 || x == 26) && (y >= 1 && y <= 26)) return 0;
    if ((y == 1 || y == 26) && (x >= 1 && x <= 26)) return 0;

    if(col == 0 && (x == 0 || x == 27)) return 0;
    if(col == 1 && (y == 0 || y == 27)) return 0;
    
    if(lis[x][y] != 0) return 0;

    return 1;
}

int mull_win_0(int x, int y, cell *head, int visited[29][29]){

    if(x < 0 || x > 27 || y < 0 || y > 27) return 0;
    
    if(visited[x][y] == 1) return 0;
    if(refer(x,y,head) != 3) return 0;
    if(y == 27) return 1;

    visited[x][y] = 1;

    if(mull_win_0(x-2, y-1, head, visited)) return 1;
    if(mull_win_0(x-2, y+1, head, visited)) return 1;
    if(mull_win_0(x+2, y-1, head, visited)) return 1;
    if(mull_win_0(x+2, y+1, head, visited)) return 1;
    if(mull_win_0(x-1, y+2, head, visited)) return 1;
    if(mull_win_0(x+1, y+2, head, visited)) return 1;
    if(mull_win_0(x-1, y-2, head, visited)) return 1;
    if(mull_win_0(x+1, y-2, head, visited)) return 1;
    
    return 0;
}

int mull_win_1(int x, int y, cell *head, int visited[29][29]){

    if(x < 0 || x > 27 || y < 0 || y > 27) return 0;
    
    if(visited[x][y] == 1) return 0;
    if(refer(x,y,head) != 4) return 0;
    if(x == 27) return 1;

    visited[x][y] = 1;

    if(mull_win_1(x-2, y-1, head, visited)) return 1;
    if(mull_win_1(x-2, y+1, head, visited)) return 1;
    if(mull_win_1(x+2, y-1, head, visited)) return 1;
    if(mull_win_1(x+2, y+1, head, visited)) return 1;
    if(mull_win_1(x-1, y+2, head, visited)) return 1;
    if(mull_win_1(x+1, y+2, head, visited)) return 1;
    if(mull_win_1(x-1, y-2, head, visited)) return 1;
    if(mull_win_1(x+1, y-2, head, visited)) return 1;

    return 0;
}