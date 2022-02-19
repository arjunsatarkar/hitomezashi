/** @file */
#ifndef HITOMEZASHI_CLI_H
#define HITOMEZASHI_CLI_H

#include <stddef.h>

/** Exit codes for main().
 */
enum Hitomezashi_Cli_Exit_Code {
  /** The program completed successfully. */
  Hitomezashi_Cli_Exit_Code_Success = 0,
  /** The arguments were invalid or the program could not handle them. */
  Hitomezashi_Cli_Exit_Code_Err_Handle_Args = 1,
  /** Printing the help text failed. */
  Hitomezashi_Cli_Exit_Code_Err_Print_Help = 2,
  /** Initialising SDL failed. */
  Hitomezashi_Cli_Exit_Code_Err_Sdl_Init = 3,
  /** hitomezashi_state_init() from libhitomezashi failed. */
  Hitomezashi_Cli_Exit_Code_Err_State_Init = 4,
  /** Saving the SDL_Surface on which the pattern was drawn as an image failed.
   */
  Hitomezashi_Cli_Exit_Code_Err_Save_Image = 5,
};

/** Read and parse arguments, ensure they are valid, and give back the
 * information in usable form to the caller. Also calls hitomezashi_cli_help()
 * if -h is passed.
 * Note that *x_pattern and *y_pattern are dynamically allocated and should be
 * freed by the caller when no longer needed.
 */
void hitomezashi_cli_handle_args(char **out_file_path, int *x_pattern_len,
                                 int *y_pattern_len, char **x_pattern,
                                 char **y_pattern, int *gap, int *thickness,
                                 int argc, char **argv);
/** Print the help text and exit.
 * Exits with Hitomezashi_Cli_Exit_Code_Success (0) on success, and
 * Hitomezashi_Cli_Exit_Code_Print_Help (2) on failure.
 */
void hitomezashi_cli_help(void);
/** Convert a string composed of ASCII 0 and 1 digits, eg\. "01010", to an array
 * of numeric 0s and 1s stored as char. */
char *hitomezashi_cli_ascii_binary_str_to_ints(char *ascii_str, size_t n);

#endif // HITOMEZASHI_CLI_H
