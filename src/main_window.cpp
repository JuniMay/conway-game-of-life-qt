#include "main_window.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  this->resize(QSize(730, 600));
  this->setWindowTitle("Conway's Game of Life");

  main_widget = new QWidget(this);
  menu_bar = new QMenuBar();
  tool_bar = new QToolBar();

  file_menu = new QMenu("&File");
  edit_menu = new QMenu("&Edit");
  view_menu = new QMenu("&View");
  help_menu = new QMenu("&Help");

  main_layout = new QHBoxLayout(main_widget);

  config_box = new QGroupBox(main_widget);
  game_view = new GameView(main_widget);
  evolve_button = new QPushButton("Evolve", tool_bar);
  reset_button = new QPushButton("Reset", tool_bar);
  random_button = new QPushButton("Random", tool_bar);
  configure_button = new QPushButton("Configure", tool_bar);

  alive_color_button = new QPushButton(config_box);
  dead_color_button = new QPushButton(config_box);

  alive_color_button->setFont(QFont("Fira Code"));
  dead_color_button->setFont(QFont("Fira Code"));

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

  alive_color_label = new QLabel("Alive Color:", config_box);
  dead_color_label = new QLabel("Dead Color:", config_box);

  this->setCentralWidget(main_widget);
  this->setMenuBar(menu_bar);
  this->addToolBar(tool_bar);

  main_widget->setLayout(main_layout);
  menu_bar->addMenu(file_menu);
  menu_bar->addMenu(edit_menu);
  menu_bar->addMenu(view_menu);
  menu_bar->addMenu(help_menu);

   tool_bar->setMovable(false);
  tool_bar->addWidget(configure_button);
  tool_bar->addWidget(random_button);
  tool_bar->addWidget(evolve_button);
  tool_bar->addWidget(reset_button);

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

  connect(evolve_button, &QPushButton::clicked, game_view,
          &GameView::evolve_step);
  connect(reset_button, &QPushButton::clicked, game_view, &GameView::reset);
  connect(configure_button, &QPushButton::clicked, this,
          &MainWindow::configure);

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
}

MainWindow::~MainWindow() {
  delete main_widget;
  delete empty;

  delete menu_bar;

  delete tool_bar;

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
