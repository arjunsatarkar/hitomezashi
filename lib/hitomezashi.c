#include "hitomezashi.h"
#include "SDL2/SDL.h"
#include <assert.h>

SDL_Color HITOMEZASHI_FG_COLOUR = {.r = 0, .g = 0, .b = 0};
SDL_Color HITOMEZASHI_BG_COLOUR = {.r = 255, .g = 255, .b = 255};

enum Hitomezashi_State_Init_Result
hitomezashi_state_init(struct Hitomezashi_State *state, int x_pattern_len,
                       int y_pattern_len, char *x_pattern, char *y_pattern,
                       int gap, int line_thickness) {
  assert(x_pattern_len >= 0);
  assert(y_pattern_len >= 0);
  assert(gap >= 0);
  assert(line_thickness > 0);

  state->y_pattern_len = y_pattern_len;
  state->x_pattern_len = x_pattern_len;
  state->x_pattern = x_pattern;
  state->y_pattern = y_pattern;
  state->gap = gap;
  state->line_thickness = line_thickness;
  state->output_width = x_pattern_len * gap;
  state->output_height = y_pattern_len * gap;

  state->surface = SDL_CreateRGBSurface(0, state->output_width,
                                        state->output_height, 32, 0, 0, 0, 0);
  if (!state->surface) {
    return Hitomezashi_State_Init_Result_Err_Create_Surface;
  }
  return Hitomezashi_State_Init_Result_Success;
}

enum Hitomezashi_Draw_Result hitomezashi_draw(struct Hitomezashi_State *state) {
  if (SDL_LockSurface(state->surface) != 0) {
    return Hitomezashi_Draw_Result_Err_Lock_Surface;
  }

  Uint32 bg_colour =
      SDL_MapRGB(state->surface->format, HITOMEZASHI_BG_COLOUR.r,
                 HITOMEZASHI_BG_COLOUR.g, HITOMEZASHI_BG_COLOUR.b);
  Uint32 fg_colour =
      SDL_MapRGB(state->surface->format, HITOMEZASHI_FG_COLOUR.r,
                 HITOMEZASHI_FG_COLOUR.g, HITOMEZASHI_FG_COLOUR.b);

  SDL_FillRect(state->surface, NULL, bg_colour);

  SDL_Rect rect;
  // Draw y pattern (horizontal) lines
  for (int i = 0; i < state->y_pattern_len; ++i) {
    for (int j = 0; j < state->x_pattern_len; ++j) {
      if (j % 2 == state->y_pattern[i]) {
        rect.x = j * state->gap;
        rect.y = i * state->gap;
        rect.w = state->gap;
        rect.h = state->line_thickness;
        SDL_FillRect(state->surface, &rect, fg_colour);
      }
    }
  }
  // Draw x pattern (vertical) lines
  for (int i = 0; i < state->x_pattern_len; ++i) {
    for (int j = 0; j < state->y_pattern_len; ++j) {
      if (j % 2 == state->x_pattern[i]) {
        rect.x = i * state->gap;
        rect.y = j * state->gap;
        rect.w = state->line_thickness;
        rect.h = state->gap;
        SDL_FillRect(state->surface, &rect, fg_colour);
      }
    }
  }
  // Join up the lines to avoid leaving holes at the intersections
  // To understand how this works, try commenting it out and see the output
  for (int x = state->gap; x < state->output_width; x += state->gap) {
    for (int y = state->gap; y < state->output_height; y += state->gap) {
      rect.x = x;
      rect.y = y;
      rect.w = state->line_thickness;
      rect.h = state->line_thickness;
      SDL_FillRect(state->surface, &rect, fg_colour);
    }
  }

  SDL_UnlockSurface(state->surface);
  return Hitomezashi_Draw_Result_Success;
}
