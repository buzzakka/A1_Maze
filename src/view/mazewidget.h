#ifndef A1_MAZE_1_VIEW_MAZEWIDGET_H
#define A1_MAZE_1_VIEW_MAZEWIDGET_H

#include <QFile>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QTextStream>

#include "../controller/maze_controller.h"

namespace s21 {
class MazeWidget : public QGraphicsView {
 public:
  using Way = std::list<std::pair<int, int>>;
  using Matrix = std::vector<std::vector<int>>;
  using Coords = std::vector<std::pair<int, int>>;

  MazeWidget(QGraphicsView *widg = nullptr);
  ~MazeWidget();

  void DrawWay();
  void DrawMaze();
  void ClearScene();
  void Save(const QString &path);
  void SetWalls(int rows, int cols);
  void LoadMaze(const QString &path);
  void ClearVec(QVector<QGraphicsEllipseItem *> &vec);

  void mousePressEvent(QMouseEvent *event) override;

 private:
  QGraphicsScene *scene_;
  int rows_{1};
  int cols_{1};
  float cell_size_v{};
  float cell_size_h{};
  Way way_;
  Coords coords_;
  Matrix vertical_walls_;
  Matrix horizontal_walls_;
  QVector<QGraphicsEllipseItem *> dots_;
  QVector<QGraphicsEllipseItem *> way_dots_;
  std::unique_ptr<MazeController> maze_controller_;
};
}  // namespace s21

#endif  // A1_MAZE_1_VIEW_MAZEWIDGET_H
