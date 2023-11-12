#include "main.h"

/**
 * calculateSize - Determines the size for casting the argument
 * @formatString: Formatted string containing arguments
 * @currentIndex: Current index tracking the position in the format string
 *
 * Returns: Size specifier.
 */
int calculateSize(const char *formatString, int *currentIndex)
{
	int currentIdx = *currentIndex + 1;
	int sizeSpecifier = 0;

	if (formatString[currentIdx] == 'l')
		sizeSpecifier = SIZE_LONG;
	else if (formatString[currentIdx] == 'h')
		sizeSpecifier = SIZE_SHORT;

	if (sizeSpecifier == 0)
		*currentIndex = currentIdx - 1;
	else
		*currentIndex = currentIdx;

	return sizeSpecifier;
}
