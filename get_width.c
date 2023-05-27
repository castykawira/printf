#include "main.h"

/**
 * get_width - Retrieves the width value from the format string
 * @format: The format string containing the width specifier
 * @i:  A pointer to track the current position in the format string
 * @list: The va_list of arguments for variable-length arguments
 * Return: An integer representing the retrieved width value
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr_i;
	int width = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (width);
}
