#include "main.h"

/**
 * printHandler - Prints an argument based on its type
 * @formatString: Formatted string containing arguments.
 * @index: Index tracking the current position in the format string.
 * @argList: List of arguments to be printed.
 * @outputBuffer: Buffer array for output.
 * @flags: Active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 * 
 * Returns: Number of characters printed or -1 if unknown specifier.
 */
int printHandler(const char *formatString, int *index, va_list argList, char outputBuffer[],
	int flags, int width, int precision, int size)
{
	int i, unknownLength = 0, printedChars = -1;

	struct FormatType {
		char fmt;
		int (*fn)(va_list, char[], int, int, int, int);
	};

	struct FormatType formatTypes[] = {
		{'c', printChar}, {'s', printString}, {'%', printPercent},
		{'i', printInt}, {'d', printInt}, {'b', printBinary},
		{'u', printUnsigned}, {'o', printOctal}, {'x', printHexadecimal},
		{'X', printHexUpper}, {'p', printPointer}, {'S', printNonPrintable},
		{'r', printReverse}, {'R', printRot13String}, {'\0', NULL}
	};

	for (i = 0; formatTypes[i].fmt != '\0'; i++)
		if (formatString[*index] == formatTypes[i].fmt)
			return (formatTypes[i].fn(argList, outputBuffer, flags, width, precision, size));

	if (formatTypes[i].fmt == '\0')
	{
		if (formatString[*index] == '\0')
			return (-1);

		unknownLength += write(1, "%%", 1);

		if (formatString[*index - 1] == ' ')
			unknownLength += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (formatString[*index] != ' ' && formatString[*index] != '%')
				--(*index);

			if (formatString[*index] == ' ')
				--(*index);

			return (1);
		}

		unknownLength += write(1, &formatString[*index], 1);
		return (unknownLength);
	}

	return (printedChars);
}
