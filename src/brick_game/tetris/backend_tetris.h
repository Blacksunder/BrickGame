/**
 @file backend_tetris.h
 @brief declaration of Model and Controller classes for a tetris
 */

#ifndef BACKEND_TETRIS_H
#define BACKEND_TETRIS_H

#include "../snake/backend_snake.h"

namespace s21 {
/** @brief Model for a tetris, inherits logic from a snake Model and
 * overrides/adds some functions */
class TetrisModel : public Model {
 private:
  int figure, next_figure;

  void s21_null_matrix(int **matr, int height, int width);
  int **s21_create_matrix(int **result, int height, int width);
  void s21_remove_matrix(int **matr, int height);
  int **matrix_turn(int **matr, int size);

 public:
  TetrisModel() : figure(0), next_figure(0) {}

  void set() override;
  int generate_figure();
  void add_figure();
  int add_red();
  int add_orange();
  int add_yellow();
  int add_pink();
  int add_green();
  int add_blue();
  int add_violant();
  void fill_next_figure();
  int figure_fall();
  void stop_field();

  int clear_lines();
  void fall_all_field();
  void pixel_fall(int i, int j);
  int increase_score(int summCleared);
  void increase_level();
  void fall();
  void update() override;

  void left() override;
  void right() override;
  void up() override {};
  void down() override { fall(); }
  void action() override;
  void start() override;
};

/** @brief Controller for a tetris, inherits logic from a snake controller */
class TetrisController : public Controller {
 public:
  explicit TetrisController(TetrisModel *src) : Controller(src) {}
};

}  // namespace s21

#endif  // BACKEND_TETRIS_H