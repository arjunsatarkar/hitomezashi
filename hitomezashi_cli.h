#ifndef HITOMEZASHI_CLI_H
#define HITOMEZASHI_CLI_H

#include <stddef.h>

enum Hitomezashi_Cli_Exit_Code {
  Hitomezashi_Cli_Exit_Code_Success = 0,
  Hitomezashi_Cli_Exit_Code_Err_Handle_Args = 1,
  Hitomezashi_Cli_Exit_Code_Err_Print_Help = 2,
  Hitomezashi_Cli_Exit_Code_Err_Sdl_Init = 3,
  Hitomezashi_Cli_Exit_Code_Err_State_Init = 4,
  Hitomezashi_Cli_Exit_Code_Err_Save_Image = 5,
};

void hitomezashi_cli_handle_args(char **out_file_path, int *x_pattern_len,
                                 int *y_pattern_len, char **x_pattern,
                                 char **y_pattern, int *gap, int *thickness,
                                 int argc, char **argv);
void hitomezashi_cli_help(void);
char *hitomezashi_cli_ascii_binary_str_to_ints(char *ascii_str, size_t n);

#endif // HITOMEZASHI_CLI_H
