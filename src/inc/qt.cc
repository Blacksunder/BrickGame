/**
 @file qt.cc
 @brief A file with main and loops functios for a desktop brick game
 */

#include <QApplication>
#include <QGraphicsView>

#include "../gui/desktop/frontend.h"

/// @brief main qt tetris loop
/// @param argc argc from main
/// @param argv argv from main
/// @return result of the application work
int snake(int argc, char* argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  model.set();
  s21::Controller controller(&model);
  s21::View scene(&controller);
  QGraphicsView view(&scene);
  view.resize(500, 500);
  view.show();
  return a.exec();
}

/// @brief main qt snake loop
/// @param argc argc from main
/// @param argv argv from main
/// @return result of the application work
int tetris(int argc, char* argv[]) {
  QApplication a(argc, argv);
  s21::TetrisModel model;
  model.set();
  s21::TetrisController controller(&model);
  s21::View scene(&controller);
  QGraphicsView view(&scene);
  view.resize(500, 500);
  view.show();
  return a.exec();
}

int main(int argc, char* argv[]) {
  int choice = 0;
  int res = 0;
  std::cout << "Choose a game:\n1 - Tetris, 2 - Snake\nEnter your choice: ";
  std::cin >> choice;
  if (choice == 2)
    res = snake(argc, argv);
  else if (choice == 1)
    res = tetris(argc, argv);
  return res;
}