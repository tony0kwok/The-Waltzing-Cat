//
//  Cat.h
//  The Waltzing Cat
//
//  Created by Kwok Tung Lim on 14/8/2017.
//  Copyright © 2017 Kwok Tung Lim. All rights reserved.
//

#ifndef Cat_h
#define Cat_h

#include <stdio.h>

#define gold 1;
#define red 2;
#define blue 3;
#define dark 4;
#define grey 5;
#define white 6;
#define tofront 1;
#define toback -1;

struct cat{
    int type; //0~10
    int reverse; //boolean(useless now in design, please get rid of it or redesign it when you have time)
    int front; //color of the front
    int back;   //color of the back
};
struct catnode{
    int down; //front(1) or back(-1) or stand(0)
    int type; //0~10
    struct cat *Cat;
};
struct Player{
    int player; //1 or 2
    int score[7]; //How much cats have player gotten
    int *numofdown;
    struct catnode *board;
    int *up; //near to player2
    int *bottom; //near to player1
};

int UI(struct Player *cplayer);
int time_rand();
void color(int x);
void gen_cat(struct cat *c);
void gen_board_ori(struct catnode *board, struct cat *c);
void gen_board(struct catnode *board, struct cat *c);
void reset(struct Player *player1, struct Player *player2, struct catnode *gameboard, int *numofdown,int *up, int *down);
void view(struct Player *cplayer);
void view_all(struct Player *cplayer);
int pushdown(struct Player *cplayer, int mpst);
int pulldown(struct Player *cplayer, int mpst);
int callend_question();
int callend(struct Player *cplayer, struct Player *nplayer); //call a end
int endgame(struct catnode *board);
int repeat(struct Player *cplayer, int color, int mpst, int downtype);
int gain(struct Player *cplayer, int mpst);
void gain_all(struct Player *cplayer);
int scorecount(struct Player *cplayer);

#endif /* Cat_h */
