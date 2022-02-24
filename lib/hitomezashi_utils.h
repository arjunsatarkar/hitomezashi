/** @file
 * Utilities connected with hitomezashi patterns that may be useful to
 * applications.
 */
#ifndef HITOMEZASHI_UTILS_H
#define HITOMEZASHI_UTILS_H

#include <stddef.h>

/** Convert a string of ASCII digit 0s and 1s, eg. "1010", to a char array of
 * numeric 0s and 1s. The return value is **dynamically allocated and must
 * be freed**.
 * @param len Length of ascii_str, not including any terminating null bytes.
 */
char *hitomezashi_ascii_binary_str_to_ints(char *ascii_str, size_t len);

#endif // HITOMEZASHI_UTILS_H
