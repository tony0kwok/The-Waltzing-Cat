//
//  Cat.c
//  The Waltzing Cat
//
//  Created by Kwok Tung Lim on 14/8/2017.
//  Copyright © 2017 Kwok Tung Lim. All rights reserved.
//

#include "Cat.h"
#include <stdlib.h>
#include <time.h>

int UI(struct Player *cplayer){     //without callend() nplayer is no need
    char *control = (char*)malloc(sizeof(char));
    int pst;
    char push = 's';
    char pull = 'l';
    char call;
    printf("Push(s) or Pull(l)?");
    scanf("%s", control);
    printf("Position? (1~11)");
    scanf("%d", &pst);
    int mpst = pst-1; //modiflied position
    if (mpst<0||mpst>10){
        printf("invalid input\n");
        return 0;
    }
    if (*control==push) {
        if(cplayer->board[mpst].down!=0){
            printf("position is taken\n");
            return 0;
        }
        if(repeat(cplayer, pushdown(cplayer, mpst), mpst, 1))
        printf("You have gained 1 cats.\n");
    }
    else{
        if(cplayer->board[mpst].down!=0){
            printf("position is taken\n");
            return 0;
        }
        if (*control==pull) {
                if(repeat(cplayer, pulldown(cplayer, mpst), mpst, 2))
                printf("You have gained 2 cats.\n");
        }
        else{
                printf("invalid input\n");
                return 0;
        }
    }
    return 1;
    
}

int time_rand(){
        int ue_imsi;
        int seed = (int)time(NULL);
        srand(seed);
        ue_imsi = rand();
        return ue_imsi;
}

void color(int x){
    switch (x) {
        case 0:
            printf("%3s", "");
            break;
        case 1:
            printf("%3s", "Go");
            break;
        case 2:
            printf("%3s", "Re");
            break;
        case 3:
            printf("%3s", "Bl");
            break;
        case 4:
            printf("%3s", "Da");
            break;
        case 5:
            printf("%3s", "Gr");
            break;
        case 6:
            printf("%3s", "Wh");
            break;
        default:
            printf("\nthe type of board is incorrect\n");
            break;
    }
}

void gen_cat(struct cat *c){
    c->type = 0; //cat0(gold,red)
    c->back = red;
    c->front = gold;
    c->reverse = 0;
    
    (c+1)->type = 1; //cat1(gold,blue)
    (c+1)->back = blue;
    (c+1)->front = gold;
    (c+1)->reverse = 0;
    
    (c+2)->type = 2; //cat2(gold,dark)
    (c+2)->back = dark;
    (c+2)->front = gold;
    (c+2)->reverse = 0;
    
    (c+3)->type = 3; //cat3(gold,grey)
    (c+3)->back = grey;
    (c+3)->front = gold;
    (c+3)->reverse = 0;
    
    (c+4)->type = 4; //cat4(gold,white)
    (c+4)->back = white;
    (c+4)->front = gold;
    (c+4)->reverse = 0;
    
    (c+5)->type = 5; //cat5(red,dark)
    (c+5)->back = dark;
    (c+5)->front = red;
    (c+5)->reverse = 0;
    
    (c+6)->type = 6; //cat6(red,grey);
    (c+6)->back = grey;
    (c+6)->front = red;
    (c+6)->reverse = 0;
    
    (c+7)->type = 7; //cat7(red,white);
    (c+7)->back = white;
    (c+7)->front = red;
    (c+7)->reverse = 0;
    
    (c+8)->type = 8; //cat8(blue,dark);
    (c+8)->back = dark;
    (c+8)->front = blue;
    (c+8)->reverse = 0;
    
    (c+9)->type = 9; //cat9(blue,grey);
    (c+9)->back = grey;
    (c+9)->front = blue;
    (c+9)->reverse = 0;
    
    (c+10)->type = 10; //cat10(blue,white);
    (c+10)->back = white;
    (c+10)->front = blue;
    (c+10)->reverse = 0;
}

void reset(struct Player *player1, struct Player *player2, struct catnode *gameboard, int *numofdown, int *gameup, int *gamedown){
    player1->player = 1;
    player2->player = 2;
    player1->board = gameboard;
    player2->board = gameboard;
    player1->numofdown = numofdown;
    player2->numofdown = numofdown;
    player1->up = gameup;
    player2->up = gameup;
    player1->bottom = gamedown;
    player2->bottom = gamedown;
    for(int i=0;i<7;i++){
        player1->score[i] = 0;
        player2->score[i] = 0;
    }
    for (int i = 0; i<11; i++) {
        player1->up[i] = 0;
        player1->bottom[i] = 0;
    }
}

void gen_board_ori(struct catnode *board, struct cat *c){
    int i,x;
    for (i = 0; i<11; i++) {
        if((c+i)->reverse != 0){
            (c+i)->reverse = 0;
            x = (c+i)->front;
            (c+i)->front = (c+i)->back;
            (c+i)->back = x;
        }
    }
    for (i = 0; i<11; i++) {    //assign the cards to board
        (board+i)->down = 0;
        (board+i)->type = i;
        (board+i)->Cat = (c+i);
    }
}

void gen_board(struct catnode *board, struct cat *c){
    int card[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int i, j, x = 11;
    for (i = 11; i; ) { //shuffle the cards
        j = rand() % i;
        x = card[--i];
        card[i] = card[j];
        card[j] = x;
    }
    for (i = 0; i<11; i++) {    //reverse the cards
        j = rand()%2;
        if ((c+i)->reverse!=j) {
            (c+i)->reverse = j;
            x = (c+i)->front;
            (c+i)->front = (c+i)->back;
            (c+i)->back = x;
        }
    }
    for (i = 0; i<11; i++) {    //assign the cards to board
        (board+i)->down = 0;
        (board+i)->type = card[i];
        (board+i)->Cat = (c+card[i]);
    }
};

void view(struct Player *cplayer){
    printf("%3d%3d%3d%3d%3d%3d%3d%3d%3d%3d%3d\n",1,2,3,4,5,6,7,8,9,10,11);
    if(cplayer->player==1)
        for (int i = 0; i<11; i++) {
            color((cplayer->up)[i]);
        }
    else
        for (int i = 0; i<11; i++) {
            color((cplayer->bottom)[i]);
        }

    printf("\n");
    if(cplayer->player==1)
        for (int i = 0; i<11; i++) {
            if((cplayer->board)[i].down)
                printf("%3s", "");
            else
                color((cplayer->board)[i].Cat->front);
        }
    else
        for (int i = 0; i<11; i++) {
            if((cplayer->board)[i].down)
                printf("%3s", "");
            else
            color((cplayer->board)[i].Cat->back);
        }
    printf("\n");
    if(cplayer->player==1)
        for (int i = 0; i<11; i++) {
            color((cplayer->bottom)[i]);
        }
    else
        for (int i = 0; i<11; i++) {
            color((cplayer->up)[i]);
        }
    printf("\n");
}

void view_all(struct Player *cplayer){
    printf("%3d%3d%3d%3d%3d%3d%3d%3d%3d%3d%3d\n",1,2,3,4,5,6,7,8,9,10,11);
    if(cplayer->player==1)
        for (int i = 0; i<11; i++) {
            color((cplayer->up)[i]);
        }
    else
        for (int i = 0; i<11; i++) {
            color((cplayer->bottom)[i]);
        }
    printf("\n");
        for (int i = 0; i<11; i++) {
            if((cplayer->board)[i].down)
                printf("%3s", "");
            else
                color((cplayer->board)[i].Cat->back);
        }
    printf("\n");
    for (int i = 0; i<11; i++) {
        if((cplayer->board)[i].down)
            printf("%3s", "");
        else
            color((cplayer->board)[i].Cat->front);
    }
    printf("\n");
    for (int i = 0; i<11; i++) {
        printf("%3d", (cplayer->board)[i].Cat->type);
    }
    printf("\n");
    if(cplayer->player==1)
        for (int i = 0; i<11; i++) {
            color((cplayer->bottom)[i]);
        }
    else
        for (int i = 0; i<11; i++) {
            color((cplayer->up)[i]);
        }
    printf("\n");
}

int pushdown(struct Player *cplayer, int mpst){ //pst:position
    int color;
    if((cplayer->board+mpst)->down){
        printf("the card is already down, please select again\n");
        return -1;
    }
    if (cplayer->player==1) {
        (cplayer->board+mpst)->down = tofront;
        color = (cplayer->board+mpst)->Cat->front;
        (cplayer->up)[mpst] = color;
    }
    else{
        (cplayer->board+mpst)->down = toback;
        color = (cplayer->board+mpst)->Cat->back;
        (cplayer->bottom)[mpst] = color;
    }
    *(cplayer->numofdown) = *(cplayer->numofdown)+1;
    return color;
}

int pulldown(struct Player *cplayer, int mpst){
    int color;
    if((cplayer->board+mpst)->down){
        printf("the card is already down, please select again\n");
        return -1;   //invalid input
    }
    if (cplayer->player==2) {
        (cplayer->board+mpst)->down = tofront;
        color = (cplayer->board+mpst)->Cat->front;
        (cplayer->up)[mpst] = color;
    }
    else{
        (cplayer->board+mpst)->down = toback;
        color = (cplayer->board+mpst)->Cat->back;
        (cplayer->bottom)[mpst] = color;
    }
    *(cplayer->numofdown) = *(cplayer->numofdown)+1;
    return color;
};

int callend_question(){
    char *control = (char*)malloc(sizeof(char));
    char call = 'c';
    printf("Callend?(c)\n");
    scanf("%s", control);
    if (*control==call) {
        return 1;
    }
    return 0;
}

int callend(struct Player *cplayer, struct Player *nplayer){
    printf("Let's invite Player%d to put down all the masks~\n", nplayer->player);
    view(nplayer);
    while (*(nplayer->numofdown)<11) {
        char *control = (char*)malloc(sizeof(char));
        int pst;
        printf("Push(s) or Pull(l)?");
        scanf("%s", control);
        printf("Position? (1~11)");
        scanf("%d", &pst);
        int mpst = pst-1; //modiflied position
        char push = 's';
        char pull = 'l';
        if (mpst<0||mpst>10){
            printf("invalid input\n");
            continue;
        }
        if (*control==push) {
            if(nplayer->board[mpst].down!=0){
                printf("position is taken\n");
                continue;
            }
            pushdown(nplayer, mpst);
        }
        else{
            if(nplayer->board[mpst].down!=0){
                printf("position is taken\n");
                continue;
            }
            if (*control==pull) {
                pulldown(nplayer, mpst);
            }
            else{
                printf("invalid input\n");
                continue;
            }
        }
        view(nplayer);
    }
    repeat(nplayer, -1, -1, 0);
    printf("Let's invite Player%d to take all remaining and finish the GAME~\n", cplayer->player);
    gain_all(cplayer);
    printf("Game Over\n");
    return 0;
}

int endgame(struct catnode *board){
    for (int i = 0; i<11; i++) {
        if(board[i].down==0)
            return 0;
    }
    printf("Game Over\n");
    return 1;
}

//find the position of the first cat of that color
//the position map:
//up        11|12|13|14|15|16|17|18|19|20|21
//middle     1| 2| 3| 4| 5| 6| 7| 8| 9|10|11
//bottom    22|23|24|25|26|27|28|29|30|31|32

int repeat(struct Player *cplayer, int color, int mpst, int downtype){
    int num = 0;
    int color_arr[7] = {0};
    switch (downtype) {         //downtype: push(1), pull(2), all pair(0)
        case 0:                                    //gain all pair   (can be developed to another func)
            for (int i = 0; i<11; i++) {
                if (cplayer->up[i]!=0) {
                    color_arr[cplayer->up[i]]++;
                }
                if (cplayer->bottom[i]!=0) {
                    color_arr[cplayer->bottom[i]]++;
                }
            }
            for (int i = 1; i<7; i++) {
                if (color_arr[i]>=2) {
                    repeat(cplayer, i, -1, 2);
                    color_arr[i] -= 2;
                    i--;
                    num += 2;
                }
            }
            printf("You have gained %d cats\n", num);
            break;
        case 1:                                    // gain one cat
            for (int i = 0; i<11; i++) {
                if (i!=mpst) {
                    if (cplayer->up[i]==color) {
                        gain(cplayer, 11+i);
                        return 1;
                        break;
                    }
                    if (cplayer->bottom[i]==color) {
                        gain(cplayer, 22+i);
                        return 1;
                        break;
                    }
                }
            }
            return 0;
            break;
        case 2:                                     //gain a pair
            for (int i = 0; i<11; i++) {
                if (i!=mpst) {
                    if (cplayer->up[i]==color) {
                        gain(cplayer, 11+i);
                        repeat(cplayer, color, i, 1);
                        return 2;
                        break;
                    }
                    if (cplayer->bottom[i]==color) {
                        gain(cplayer, 22+i);
                        repeat(cplayer, color, i, 1);
                        return 2;
                        break;
                    }
                }
            }
            return 0;
            break;
        default:
            printf("Error: downtype error");
            return 0;
            break;
    }
    return 0;
};

int gain(struct Player *cplayer, int mpst){
    if (mpst>32||mpst<11) {
        printf("Error: invalid position");
        return 0;
    }
    if (mpst>21) {
        int x = mpst%11;
        cplayer->score[(cplayer->bottom[x])]++;
        cplayer->bottom[x] = 0;         //erase cat from bottom
        return 1;
    }
    else{
        int x = mpst%11;
        cplayer->score[(cplayer->up[x])]++;
        cplayer->up[x] = 0;         //erase cat from up
        return 1;
    }
}

void gain_all(struct Player *cplayer){
    int count = 0;
    for (int i = 0; i<11; i++) {
        if (cplayer->up[i]!=0) {
            (cplayer->score[cplayer->up[i]])++;
            cplayer->up[i] = 0;
            count++;
        }
        else{
            if (cplayer->bottom[i]!=0) {
                (cplayer->score[cplayer->bottom[i]])++;
                cplayer->bottom[i] = 0;
                count++;
            }
        }
    }
    printf("You have gained %d cats\n", count);
}

int scorecount(struct Player *cplayer){
    int total = (cplayer->score[1])*2;
    for (int i = 2; i<=6; i++) {
        total += cplayer->score[i];
    }
    int min = 0;
    if(cplayer->score[2]>0&&cplayer->score[3]>0){
        min = cplayer->score[2];
        if (cplayer->score[3]<min) {
            min = cplayer->score[3];
        }
        total += min*3;
    }
    return total;
}

