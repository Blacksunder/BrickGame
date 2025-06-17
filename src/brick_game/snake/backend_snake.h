/**
 @file backend_snake.h
 @brief declaration of Model and Controller classes for a snake
 */

#ifndef BACKEND_SNAKE_H
#define BACKEND_SNAKE_H

#include "../defines.h"

namespace s21 {
/** @brief model class, which contains current GameInfo_t and change it */
class Model {
 private:
  GameInfo_t* game;

  void set_apple();
  bool gameover_or_not(std::pair<int, int> direction, int i, int j);

 public:
  Model() {
    game = new GameInfo_t;
    game->field = new int*[24];
    for (int i = 0; i < 24; ++i) game->field[i] = new int[14];
    game->next = new int*[4];
    for (int i = 0; i < 4; ++i) game->next[i] = new int[4];
    Model::set();
  }

  ~Model() {
    write_record();
    for (int i = 0; i < 24; ++i) delete[] game->field[i];
    delete[] game->field;
    for (int i = 0; i < 4; ++i) delete[] game->next[i];
    delete[] game->next;
    delete game;
  }

  /// @brief get GameInfo_t for inherit class
  /// @return pointer to GameInfo_t
  GameInfo_t* GameInfo_mutator() { return game; }

  virtual void set();
  void add_apple();
  void move_snake();
  bool grow_snake();
  int get_record();
  void write_record();
  int get_type(int i, int j);
  /// @brief returns next[0][0] element
  /// @return next[0][0]
  int* get_next() { return &game->next[0][0]; }
  /// @brief returns current state of the game
  /// @return struct GameInfo_t
  virtual GameInfo_t get_GameInfo_t() { return *game; }
  virtual void left();
  virtual void right();
  virtual void up();
  virtual void down();
  virtual void start();
  virtual void terminate();
  virtual void pause();
  /// @brief in case of snake, does nothing
  virtual void action() {};
  std::pair<int, int> find_head_x_y();
  std::pair<int, int> get_direction_x_y(int i, int j);
  virtual void update();
};

/** @brief controller class, which contains Model and calls it's methods if
 * frontend ask for it */
class Controller {
 private:
  Model* model;

 public:
  Controller() {}
  explicit Controller(s21::Model* src) { model = src; }

  /// @brief get next[0][0] element (for a snake)
  /// @return next[0][0]
  int* get_next() { return model->get_next(); }

  /// @brief separates and uses input
  /// @param action input type
  /// @param hold true if press is long
  void userInput(UserAction_t action, bool hold) {
    if (!hold) switch (action) {
        case Up:
          model->up();
          break;
        case Down:
          model->down();
          break;
        case Left:
          model->left();
          break;
        case Right:
          model->right();
          break;
        case Start:
          model->start();
          break;
        case Terminate:
          model->terminate();
          break;
        case Pause:
          model->pause();
          break;
        case Action:
          model->action();
          break;
        default:
          break;
      }
  }

  /// @brief change and return the field in case of timeout
  GameInfo_t updateCurrentState() {
    model->update();
    return model->get_GameInfo_t();
  }

  /// @brief get GameInfo_t without changes
  /// @return current GameInfo_t
  GameInfo_t get_GameInfo_t() { return model->get_GameInfo_t(); }
};

}  // namespace s21

#endif  // BACKEND_SNAKE_H