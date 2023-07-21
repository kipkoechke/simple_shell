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

/**
 * _getenv - Gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * 			Used to maintain constant function prototype.
 * @name: Env var name.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	/* Loop through the environment linked list */
	while (node)
	{
		/* Check if the current node's string starts with the given name */
		p = starts_with(node->str, name);

		/** If a match is found,
		 *	return the address of the next character (value) */
		if (p && *p)
			return (p);

		node = node->next;
	}

	/* Return NULL if the environment variable is not found */
	return (NULL);
}
