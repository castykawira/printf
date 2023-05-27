#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints a pointer address to a buffer
 * @types: The va_list containing the pointer argument
 * @buffer: The character buffer to store the printed pointer address
 * @flags: Formatting flags for the pointer address
 * @width: Width specifier for the pointer address
 * @precision: Precision specifier for the pointer address
 * @size: Size specifier for the pointer address
 * Return: Number of characters printed, or -1 if an error occurs
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addr;
	char map_to[] = "0123456789abcdef";
	void *addr = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addr == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addr = (unsigned long)addr;

	while (num_addr > 0)
	{
		buffer[ind--] = map_to[num_addr % 16];
		num_addr /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints non-printable characters to a buffer
 * @types: The va_list containing the argument to print
 * @buffer: The character buffer to store the printed non-printable characters
 * @flags: Formatting flags for the non-printable characters
 * @width: Width specifier for the non-printable characters
 * @precision: Precision specifier for the non-printable characters
 * @size: Size specifier for the non-printable characters
 * Return: Number of characters printed, or -1 if an error occurs
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int p = 0, offset = 0;
	char *s = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (s == NULL)
		return (write(1, "(null)", 6));

	while (s[p] != '\0')
	{
		if (is_printable(s[p]))
			buffer[p + offset] = s[p];
		else
			offset += append_hexa_code(s[p], buffer, p + offset);

		p++;
	}

	buffer[p + offset] = '\0';

	return (write(1, buffer, p + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints a reversed string to a buffer
 * @types: The va_list containing the argument to print
 * @buffer: The character buffer to store the reversed string
 * @flags: Formatting flags for the reversed string
 * @width: Width specifier for the reversed string
 * @precision: Precision specifier for the reversed string
 * @size: Size specifier for the reversed string
 * Return: Number of characters printed, or -1 if an error occurs
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *s;
	int p, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	s = va_arg(types, char *);

	if (s == NULL)
	{
		UNUSED(precision);

		s = ")Null(";
	}
	for (p = 0; s[p]; p++)
		;

	for (p = p - 1; p >= 0; p--)
	{
		char z = s[p];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a ROT13-encoded string to a buffer
 * @types: The va_list containing the argument to print
 * @buffer: The character buffer to store the ROT13-encoded string
 * @flags: Formatting flags for the ROT13-encoded string
 * @width: Width specifier for the ROT13-encoded string
 * @precision: Precision specifier for the ROT13-encoded string
 * @size: Size specifier for the ROT13-encoded string
 * Return: Number of characters printed, or -1 if an error occurs
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c;
	char *s;
	unsigned int m, n;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	s = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (s == NULL)
		s = "(AHYY)";
	for (m = 0; s[m]; m++)
	{
		for (n = 0; in[n]; n++)
		{
			if (in[n] == s[m])
			{
				c = out[n];
				write(1, &c, 1);
				count++;
				break;
			}
		}
		if (!in[n])
		{
			c = s[m];
			write(1, &c, 1);
			count++;
		}
	}
	return (count);
}
