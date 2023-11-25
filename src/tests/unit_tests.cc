#include <regex>

#include "../controller/maze_controller.h"
#include "../model/lee_algorithm.h"
#include "../model/maze_builder.h"
#include "gtest/gtest.h"

/*
    ========== ТЕСТЫ MAZE BUILDER (START) ==========
*/

s21::MazeBuilder builder;
s21::LeeAlgorithm algorithm;

std::string ReadFile() {
  std::ifstream in("maze.txt");
  if (!in.is_open()) {
    throw std::runtime_error("Unable to open file maze.txt");
  }

  std::string content((std::istreambuf_iterator<char>(in)),
                      std::istreambuf_iterator<char>());
  return content;
}

bool IsCorrectMatrix(std::vector<std::vector<int>> matrix) {
  for (auto it_1 = matrix.begin(); it_1 != matrix.end(); ++it_1)
    for (auto it_2 = (*it_1).begin(); it_2 != (*it_1).end(); ++it_2)
      if (*it_2 != 1 && *it_2 != 0) return false;
  return true;
}

TEST(test_maze_model_builder, builder_correct_values_1) {
  ASSERT_NO_THROW(builder.BuildMaze(5, 5));
  std::vector<std::vector<int>> bottom_wals = builder.GetHorizontalWalls();
  std::vector<std::vector<int>> right_wals = builder.GetVerticalWalls();
  ASSERT_TRUE(IsCorrectMatrix(bottom_wals));
  ASSERT_TRUE(IsCorrectMatrix(right_wals));
}

TEST(test_maze_model_builder, builder_incorrect_values_1) {
  ASSERT_ANY_THROW(builder.BuildMaze(0, 0));
}

TEST(test_maze_model_builder, builder_incorrect_values_2) {
  ASSERT_ANY_THROW(builder.BuildMaze(10, 0));
}

TEST(test_maze_model_builder, builder_incorrect_values_3) {
  ASSERT_ANY_THROW(builder.BuildMaze(0, 10));
}

TEST(test_maze_model_builder, builder_incorrect_values_4) {
  ASSERT_ANY_THROW(builder.BuildMaze(-1, -1));
}

/*
    ========== ТЕСТЫ MAZE BUILDER (END) ==========
*/

/*
    ========== ТЕСТЫ LEE ALGORITHM (START) ==========
*/

s21::LeeAlgorithm solver;

TEST(test_lee_algorithm_solver, solver_correct_values_1) {
  int row = 2, col = 2;
  std::vector<std::vector<int>> right({{0, 0}, {0, 0}});
  std::vector<std::vector<int>> bottom({{1, 0}, {0, 0}});
  std::list<std::pair<int, int>> correct_path = {
      {0, 0}, {1, 0}, {1, 1}, {0, 1}};
  std::list<std::pair<int, int>> path =
      solver.Solve(row, col, right, bottom, {0, 0}, {0, 1});
  ASSERT_TRUE(correct_path == path);
}

TEST(test_lee_algorithm_solver, solver_correct_values_2) {
  int row = 2, col = 4;
  std::vector<std::vector<int>> right({{0, 0, 0, 0}, {0, 0, 0, 0}});
  std::vector<std::vector<int>> bottom({{1, 0, 0, 0}, {0, 0, 0, 0}});
  std::list<std::pair<int, int>> correct_path = {
      {0, 0}, {1, 0}, {1, 1}, {0, 1}};
  std::list<std::pair<int, int>> path =
      solver.Solve(row, col, right, bottom, {0, 0}, {0, 1});
  ASSERT_TRUE(correct_path == path);
}

TEST(test_lee_algorithm_solver, solver_correct_values_3) {
  int row = 1, col = 10;
  std::vector<std::vector<int>> right({std::vector<int>(10, 0)});
  std::vector<std::vector<int>> bottom({std::vector<int>(10, 0)});
  std::list<std::pair<int, int>> correct_path = {{0, 0}, {1, 0}, {2, 0}, {3, 0},
                                                 {4, 0}, {5, 0}, {6, 0}, {7, 0},
                                                 {8, 0}, {9, 0}};
  std::list<std::pair<int, int>> path =
      solver.Solve(row, col, right, bottom, {0, 0}, {9, 0});
  ASSERT_TRUE(correct_path == path);
}

TEST(test_lee_algorithm_solver, solver_correct_values_4) {
  int row = 1, col = 10;
  std::vector<std::vector<int>> right({std::vector<int>(10, 0)});
  std::vector<std::vector<int>> bottom({std::vector<int>(10, 0)});
  std::list<std::pair<int, int>> correct_path = {{0, 0}, {1, 0}, {2, 0}, {3, 0},
                                                 {4, 0}, {5, 0}, {6, 0}, {7, 0},
                                                 {8, 0}, {9, 0}};
  std::list<std::pair<int, int>> path =
      solver.Solve(row, col, right, bottom, {0, 0}, {9, 0});
  ASSERT_TRUE(correct_path == path);
}

TEST(test_lee_algorithm_solver, solver_correct_values_5) {
  int row = 10, col = 1;
  std::vector<std::vector<int>> right(
      {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}});
  std::vector<std::vector<int>> bottom(
      {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}});
  std::list<std::pair<int, int>> correct_path = {{0, 0}, {0, 1}, {0, 2}, {0, 3},
                                                 {0, 4}, {0, 5}, {0, 6}, {0, 7},
                                                 {0, 8}, {0, 9}};
  std::list<std::pair<int, int>> path =
      solver.Solve(row, col, right, bottom, {0, 0}, {0, 9});
  ASSERT_TRUE(correct_path == path);
}

TEST(test_lee_algorithm_solver, solver_complex_correct_values_6) {
  std::list<std::pair<int, int>> correct_path = {
      {0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}, {1, 2}, {1, 3}, {2, 3}, {3, 3},
      {3, 4}, {4, 4}, {4, 3}, {5, 3}, {5, 2}, {4, 2}, {3, 2}, {3, 1}, {3, 0},
      {4, 0}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {7, 2}, {7, 3}, {8, 3}, {8, 2},
      {8, 1}, {8, 0}, {9, 0}, {9, 1}, {9, 2}, {9, 3}, {9, 4}, {9, 5}, {9, 6},
      {8, 6}, {8, 5}, {7, 5}, {7, 6}, {6, 6}, {5, 6}, {5, 7}, {6, 7}, {6, 8},
      {6, 9}, {7, 9}, {8, 9}, {9, 9}};
  std::list<std::pair<int, int>> path =
      solver.Solve("maze_ex_10.txt", {0, 0}, {9, 9});
  ASSERT_TRUE(correct_path == path);
}

/*
    ========== ТЕСТЫ LEE ALGORITHM (END) ==========
*/

bool CompareLists(const std::list<std::pair<int, int>>& list1,
                  const std::list<std::pair<int, int>>& list2) {
  if (list1.size() != list2.size()) {
    return false;
  }

  auto it1 = list1.begin();
  auto it2 = list2.begin();

  while (it1 != list1.end() && it2 != list2.end()) {
    if (*it1 != *it2) {
      return false;
    }

    ++it1;
    ++it2;
  }

  return true;
}

TEST(test_maze_lee_algorithm, lee_algorithm_1) {
  s21::LeeAlgorithm al;
  std::vector<std::vector<int>> rw = {{0, 0, 0}, {1, 0, 1}, {0, 1, 0}};
  std::vector<std::vector<int>> bw = {{1, 0, 1}, {0, 0, 0}, {1, 1, 1}};
  std::list<std::pair<int, int>> right_way = {
      {0, 0}, {1, 0}, {1, 1}, {1, 2}, {0, 2}};
  std::list<std::pair<int, int>> way = al.Solve(3, 3, rw, bw, {0, 0}, {0, 2});
  ASSERT_TRUE(CompareLists(way, right_way));
}

TEST(test_maze_lee_algorithm, lee_algorithm_2) {
  s21::LeeAlgorithm al;
  std::vector<std::vector<int>> rw = {
      {1, 1, 0, 0, 0, 0, 1, 0, 0, 1}, {0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
      {1, 0, 0, 1, 0, 1, 1, 0, 1, 1}, {1, 1, 1, 0, 0, 0, 1, 1, 0, 1},
      {0, 1, 0, 1, 0, 0, 1, 0, 1, 1}, {1, 0, 1, 0, 1, 0, 0, 1, 1, 1},
      {1, 0, 1, 1, 1, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
      {1, 1, 0, 0, 1, 0, 0, 1, 0, 1}, {0, 0, 0, 1, 0, 0, 0, 0, 0, 1}};
  std::vector<std::vector<int>> bw = {
      {0, 0, 0, 1, 0, 1, 0, 0, 1, 0}, {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 1, 1, 1, 0, 1, 0, 0}, {0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
      {0, 0, 0, 1, 0, 1, 1, 0, 0, 0}, {0, 1, 1, 0, 1, 0, 1, 1, 1, 0},
      {1, 1, 0, 0, 0, 1, 1, 0, 0, 1}, {0, 1, 1, 1, 1, 0, 1, 0, 0, 0},
      {0, 0, 1, 1, 0, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
  std::list<std::pair<int, int>> right_way = {
      {1, 3}, {1, 2}, {2, 2}, {3, 2}, {3, 1}, {2, 1}, {2, 0}, {3, 0},
      {4, 0}, {5, 0}, {6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {5, 4},
      {4, 4}, {4, 5}, {3, 5}, {3, 6}, {3, 7}, {4, 7}, {5, 7}, {5, 8},
      {6, 8}, {7, 8}, {7, 7}, {7, 6}, {6, 6}, {5, 6}, {5, 5}, {6, 5},
      {7, 5}, {7, 4}, {8, 4}, {8, 3}, {9, 3}, {9, 4}, {9, 5},
  };
  std::list<std::pair<int, int>> way = al.Solve(10, 10, rw, bw, {1, 3}, {9, 5});
  ASSERT_TRUE(CompareLists(way, right_way));
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
