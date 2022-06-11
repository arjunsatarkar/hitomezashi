/** @file */
#ifndef HITOMEZASHI_WEB_H
#define HITOMEZASHI_WEB_H

#include "SDL2/SDL.h"
#include "emscripten.h"

void main_loop(void);

char *hitomezashi_web_get_x_pattern(void);
char *hitomezashi_web_get_y_pattern(void);
unsigned int hitomezashi_web_get_gap(void);
unsigned int hitomezashi_web_get_line_thickness(void);
Uint32 hitomezashi_web_get_fg_colour(void);
Uint32 hitomezashi_web_get_bg_colour(void);

#endif // HITOMEZASHI_WEB_H
