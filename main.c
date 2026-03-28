#include "twixt.h"

int main(){
    cell *head = NULL;
    initialise_environment(&head);
    printline(&head);

    printf("Twixt Offline!\n");
    printf("Enter coordinates as 'x y'. Enter '0 0' to exit.\n");

    int visited[29][29];

    for(;;){
        int x,y;
        int leave = 0;

        // RED TURN
        while(1){
            printf("\nRed (x): ");
            scanf(" %d %d",&x,&y);

            if(x == 0 && y == 0){
                leave = 1;
                break;
            }

            if(conditions(x,y,0) == 1){
                update(x,y,3, &head);
                lis[x][y] = 1;
            }else{
                printf("Invalid Move!\n");
                continue;
            }
            printf("\n");
            printline(&head);

            int win = 0;
            for(int i = 1; i <= 26; i++){
                if(refer(i, 0, head) == 3){
                    memset(visited, 0, sizeof(visited));
                    if(mull_win_0(i, 0, head, visited) == 1){
                        printf("\nRed Wins!\n");
                        win = 1;
                        leave = 1;
                        break;
                    }
                } 
            }
            if(win) break;
            break;
        }

        if(leave == 1) break;

        while(1){
            printf("\nBlue (o): ");
            scanf(" %d %d",&x,&y);

            if(x == 0 && y == 0){
                leave = 1;
                break;
            }

            if(conditions(x,y,1) == 1){
                update(x,y,4,&head);
                lis[x][y] = 1;
            } else{
                printf("Invalid Move!\n");
                continue;
            }
            printf("\n");
            printline(&head);

            int win = 0;
            for(int j = 1; j <= 26; j++){
                if(refer(0, j, head) == 4){
                    memset(visited, 0, sizeof(visited));
                    if(mull_win_1(0, j, head, visited) == 1){
                        printf("\nBlue wins!\n");
                        win = 1;
                        leave = 1;
                        break;
                    }
                } 
            }
            if(win) break;
            break;
        }

        if(leave == 1) break;
    }

    return 0;
}