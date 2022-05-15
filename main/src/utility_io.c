#include "utility_io.h"

#include <stdlib.h>

void write_break()
{
	write_str("\n");
}

void write_str(const char *str)
{
	write(1, str, ft_strlen(str));
}

void write_str_unterminated(const char *str, size_t length)
{
	write(1, str, length);
}

void write_bool(t_bool value)
{
	if (value)
		write(1, "true", 4);
	else
		write(1, "false", 5);
}

void write_int(int value)
{
	char buffer[I_BUFFER_LEN];
	ft_bzero(buffer, I_BUFFER_LEN);

	size_t buffer_i = I_BUFFER_LEN;

	do
	{
		unsigned char digit = (unsigned char) (value % 10);

		buffer[--buffer_i] = '0' + digit;
		value = value / 10;
	} while (value > 0);

	write(1, buffer + buffer_i, I_BUFFER_LEN - buffer_i);
}

void write_ulong(unsigned long value, unsigned char base, t_bool use_prefix)
{
	char buffer[UL_BUFFER_LEN];
	ft_bzero(buffer, UL_BUFFER_LEN);

	size_t buffer_i = UL_BUFFER_LEN;

	do
	{
		unsigned char digit = (unsigned char)(value % base);

		buffer[--buffer_i] = digit < 10 ? ('0' + digit) : ('A' + digit - 10);
		value = value / base;
	}
	while (value > 0);

	if (use_prefix && base == 16)
	{
		buffer[--buffer_i] = 'x';
		buffer[--buffer_i] = '0';
	}

	write(1, buffer + buffer_i, UL_BUFFER_LEN - buffer_i);
}

void write_ptr(const void *ptr)
{
	write_ulong((size_t) ptr, 16, true);
}

char char_if_visible(char value)
{
	if (value < 0x20 || value > 0x7e)
		return '.';
	else
		return value;
}

void hex_dump(const void *ptr, size_t length)
{
	const char *char_ptr = ptr;

	for (size_t line_i = 0; line_i * 16 < length; line_i++)
	{
		write_ptr(char_ptr + line_i * 16);
		write_str(" ");

		char buffer[69];
		unsigned int buffer_i = 0;

		for (int byte_i = 0; byte_i < 16; byte_i++)
		{
			if (line_i * 16 + byte_i < length)
			{
				// Hard coded cast to base 16
				buffer[buffer_i++] = '0' + char_ptr[line_i * 16 + byte_i] % 16;
				buffer[buffer_i++] = '0' + char_ptr[line_i * 16 + byte_i] / 16;
			}
			else
			{
				buffer[buffer_i++] = ' ';
				buffer[buffer_i++] = ' ';
			}

			buffer[buffer_i++] = ' ';

			if ((byte_i + 1) % 8 == 0) // TODO Is space correct?
				buffer[buffer_i++] = ' ';
		}

		buffer[buffer_i++] = '|';
		for (int byte_i = 0; byte_i < 16; byte_i++)
		{
			if (line_i * 16 + byte_i < length)
				buffer[buffer_i++] = char_if_visible(char_ptr[line_i * 16 + byte_i]);
			else
				buffer[buffer_i++] = ' ';
		}
		buffer[buffer_i++] = '|';
		buffer[buffer_i] = '\0';

		write_str(buffer);
		write_break();
	}
}