#include "shell.h"

/**
 * my_env - Prints the current environment.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */
int my_env(info_t *info)
{
	/** Call the print_list_str function
	 * to print the environment linked list */
	print_list_str(info->env);

	return (0);
}
