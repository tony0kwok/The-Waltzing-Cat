//
//  main.c
//  The Waltzing Cat
//
//  Created by Kwok Tung Lim on 14/8/2017.
//  Copyright © 2017 Kwok Tung Lim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Cat.h"

int main(int argc, const char * argv[]) {
    struct Player player1;
    struct Player player2;
    int cplayer = 1;
    srand(time(NULL));
    struct catnode board[11];
    struct cat c[11];
    int numofdown = 0;
    int up[11] = {0};
    int down[11] = {0};
    gen_cat(c);
    reset(&player1, &player2, board, &numofdown, up, down);
    gen_board(player1.board, c);
    view_all(&player1);
    while (!endgame(board)) {
        if (cplayer==1) {
            view(&player1);
            if(callend_question()){
                callend(&player1, &player2);
                break;
            }
            while(!UI(&player1));
            view(&player1);
            cplayer = 2;
        }
        else{
            view(&player2);
            if(callend_question()){
                callend(&player2, &player1);
                break;
            }
            while(!UI(&player2));
            view(&player2);
            cplayer = 1;
        }
    }
    printf("Score of Player1 = %d\n", scorecount(&player1));
    printf("Score of Player2 = %d\n", scorecount(&player2));
    
    
    
    
    return 0;
}
