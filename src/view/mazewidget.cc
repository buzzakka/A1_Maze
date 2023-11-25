#include "mazewidget.h"

namespace s21 {
MazeWidget::MazeWidget(QGraphicsView *widg) : QGraphicsView(widg) {
  scene_ = new QGraphicsScene(this);
  maze_controller_ = std::make_unique<MazeController>();
  vertical_walls_.push_back({0});
  horizontal_walls_.push_back({0});
  DrawMaze();
}

MazeWidget::~MazeWidget() {
  ClearScene();
  delete scene_;
  scene_ = nullptr;
}

void MazeWidget::ClearVec(QVector<QGraphicsEllipseItem *> &vec) {
  for (int i = 0; i < vec.size(); i++) {
    delete vec[i];
    vec[i] = nullptr;
  }
  vec.clear();
}

void MazeWidget::ClearScene() {
  ClearVec(dots_);
  ClearVec(way_dots_);
  scene_->clear();
  coords_.clear();
}

void MazeWidget::Save(const QString &path) {
  QFile file(path);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&file);
    out << rows_ << " " << cols_ << "\n";
    for (const auto &row : vertical_walls_) {
      for (int val : row) out << val << " ";
      out << "\n";
    }
    out << "\n";
    for (const auto &row : horizontal_walls_) {
      for (int val : row) out << val << " ";
      out << "\n";
    }
    file.close();
  }
}

void MazeWidget::LoadMaze(const QString &path) {
  QFile file(path);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    in >> rows_ >> cols_;
    for (int i = 0; i < 2; ++i) {
      Matrix matrix;
      for (int row = 0; row < rows_; ++row) {
        std::vector<int> row_vec;
        for (int col = 0; col < cols_; ++col) {
          int value;
          in >> value;
          row_vec.push_back(value);
        }
        matrix.push_back(row_vec);
      }
      if (i == 0)
        vertical_walls_ = matrix;
      else
        horizontal_walls_ = matrix;
    }
    file.close();
    DrawMaze();
  }
}

void MazeWidget::SetWalls(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  maze_controller_->MakeMaze(rows, cols);
  vertical_walls_ = maze_controller_->GetVerticalWalls();
  horizontal_walls_ = maze_controller_->GetHorizontalWalls();
}

void MazeWidget::DrawMaze() {
  ClearScene();
  setScene(scene_);
  cell_size_v = 600.0 / rows_;
  cell_size_h = 600.0 / cols_;
  QPen wall_pen(Qt::white, 2);
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      if (vertical_walls_[row][col] == 1) {
        scene_->addLine((col + 1) * cell_size_h, row * cell_size_v,
                        (col + 1) * cell_size_h, (row + 1) * cell_size_v,
                        wall_pen);
      }
    }
  }
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      if (horizontal_walls_[row][col] == 1) {
        scene_->addLine(col * cell_size_h, (row + 1) * cell_size_v,
                        (col + 1) * cell_size_h, (row + 1) * cell_size_v,
                        wall_pen);
      }
    }
  }
  scene_->addRect(0, 0, cols_ * cell_size_h, rows_ * cell_size_v, wall_pen);
}

void MazeWidget::DrawWay() {
  for (const auto &coords : way_) {
    auto [x, y] = coords;
    float ellipse_width = 0.2 * cell_size_h;
    float ellipse_height = 0.2 * cell_size_v;
    float x_offset = (cell_size_h - ellipse_width) / 2;
    float y_offset = (cell_size_v - ellipse_height) / 2;
    QPen pen(Qt::red, 2);
    QGraphicsEllipseItem *way_dot = scene_->addEllipse(
        x * cell_size_h + x_offset, y * cell_size_v + y_offset, ellipse_width,
        ellipse_height, pen);
    way_dot->setBrush(Qt::red);
    way_dots_.append(way_dot);
  }
}

void MazeWidget::mousePressEvent(QMouseEvent *event) {
  if (dots_.size() == 2) {
    coords_.clear();
    ClearVec(dots_);
    ClearVec(way_dots_);
  }
  int x = event->pos().x() / cell_size_h;
  int y = event->pos().y() / cell_size_v;
  if (y < rows_ && x < cols_) {
    float ellipse_width = 0.5 * cell_size_h;
    float ellipse_height = 0.5 * cell_size_v;
    float x_offset = (cell_size_h - ellipse_width) / 2;
    float y_offset = (cell_size_v - ellipse_height) / 2;
    QPen pen(Qt::blue, 2);
    QGraphicsEllipseItem *dot = scene_->addEllipse(
        x * cell_size_h + x_offset, y * cell_size_v + y_offset, ellipse_width,
        ellipse_height, pen);
    dot->setBrush(Qt::blue);
    dots_.append(dot);
    coords_.push_back({x, y});
    if (dots_.size() == 2) {
      way_ =
          maze_controller_->MakeWay(rows_, cols_, vertical_walls_,
                                    horizontal_walls_, coords_[0], coords_[1]);
      DrawWay();
    }
  }
}
}  // namespace s21
