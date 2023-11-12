#include "main.h"
/**
 * prints a character.
 */
int print_char(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	return handle_write_char(va_arg(types, int) buffer, flags, width, precision, size);
}
/**
 * prints a string.
 */
int prints_string(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	char *str = va_arg(types, char*);
	if (!str) str = (precision >= 6) ? " ":"(null)";
int length = (precision >=0) ? precision : strlen(str);
	if (width > length)
{
	if (flags & F_MINUS) printf("%.*s%*s", length, str, width - length, "");
	else printf("%*s%.*s", width - length, "", length, str);
	return width;
}
/**
 * prints a percent sign.
 */
int print_percent(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return write(1, "%%", 1);
}

/**
 * prints an integer.
 */
int print_percent(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	long int n = convert_size_number(va_arg(types, long int), size);
	char numStr[BUFF_SIZE];
	int isNegative = (n < 0) ? (n = -n, 1) : 0;

	int i = BUFF_SIZE -2;
	do {
		numStr[i--] = (n % 10)+ '0';
		n /= 10;
	}
	while (n > 0);
	return write_number(isNegative, i + 1, numStr, flags, width, precision, size);
}
/**
 * prints a binary representation of an unsigned integer.
 */
int print_binary(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	unsigned int n = va_arg(types, unsigned int);
	int count = 0;
	for (int i = 31; i >= 0; i--)
	{
		char z = '0' + ((n >> i) & 1);
		if (count || i == 0) write(1. &z, 1);
		if (z == '1') count++;
	}
	return count;
}
