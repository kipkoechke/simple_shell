#include "shell.h"
/**
 * interactive_mode - shell in interactive mode
 * @info: the address of the struct
 *
 * Return: returns 1 if shell is interactive mode
 * 	returns 0 if otherwise
 */
int interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <=2);
}
