#include "loader.h"

LoadInfo interpret(QFile &file, bool &ok) {
  LoadInfo res = {0, 0, 0, 0, ' ', ' ', Universe()};
  if (!file.exists()) {
    ok = false;
    return res;
  }
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    ok = false;
    return res;
  }
  QTextStream pattern_stream(&file);
  pattern_stream >> res.alive_char;
  pattern_stream >> res.dead_char;
  while (res.dead_char == ' ') {
    pattern_stream >> res.dead_char;
  }
  pattern_stream >> res.row_idx >> res.col_idx >> res.row_cnt >> res.col_cnt;
  res.pattern = Universe(res.row_cnt, QVector<CellState>(res.col_cnt));
  QChar c;
  int i = 0, j = 0;
  while (i < res.row_cnt) {
    pattern_stream >> c;
    if (c != res.alive_char && c != res.dead_char) {
      continue;
    } else {
      if (c == res.alive_char) {
        res.pattern[i][j] = Alive;
      } else {
        res.pattern[i][j] = Dead;
      }
      j += 1;
      if (j >= res.col_cnt) {
        j = 0;
        i += 1;
      }
    }
  }
  ok = true;
  return res;
}
