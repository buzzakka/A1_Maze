#include "mazeview.h"

#include "ui_mazeview.h"

namespace s21 {
MazeView::MazeView(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MazeView) {
  ui_->setupUi(this);
  maze_widget_ = std::make_unique<MazeWidget>(ui_->graphicsView);

  setFixedSize(910, 660);

  connect(ui_->btnOpenFile, SIGNAL(clicked()), this,
          SLOT(OnBtnOpenFileClicked()));
  connect(ui_->btnSaveFile, SIGNAL(clicked()), this,
          SLOT(OnBtnSaveFileClicked()));
  connect(ui_->btnGenerate, SIGNAL(clicked()), this,
          SLOT(OnBtnGenerateClicked()));
}

MazeView::~MazeView() { delete ui_; }

void MazeView::OnBtnOpenFileClicked() {
  QString path = QFileDialog::getOpenFileName(this, "Open maze", QString(),
                                              "Maze file (*.txt)");
  maze_widget_->LoadMaze(path);
}

void MazeView::OnBtnSaveFileClicked() {
  QString path = QFileDialog::getSaveFileName(this, "Save maze", QString(),
                                              "Maze file (*.txt)");
  maze_widget_->Save(path);
}

void MazeView::OnBtnGenerateClicked() {
  int rows = ui_->RowsValue->value();
  int cols = ui_->ColsValue->value();
  maze_widget_->SetWalls(rows, cols);
  maze_widget_->DrawMaze();
}
}  // namespace s21
