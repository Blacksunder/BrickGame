/**
 @file backend_tetris.cc
 @brief implementation of all tetris logic
 */

#include "backend_tetris.h"

/// @brief initializing matrix with nulles
/// @param matr pointer to matrix
/// @param height number of rows
/// @param width number of cols
void s21::TetrisModel::s21_null_matrix(int** matr, int height, int width) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      matr[i][j] = 0;
    }
  }
}

/// @brief default state of the field
void s21::TetrisModel::set() {
  GameInfo_t* game = GameInfo_mutator();
  s21_null_matrix(game->field, 24, 14);
  s21_null_matrix(game->next, 4, 4);
  game->level = 1;
  game->high_score = get_record();
  game->score = 0;
  game->speed = 25 - game->level * 2;
  game->pause = 3;
  figure = next_figure = 0;
}

/// @brief generate random number of the figure
/// @return number of the figure
int s21::TetrisModel::generate_figure() {
  srand(time(NULL));
  return rand() % 7;
}

/// @brief adding figure to the field
void s21::TetrisModel::add_figure() {
  GameInfo_t* game = GameInfo_mutator();
  int gameOver = 0;
  if (game->pause == 2) gameOver = 1;
  for (int j = 2; j < 12 && !gameOver; j++) {
    if (game->field[2][j] == 1) gameOver = 1;
  }
  if (!gameOver) {
    switch (figure) {
      case 0:
        gameOver = add_red();
        break;
      case 1:
        gameOver = add_orange();
        break;
      case 2:
        gameOver = add_yellow();
        break;
      case 3:
        gameOver = add_pink();
        break;
      case 4:
        gameOver = add_green();
        break;
      case 5:
        gameOver = add_blue();
        break;
      case 6:
        gameOver = add_violant();
        break;
    }
  }
  if (gameOver) {
    write_record();
    game->pause = 2;
  }
}

/// @brief adding red figure
/// @return 1 if adding is impossible, 0 if figure is added
int s21::TetrisModel::add_red() {
  GameInfo_t* game = GameInfo_mutator();
  int gameOver = 0;
  if (game->pause == 2) gameOver = 1;
  for (int j = 5; j < 9 && !gameOver; j++) {
    if (game->field[2][j] == 1)
      gameOver = 1;
    else
      game->field[2][j] = 2;
  }
  if (!gameOver) {
    game->field[0][5] = game->field[0][6] = game->field[0][7] =
        game->field[0][8] = 3;
    game->field[1][5] = game->field[1][6] = game->field[1][7] =
        game->field[1][8] = 3;
  }
  for (int j = 5; j < 9 && !gameOver; j++) {
    if (game->field[3][j] == 0)
      game->field[3][j] = 3;
    else
      game->field[3][j] = 4;
  }
  return gameOver;
}

/// @brief adding orange figure
/// @return 1 if adding is impossible, 0 if figure is added
int s21::TetrisModel::add_orange() {
  GameInfo_t* game = GameInfo_mutator();
  int gameOver = 0;
  if (game->pause == 2) gameOver = 1;
  if (game->field[2][6] == 1)
    gameOver = 1;
  else
    game->field[2][6] = 2;
  for (int i = 6; i < 9 && !gameOver; i++) {
    if (game->field[3][i] == 1)
      gameOver = 1;
    else
      game->field[3][i] = 2;
  }
  if (!gameOver) {
    game->field[2][7] = game->field[2][8] = 3;
  }
  for (int j = 6; j < 9 && !gameOver; j++) {
    if (game->field[4][j] == 0)
      game->field[4][j] = 3;
    else
      game->field[4][j] = 4;
  }
  return gameOver;
}

/// @brief adding yellow figure
/// @return 1 if adding is impossible, 0 if figure is added
int s21::TetrisModel::add_yellow() {
  GameInfo_t* game = GameInfo_mutator();
  int gameOver = 0;
  if (game->pause == 2) gameOver = 1;
  if (game->field[2][8] == 1)
    gameOver = 1;
  else
    game->field[2][8] = 2;
  for (int i = 6; i < 9 && !gameOver; i++) {
    if (game->field[3][i] == 1)
      gameOver = 1;
    else
      game->field[3][i] = 2;
  }
  if (!gameOver) {
    game->field[2][6] = game->field[2][7] = 3;
  }
  for (int j = 6; j < 9 && !gameOver; j++) {
    if (game->field[4][j] == 0)
      game->field[4][j] = 3;
    else
      game->field[4][j] = 4;
  }
  return gameOver;
}

/// @brief adding pink figure
/// @return 1 if adding is impossible, 0 if figure is added
int s21::TetrisModel::add_pink() {
  GameInfo_t* game = GameInfo_mutator();
  int gameOver = 0;
  if (game->pause == 2) gameOver = 1;
  for (int i = 2; i < 4 && !gameOver; i++) {
    for (int j = 6; j < 8 && !gameOver; j++) {
      if (game->field[i][j] == 1)
        gameOver = 1;
      else
        game->field[i][j] = 2;
    }
  }
  return gameOver;
}

/// @brief adding green figure
/// @return 1 if adding is impossible, 0 if figure is added
int s21::TetrisModel::add_green() {
  GameInfo_t* game = GameInfo_mutator();
  int gameOver = 0;
  if (game->pause == 2) gameOver = 1;
  if (game->field[2][7] == 1 || game->field[2][8] == 1 ||
      game->field[3][6] == 1 || game->field[3][7] == 1)
    gameOver = 1;
  else
    game->field[2][7] = game->field[2][8] = game->field[3][6] =
        game->field[3][7] = 2;
  if (!gameOver) {
    game->field[2][6] = game->field[3][8] = 3;
  }
  for (int j = 6; j < 9 && !gameOver; j++) {
    if (game->field[4][j] == 0)
      game->field[4][j] = 3;
    else
      game->field[4][j] = 4;
  }
  return gameOver;
}

/// @brief adding blue figure
/// @return 1 if adding is impossible, 0 if figure is added
int s21::TetrisModel::add_blue() {
  GameInfo_t* game = GameInfo_mutator();
  int gameOver = 0;
  if (game->pause == 2) gameOver = 1;
  if (game->field[2][7] == 1 || game->field[3][6] == 1 ||
      game->field[3][7] == 1 || game->field[3][8] == 1)
    gameOver = 1;
  else
    game->field[2][7] = game->field[3][6] = game->field[3][7] =
        game->field[3][8] = 2;
  if (!gameOver) game->field[2][6] = game->field[2][8] = 3;
  for (int j = 6; j < 9 && !gameOver; j++) {
    if (game->field[4][j] == 0)
      game->field[4][j] = 3;
    else
      game->field[4][j] = 4;
  }
  return gameOver;
}

/// @brief adding violant figure
/// @return 1 if adding is impossible, 0 if figure is added
int s21::TetrisModel::add_violant() {
  GameInfo_t* game = GameInfo_mutator();
  int gameOver = 0;
  if (game->pause == 2) gameOver = 1;
  if (game->field[2][6] == 1 || game->field[2][7] == 1 ||
      game->field[3][7] == 1 || game->field[3][8] == 1)
    gameOver = 1;
  else
    game->field[2][6] = game->field[2][7] = game->field[3][7] =
        game->field[3][8] = 2;
  if (!gameOver) {
    game->field[2][8] = game->field[3][6] = 3;
  }
  for (int j = 6; j < 9 && !gameOver; j++) {
    if (game->field[4][j] == 0)
      game->field[4][j] = 3;
    else
      game->field[4][j] = 4;
  }
  return gameOver;
}

/// @brief shifting a figure 1 ceil down
/// @return 1 if figure reached the bottom, 0 if did not
int s21::TetrisModel::figure_fall() {
  GameInfo_t* game = GameInfo_mutator();
  int stop = 0;
  /// check for the possibility of the shift
  for (int i = 2; i < 22 && game->pause == 0; i++) {
    for (int j = 2; j < 12; j++) {
      if (game->field[i][j] == 2 && i == 21)
        stop = 1;
      else if (game->field[i][j] == 2 &&
               (game->field[i + 1][j] == 1 || game->field[i + 1][j] == 4))
        stop = 1;
    }
  }
  /// shift
  for (int i = 23; i > 0 && !stop && game->pause == 0; i--) {
    for (int j = 13; j >= 0; j--) {
      if (game->field[i - 1][j] == 2) {
        game->field[i][j] = 2;
        game->field[i - 1][j] = 0;
      } else if (game->field[i - 1][j] == 3 && game->field[i][j] == 0) {
        game->field[i][j] = 3;
        game->field[i - 1][j] = 0;
      } else if (game->field[i - 1][j] == 3 && game->field[i][j] == 1) {
        game->field[i][j] = 4;
        game->field[i - 1][j] = 0;
      } else if (game->field[i - 1][j] == 4 && game->field[i][j] == 1) {
        game->field[i][j] = 4;
        game->field[i - 1][j] = 1;
      } else if (game->field[i - 1][j] == 4) {
        game->field[i][j] = 3;
        game->field[i - 1][j] = 1;
      }
    }
  }
  return stop;
}

/// @brief stops all moving ceils
void s21::TetrisModel::stop_field() {
  GameInfo_t* game = GameInfo_mutator();
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 14; j++) {
      if (game->field[i][j] == 2 || game->field[i][j] == 4)
        game->field[i][j] = 1;
      else if (game->field[i][j] == 3)
        game->field[i][j] = 0;
    }
  }
}

/// @brief shifting figure left
void s21::TetrisModel::left() {
  GameInfo_t* game = GameInfo_mutator();
  int stop = 0;
  /// check for the possibility of the shift
  for (int i = 0; i < 24 && !stop; i++) {
    for (int j = 0; j < 14 - 1 && !stop; j++) {
      if (game->field[i][j] == 2 && j == 2)
        stop = 1;
      else if (game->field[i][j] == 2 &&
               (game->field[i][j - 1] == 1 || game->field[i][j - 1] == 4))
        stop = 1;
    }
  }
  /// shift
  for (int i = 0; i < 24 && !stop; i++) {
    for (int j = 0; j < 14 - 2 && !stop; j++) {
      if (game->field[i][j + 1] == 2) {
        game->field[i][j] = 2;
        game->field[i][j + 1] = 0;
      } else if (game->field[i][j + 1] == 3 && game->field[i][j] == 0) {
        game->field[i][j] = 3;
        game->field[i][j + 1] = 0;
      } else if (game->field[i][j + 1] == 3 && game->field[i][j] == 1) {
        game->field[i][j] = 4;
        game->field[i][j + 1] = 0;
      } else if (game->field[i][j + 1] == 4 && game->field[i][j] == 1) {
        game->field[i][j] = 4;
        game->field[i][j + 1] = 1;
      } else if (game->field[i][j + 1] == 4 && game->field[i][j] == 0) {
        game->field[i][j] = 0;
        game->field[i][j + 1] = 1;
      }
    }
  }
}

/// @brief shifting figure right
void s21::TetrisModel::right() {
  GameInfo_t* game = GameInfo_mutator();
  int stop = 0;
  /// check for the possibility of the shift
  for (int i = 0; i < 24 && !stop; i++) {
    for (int j = 14 - 1; j >= 0 && !stop; j--) {
      if (game->field[i][j] == 2 && j == 11)
        stop = 1;
      else if (game->field[i][j] == 2 &&
               (game->field[i][j + 1] == 1 || game->field[i][j + 1] == 4))
        stop = 1;
    }
  }
  /// shift
  for (int i = 0; i < 24 && !stop; i++) {
    for (int j = 14 - 1; j > 0 && !stop; j--) {
      if (game->field[i][j - 1] == 2) {
        game->field[i][j] = 2;
        game->field[i][j - 1] = 0;
      } else if (game->field[i][j - 1] == 3 && game->field[i][j] == 0) {
        game->field[i][j] = 3;
        game->field[i][j - 1] = 0;
      } else if (game->field[i][j - 1] == 3 && game->field[i][j] == 1) {
        game->field[i][j] = 4;
        game->field[i][j - 1] = 0;
      } else if (game->field[i][j - 1] == 4 && game->field[i][j] == 1) {
        game->field[i][j] = 4;
        game->field[i][j - 1] = 1;
      } else if (game->field[i][j - 1] == 4 && game->field[i][j] == 0) {
        game->field[i][j] = 0;
        game->field[i][j - 1] = 1;
      }
    }
  }
}

/// @brief rotation of the figure
void s21::TetrisModel::action() {
  GameInfo_t* game = GameInfo_mutator();
  int** fig = NULL;
  int size = 0;
  if (figure == 0)
    size = 4;
  else if (figure == 3)
    size = 0;
  else
    size = 3;
  fig = s21_create_matrix(fig, size, size);
  int m = 0, n = 0, found = 0;
  for (int i = 0; i < 24 && !found && fig != NULL; i++) {
    for (int j = 0; j < 14 && !found; j++) {
      if (game->field[i][j] == 3 || game->field[i][j] == 4 ||
          game->field[i][j] == 2) {
        found = 1;
        m = i;
        n = j;
      }
    }
  }
  for (int i = 0; i < size && fig != NULL; i++) {
    for (int j = 0; j < size; j++) {
      if (game->field[i + m][j + n] == 2)
        fig[i][j] = 2;
      else
        fig[i][j] = 3;
    }
  }
  int** rotated = matrix_turn(fig, size);
  int canRotate = 1;
  for (int i = 0; i < size && rotated != NULL && canRotate; i++) {
    for (int j = 0; j < size && canRotate; j++) {
      if (rotated[i][j] == 2 &&
          (game->field[i + m][j + n] == 4 || game->field[i + m][j + n] == 1 ||
           j + n <= 1 || j + n >= 12 || i + m <= 1 || i + m >= 22))
        canRotate = 0;
    }
  }
  for (int i = 0; i < size && rotated != NULL && canRotate; i++) {
    for (int j = 0; j < size; j++) {
      if (rotated[i][j] == 2)
        game->field[i + m][j + n] = 2;
      else if (rotated[i][j] == 3 && (game->field[i + m][j + n] == 0 ||
                                      game->field[i + m][j + n] == 2))
        game->field[i + m][j + n] = 3;
      else if (rotated[i][j] == 3 && (game->field[i + m][j + n] == 1 ||
                                      game->field[i + m][j + n] == 4))
        game->field[i + m][j + n] = 4;
    }
  }
  if (rotated != NULL) s21_remove_matrix(rotated, size);
}

/// @brief allocate memory for a matrix and null it
/// @param result pointer to allocate
/// @param height number of rows
/// @param width number of cols
/// @return allocated pointer
int** s21::TetrisModel::s21_create_matrix(int** result, int height, int width) {
  result = (int**)malloc(sizeof(int*) * width * height);
  for (int i = 0; i < height; i++) {
    result[i] = (int*)malloc(sizeof(int) * width);
  }
  s21_null_matrix(result, height, width);
  return result;
}

void s21::TetrisModel::s21_remove_matrix(int** matr, int height) {
  int empty = 0;
  if (matr == NULL) empty = 1;
  for (int i = 0; empty == 0 && i < height; i++) {
    free(matr[i]);
  }
  if (empty == 0) {
    free(matr);
  }
}

/// @brief turn matrix for 90*
/// @param matr matrix to turn
/// @param size size of the square matrix
/// @return turned matrix
int** s21::TetrisModel::matrix_turn(int** matr, int size) {
  int** rotated = NULL;
  rotated = s21_create_matrix(rotated, size, size);
  for (int i = 0; i < size && rotated != NULL && matr != NULL; i++) {
    for (int j = 0; j < size; j++) {
      rotated[size - 1 - j][i] = matr[i][j];
    }
  }
  if (matr != NULL) s21_remove_matrix(matr, size);
  return rotated;
}

/// @brief scoring filled lines and delete them
/// @return number of deleted lines
int s21::TetrisModel::clear_lines() {
  GameInfo_t* game = GameInfo_mutator();
  int cleared = 0;
  for (int i = 2; i < 24 - 2; i++) {
    int clear = 1;
    for (int j = 2; j < 14 - 2 && clear; j++) {
      if (game->field[i][j] != 1) clear = 0;
    }
    for (int j = 2; j < 14 - 2 && clear; j++) {
      game->field[i][j] = 0;
    }
    if (clear) cleared++;
  }
  return cleared;
}

/// @brief fall the field when rows are deleted
void s21::TetrisModel::fall_all_field() {
  const GameInfo_t* game = GameInfo_mutator();
  for (int i = 24 - 2; i >= 2; i--) {
    for (int j = 2; j < 14 - 2; j++) {
      if (game->field[i][j] == 1) pixel_fall(i, j);
    }
  }
}

/// @brief fall a one pixel of the field
/// @param i Y of pixel
/// @param j X of pixel
void s21::TetrisModel::pixel_fall(int i, int j) {
  GameInfo_t* game = GameInfo_mutator();
  int fell = 0;
  for (int k = i; k < 24 - 2 && !fell; k++) {
    if (game->field[k][j] == 1 && (game->field[k + 1][j] == 1 || k == 24 - 3))
      fell = 1;
    else {
      game->field[k][j] = 0;
      game->field[k + 1][j] = 1;
    }
  }
}

/// @brief count delta score
/// @param summCleared number of deleted rows
/// @return delta score
int s21::TetrisModel::increase_score(int summCleared) {
  int score = 0;
  switch (summCleared) {
    case 1:
      score = 100;
      break;
    case 2:
      score = 300;
      break;
    case 3:
      score = 700;
      break;
    case 4:
      score = 1500;
      break;
  }
  if (summCleared > 4) {
    score = 1500;
    score += increase_score(summCleared - 4);
  }
  return score;
}

/// @brief count a level
void s21::TetrisModel::increase_level() {
  GameInfo_t* game = GameInfo_mutator();
  game->level = game->score / 600;
  if (game->level > 10)
    game->level = 10;
  else if (game->level == 0)
    game->level = 1;
}

/// fill "next" field to show the next figure
void s21::TetrisModel::fill_next_figure() {
  GameInfo_t* game = GameInfo_mutator();
  s21_null_matrix(game->next, 4, 4);
  switch (next_figure) {
    case 0:
      game->next[1][0] = game->next[1][1] = game->next[1][2] =
          game->next[1][3] = 1;
      break;
    case 1:
      game->next[1][1] = game->next[2][1] = game->next[2][2] =
          game->next[2][3] = 1;
      break;
    case 2:
      game->next[1][3] = game->next[2][1] = game->next[2][2] =
          game->next[2][3] = 1;
      break;
    case 3:
      game->next[1][1] = game->next[2][1] = game->next[1][2] =
          game->next[2][2] = 1;
      break;
    case 4:
      game->next[1][1] = game->next[1][2] = game->next[2][0] =
          game->next[2][1] = 1;
      break;
    case 5:
      game->next[1][1] = game->next[2][0] = game->next[2][1] =
          game->next[2][2] = 1;
      break;
    case 6:
      game->next[1][1] = game->next[1][2] = game->next[2][2] =
          game->next[2][3] = 1;
      break;
  }
}

/// @brief main process of shifting a figure down
void s21::TetrisModel::fall() {
  GameInfo_t* game = GameInfo_mutator();
  if (game->pause == 0 && figure_fall()) {
    stop_field();
    int cleared = clear_lines();
    int summCleared = 0;
    while (cleared != 0) {
      fall_all_field();
      summCleared += cleared;
      cleared = clear_lines();
    }
    game->score += increase_score(summCleared);
    if (game->level < 10) increase_level();
    game->speed = 25 - game->level * 2;
    figure = next_figure;
    add_figure();
    next_figure = generate_figure();
    fill_next_figure();
  }
}

/// @brief if Start input recieved
void s21::TetrisModel::start() {
  if (GameInfo_mutator()->pause == 3) {
    set();
    figure = generate_figure();
    add_figure();
    next_figure = generate_figure();
    fill_next_figure();
    GameInfo_mutator()->pause = 0;
  } else if (GameInfo_mutator()->pause == 2 || GameInfo_mutator()->pause == 4) {
    write_record();
    set();
  }
}

/// @brief updating GameInfo_t
void s21::TetrisModel::update() {
  const GameInfo_t* game = GameInfo_mutator();
  if (game->pause == 0) {
    fall();
  } else if (game->pause == 2)
    write_record();
  else if (game->pause == 3)
    set();
}