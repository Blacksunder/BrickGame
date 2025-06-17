/**
 @file console.cc
 @brief A file with main and loops functios for a console brick game
 */

#include "../brick_game/tetris/backend_tetris.h"
#include "../gui/cli/frontend.h"

/// @brief main console tetris loop
void tetris() {
  s21::TetrisModel model;
  model.set();
  s21::TetrisController controller(&model);
  WINDOW *field = newwin(22, 22, 0, 0);
  WINDOW *panel = newwin(22, 22, 0, 25);
  nodelay(stdscr, TRUE);
  bool gameOver = false;
  GameInfo_t current_state = controller.get_GameInfo_t();
  while (!gameOver) {
    int timer = 0;
    while (timer < 15 && !gameOver) {
      controller.userInput(keyPress(1), false);
      current_state = controller.get_GameInfo_t();
      printAll(panel, field, current_state, 24, 14);
      if (current_state.pause == 3 || current_state.pause == 1) {
        printPause(panel, current_state);
        if (current_state.pause == 3)
          controller.userInput(Start, false);
        else if (current_state.pause == 1)
          controller.userInput(Pause, false);
      }
      ++timer;
      if (current_state.pause == 2) gameOver = true;
    }
    current_state = controller.updateCurrentState();
    if (current_state.pause == 2) gameOver = true;
  }
  if (!endOfGame(current_state, 24, 14, field, panel)) tetris();
}

/// @brief main console snake loop
void snake() {
  s21::Model model;
  model.set();
  s21::Controller controller(&model);
  WINDOW *field = newwin(22, 22, 0, 0);
  WINDOW *panel = newwin(22, 22, 0, 25);
  nodelay(stdscr, TRUE);
  bool gameOver = false, victory = false;
  GameInfo_t current_state = controller.get_GameInfo_t();
  while (!gameOver && !victory) {
    int timer = 0;
    while (timer < 15 && !gameOver) {
      controller.userInput(keyPress(2), false);
      current_state = controller.get_GameInfo_t();
      printAll(panel, field, current_state, 24, 14);
      if (current_state.pause == 3 || current_state.pause == 1) {
        printPause(panel, current_state);
        if (current_state.pause == 3)
          controller.userInput(Start, false);
        else if (current_state.pause == 1)
          controller.userInput(Pause, false);
      }
      ++timer;
      if (current_state.next[0][0] == -1) {
        timer = 0;
        *controller.get_next() = -2;
      }
      if (current_state.pause == 2)
        gameOver = true;
      else if (current_state.pause == 4)
        victory = true;
    }
    current_state = controller.updateCurrentState();
    if (current_state.pause == 2)
      gameOver = true;
    else if (current_state.pause == 4)
      victory = true;
  }
  if (!endOfGame(current_state, 24, 14, field, panel)) snake();
}

int main() {
  int choice = 0;
  std::cout << "Choose a game:\n1 - Tetris, 2 - Snake\nEnter your choice: ";
  std::cin >> choice;

  initscr();
  noecho();
  curs_set(0);

  if (choice == 1) {
    tetris();
  } else if (choice == 2) {
    snake();
  }

  endwin();
  return 0;
}