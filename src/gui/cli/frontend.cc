/**
 @file frontend.cc
 @brief implementation of console interface functions
 */

#include "frontend.h"

/// @brief main field draw function
/// @param field window with game field
/// @param game current GameInfo_t
/// @param height number of rows
/// @param width number of cols
void printField(WINDOW *field, GameInfo_t game, int height, int width) {
  int curr_game = 1;
  if (game.next[0][0] < 0) curr_game = 2;
  wprintw(field, "\n");
  for (int i = 2; i < height - 2; i++) {
    wprintw(field, " ");
    for (int j = 2; j < width - 2; j++) {
      int type = abs(game.field[i][j] / 100);
      if (curr_game == 1) {
        if (game.field[i][j] == 0 || game.field[i][j] == 3)
          type = Empty;
        else
          type = Body;
      }
      if (type == Empty)
        wprintw(field, "  ");
      else if (type == Apple)
        wprintw(field, "()");
      else if (type == Body || type == Teil)
        wprintw(field, "[]");
      else if (type == Head)
        wprintw(field, "{}");
    }
    wprintw(field, "\n");
  }
}

/// @brief main panel print function
/// @param panel window with information panel
/// @param game current GameInfo_t
void printPanel(WINDOW *panel, GameInfo_t game) {
  wprintw(panel, "\n\n");
  if (game.score < game.high_score)
    wprintw(panel, "     Record: %d", game.high_score);
  else
    wprintw(panel, "     Record: %d", game.score);
  wprintw(panel, "\n\n");
  wprintw(panel, "    Current score:\n\n%12d", game.score);
  wprintw(panel, "\n\n");
  wprintw(panel, "       Level: %d", game.level);
  wprintw(panel, "\n\n");
  if (game.pause == 1)
    wprintw(panel, "      Pause: on\n    Press any key\n     to continue\n");
  else if (game.pause == 3)
    wprintw(panel, "\n    Press any key\n       to begin\n");
  else if (game.pause == 2)
    wprintw(panel,
            "     Game is over\n\n  Press R to restart\n     or Q to exit");
  else if (game.pause == 4)
    wprintw(panel, "     You win!\n\n  Press R to restart\n     or Q to exit");
  else
    wprintw(panel, "      Pause: off\n\n\n");
  wprintw(panel, "\n\n");
  int curr_game = 1;
  if (game.next[0][0] < 0) curr_game = 2;
  if (curr_game == 1) {
    wprintw(panel, "     Next figure:");
    wprintw(panel, "\n");
    for (int i = 0; i < 4; i++) {
      wprintw(panel, "       ");
      for (int j = 0; j < 4; j++) {
        if (game.next[i][j] == 1)
          wprintw(panel, "[]");
        else
          wprintw(panel, "  ");
      }
      wprintw(panel, "\n");
    }
  }
}

/// @brief the state after gameover or victory
/// @param game current GameInfo_t
/// @param height nu,ber of rows
/// @param width number of cols
/// @param field window with game field
/// @param panel window with information panel
/// @return 0 if choice is restart, 1 if quit
int endOfGame(GameInfo_t game, int height, int width, WINDOW *field,
              WINDOW *panel) {
  nodelay(stdscr, FALSE);
  wclear(field);
  wclear(panel);
  printField(field, game, height, width);
  box(field, 0, 0);
  wrefresh(field);
  printPanel(panel, game);
  box(panel, 0, 0);
  wrefresh(panel);
  int mode = 0;
  while (mode != 'r' && mode != 'q' && mode != 'R' && mode != 'Q')
    mode = getch();
  if (mode == 'r' || mode == 'R') {
    mode = 0;
  } else if (mode == 'q' || mode == 'Q') {
    mode = 1;
  }
  delwin(field);
  delwin(panel);
  return mode;
}

/// @brief stop the game in case of pause
/// @param panel window with information panel
/// @param game current GameInfo_t
void printPause(WINDOW *panel, GameInfo_t game) {
  if (game.pause == 1 || game.pause == 3) {
    wclear(panel);
    printPanel(panel, game);
    box(panel, 0, 0);
    wrefresh(panel);
    nodelay(stdscr, FALSE);
    getch();
    nodelay(stdscr, TRUE);
  }
}

/// @brief main print function
/// @param panel window with information panel
/// @param field window with game field
/// @param game current GameInfo_t
/// @param height number of rows
/// @param width number of cols
void printAll(WINDOW *panel, WINDOW *field, GameInfo_t game, int height,
              int width) {
  wclear(field);
  wclear(panel);
  printField(field, game, height, width);
  box(field, 0, 0);
  wrefresh(field);
  printPanel(panel, game);
  box(panel, 0, 0);
  wrefresh(panel);
  usleep(300 * game.speed);
}

/// @brief recieve input signals
/// @param game indicates which game is running now, 1 - tetris, 2 - snake
/// @return input mode
UserAction_t keyPress(int game) {
  int ch = getch();
  UserAction_t action = Up;
  if (game == 2) action = Action;
  if (ch == '\033') {
    getch();
    switch (getch()) {
      case 'B':
        action = Down;
        break;
      case 'C':
        action = Right;
        break;
      case 'D':
        action = Left;
        break;
      case 'A':
        action = Up;
        break;
    }
  }
  switch (ch) {
    case 'p':
      action = Pause;
      break;
    case 'P':
      action = Pause;
      break;
    case 'q':
      action = Terminate;
      break;
    case 'Q':
      action = Terminate;
      break;
    case ' ':
      action = Action;
  }
  return action;
}