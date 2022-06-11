#include "hitomezashi_web.h"
#include "SDL2/SDL.h"
#include "emscripten.h"
#include "hitomezashi.h"
#include "hitomezashi_utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

SDL_Window *window;

int EMSCRIPTEN_KEEPALIVE main(void) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    return EXIT_FAILURE;

  // Stop SDL from capturing all input and stopping input elements from working
  SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#canvas");

  if (!(window = SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_RESIZABLE)))
    return EXIT_FAILURE;

  emscripten_set_main_loop(main_loop, -1, true);

  return EXIT_SUCCESS;
}

void EMSCRIPTEN_KEEPALIVE main_loop(void) {
  const char *x_pattern_raw = hitomezashi_web_get_x_pattern();
  const char *y_pattern_raw = hitomezashi_web_get_y_pattern();
  const int x_pattern_len = strlen(x_pattern_raw);
  const int y_pattern_len = strlen(y_pattern_raw);
  const char *x_pattern =
      hitomezashi_ascii_binary_str_to_ints(x_pattern_raw, x_pattern_len);
  const char *y_pattern =
      hitomezashi_ascii_binary_str_to_ints(y_pattern_raw, y_pattern_len);

  const int gap = hitomezashi_web_get_gap();
  const int line_thickness = hitomezashi_web_get_line_thickness();

  const Uint32 fg_colour = hitomezashi_web_get_fg_colour();
  const Uint32 bg_colour = hitomezashi_web_get_bg_colour();

  // If any of these are 0, input was invalid
  if (!(x_pattern_len && y_pattern_len && gap && line_thickness))
    return;

  struct Hitomezashi_State state;
  hitomezashi_state_init(&state, x_pattern_len, y_pattern_len, x_pattern,
                         y_pattern, gap, line_thickness, fg_colour, bg_colour);
  SDL_SetWindowSize(window, state.output_width, state.output_height);
  hitomezashi_draw(&state);

  SDL_BlitSurface(state.surface, NULL, SDL_GetWindowSurface(window), NULL);
  SDL_UpdateWindowSurface(window);

  free((char *)x_pattern_raw);
  free((char *)y_pattern_raw);
  free((char *)x_pattern);
  free((char *)y_pattern);
  SDL_FreeSurface(state.surface);
}

EM_JS(char *, hitomezashi_web_get_x_pattern, (void), {
  let result_js = document.querySelector("input[name=\"x_pattern\"]").value;
  for (let c of result_js) {
    if (c != "0" && c != "1") {
      result_js = "";
      break;
    }
  }
  const result_length_bytes = lengthBytesUTF8(result_js) + 1;
  let result_wasm_heap = _malloc(result_length_bytes);
  stringToUTF8(result_js, result_wasm_heap, result_length_bytes);
  return result_wasm_heap;
})

EM_JS(char *, hitomezashi_web_get_y_pattern, (void), {
  let result_js = document.querySelector("input[name=\"y_pattern\"]").value;
  for (let c of result_js) {
    if (c != "0" && c != "1") {
      result_js = "";
      break;
    }
  }
  const result_length_bytes = lengthBytesUTF8(result_js) + 1;
  let result_wasm_heap = _malloc(result_length_bytes);
  stringToUTF8(result_js, result_wasm_heap, result_length_bytes);
  return result_wasm_heap;
})

EM_JS(unsigned int, hitomezashi_web_get_gap, (void), {
  const result = +document.querySelector("input[name=\"gap\"").value;
  return (result > 0 ? result : 0);
})

EM_JS(unsigned int, hitomezashi_web_get_line_thickness, (void), {
  const result = +document.querySelector("input[name=\"line_thickness\"").value;
  return (result > 0 ? result : 0);
})

EM_JS(Uint32, hitomezashi_web_get_fg_colour, (void), {
  const result = parseInt(
      document.querySelector("input[name=\"fg_colour\"]").value.slice(1), 16);
  return (result ? result : 0);
})

EM_JS(Uint32, hitomezashi_web_get_bg_colour, (void), {
  const result = parseInt(
      document.querySelector("input[name=\"bg_colour\"]").value.slice(1), 16);
  return (result ? result : 0);
})
