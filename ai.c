//
// Created by flow on 2020. 11. 23..
//
#include <math.h>
#include "ai.h"

Point firstFreeCell(Amoba* amoba){
    for (int i = 0; i < amoba->y; ++i) {
        for (int j = 0; j < amoba->x; ++j) {
            if (amoba->table[i][j] == ' ') {
                Point p;
                p.y=i;
                p.x=j;
                return p;
            }
        }

    }
}

void dumbAI(Amoba *amoba) {
    Point p=firstFreeCell(amoba);
    amoba->table[p.y][p.x]='0';
}

int calculateValueOfEnding(Amoba* amoba){
    if (isItStillRunning(amoba) == true){
        return 0;
    }else{
        if(amoba->didSomeoneWon==false){
            return 0;
        }else{
            if(amoba->table[amoba->winningPoint.y][amoba->winningPoint.x]=='X'){
                return -10;
            }else if(amoba->table[amoba->winningPoint.y][amoba->winningPoint.x]=='0'){
                return 10;
            }
        }
    }
}

int max(int a, int b){
    if(a>b){
        return a;
    }else{
        return b;
    }
}

int min(int a, int b){
    if (a<b){
        return a;
    }else{
        return b;
    }
}

int minimax(Amoba* amoba, int depth, bool maximizing){
    if(depth==0 || isItStillRunning(amoba) == false){
        return calculateValueOfEnding(amoba);
    }
    int value=0;
    if (maximizing==true){
        value=-INF;
        for (int i = 0; i < amoba->y; ++i) {
            for (int j = 0; j < amoba->x; ++j) {
                if (amoba->table[i][j]==' '){
                    amoba->table[i][j]='0';
                    value=max(value, minimax(amoba, depth - 1, false));
                    amoba->table[i][j]=' ';
                    if (value!=0){
                        value=value-1;
                    }
                }
            }
        }
    }else{
        value=INF;
        for (int i = 0; i < amoba->y; ++i) {
            for (int j = 0; j < amoba->x; ++j) {
                if (amoba->table[i][j]==' '){
                    amoba->table[i][j]='X';
                    value=min(value, minimax(amoba, depth - 1, true));
                    amoba->table[i][j]=' ';
                    if (value!=0){
                        value=value+1;
                    }
                }
            }
        }
    }
    return value;
}

int alphabeta(Amoba* amoba, int depth, bool maximizing){
    if(depth==0 || isItStillRunning(amoba) == false){
        return calculateValueOfEnding(amoba);
    }
    int value=0;
    if (maximizing==true){
        value=-INF;
        for (int i = 0; i < amoba->y; ++i) {
            for (int j = 0; j < amoba->x; ++j) {
                if (amoba->table[i][j]==' '){
                    amoba->table[i][j]='0';
                    value=max(value, alphabeta(amoba, depth - 1, false));
                    amoba->table[i][j]=' ';
                    if (value!=0){
                        value=value-1;
                    }
                    amoba->alpha=max(amoba->alpha, value);
                    if(amoba->alpha>=amoba->beta){
                        break;
                    }
                }
            }
        }
    }else{
        value=INF;
        for (int i = 0; i < amoba->y; ++i) {
            for (int j = 0; j < amoba->x; ++j) {
                if (amoba->table[i][j]==' '){
                    amoba->table[i][j]='X';
                    value=min(value, alphabeta(amoba, depth - 1, true));
                    amoba->table[i][j]=' ';
                    if (value!=0){
                        value=value+1;
                    }
                    amoba->beta=min(amoba->beta, value);
                    if (amoba->beta<=amoba->alpha){
                        break;
                    }
                }
            }
        }
    }
    return value;
}

Point optimalCell(Amoba* amoba){
    int bestValue=-INF;
    Point optimal=firstFreeCell(amoba);
    for (int i = 0; i < amoba->y; ++i) {
        for (int j = 0; j < amoba->x; ++j) {
            if (amoba->table[i][j]==' '){
                amoba->table[i][j]='0';
                //int currentValue=minimax(amoba, 4, false);
                int currentValue=alphabeta(amoba, 6, false);
                amoba->didSomeoneWon=false;
                amoba->howDidItWin=0;
                amoba->alpha=-INF;
                amoba->beta=INF;
                amoba->table[i][j]=' ';
                if(currentValue>bestValue){
                    bestValue=currentValue;
                    optimal.y=i;
                    optimal.x=j;
                }
            }
        }
    }
    return optimal;
}

void smartAI(Amoba *amoba) {
    Point p=optimalCell(amoba);
    amoba->table[p.y][p.x]='0';
}