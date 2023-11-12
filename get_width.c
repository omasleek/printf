#include "main.h"

/**
 * calculateWidth - Calculates the width for printing
 * @formatString: Formatted string containing arguments.
 * @currentIndex: Current index tracking the position in the format string.
 * @argList: List of arguments.
 *
 * Returns: Calculated width.
 */
int calculateWidth(const char *formatString, int *currentIndex, va_list argList)
{
	int currentIdx;
	int width = 0;

	for (currentIdx = *currentIndex + 1; formatString[currentIdx] != '\0'; currentIdx++)
	{
		if (isDigit(formatString[currentIdx]))
		{
			width *= 10;
			width += formatString[currentIdx] - '0';
		}
		else if (formatString[currentIdx] == '*')
		{
			currentIdx++;
			width = va_arg(argList, int);
			break;
		}
		else
			break;
	}

	*currentIndex = currentIdx - 1;

	return width;
}
