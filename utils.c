#include "main.h"

/**
 * is_printable - checks if a character is printable
 * @c: Character to be checked
 * Return: 1 if the character is printable, 0 otherwise
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Appends the hexadecimal representation of an
 * ASCII code to a buffer at the specified index
 * @buffer: The buffer to which the hexadecimal code will be appended
 * @i: The index in the buffer where the hexadecimal code should be added
 * @ascii_code: The ASCII code to be converted to hexadecimal
 * Return: The updated index in the buffer after appending the hexadecimal code
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Checks if a character is a digit
 * @c: The character to be checked
 * Return: 1 if the character is a digit, 0 otherwise
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Converts a number to a different size representation
 * @num: Number to be converted
 * @size: The desired size representation
 * Return: The converted number with the specified size
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Converts an unsigned number to
 * a different size representation
 * @num: The unsigned number to be converted
 * @size: The desired size representation
 * Return: The converted number with the specified size
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
