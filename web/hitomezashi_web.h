/** @file */
#ifndef HITOMEZASHI_WEB_H
#define HITOMEZASHI_WEB_H

#include "emscripten.h"

enum Hitomezashi_Web_Result {
  Hitomezashi_Web_Result_Success = 0,
  Hitomezashi_Web_Result_Err_Get_Params = 1,
  Hitomezashi_Web_Result_Err_Sdl_Init = 2,
  Hitomezashi_Web_Result_Err_State_Init = 3,
};

int hitomezashi_web(int x_pattern_len, int y_pattern_len, char *x_pattern,
                    char *y_pattern, int gap, int line_thickness);

/** Parse the URL query string and return the parameters thereof.
 *
 * This is implemented in JS with EM_JS, in order to access the query string.
 * The friction of interoperation is the reason for turning the query string
 * into a different string that the C code must parse to the actual values,
 * rather than sending the data back individually with the correct types.
 * That is probably possible, but it seems unpleasant.
 *
 * The query string's x_pattern, y_pattern, gap, and line_thickness are
 * parsed. If not all of them are present, "i" is returned. If x_pattern or
 * y_pattern in the query string have characters other than ASCII digits 0
 * and 1, "i" is returned. Otherwise, the values are returned as a
 * newline-delimited string in the order x_pattern, y_pattern, gap,
 * line_thickness.
 */
char *hitomezashi_web_get_args(void);

#endif // HITOMEZASHI_WEB_H
