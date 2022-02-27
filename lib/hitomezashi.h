/** @file */

#ifndef HITOMEZASHI_HITOMEZASHI_H
#define HITOMEZASHI_HITOMEZASHI_H

#include "SDL2/SDL.h"

/** The state of a hitomezashi pattern.
 */
struct Hitomezashi_State {
  int x_pattern_len;
  int y_pattern_len;

  /** Pattern used to draw the vertical lines conceptually originating from the
   * x axis. This is an array of 0s and 1s.
   */
  char *x_pattern;
  /** Pattern used to draw the horizontal lines conceptually originating from
   * the y axis. This is an array of 0s and 1s.
   */
  char *y_pattern;

  /** Gap between parallel lines. */
  int gap;

  int line_thickness;

  Uint32 fg_colour;
  Uint32 bg_colour;

  /** Width in pixels of the SDL_Surface needed to hold the pattern. This is
   * calculated by hitomezashi_state_init(). */
  int output_width;
  /** Height in pixels of the SDL_Surface needed to hold the pattern. This is
   * calculated by hitomezashi_state_init(). */
  int output_height;

  /** Surface the pattern is drawn to by hitomezashi_draw(). */
  SDL_Surface *surface;
};

enum Hitomezashi_State_Init_Result {
  Hitomezashi_State_Init_Result_Success,
  /** The function failed as it encountered an error initialising the
     SDL_Surface in state. */
  Hitomezashi_State_Init_Result_Err_Create_Surface,
};

enum Hitomezashi_Draw_Result {
  Hitomezashi_Draw_Result_Success,
  /** The function failed as it encountered an error "locking" the surface to
     write to it. */
  Hitomezashi_Draw_Result_Err_Lock_Surface,
};

/** Initialise a Hitomezashi_State struct so that it is ready to be passed to
 * hitomezashi_draw(). */
enum Hitomezashi_State_Init_Result
hitomezashi_state_init(struct Hitomezashi_State *state, int x_pattern_len,
                       int y_pattern_len, char *x_pattern, char *y_pattern,
                       int gap, int line_thickness, Uint32 fg_colour,
                       Uint32 bg_colour);

/** Draw the hitomezashi pattern to state->surface. */
enum Hitomezashi_Draw_Result hitomezashi_draw(struct Hitomezashi_State *state);

#endif // HITOMEZASHI_HITOMEZASHI_H
