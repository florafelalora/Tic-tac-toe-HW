//
// Created by flow on 2020. 11. 23..
//

#include "game.h"

Point getSizeOfTable() {
    Point sizeOfTable = getPosition();
    if (sizeOfTable.x < 3 || sizeOfTable.y < 3) {
        printf("Kérlek próbáld újra, túl kicsi pályát adtál meg!\n");
        sizeOfTable = getSizeOfTable();
    }
    return sizeOfTable;
}


void startGame() {
    Point sizeOfTable = getSizeOfTable();
    Amoba *amoba = amobaCreate(sizeOfTable.y, sizeOfTable.x);

    printf("A választott pálya mérete: %dx%d, a nyeréshez %d hosszú csíkot kell leraknod.\n", sizeOfTable.y,
           sizeOfTable.x, amoba->lineToWin);
    bool running = true;
    while (running) {

        if (amoba->xmovesnext) {
            xMoves(amoba);
            amoba->xmovesnext = false;
        } else {
            amoba->isItSimulation = true;
            smartAI(amoba);
            amoba->xmovesnext = true;
            amoba->isItSimulation = false;
            amobaWriteOut(amoba);
        }
        running = isItStillRunning(amoba);
    }
    if (amoba->didSomeoneWon == true) {
        printf("%c nyert!\n", amoba->table[amoba->winningPoint.y][amoba->winningPoint.x]);
    } else {
        printf("Döntetlen\n");
    }
    amobaWriteOut(amoba);
    amobaDelete(amoba);
}