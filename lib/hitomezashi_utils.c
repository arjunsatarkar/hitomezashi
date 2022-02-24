#include "hitomezashi_utils.h"

#include <stddef.h>
#include <stdlib.h>

char *hitomezashi_ascii_binary_str_to_ints(char *ascii_str, size_t len) {
  char *res = malloc(len);
  for (int i = 0; i < len; ++i) {
    switch (ascii_str[i]) {
    case '0':;
      res[i] = 0;
      break;
    case '1':;
      res[i] = 1;
      break;
    default:;
      free(res);
      return NULL;
    }
  }
  return res;
}
