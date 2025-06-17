/**
 @file frontend.h
 @brief declaration of console interface functions
 */

#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <unistd.h>

#include "../../brick_game/defines.h"

void printField(WINDOW *field, GameInfo_t game, int height, int width);
void printPanel(WINDOW *panel, GameInfo_t game);
int endOfGame(GameInfo_t game, int height, int width, WINDOW *field,
              WINDOW *panel);
void printPause(WINDOW *panel, GameInfo_t game);
void printAll(WINDOW *panel, WINDOW *field, GameInfo_t game, int height,
              int width);
UserAction_t keyPress(int game);

#endif  // FRONTEND_H