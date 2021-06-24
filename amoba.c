//
// Created by flow on 2020. 11. 22..
//

#include "amoba.h"

Amoba *amobaCreate(int y, int x) {
    Amoba *amoba = malloc(sizeof(Amoba));
    amoba->xmovesnext = true;
    amoba->y = y;
    amoba->x = x;
    amoba->table = (char **) malloc(amoba->y * sizeof(char *));

    for (int i = 0; i < amoba->y; i++) {
        amoba->table[i] = (char *) malloc(amoba->x * sizeof(char));
    }
    for (int i = 0; i < amoba->y; i++) {
        for (int j = 0; j < amoba->x; j++) {
            amoba->table[i][j] = ' ';
        }
    }
    amoba->isItSimulation = false;
    if (amoba->x == 3 || amoba->y == 3) {
        amoba->lineToWin = 3;
    } else if (amoba->x == 4 || amoba->y == 4) {
        amoba->lineToWin = 4;
    } else {
        amoba->lineToWin = 5;
    }
    amoba->didSomeoneWon = false;
    amoba->howDidItWin=0;
    amoba->alpha=-INF;
    amoba->beta=INF;
    amoba->firstMoveToOptimal.y=-1;
    amoba->firstMoveToOptimal.x=-1;
    return amoba;
}

Amoba* copyAmoba(Amoba* amoba){
    Amoba* am=amobaCreate(amoba->y, amoba->x);
    am->xmovesnext=amoba->xmovesnext;
    for (int y = 0; y < am->y; ++y) {
        for (int x = 0; x < am->x; ++x) {
            am->table[y][x]=amoba->table[y][x];
        }
    }
    am->isItSimulation=amoba->isItSimulation;
    am->lineToWin=amoba->lineToWin;
    am->winningPoint=amoba->winningPoint;
    am->didSomeoneWon=amoba->didSomeoneWon;
    am->howDidItWin=amoba->howDidItWin;
    am->alpha=amoba->alpha;
    am->beta=amoba->beta;
    am->firstMoveToOptimal.y=amoba->firstMoveToOptimal.y;
    am->firstMoveToOptimal.x=amoba->firstMoveToOptimal.x;
    return am;
}

void amobaDelete(Amoba *amoba) {
    for (int i = 0; i < amoba->y; i++) {
        free(amoba->table[i]);
    }
    free(amoba->table);
    free(amoba);
}

void amobaWriteOut(Amoba *amoba) {
    for (int i = 0; i < amoba->y; i++) {
        for (int j = 0; j < amoba->x; j++) {
            printf("%c", amoba->table[i][j]);
        }
        printf("\n");
    }
}

int scanCoord() {
    int num;
    char typo;
    if (scanf("%d%c", &num, &typo) != 2 || typo != '\n') {
        {
            typo = getchar();
        }
        while (getchar() != '\n');
        printf("Kérlek próbáld újra!\n");
        num = scanCoord();
    }
    return num;
}

Point getPosition() {
    Point p;
    p.y = scanCoord();
    p.x = scanCoord();
    return p;
}

void putXthere(Amoba *amoba, Point p) {
    if(amoba->y<=p.y||amoba->x<=p.x){
        printf("A pálya kisebb, oda nem tudsz tenni! Kérlek próbáld meg újra!\n");
        xMoves(amoba);
    }else if (amoba->table[p.y][p.x] == ' ') {
        amoba->table[p.y][p.x] = 'X';
    } else {
        printf("A hely már foglalt, válassz újat!\n");
        xMoves(amoba);
    }
}

void xMoves(Amoba *amoba) {
    Point p = getPosition();
    putXthere(amoba, p);
}

bool isItStillRunning(Amoba *amoba) {
    //sorban van-e nyerés
    for (int i = 0; i < amoba->y; ++i) {
        for (int j = 0; j < amoba->x - amoba->lineToWin + 1; ++j) {
            if (amoba->table[i][j] != ' ') {
                for (int k = 1; k < amoba->lineToWin; ++k) {
                    if (amoba->table[i][j] != amoba->table[i][j + k]) {
                        break;
                    }else if(k==amoba->lineToWin-1){
                        amoba->winningPoint.y = i;
                        amoba->winningPoint.x = j;
                        amoba->didSomeoneWon = true;
                        amoba->howDidItWin=1;
                        return false;
                    }
                }

            }
        }
    }
    //oszlopban van-e nyerés
    for (int i = 0; i < amoba->y - amoba->lineToWin + 1; ++i) {
        for (int j = 0; j < amoba->x; ++j) {
            if (amoba->table[i][j] != ' ') {
                for (int k = 1; k < amoba->lineToWin; ++k) {
                    if (amoba->table[i][j] != amoba->table[i + k][j]) {
                        break;
                    }else if(k==amoba->lineToWin-1){
                        amoba->winningPoint.y = i;
                        amoba->winningPoint.x = j;
                        amoba->didSomeoneWon = true;
                        amoba->howDidItWin=2;
                        return false;
                    }

                }

            }
        }
    }
    //bal átlóban van-e nyerés
    for (int i = 0; i < amoba->y - amoba->lineToWin + 1; ++i) {
        for (int j = 0; j < amoba->x - amoba->lineToWin + 1; ++j) {
            if (amoba->table[i][j] != ' ') {
                for (int k = 1; k < amoba->lineToWin; ++k) {
                    if (amoba->table[i][j] != amoba->table[i + k][j + k]) {
                        break;
                    }else if(k==amoba->lineToWin-1){
                        amoba->winningPoint.y = i;
                        amoba->winningPoint.x = j;
                        amoba->didSomeoneWon = true;
                        amoba->howDidItWin=3;
                        return false;
                    }
                }


            }
        }
    }
    //jobb átlóban van-e nyerés
    for (int i = 0; i < amoba->y - amoba->lineToWin + 1; ++i) {
        for (int j = 0 + amoba->lineToWin - 1; j < amoba->x; ++j) {
            if (amoba->table[i][j] != ' ') {
                for (int k = 1; k < amoba->lineToWin; ++k) {
                    if (amoba->table[i][j] != amoba->table[i + k][j - k]) {
                        break;
                    }else if(k==amoba->lineToWin-1){
                        amoba->winningPoint.y = i;
                        amoba->winningPoint.x = j;
                        amoba->didSomeoneWon = true;
                        amoba->howDidItWin=4;
                        return false;
                    }
                }

            }
        }
    }
    //van-e még üres hely a táblán
    for (int i = 0; i < amoba->y; ++i) {
        for (int j = 0; j < amoba->x; ++j) {
            if (amoba->table[i][j] == ' ') {
                return true;
            }
        }
    }
    amoba->howDidItWin=5;
    return false;
}