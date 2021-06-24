//
// Created by flow on 2020. 11. 23..
//

#ifndef AMOBA_AI_H
#define AMOBA_AI_H

#include "amoba.h"
//Mert csak... avagy test with eval
#define INF 0xFFFFFFF

Point firstFreeCell(Amoba* amoba);

void dumbAI(Amoba *amoba);

int calculateValueOfEnding(Amoba* amoba);

int max(int a, int b);

int min(int a, int b);

int minimax(Amoba* amoba, int depth, bool maximizing);

Point optimalCell(Amoba* amoba);

void smartAI(Amoba *amoba);

#endif //AMOBA_AI_H