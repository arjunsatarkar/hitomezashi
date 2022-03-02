#include "hitomezashi_web.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "SDL2/SDL.h"
#include "emscripten.h"
#include "hitomezashi.h"
#include "hitomezashi_utils.h"

int EMSCRIPTEN_KEEPALIVE main(void) {
  char *param_str = hitomezashi_web_get_args();

  if (param_str[0] == 'i') {
    return Hitomezashi_Web_Result_Err_Get_Params;
  }

  char *x_pattern_str = strtok(param_str, "\n");
  int x_pattern_len = strlen(x_pattern_str);
  // We needn't bother checking whether
  // hitomezashi_ascii_binary_str_to_ints() was successful as the strings
  // passed to it are validated by hitomezashi_web_get_args() in JS.
  char *x_pattern =
      hitomezashi_ascii_binary_str_to_ints(x_pattern_str, x_pattern_len);

  char *y_pattern_str = strtok(NULL, "\n");
  int y_pattern_len = strlen(y_pattern_str);
  char *y_pattern =
      hitomezashi_ascii_binary_str_to_ints(y_pattern_str, y_pattern_len);

  int gap = strtol(strtok(NULL, "\n"), NULL, 0);
  int line_thickness = strtol(strtok(NULL, "\n"), NULL, 0);

  Uint32 fg_colour = strtol(strtok(NULL, "\n"), NULL, 0);
  Uint32 bg_colour = strtol(strtok(NULL, "\n"), NULL, 0);

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    return Hitomezashi_Web_Result_Err_Sdl_Init;
  }

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;

  struct Hitomezashi_State state;
  if (hitomezashi_state_init(&state, x_pattern_len, y_pattern_len, x_pattern,
                             y_pattern, gap, line_thickness, fg_colour,
                             bg_colour) != 0) {
    return Hitomezashi_Web_Result_Err_State_Init;
  }

  // Stop SDL from capturing all input and stopping input elements from working
  SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#canvas");
  SDL_CreateWindowAndRenderer(state.output_width, state.output_height, 0,
                              &window, &renderer);

  hitomezashi_draw(&state);

  texture = SDL_CreateTextureFromSurface(renderer, state.surface);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);

  // Since this is a short-lived application which is only run on page load,
  // we do not need to delay the exit of main by freeing memory - it will be
  // reclaimed by the browser automatically.

  return Hitomezashi_Web_Result_Success;
}

EM_JS(char *, hitomezashi_web_get_args, (void), {
  function validate_pattern(pattern) {
    let valid = true;
    for (let c of pattern) {
      if (c != "0" && c != "1") {
        valid = false;
        break;
      }
    }
    return valid;
  }

  let result_js = "";

  let search_params = new URLSearchParams(window.location.search);

  const x_pattern = search_params.get("x_pattern");
  const y_pattern = search_params.get("y_pattern");
  const gap = search_params.get("gap");
  const line_thickness = search_params.get("line_thickness");
  let fg_colour = search_params.get("fg_colour");
  let bg_colour = search_params.get("bg_colour");
  if (!fg_colour) {
    fg_colour = "#000000";
  }
  if (!bg_colour) {
    bg_colour = "#FFFFFF";
  }
  fg_colour = "0x" + fg_colour.slice(1);
  bg_colour = "0x" + bg_colour.slice(1);

  if (!(x_pattern && y_pattern && gap && line_thickness)) {
    result_js = "i";
  } else {
    const patterns_are_valid =
        validate_pattern(x_pattern) && validate_pattern(y_pattern);
    if (!patterns_are_valid) {
      result_js = "i";
    } else {
      result_js = x_pattern + "\n" + y_pattern + "\n" + gap + "\n" +
                  line_thickness + "\n" + fg_colour + "\n" + bg_colour + "\n";
    }
  }

  const result_length_bytes = lengthBytesUTF8(result_js) + 1;
  let result_wasm_heap = _malloc(result_length_bytes);
  stringToUTF8(result_js, result_wasm_heap, result_length_bytes);
  return result_wasm_heap;
})
