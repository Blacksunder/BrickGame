#include <gtest/gtest.h>

#include "../brick_game/snake/backend_snake.h"
#include "../brick_game/tetris/backend_tetris.h"

GTEST_TEST(snake, set) {
  s21::Model model;
  model.set();

  s21::Controller controller(&model);

  int startY = 24 / 2;
  int startX = 14 / 2 - 2;
  ASSERT_EQ(controller.get_GameInfo_t().field[startY][startX - 1],
            Teil * 100 + 10);
  ASSERT_EQ(controller.get_GameInfo_t().field[startY][startX],
            controller.get_GameInfo_t().field[startY][startX + 1]);
  ASSERT_EQ(controller.get_GameInfo_t().field[startY][startX + 1],
            Body * 100 + 10);
  ASSERT_EQ(controller.get_GameInfo_t().field[startY][startX + 2],
            Head * 100 + 10);
  ASSERT_EQ(controller.get_GameInfo_t().score, 4);
  ASSERT_EQ(controller.get_GameInfo_t().level, 1);
  ASSERT_EQ(controller.get_GameInfo_t().high_score,
            model.get_GameInfo_t().high_score);
}

GTEST_TEST(snake, add_apple) {
  s21::Model model;
  model.set();

  s21::Controller controller(&model);

  controller.userInput(Start, false);
  model.add_apple();

  bool found = false;
  for (int i = 2; !found && i < 22; ++i) {
    for (int j = 2; !found && j < 12; ++j) {
      if (controller.get_GameInfo_t().field[i][j] / 100 == Apple) found = true;
    }
  }
  ASSERT_TRUE(found);
}

GTEST_TEST(snake, up) {
  s21::Model model;
  model.set();

  s21::Controller controller(&model);

  controller.userInput(Start, false);
  bool found = false;
  int yHead, xHead;
  for (int i = 2; !found && i < 22; ++i) {
    for (int j = 2; !found && j < 12; ++j) {
      if (abs(controller.get_GameInfo_t().field[i][j] / 100) == Head) {
        found = true;
        yHead = i;
        xHead = j;
      }
    }
  }
  controller.userInput(Up, false);
  ASSERT_EQ(controller.get_GameInfo_t().field[yHead - 1][xHead],
            -1 * (Head * 100 + 1));
  controller.userInput(Up, false);
  ASSERT_EQ(controller.get_GameInfo_t().field[yHead - 2][xHead],
            -1 * (Head * 100 + 1));
  controller.userInput(Down, false);
  ASSERT_EQ(controller.get_GameInfo_t().field[yHead - 2][xHead],
            -1 * (Head * 100 + 1));
}

GTEST_TEST(snake, down) {
  s21::Model model;
  model.set();

  s21::Controller controller(&model);

  controller.userInput(Start, false);

  bool found = false;
  int yHead, xHead;
  for (int i = 2; !found && i < 22; ++i) {
    for (int j = 2; !found && j < 12; ++j) {
      if (abs(controller.get_GameInfo_t().field[i][j] / 100) == Head) {
        found = true;
        yHead = i;
        xHead = j;
      }
    }
  }
  controller.userInput(Down, false);
  ASSERT_EQ(controller.get_GameInfo_t().field[yHead + 1][xHead],
            Head * 100 + 1);
  controller.userInput(Down, false);
  ASSERT_EQ(controller.get_GameInfo_t().field[yHead + 2][xHead],
            Head * 100 + 1);
  controller.userInput(Up, false);
  ASSERT_EQ(controller.get_GameInfo_t().field[yHead + 2][xHead],
            Head * 100 + 1);
}

GTEST_TEST(snake, left) {
  s21::Model model;
  model.set();

  s21::Controller controller(&model);

  controller.userInput(Start, false);
  bool found = false;
  int yHead, xHead;
  for (int i = 2; !found && i < 22; ++i) {
    for (int j = 2; !found && j < 12; ++j) {
      if (abs(controller.get_GameInfo_t().field[i][j] / 100) == Head) {
        found = true;
        yHead = i;
        xHead = j;
      }
    }
  }
  controller.userInput(Up, false);
  controller.userInput(Left, false);
  ASSERT_EQ(controller.get_GameInfo_t().field[yHead - 1][xHead - 1],
            -1 * (Head * 100 + 10));
  controller.userInput(Left, false);
  ASSERT_EQ(controller.get_GameInfo_t().field[yHead - 1][xHead - 2],
            -1 * (Head * 100 + 10));
  controller.userInput(Right, false);
  ASSERT_EQ(controller.get_GameInfo_t().field[yHead - 1][xHead - 2],
            -1 * (Head * 100 + 10));
}

GTEST_TEST(snake, right) {
  s21::Model model;
  model.set();

  s21::Controller controller(&model);

  controller.userInput(Start, false);
  bool found = false;
  int yHead, xHead;
  for (int i = 2; !found && i < 22; ++i) {
    for (int j = 2; !found && j < 12; ++j) {
      if (abs(controller.get_GameInfo_t().field[i][j] / 100) == Head) {
        found = true;
        yHead = i;
        xHead = j;
      }
    }
  }
  controller.userInput(Up, false);
  controller.userInput(Right, false);
  ASSERT_EQ(controller.get_GameInfo_t().field[yHead - 1][xHead + 1],
            Head * 100 + 10);
  controller.userInput(Right, false);
  ASSERT_EQ(controller.get_GameInfo_t().field[yHead - 1][xHead + 2],
            Head * 100 + 10);
  controller.userInput(Left, false);
  ASSERT_EQ(controller.get_GameInfo_t().field[yHead - 1][xHead + 2],
            Head * 100 + 10);
}

GTEST_TEST(snake, start_pause_end) {
  s21::Model model;
  model.set();

  s21::Controller controller(&model);

  ASSERT_EQ(controller.get_GameInfo_t().pause, 3);
  controller.userInput(Start, false);
  ASSERT_EQ(controller.get_GameInfo_t().pause, 0);
  controller.userInput(Pause, false);
  ASSERT_EQ(controller.get_GameInfo_t().pause, 1);
  controller.userInput(Pause, false);
  ASSERT_EQ(controller.get_GameInfo_t().pause, 0);
  controller.userInput(Terminate, false);
  ASSERT_EQ(controller.get_GameInfo_t().pause, 2);
  controller.userInput(Start, false);
  ASSERT_EQ(controller.get_GameInfo_t().pause, 3);
  controller.userInput(Action, false);
  ASSERT_EQ(controller.get_GameInfo_t().pause, 3);
}

GTEST_TEST(tetris, generate_figure) {
  s21::TetrisModel model;
  model.set();

  s21::TetrisController controller(&model);

  int figure = model.generate_figure();
  int success;
  if (figure >= 0 && figure <= 6)
    success = 1;
  else
    success = 0;
  ASSERT_EQ(success, 1);
}

GTEST_TEST(tetris, set) {
  s21::TetrisModel model;
  model.set();

  s21::TetrisController controller(&model);

  for (int i = 0; i < 24; ++i)
    for (int j = 0; j < 14; ++j)
      ASSERT_EQ(model.get_GameInfo_t().field[i][j], 0);
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j) ASSERT_EQ(model.get_GameInfo_t().next[i][j], 0);
  ASSERT_EQ(model.get_GameInfo_t().level, 1);
  ASSERT_EQ(model.get_GameInfo_t().high_score, model.get_record());
  ASSERT_EQ(model.get_GameInfo_t().score, 0);
  ASSERT_EQ(model.get_GameInfo_t().speed, 23);
  ASSERT_EQ(model.get_GameInfo_t().pause, 3);
}

GTEST_TEST(tetris, add_figures) {
  s21::TetrisModel model;
  model.set();

  s21::TetrisController controller(&model);

  controller.userInput(Start, false);

  model.set();

  model.add_red();

  for (int j = 5; j < 9; j++) ASSERT_EQ(model.get_GameInfo_t().field[0][j], 3);
  for (int j = 5; j < 9; j++) ASSERT_EQ(model.get_GameInfo_t().field[1][j], 3);
  for (int j = 5; j < 9; j++) ASSERT_EQ(model.get_GameInfo_t().field[2][j], 2);
  for (int j = 5; j < 9; j++) ASSERT_EQ(model.get_GameInfo_t().field[3][j], 3);

  model.set();

  model.add_orange();

  ASSERT_EQ(model.get_GameInfo_t().field[2][6], 2);
  for (int j = 7; j < 9; j++) ASSERT_EQ(model.get_GameInfo_t().field[2][j], 3);
  for (int j = 6; j < 9; j++) ASSERT_EQ(model.get_GameInfo_t().field[3][j], 2);
  for (int j = 6; j < 9; j++) ASSERT_EQ(model.get_GameInfo_t().field[4][j], 3);

  model.set();

  model.add_yellow();

  ASSERT_EQ(model.get_GameInfo_t().field[2][8], 2);
  for (int j = 6; j < 8; j++) ASSERT_EQ(model.get_GameInfo_t().field[2][j], 3);
  for (int j = 6; j < 9; j++) ASSERT_EQ(model.get_GameInfo_t().field[3][j], 2);
  for (int j = 6; j < 9; j++) ASSERT_EQ(model.get_GameInfo_t().field[4][j], 3);

  model.set();

  model.add_pink();

  for (int i = 2; i < 4; i++) {
    for (int j = 6; j < 8; j++) {
      ASSERT_EQ(model.get_GameInfo_t().field[i][j], 2);
    }
  }

  model.set();

  model.add_green();

  for (int j = 7; j < 9; j++) ASSERT_EQ(model.get_GameInfo_t().field[2][j], 2);
  for (int j = 6; j < 8; j++) ASSERT_EQ(model.get_GameInfo_t().field[3][j], 2);
  ASSERT_EQ(model.get_GameInfo_t().field[2][6], 3);
  ASSERT_EQ(model.get_GameInfo_t().field[3][8], 3);
  for (int j = 6; j < 9; j++) ASSERT_EQ(model.get_GameInfo_t().field[4][j], 3);

  model.set();

  model.add_blue();

  ASSERT_EQ(model.get_GameInfo_t().field[2][7], 2);
  ASSERT_EQ(model.get_GameInfo_t().field[2][6], 3);
  ASSERT_EQ(model.get_GameInfo_t().field[2][8], 3);
  for (int j = 6; j < 9; j++) ASSERT_EQ(model.get_GameInfo_t().field[3][j], 2);
  for (int j = 6; j < 9; j++) ASSERT_EQ(model.get_GameInfo_t().field[4][j], 3);

  model.set();

  model.add_violant();

  for (int j = 6; j < 8; j++) ASSERT_EQ(model.get_GameInfo_t().field[2][j], 2);
  for (int j = 7; j < 9; j++) ASSERT_EQ(model.get_GameInfo_t().field[3][j], 2);
  ASSERT_EQ(model.get_GameInfo_t().field[2][8], 3);
  ASSERT_EQ(model.get_GameInfo_t().field[3][6], 3);
  for (int j = 6; j < 9; j++) ASSERT_EQ(model.get_GameInfo_t().field[4][j], 3);
}

GTEST_TEST(tetris, moving) {
  s21::TetrisModel model;
  model.set();

  s21::TetrisController controller(&model);
  controller.userInput(Start, false);

  bool foundAdded = false;
  int y = 0, x = 0, value = 0;

  for (int i = 2; i < 22 && !foundAdded; ++i)
    for (int j = 2; j < 12 && !foundAdded; ++j)
      if (controller.get_GameInfo_t().field[i][j] != 0) {
        foundAdded = true;
        y = i;
        x = j;
        value = controller.get_GameInfo_t().field[i][j];
      }
  ASSERT_EQ(foundAdded, true);

  controller.userInput(Down, false);
  for (int i = 0; i < 10; ++i) controller.userInput(Right, false);

  ASSERT_NE(controller.get_GameInfo_t().field[y][x], value);

  for (int i = 0; i < 10; ++i) controller.userInput(Left, false);
  ASSERT_NE(controller.get_GameInfo_t().field[y][x], value);

  for (int i = 0; i < 20; ++i) controller.userInput(Down, false);
  bool foundFell = false;
  for (int j = 2; j < 12; ++j)
    if (controller.get_GameInfo_t().field[21][j] == 1) foundFell = true;
  ASSERT_EQ(foundFell, true);

  for (int i = 0; i < 40; ++i) controller.userInput(Down, false);
  for (int j = 2; j < 12; ++j)
    if (controller.get_GameInfo_t().field[19][j] == 1) foundFell = true;
  ASSERT_EQ(foundFell, true);

  controller.userInput(Terminate, false);
  controller.userInput(Start, false);
  controller.userInput(Start, false);
  for (int k = 0; k < 10; ++k) {
    ASSERT_EQ(controller.get_GameInfo_t().pause, 0);
    for (int i = 0; i < 25; ++i) {
      for (int j = 0; j < 25; ++j) {
        controller.userInput(Action, false);
        controller.userInput(Left, false);
        controller.userInput(Right, false);
        controller.userInput(Up, false);
        controller.userInput(Down, false);
        controller.userInput(Right, false);
        controller.userInput(Left, false);
        controller.updateCurrentState();
        usleep(50);
      }
    }
    ASSERT_EQ(controller.get_GameInfo_t().pause, 2);
    controller.userInput(Start, false);
    ASSERT_EQ(controller.get_GameInfo_t().pause, 3);
    controller.userInput(Start, false);
  }
  model.fall_all_field();
  for (int i = 2; i < 22; ++i) {
    for (int j = 2; j < 12; ++j) {
      model.pixel_fall(i, j);
    }
  }
}

GTEST_TEST(tetris, next_field) {
  s21::TetrisModel model;
  model.set();

  s21::TetrisController controller(&model);

  controller.userInput(Start, false);

  bool filled = false;

  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      if (controller.get_GameInfo_t().next[i][j] != 0) filled = true;

  ASSERT_EQ(filled, true);

  for (int i = 0; i < 100; ++i) controller.userInput(Down, false);
}

GTEST_TEST(tetris, start_pause_end) {
  s21::TetrisModel model;
  model.set();

  s21::TetrisController controller(&model);

  ASSERT_EQ(controller.get_GameInfo_t().pause, 3);
  controller.userInput(Start, false);
  ASSERT_EQ(controller.get_GameInfo_t().pause, 0);
  controller.userInput(Pause, false);
  ASSERT_EQ(controller.get_GameInfo_t().pause, 1);
  controller.userInput(Pause, false);
  ASSERT_EQ(controller.get_GameInfo_t().pause, 0);
  controller.userInput(Terminate, false);
  ASSERT_EQ(controller.get_GameInfo_t().pause, 2);
  controller.userInput(Start, false);
  controller.updateCurrentState();
  ASSERT_EQ(controller.get_GameInfo_t().pause, 3);
  controller.userInput(Action, false);
  ASSERT_EQ(controller.get_GameInfo_t().pause, 3);
}

GTEST_TEST(tetris, score) {
  s21::TetrisModel model;
  model.set();

  s21::TetrisController controller(&model);

  int score = model.increase_score(1);
  ASSERT_EQ(score, 100);

  score = model.increase_score(2);
  ASSERT_EQ(score, 300);

  score = model.increase_score(3);
  ASSERT_EQ(score, 700);

  score = model.increase_score(4);
  ASSERT_EQ(score, 1500);

  score = model.increase_score(5);
  ASSERT_EQ(score, 1600);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
