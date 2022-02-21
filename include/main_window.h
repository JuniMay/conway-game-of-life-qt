#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include "common.h"
#include "game_view.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 public slots:
  void configure();
  void get_alive_color();
  void get_dead_color();

 signals:
  void configure_alive_color(QColor c);
  void configure_dead_color(QColor c);
  void configure_height(int n);
  void configure_width(int n);

 private:
  QWidget *main_widget, *empty;
  QMenuBar *menu_bar;
  QToolBar *tool_bar;
  QMenu *file_menu, *edit_menu, *view_menu, *help_menu;
  QHBoxLayout *main_layout;
  QGridLayout *config_layout;
  QGroupBox *config_box;
  GameView *game_view;

  QLabel *alive_color_label, *dead_color_label, *height_label, *width_label;
  QLineEdit *height_line_edit, *width_line_edit;

  QPushButton *evolve_button, *reset_button, *random_button, *configure_button,
      *alive_color_button, *dead_color_button;

  QColor alive_color = QColor::fromRgb(0xff, 0xff, 0xff);
  QColor dead_color = QColor::fromRgb(0, 0, 0);
};

#endif
