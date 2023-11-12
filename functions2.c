#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * printPointer - Prints the value of a pointer variable
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int printPointer(va_list argList, char outputBuffer[],
	int flags, int width, int precision, int size)
{
	char extraChar = 0, paddingChar = ' ';
	int index = BUFF_SIZE - 2, length = 2, paddingStart = 1; /* length=2, for '0x' */
	unsigned long address;
	char hexMap[] = "0123456789abcdef";
	void *pointerAddress = va_arg(argList, void *);

	UNUSED(width);
	UNUSED(size);

	if (pointerAddress == NULL)
		return (write(1, "(nil)", 5));

	outputBuffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	address = (unsigned long)pointerAddress;

	while (address > 0)
	{
		outputBuffer[index--] = hexMap[address % 16];
		address /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddingChar = '0';
	if (flags & F_PLUS)
		extraChar = '+', length++;
	else if (flags & F_SPACE)
		extraChar = ' ', length++;

	index++;

	return (writePointer(outputBuffer, index, length,
		width, flags, paddingChar, extraChar, paddingStart));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * printNonPrintable - Prints ASCII codes in hexadecimal of non-printable characters
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int printNonPrintable(va_list argList, char outputBuffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(argList, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (isPrintable(str[i]))
			outputBuffer[i + offset] = str[i];
		else
			offset += appendHexCode(str[i], outputBuffer, i + offset);

		i++;
	}

	outputBuffer[i + offset] = '\0';

	return (write(1, outputBuffer, i + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * printReverse - Prints reverse string.
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int printReverse(va_list argList, char outputBuffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(outputBuffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(argList, char *);

	if (str == NULL)
	{
		UNUSED(precision);
		str = ")Null(";
	}

	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];
		write(1, &z, 1);
		count++;
	}
	return (count);
}

/************************* PRINT A STRING IN ROT13 *************************/
/**
 * printRot13String - Print a string in ROT13.
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int printRot13String(va_list argList, char outputBuffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(argList, char *);

	UNUSED(outputBuffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
