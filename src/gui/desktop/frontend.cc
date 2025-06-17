/**
 @file frontend.cc
 @brief implementation of desktop interface functions
 */

#include "frontend.h"

s21::View::View(s21::Controller* src) {
  game_controller = src;
  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));
  items = new QGraphicsRectItem**[20];
  for (int i = 0; i < 20; ++i) {
    items[i] = new QGraphicsRectItem*[10];
    for (int j = 0; j < 10; ++j) {
      items[i][j] = new QGraphicsRectItem(20 * j, 20 * i, 20, 20);
    }
  }
  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < 10; ++j) addItem(items[i][j]);
  }
  next_figure = new QGraphicsRectItem**[4];
  for (int i = 0; i < 4; ++i) {
    next_figure[i] = new QGraphicsRectItem*[4];
    for (int j = 0; j < 4; ++j) {
      next_figure[i][j] =
          new QGraphicsRectItem(20 * j + 275, 20 * i + 300, 20, 20);
      addItem(next_figure[i][j]);
    }
  }
  menu = new QGraphicsTextItem();
  menu->setPos(10 * 20 + 10, 15 * 10);
  addItem(menu);
  res_info = new QGraphicsTextItem();
  res_info->setPos(10 * 20 + 10, 5 * 10);
  addItem(res_info);
  timer->start(game_controller->get_GameInfo_t().speed * 10);
  update_field(game_controller->updateCurrentState());
}

s21::View::~View() {
  delete timer;
  delete res_info;
  delete menu;
  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < 10; ++j) {
      delete items[i][j];
    }
    delete[] items[i];
  }
  delete[] items;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      delete next_figure[i][j];
    }
    delete[] next_figure[i];
  }
  delete[] next_figure;
}

void s21::View::keyPressEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key_Up:
      game_controller->userInput(Up, false);
      break;
    case Qt::Key_Left:
      game_controller->userInput(Left, false);
      break;
    case Qt::Key_Right:
      game_controller->userInput(Right, false);
      break;
    case Qt::Key_Down:
      game_controller->userInput(Down, false);
      break;
    case Qt::Key_P:
      game_controller->userInput(Pause, false);
      break;
    case Qt::Key_S:
      game_controller->userInput(Start, false);
      break;
    case Qt::Key_Space:
      game_controller->userInput(Action, false);
      break;
    case Qt::Key_Escape:
      game_controller->userInput(Terminate, false);
      break;
  }
  // reset the timer if snake was turned
  if (*game_controller->get_next() == -1) {
    timer->stop();
    timer->start(game_controller->get_GameInfo_t().speed * 10);
    *game_controller->get_next() = -2;
  }
  update_field(game_controller->get_GameInfo_t());
}

void s21::View::update_field(GameInfo_t game) {
  int curr_game = 1;
  if (game.next[0][0] < 0) curr_game = 2;
  for (int i = 2; i < 22; ++i) {
    for (int j = 2; j < 12; ++j) {
      int y = i - 2, x = j - 2;
      int type = abs(game.field[i][j] / 100);
      if (curr_game == 1) {
        if (game.field[i][j] == 0 || game.field[i][j] == 3)
          type = Empty;
        else
          type = Body;
      }
      switch (type) {
        case Empty:
          items[y][x]->setBrush(Qt::gray);
          break;
        case Apple:
          items[y][x]->setBrush(Qt::red);
          break;
        case Head:
          items[y][x]->setBrush(Qt::yellow);
          break;
        default:
          items[y][x]->setBrush(Qt::green);
          break;
      }
    }
  }
  for (int i = 0; i < 4 && curr_game == 1; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (game.next[i][j] == 1 && game.pause != 3)
        next_figure[i][j]->setBrush(Qt::green);
      else
        next_figure[i][j]->setBrush(Qt::gray);
    }
  }
  update_text_items(game);
}

void s21::View::update_text_items(GameInfo_t game) {
  int rec = game.high_score;
  if (game.score > rec) rec = game.score;
  if (game.next[0][0] == 0)
    menu->setPlainText(QString::asprintf(
        "\n            Current score: %d\n\n                  "
        "Record: %d\n\n                     Level: %d\n\n"
        "                  Next figure:",
        game.score, rec, game.level));
  else
    menu->setPlainText(QString::asprintf(
        "\n            Current score: %d\n\n                  "
        "Record: %d\n\n                     Level: %d\n",
        game.score, rec, game.level));
  if (game.pause == 0)
    res_info->setPlainText(QString("            Press 'P' for pause"));
  else if (game.pause == 1)
    res_info->setPlainText(QString(
        "          Press 'P' to continue\n       or 'Esc' to end the game"));
  else if (game.pause == 2)
    res_info->setPlainText(
        QString("                   Game over\n\n   Press 'S' to restart the "
                "game\n\n    or close the window to quit"));
  else if (game.pause == 3)
    res_info->setPlainText(QString("    Press 'S' to start the game!"));
  else if (game.pause == 4)
    res_info->setPlainText(
        QString("Congratulations, you are winner!\n\n     Press S to restart "
                "the game\n\n     or close the window to quit"));
}