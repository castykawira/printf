#include "main.h"

/**
 * get_size - Retrieves the size specifier from the format string
 * @format: The format string containing the size specifier
 * @i: A pointer to track the current position in the format string
 * Return: An integer representing the retrieved size specifier
 */
int get_size(const char *format, int *i)
{
	int curr_i = *i + 1;
	int size = 0;

	if (format[curr_i] == 'l')
		size = S_LONG;
	else if (format[curr_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;

	return (size);
}
