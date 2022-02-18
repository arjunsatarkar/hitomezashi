#ifndef HITOMEZASHI_HITOMEZASHI_H
#define HITOMEZASHI_HITOMEZASHI_H

#include "SDL.h"

struct Hitomezashi_State {
  int x_pattern_len;
  int y_pattern_len;

  char *x_pattern;
  char *y_pattern;

  int gap;

  int line_thickness;

  int output_width;
  int output_height;

  SDL_Surface *surface;
};

enum Hitomezashi_State_Init_Result {
  Hitomezashi_State_Init_Result_Success,
  Hitomezashi_State_Init_Result_Err_Create_Surface,
};

enum Hitomezashi_Draw_Result {
  Hitomezashi_Draw_Result_Success,
  Hitomezashi_Draw_Result_Err_Lock_Surface,
};

enum Hitomezashi_State_Init_Result
hitomezashi_state_init(struct Hitomezashi_State *state, int x_pattern_len,
                       int y_pattern_len, char *x_pattern, char *y_pattern,
                       int gap, int line_thickness);

enum Hitomezashi_Draw_Result hitomezashi_draw(struct Hitomezashi_State *state);

#endif // HITOMEZASHI_HITOMEZASHI_H
