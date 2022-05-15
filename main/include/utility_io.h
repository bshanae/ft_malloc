#ifndef UTILITY_IO
#define UTILITY_IO

#include "libft_standart.h"

#define I_BUFFER_LEN 64
#define UL_BUFFER_LEN 64

void write_break();
void write_str(const char *str);
void write_str_unterminated(const char *str, size_t length);
void write_bool(t_bool value);
void write_int(int value);
void write_ulong(unsigned long value, unsigned char base, t_bool use_prefix);
void write_ptr(const void *ptr);

void hex_dump(const void *ptr, size_t length);

#endif