#ifndef A1_MAZE_1_CONTROLLER_MAZE_CONTROLLER_H
#define A1_MAZE_1_CONTROLLER_MAZE_CONTROLLER_H

#include "./../model/lee_algorithm.h"
#include "./../model/maze_builder.h"

namespace s21 {
class MazeController {
 public:
  using Coord = std::pair<int, int>;
  using Way = std::list<std::pair<int, int>>;
  using Matrix = std::vector<std::vector<int>>;

  MazeController(){};

  Matrix& GetVerticalWalls() { return builder_.GetVerticalWalls(); }
  Matrix& GetHorizontalWalls() { return builder_.GetHorizontalWalls(); }

  Way MakeWay(int rows, int cols, Matrix vert_walls, Matrix horiz_walls,
              Coord start, Coord end) {
    return solution_.Solve(rows, cols, vert_walls, horiz_walls, start, end);
  }

  void MakeMaze(int rows, int cols) { builder_.BuildMaze(rows, cols); }

 private:
  MazeBuilder builder_;
  LeeAlgorithm solution_;
};
}  // namespace s21

#endif  // A1_MAZE_1_CONTROLLER_MAZE_CONTROLLER_H
