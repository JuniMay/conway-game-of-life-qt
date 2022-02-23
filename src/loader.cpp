#include "loader.h"

LoadInfo interpret(QFile &file, bool &ok) {
  LoadInfo info = {0, 0, 0, 0, ' ', ' ', Universe()};
  if (!file.exists()) {
    ok = false;
    return info;
  }
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    ok = false;
    return info;
  }
  QTextStream pattern_stream(&file);
  pattern_stream >> info.alive_char;
  pattern_stream >> info.dead_char;
  while (info.dead_char == ' ') {
    pattern_stream >> info.dead_char;
  }
  pattern_stream >> info.row_idx >> info.col_idx >> info.row_cnt >>
      info.col_cnt;

  info.pattern = Universe(info.row_cnt, QVector<CellState>(info.col_cnt));
  QChar c;
  int i = 0, j = 0;
  while (i < info.row_cnt) {
    pattern_stream >> c;
    if (c != info.alive_char && c != info.dead_char) {
      continue;
    } else {
      if (c == info.alive_char) {
        info.pattern[i][j] = Alive;
      } else {
        info.pattern[i][j] = Dead;
      }
      j += 1;
      if (j >= info.col_cnt) {
        j = 0;
        i += 1;
      }
    }
  }
  ok = true;
  file.close();
  return info;
}

void save_to_file(QFile &file, LoadInfo &info) {
  bool ok = file.open(QIODevice::ReadWrite | QIODevice::Text);
  if (!ok) return;  // TODO: call a MessageBox in MainWindow;
  QTextStream pattern_stream(&file);
  pattern_stream << info.alive_char << ' ' << info.dead_char << ' '
                 << info.row_idx << ' ' << info.col_idx << ' ' << info.row_cnt
                 << ' ' << info.col_cnt << '\n';
  for (int i = 0; i < info.row_cnt; i++) {
    for (int j = 0; j < info.col_cnt; j++) {
      if (info.pattern[i][j] == Alive) {
        pattern_stream << info.alive_char;
      } else {
        pattern_stream << info.dead_char;
      }
    }
    pattern_stream << '\n';
  }
  file.close();
}
