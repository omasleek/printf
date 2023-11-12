#include "main.h"

/**
 * calculatePrecision - Determines the precision for printing
 * @formatString: Formatted string containing arguments
 * @currentIndex: Current index tracking the position in the format string
 * @argList: List of arguments
 *
 * Returns: Precision specifier.
 */
int calculatePrecision(const char *formatString, int *currentIndex, va_list argList)
{
	int currentIdx = *currentIndex + 1;
	int precision = -1;

	if (formatString[currentIdx] != '.')
		return precision;

	precision = 0;

	for (currentIdx += 1; formatString[currentIdx] != '\0'; currentIdx++)
	{
		if (isDigit(formatString[currentIdx]))
		{
			precision *= 10;
			precision += formatString[currentIdx] - '0';
		}
		else if (formatString[currentIdx] == '*')
		{
			currentIdx++;
			precision = va_arg(argList, int);
			break;
		}
		else
			break;
	}

	*currentIndex = currentIdx - 1;

	return precision;
}
