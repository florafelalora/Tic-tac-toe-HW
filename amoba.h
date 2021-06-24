//
// Created by flow on 2020. 11. 22..
//

#ifndef AMOBA_AMOBA_H
#define AMOBA_AMOBA_H

#include <stdlib.h>
#include<stdio.h>
#include <stdbool.h>
#include <string.h>

#define INF 0xFFFFFFF

typedef struct Point {
    int y;
    int x;
} Point;

typedef struct Amoba {
    bool xmovesnext;
    int y;
    int x;
    //00-tól indexelve, yx formátum
    char **table;
    bool isItSimulation;
    int lineToWin;
    Point winningPoint;
    bool didSomeoneWon;
    int howDidItWin;
    int alpha;
    int beta;
    Point firstMoveToOptimal;
} Amoba;

int scanCoord();

Amoba *amobaCreate(int y, int x);

Amoba* copyAmoba(Amoba* amoba);

void amobaDelete(Amoba *amoba);

void amobaWriteOut(Amoba *amoba);

Point getPosition();

void putXthere(Amoba *amoba, Point p);

void xMoves(Amoba *amoba);

bool isItStillRunning(Amoba *amoba);

#endif //AMOBA_AMOBA_H
