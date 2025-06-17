/**
 @file defines.h
 @brief neccessary includes, defines and structures in accordance with the task
 */

#ifndef DEFINES_H
#define DEFINES_H

#include <time.h>

#include <cstring>
#include <iostream>

#define Empty 0
#define Body 1
#define Head 2
#define Teil 3
#define Apple 4
#define WillBeHead 5
#define WillBeTeil 6

/// @brief enum of user input in accordance with the task
enum UserAction_t {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
};

/// @brief describes the game state in accordance with the task
typedef struct {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

#endif  // DEFINES_H