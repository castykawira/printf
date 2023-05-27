#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Print a single character to a buffer
 * @types: The va_list containing the character argument
 * @buffer: The character buffer to store the printed character
 * @flags: Formatting flags for the character
 * @width: Width specifier for the character
 * @precision: Precision specifier for the character
 * @size: Size specifier for the character
 * Return: Number of characters printed, or -1 if an error occurs
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string to a buffer
 * @types: The va_list containing the string argument
 * @buffer: The character buffer to store the printed string
 * @flags: Formatting flags for the string
 * @width: Width specifier for the string
 * @precision: Precision specifier for the string
 * @size: Size specifier for the string
 * Return: Number of characters printed, or -1 if an error occurs
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, a;
	char *s = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (s == NULL)
	{
		s = "(null)";
		if (precision >= 6)
			s = "      ";
	}

	while (s[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &s[0], length);
			for (a = width - length; a > 0; a--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (a = width - length; a > 0; a--)
				write(1, " ", 1);
			write(1, &s[0], length);
			return (width);
		}
	}

	return (write(1, s, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent symbol to a buffer
 * @types: The va_list containing the percent symbol argument (unused)
 * @buffer: The character buffer to store the printed percent symbol
 * @flags: Formatting flags for the percent symbol (unused)
 * @width: Width specifier for the percent symbol (unused)
 * @precision: Precision specifier for the percent symbol (unused)
 * @size: Size specifier for the percent symbol (unused)
 * Return: Number of characters printed, -1 if an error occurs
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print an integer to a buffer
 * @types: The va_list containing the integer argument
 * @buffer: The character buffer to store the printed integer
 * @flags: Formatting flags for the integer
 * @width: Width specifier for the integer
 * @precision: Precision specifier for the integer
 * @size: Size specifier for the integer
 * Return: Number of characters printed, or -1 if an error occurs
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[a--] = (num % 10) + '0';
		num /= 10;
	}

	a++;

	return (write_number(is_negative, a, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Print an integer in binary format to a buffer
 * @types: The va_list containing the integer argument
 * @buffer: The character buffer to store the printed binary representation
 * @flags: Formatting flags for the binary representation
 * @width: Width specifier for the binary representation
 * @precision: Precision specifier for the binary representation
 * @size: Size specifier for the binary representation
 * Return: Number of characters printed,or -1 if an error occurs
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, r, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	r = 2147483648; /* (2 ^ 31) */
	a[0] = n / r;
	for (i = 1; i < 32; i++)
	{
		r /= 2;
		a[i] = (n / r) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
