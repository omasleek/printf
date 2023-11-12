#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * Prints an unsigned number
 * @args: List of arguments
 * @buff: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int printUnsigned(va_list args, char buff[], int flags, int width, int precision, int size) {
    int index = BUFF_SIZE - 2;
    unsigned long int num = va_arg(args, unsigned long int);

    num = convertSizeUnsigned(num, size);

    if (num == 0)
        buff[index--] = '0';

    buff[BUFF_SIZE - 1] = '\0';

    while (num > 0) {
        buff[index--] = (num % 10) + '0';
        num /= 10;
    }

    index++;

    return writeUnsigned(0, index, buff, flags, width, precision, size);
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * Prints an unsigned number in octal notation
 * @args: List of arguments
 * @buff: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int printOctal(va_list args, char buff[], int flags, int width, int precision, int size) {
    int index = BUFF_SIZE - 2;
    unsigned long int num = va_arg(args, unsigned long int);
    unsigned long int initNum = num;

    UNUSED(width);

    num = convertSizeUnsigned(num, size);

    if (num == 0)
        buff[index--] = '0';

    buff[BUFF_SIZE - 1] = '\0';

    while (num > 0) {
        buff[index--] = (num % 8) + '0';
        num /= 8;
    }

    if (flags & F_HASH && initNum != 0)
        buff[index--] = '0';

    index++;

    return writeUnsigned(0, index, buff, flags, width, precision, size);
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * Prints an unsigned number in hexadecimal notation
 * @args: List of arguments
 * @buff: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int printHexadecimal(va_list args, char buff[], int flags, int width, int precision, int size) {
    return printHex(args, "0123456789abcdef", buff, flags, 'x', width, precision, size);
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * Prints an unsigned number in upper hexadecimal notation
 * @args: List of arguments
 * @buff: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int printHexUpper(va_list args, char buff[], int flags, int width, int precision, int size) {
    return printHex(args, "0123456789ABCDEF", buff, flags, 'X', width, precision, size);
}

/************** PRINT HEX NUMBER IN LOWER OR UPPER **************/
/**
 * Prints a hexadecimal number in lower or upper case
 * @args: List of arguments
 * @mapTo: Array of values to map the number to
 * @buff: Buffer array for printing
 * @flags: Active flags
 * @flagChar: Flag character
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int printHex(va_list args, char mapTo[], char buff[], int flags, char flagChar, int width, int precision, int size) {
    int index = BUFF_SIZE - 2;
    unsigned long int num = va_arg(args, unsigned long int);
    unsigned long int initNum = num;

    UNUSED(width);

    num = convertSizeUnsigned(num, size);
    if (num == 0)
        buff[index--] = '0';

   buff[BUFF_SIZE - 1] = '\0';

    while (num > 0) {
        buff[index--] = mapTo[num % 16];
	um /= 16;
}
    if (flags & F_HASH && initNum != 0) {
	 buff[index--] = flagChar;
       buff[index--] = '0';
   }

   index++;

   return writeUnsigned(0, index, buff, flags, width, precision, size);
}
