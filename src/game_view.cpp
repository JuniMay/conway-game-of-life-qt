#include "game_view.h"

GameView::GameView(QWidget* parent) : QWidget(parent) {
  qDebug() << row_cnt << col_cnt;
  gen = Universe(row_cnt, QVector<CellState>(col_cnt, Dead));
  prev_gen = Universe(row_cnt, QVector<CellState>(col_cnt, Dead));
}
GameView::~GameView() {}

int GameView::get_row_cnt() const { return row_cnt; }
int GameView::get_col_cnt() const { return col_cnt; }
QColor GameView::get_alive_color() const { return alive_color; }
QColor GameView::get_dead_color() const { return dead_color; }
int GameView::get_gen_cnt() const { return gen_cnt; }

void GameView::set_row_cnt(const int& _row_cnt) {
  qDebug() << _row_cnt;
  row_cnt = _row_cnt;
  gen.resize(row_cnt);
  prev_gen.resize(row_cnt);
}
void GameView::set_col_cnt(const int& _col_cnt) {
  qDebug() << _col_cnt;
  col_cnt = _col_cnt;
  for (int i = 0; i < row_cnt; i++) {
    gen[i].resize(col_cnt);
    prev_gen[i].resize(col_cnt);
  }
}
void GameView::set_alive_color(const QColor& _alive_color) {
  qDebug() << _alive_color.name();
  alive_color = _alive_color;
  update();
}
void GameView::set_dead_color(const QColor& _dead_color) {
  qDebug() << _dead_color.name();
  dead_color = _dead_color;
  update();
}

int GameView::get_neighbor_cnt(const int& row_idx, const int& col_idx) {
  int cnt = 0;
  for (int i = std::max(row_idx - 1, 0);
       i <= std::min(row_idx + 1, row_cnt - 1); i++) {
    for (int j = std::max(col_idx - 1, 0);
         j <= std::min(col_idx + 1, col_cnt - 1); j++) {
      if (i == row_idx && j == col_idx) continue;
      if (prev_gen[i][j] == Alive) {
        cnt++;
      }
    }
  }
  return cnt;
}

void GameView::evolve_step() {
  prev_gen = gen;
  gen_cnt++;
  for (int i = 0; i < row_cnt; i++) {
    for (int j = 0; j < col_cnt; j++) {
      int cnt = get_neighbor_cnt(i, j);
      if (prev_gen[i][j] == Alive) {
        if (cnt < 2 || cnt > 3) {
          gen[i][j] = Dead;
        }
      } else {
        if (cnt == 3) {
          gen[i][j] = Alive;
        }
      }
    }
  }
  update();
}

void GameView::evolve(const int& n) {
  for (int i = 0; i < n; ++i) {
    evolve_step();
  }
}

void GameView::reset() {
  gen_cnt = 0;
  for (int i = 0; i < row_cnt; i++) {
    for (int j = 0; j < col_cnt; j++) {
      gen[i][j] = Dead;
      prev_gen[i][j] = Dead;
    }
  }
  update();
}

void GameView::update_view() {}

void GameView::paintEvent(QPaintEvent*) {
  int cell_size = 20;

  QPainter painter(this);
  QRect border(0, 0, col_cnt * cell_size, row_cnt * cell_size);
  painter.setBrush(QBrush(dead_color));
  painter.fillRect(border, painter.brush());
  painter.setPen(QPen(alive_color, 2));
  painter.drawRect(border);

  painter.setPen(QPen(alive_color, 1));
  for (int i = 0; i <= row_cnt * cell_size; i += cell_size) {
    painter.drawLine(0, i, col_cnt * cell_size, i);
  }
  for (int i = 0; i <= col_cnt * cell_size; i += cell_size) {
    painter.drawLine(i, 0, i, row_cnt * cell_size);
  }

  for (int i = 0; i < row_cnt; i++) {
    for (int j = 0; j < col_cnt; j++) {
      if (gen[i][j] == Dead) continue;
      QRect cell_rect(cell_size * j, cell_size * i, cell_size, cell_size);
      painter.setBrush(QBrush(alive_color));
      painter.fillRect(cell_rect, painter.brush());
    }
  }
}

void GameView::mousePressEvent(QMouseEvent* event) {
  int cell_size = 20;
  int row_idx = (event->pos().y() - 2) / cell_size;
  int col_idx = (event->pos().x() - 2) / cell_size;
  if (gen[row_idx][col_idx] == Alive) {
    gen[row_idx][col_idx] = Dead;
  } else {
    gen[row_idx][col_idx] = Alive;
  }
  update();
}
