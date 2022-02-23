#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include "common.h"
#include "loader.h"

class GameView : public QWidget {
  Q_OBJECT

  //  Q_PROPERTY(int row_cnt READ get_row_cnt WRITE set_row_cnt)
  //  Q_PROPERTY(int col_cnt READ get_col_cnt WRITE set_col_cnt)
  //  Q_PROPERTY(QColor alive_color READ get_alive_color WRITE set_alive_color)
  //  Q_PROPERTY(QColor dead_color READ get_dead_color WRITE set_dead_color)
  //  Q_PROPERTY(int gen_cnt READ get_gen_cnt)

 public:
  explicit GameView(QWidget* parent = nullptr);
  ~GameView();

  int get_row_cnt() const;
  int get_col_cnt() const;
  QColor get_alive_color() const;
  QColor get_dead_color() const;
  int get_gen_cnt() const;

  int get_neighbor_cnt(const int& row_idx, const int& col_idx);

  void load_pattern(LoadInfo& info);
  void save_pattern(LoadInfo& info);

 public slots:
  void set_row_cnt(const int& _row_cnt);
  void set_col_cnt(const int& _col_cnt);
  void set_alive_color(const QColor& _alive_color);
  void set_dead_color(const QColor& _dead_color);

  void evolve_step();
  void evolve(const int& n);
  void reset();

  void random();

 private:
  int row_cnt = 50;
  int col_cnt = 50;
  int gen_cnt = 0;
  QColor alive_color = QColor::fromRgb(0xff, 0xff, 0xff);
  QColor dead_color = QColor::fromRgb(0, 0, 0);
  Universe gen, prev_gen;

 protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);
};

#endif
