#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Print an unsigned integer to a buffer
 * @types: The va_list containing the unsigned integer argument
 * @buffer: The character buffer to store the printed unsigned integer
 * @flags: Formatting flags for the unsigned integer
 * @width: Width specifier for the unsigned integer
 * @precision: Precision specifier for the unsigned integer
 * @size: Size specifier for the unsigned integer
 * Return: Number of characters printed, or -1 if an error occurs
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Print an octal number to a buffer
 * @types: The va_list containing the octal number argument
 * @buffer: The character buffer to store the printed octal number
 * @flags: Formatting flags for the octal number
 * @width: Width specifier for the octal number
 * @precision: Precision specifier for the octal number
 * @size: Size specifier for the octal number
 * Return: Number of characters printed, or -1 if an error occurs
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int b = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[b--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[b--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[b--] = '0';

	b++;

	return (write_unsgnd(0, b, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Print a hexadecimal number to a buffer
 * @types: The va_list containing the hexadecimal number argument
 * @buffer: The character buffer to store the printed hexadecimal number
 * @flags: Formatting flags for the hexadecimal number
 * @width: Width specifier for the hexadecimal number
 * @precision: Precision specifier for the hexadecimal number
 * @size: Size specifier for the hexadecimal number
 * Return: Number of characters printed, or -1 if an error occurs
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Print an uppercase hexadecimal number to a buffer
 * @types: The va_list containing the hexadecimal number argument
 * @buffer: The character buffer to store the printed hexadecimal number
 * @flags: Formatting flags for the hexadecimal number
 * @width: Width specifier for the hexadecimal number
 * @precision: Precision specifier for the hexadecimal number
 * @size: Size specifier for the hexadecimal number
 * Return: Number of characters printed, or -1 if an error occurs
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Print a hexadecimal number to a buffer
 * @types: The va_list containing the hexadecimal number argument
 * @map_to: The character map used for the hexadecimal digits
 * @buffer: The character buffer to store the printed hexadecimal number
 * @flags: Formatting flags for the hexadecimal number
 * @flag_ch: Flag character used for formatting
 * @width: Width specifier for the hexadecimal number
 * @precision: Precision specifier for the hexadecimal number
 * @size:Size specifier for the hexadecimal number
 * Return: Number of characters printed, or -1 if an error occurs
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int n = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[n--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[n--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[n--] = flag_ch;
		buffer[n--] = '0';
	}

	n++;

	return (write_unsgnd(0, n, buffer, flags, width, precision, size));
}
