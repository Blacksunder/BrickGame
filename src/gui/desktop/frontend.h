/**
 @file frontend.h
 @brief declaration of View class, and all it's methods
 */

#ifndef FRONTEND_H
#define FRONTEND_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QObject>
#include <QTimer>

#include "../../brick_game/tetris/backend_tetris.h"

namespace s21 {
/** @brief View class, implements desktop interface using qt framework, contains
 * Controller and Qt items */
class View : public QGraphicsScene {
  Q_OBJECT
 private:
  QGraphicsRectItem*** items;
  QGraphicsRectItem*** next_figure;
  QGraphicsTextItem* menu;
  QGraphicsTextItem* res_info;
  s21::Controller* game_controller;
  QTimer* timer;

 public:
  explicit View(s21::Controller* src);
  ~View();

  /// @brief recieve input signals
  /// @param event qt event, occurs when any keyboard key is pressed
  void keyPressEvent(QKeyEvent* event);

  /// @brief main field draw function
  /// @param game current GameInfo_t
  void update_field(GameInfo_t game);

  /// @brief main information draw function
  /// @param game current GameInfo_t
  void update_text_items(GameInfo_t game);

 public slots:
  /// @brief slot, connected to the timer
  void move() { update_field(game_controller->updateCurrentState()); }
};

}  // namespace s21

#endif  // FRONTEND_H