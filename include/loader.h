#ifndef __LOADER_H__
#define __LOADER_H__

#include "common.h"

struct LoadInfo {
  int row_idx, col_idx, row_cnt, col_cnt;
  QChar alive_char, dead_char;
  Universe pattern;
};

LoadInfo interpret(QFile &file, bool &ok);

#endif