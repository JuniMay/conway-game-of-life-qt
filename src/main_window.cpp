#include "main_window.h"

#include "loader.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  this->resize(QSize(730, 560));
  this->setWindowTitle("Conway's Game of Life");

  main_widget = new QWidget(this);
  menu_bar = new QMenuBar();

  file_menu = new QMenu("&File");
  edit_menu = new QMenu("&Edit");
  view_menu = new QMenu("&View");
  help_menu = new QMenu("&Help");

  load_pattern_action = new QAction("Load", file_menu);
  save_pattern_action = new QAction("Save", file_menu);
  file_menu->addAction(load_pattern_action);
  file_menu->addAction(save_pattern_action);

  main_layout = new QHBoxLayout(main_widget);

  config_box = new QGroupBox(main_widget);
  game_view = new GameView(main_widget);

  alive_color_button = new QPushButton(config_box);
  dead_color_button = new QPushButton(config_box);

  alive_color_label = new QLabel("Alive Color:", config_box);
  dead_color_label = new QLabel("Dead Color:", config_box);

  alive_color_button->setFont(QFont("Fira Code"));
  dead_color_button->setFont(QFont("Fira Code"));

  evolve_button = new QPushButton("Evolve", config_box);
  reset_button = new QPushButton("Reset", config_box);
  random_button = new QPushButton("Random", config_box);
  configure_button = new QPushButton("Configure", config_box);

  evolve_button->setShortcut(Qt::Key_Space);

  alive_color_button->setText(alive_color.name());
  dead_color_button->setText(dead_color.name());

  config_box->setFixedWidth(200);
  config_layout = new QGridLayout(config_box);

  empty = new QWidget(config_box);
  empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

  height_label = new QLabel("Height:", config_box);
  height_line_edit = new QLineEdit(config_box);
  width_label = new QLabel("Width:", config_box);
  width_line_edit = new QLineEdit(config_box);

  height_line_edit->setFont(QFont("Fira Code"));
  width_line_edit->setFont(QFont("Fira Code"));

  this->setCentralWidget(main_widget);
  this->setMenuBar(menu_bar);

  main_widget->setLayout(main_layout);
  menu_bar->addMenu(file_menu);
  menu_bar->addMenu(edit_menu);
  menu_bar->addMenu(view_menu);
  menu_bar->addMenu(help_menu);

  this->statusBar()->showMessage("Done", 2000);

  main_layout->addWidget(config_box);

  main_layout->addWidget(game_view);

  main_layout->setStretch(0, 1);
  main_layout->setStretch(1, 3);

  config_box->setLayout(config_layout);

  config_layout->addWidget(alive_color_label, 0, 0, Qt::AlignRight);
  config_layout->addWidget(alive_color_button, 0, 1);
  config_layout->addWidget(dead_color_label, 1, 0, Qt::AlignRight);
  config_layout->addWidget(dead_color_button, 1, 1);
  config_layout->addWidget(height_label, 2, 0, Qt::AlignRight);
  config_layout->addWidget(height_line_edit, 2, 1);
  config_layout->addWidget(width_label, 3, 0, Qt::AlignRight);
  config_layout->addWidget(width_line_edit, 3, 1);
  config_layout->addWidget(empty, 4, 0, 1, 2);
  config_layout->addWidget(configure_button, 5, 0, 1, 2);
  config_layout->addWidget(evolve_button, 6, 0, 1, 2);
  config_layout->addWidget(random_button, 7, 0, 1, 2);
  config_layout->addWidget(reset_button, 8, 0, 1, 2);

  height_line_edit->setText("50");
  width_line_edit->setText("50");

  connect(evolve_button, &QPushButton::clicked, game_view,
          &GameView::evolve_step);
  connect(reset_button, &QPushButton::clicked, game_view, &GameView::reset);
  connect(configure_button, &QPushButton::clicked, this,
          &MainWindow::configure);
  connect(random_button, &QPushButton::clicked, game_view, &GameView::random);

  connect(this, &MainWindow::configure_alive_color, game_view,
          &GameView::set_alive_color);
  connect(this, &MainWindow::configure_dead_color, game_view,
          &GameView::set_dead_color);
  connect(this, &MainWindow::configure_height, game_view,
          &GameView::set_row_cnt);
  connect(this, &MainWindow::configure_width, game_view,
          &GameView::set_col_cnt);

  connect(alive_color_button, &QPushButton::clicked, this,
          &MainWindow::get_alive_color);
  connect(dead_color_button, &QPushButton::clicked, this,
          &MainWindow::get_dead_color);

  connect(load_pattern_action, &QAction::triggered, this,
          &MainWindow::load_pattern_file);
  connect(save_pattern_action, &QAction::triggered, this,
          &MainWindow::save_pattern_file);
}

MainWindow::~MainWindow() {
  delete main_widget;
  delete empty;

  delete menu_bar;

  delete file_menu;
  delete edit_menu;
  delete view_menu;
  delete help_menu;

  delete main_layout;
  delete config_layout;

  delete config_box;

  delete game_view;

  delete height_label;
  delete width_label;
  delete height_line_edit;
  delete width_line_edit;
  delete alive_color_label;
  delete dead_color_label;

  delete evolve_button;
  delete reset_button;
  delete random_button;
  delete configure_button;

  delete alive_color_button;
  delete dead_color_button;

  delete load_pattern_action;
  delete save_pattern_action;
}

void MainWindow::configure() {
  emit configure_alive_color(alive_color);
  emit configure_dead_color(dead_color);
  emit configure_height(height_line_edit->text().toInt());
  emit configure_width(width_line_edit->text().toInt());
}

void MainWindow::get_alive_color() {
  alive_color = QColorDialog::getColor();
  alive_color_button->setText(alive_color.name());
}

void MainWindow::get_dead_color() {
  dead_color = QColorDialog::getColor();
  dead_color_button->setText(dead_color.name());
}

void MainWindow::load_pattern_file() {
  QStringList path_list =
      QFileDialog::getOpenFileNames(this, tr("Open pattern file"));
  QString path = path_list[0];
  bool ok;
  QFile file(path);
  LoadInfo info = interpret(file, ok);
  if (!ok) {
    QMessageBox::information(this, tr("Load error"),
                             tr("Maybe invalid file format"));
  } else {
    game_view->load_pattern(info);
  }
}

void MainWindow::save_pattern_file() {
  QString path = QFileDialog::getSaveFileName(this, tr("Save pattern"));
  LoadInfo info;
  game_view->save_pattern(info);
  QFile file(path);
  save_to_file(file, info);
}
