/**
 @file backend_snake.cc
 @brief implementation of all snake logic
 */

#include "backend_snake.h"

/// @brief default state of the game
void s21::Model::set() {
  for (int i = 0; i < 24; ++i)
    for (int j = 0; j < 14; ++j) game->field[i][j] = 0;
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j) game->next[i][j] = 0;
  game->next[0][0] = -2;
  int startY = 24 / 2;
  int startX = 14 / 2 - 2;
  game->field[startY][startX - 1] = Teil * 100 + 10;
  game->field[startY][startX] = game->field[startY][startX + 1] =
      Body * 100 + 10;
  game->field[startY][startX + 2] = Head * 100 + 10;
  game->score = 4;
  game->level = 1;
  game->high_score = get_record();
  game->pause = 3;
  game->speed = 50 - game->level * 2;
}

/// @brief adding apple if necessary
void s21::Model::add_apple() {
  bool need = true;
  bool victory = false;
  if (game->score == 200) victory = true;
  for (int i = 2; !victory && i < 22 && need; ++i) {
    for (int j = 2; j < 12 && need; ++j) {
      if (get_type(i, j) == Apple) need = false;
    }
  }
  if (!victory && need && game->pause == 0) set_apple();
}

/// @brief adding apple
void s21::Model::set_apple() {
  int empty = 0;
  for (int i = 2; i < 22; ++i) {
    for (int j = 2; j < 12; ++j) {
      if (get_type(i, j) == Empty) empty++;
    }
  }
  srand(time(NULL));
  int apple = rand() % empty;
  int count = 0;
  bool end = false;
  for (int i = 2; i < 22 && !end; ++i) {
    for (int j = 2; j < 12 && !end; ++j) {
      if (count == apple && get_type(i, j) == Empty) {
        game->field[i][j] = Apple * 100;
        end = true;
      } else if (get_type(i, j) == Empty)
        count++;
    }
  }
}

/// @brief main moving process
void s21::Model::move_snake() {
  bool victory = false;
  if (game->score == 200) victory = true;

  std::pair<int, int> headCoords = find_head_x_y();
  std::pair<int, int> directionHead =
      get_direction_x_y(headCoords.second, headCoords.first);
  bool game_over =
      gameover_or_not(directionHead, headCoords.second, headCoords.first);

  bool movedTeil = false;
  for (int i = 0; !victory && i < 24 && !game_over; ++i) {
    for (int j = 0; j < 14 && !game_over; ++j) {
      if (get_type(i, j) == Head && !game_over && movedTeil) {
        std::pair<int, int> direction = get_direction_x_y(i, j);
        int sign = abs(game->field[i][j]) / game->field[i][j];
        game->field[i + direction.second][j + direction.first] =
            sign * WillBeHead * 100 + game->field[i][j] % 100;
        game->field[i][j] = sign * Body * 100 + game->field[i][j] % 100;
      } else if (get_type(i, j) == Teil && !game_over) {
        std::pair<int, int> direction = get_direction_x_y(i, j);
        int sign = abs(game->field[i + direction.second][j + direction.first]) /
                   game->field[i + direction.second][j + direction.first];
        game->field[i + direction.second][j + direction.first] =
            sign * WillBeTeil * 100 +
            game->field[i + direction.second][j + direction.first] % 100;
        game->field[i][j] = 0;
        movedTeil = true;
        i = j = 0;
      }
    }
  }
  for (int i = 0; !victory && i < 24 && !game_over; ++i) {
    for (int j = 0; j < 14; ++j) {
      int sign;
      if (get_type(i, j) != Empty)
        sign = abs(game->field[i][j]) / game->field[i][j];
      if (get_type(i, j) == WillBeHead)
        game->field[i][j] = sign * Head * 100 + game->field[i][j] % 100;
      else if (get_type(i, j) == WillBeTeil)
        game->field[i][j] = sign * Teil * 100 + game->field[i][j] % 100;
    }
  }
  if (game_over)
    game->pause = 2;
  else if (victory)
    game->pause = 4;
}

/// @brief growing by one point
/// @return true if growed, false if not
bool s21::Model::grow_snake() {
  bool growed = false;
  int xHead = 0, yHead = 0;
  bool foundHead = false;
  for (int i = 2; i < 22 && !foundHead; ++i) {
    for (int j = 2; j < 12 && !foundHead; ++j) {
      if (get_type(i, j) == Head) {
        xHead = j;
        yHead = i;
        foundHead = true;
      }
    }
  }
  std::pair<int, int> directionHead = get_direction_x_y(yHead, xHead);
  int type =
      get_type(yHead + directionHead.second, xHead + directionHead.first);
  if (type == Apple) {
    int sign = abs(game->field[yHead][xHead]) / game->field[yHead][xHead];
    game->field[yHead + directionHead.second][xHead + directionHead.first] =
        sign * Head * 100 + game->field[yHead][xHead] % 100;
    game->field[yHead][xHead] =
        sign * Body * 100 + game->field[yHead][xHead] % 100;
    ++game->score;
    growed = true;
  }
  return growed;
}

/// @brief check for connecting borders or itself
/// @param direction x and y velocity of the ceil
/// @param i y of the ceil
/// @param j x of the ceil
/// @return true if connected, false if not
bool s21::Model::gameover_or_not(std::pair<int, int> direction, int i, int j) {
  bool game_over = false;
  int type = get_type(i + direction.second, j + direction.first);
  if ((type != Empty && type != Apple && type != Teil) ||
      i + direction.second == 22 || i + direction.second == 1 ||
      j + direction.first == 12 || j + direction.first == 1) {
    game_over = true;
  }
  return game_over;
}

/// @brief get type of the ceil
/// @param i y of the ceil
/// @param j x of the ceil
/// @return type
int s21::Model::get_type(int i, int j) { return abs(game->field[i][j] / 100); }

/// @brief get velocity of the ceil
/// @param i y of the ceil
/// @param j x of the ceil
/// @return pair of velocities (by X and by Y)
std::pair<int, int> s21::Model::get_direction_x_y(int i, int j) {
  int x = (game->field[i][j] % 100) / 10;
  int y = game->field[i][j] % 10;
  return std::pair<int, int>{x, y};
}

/// @brief get the record from score.txt
/// @return record
int s21::Model::get_record() {
  int curr_game = 1;
  if (game->next[0][0] < 0) curr_game = 2;
  int rec_tetris = 0, rec_snake = 0;
  FILE* rec = fopen("score.txt", "r");
  if (rec != NULL) {
    fscanf(rec, "%d%d", &rec_tetris, &rec_snake);
    fclose(rec);
  }
  int to_return = rec_tetris;
  if (curr_game == 2) to_return = rec_snake;
  return to_return;
}

/// @brief add a new record to the score file
void s21::Model::write_record() {
  int curr_game = 1;
  if (game->next[0][0] < 0) curr_game = 2;
  int rec_tetris = 0, rec_snake = 0;
  FILE* rec = fopen("score.txt", "r");
  if (rec != NULL) {
    fscanf(rec, "%d%d", &rec_tetris, &rec_snake);
    fclose(rec);
  }

  if (game->score > game->high_score) {
    rec = fopen("score.txt", "w");
    if (rec != NULL) {
      if (curr_game == 1)
        fprintf(rec, "%d\n%d", game->score, rec_snake);
      else if (curr_game == 2)
        fprintf(rec, "%d\n%d", rec_tetris, game->score);
      fclose(rec);
    }
  }
}

/// @brief turn up or accelerate
void s21::Model::up() {
  std::pair<int, int> head = find_head_x_y();
  int yHead = head.second;
  int xHead = head.first;
  int direction = get_direction_x_y(yHead, xHead).second;
  if (game->pause == 0 && direction == 0) {
    game->field[yHead][xHead] = -1 * (Head * 100 + 1);
    game->next[0][0] = -1;
    update();
  } else if (direction == -1) {
    update();
  }
}

/// @brief turn down or accelerate
void s21::Model::down() {
  std::pair<int, int> head = find_head_x_y();
  int yHead = head.second;
  int xHead = head.first;
  int direction = get_direction_x_y(yHead, xHead).second;
  if (game->pause == 0 && direction == 0) {
    game->field[yHead][xHead] = Head * 100 + 1;
    game->next[0][0] = -1;
    update();
  } else if (direction == 1) {
    update();
  }
}

/// @brief turn left or accelerate
void s21::Model::left() {
  std::pair<int, int> head = find_head_x_y();
  int yHead = head.second;
  int xHead = head.first;
  int direction = get_direction_x_y(yHead, xHead).first;
  if (game->pause == 0 && direction == 0) {
    game->field[yHead][xHead] = -1 * (Head * 100 + 10);
    game->next[0][0] = -1;
    update();
  } else if (direction == -1) {
    update();
  }
}

/// @brief turn right or accelerate
void s21::Model::right() {
  std::pair<int, int> head = find_head_x_y();
  int yHead = head.second;
  int xHead = head.first;
  int direction = get_direction_x_y(yHead, xHead).first;
  if (game->pause == 0 && direction == 0) {
    game->field[yHead][xHead] = Head * 100 + 10;
    game->next[0][0] = -1;
    update();
  } else if (direction == 1) {
    update();
  }
}

/// @brief actions in case of Start input
void s21::Model::start() {
  if (game->pause == 3) {
    set();
    game->pause = 0;
  } else if (game->pause == 2 || game->pause == 4) {
    write_record();
    set();
  }
}

/// @brief actions in case of Terminate input
void s21::Model::terminate() {
  if (game->pause != 2 && game->pause != 4) {
    write_record();
    game->pause = 2;
  }
}

/// @brief actions in case of Pause input
void s21::Model::pause() {
  if (game->pause == 0)
    game->pause = 1;
  else if (game->pause == 1)
    game->pause = 0;
}

/// @brief updating GameInfo_t
void s21::Model::update() {
  if (game->pause == 0 && !grow_snake()) {
    move_snake();
  }
  if (game->pause == 0)
    add_apple();
  else if (game->pause == 2 || game->pause == 4)
    write_record();
  else if (game->pause == 3)
    set();
  if (game->score >= 50)
    game->level = 10;
  else if (game->score > 4)
    game->level = game->score / 5;
  game->speed = 50 - game->level * 2;
}

/// @brief find coordinates of the Head
/// @return pair of coordinates (X, Y)
std::pair<int, int> s21::Model::find_head_x_y() {
  int yHead = 0, xHead = 0;
  bool found = false;
  for (int i = 2; i < 22 && !found; ++i) {
    for (int j = 2; j < 12 && !found; ++j) {
      if (get_type(i, j) == Head) {
        yHead = i;
        xHead = j;
        found = true;
      }
    }
  }
  return std::pair<int, int>(xHead, yHead);
}