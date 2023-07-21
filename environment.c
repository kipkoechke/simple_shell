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
/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Description: This function initializes a new environment variable or
 *              modifies an existing one with the provided name and value.
 *              The function expects two arguments: the variable name and
 *              its value. If the variable name already exists, its value
 *              will be updated.
 *
 * Return: Always 0.
 */
int _mysetenv(info_t *info)
{
	/* Check if the number of arguments is correct */
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	/** Call the _setenv function to initialize
	 * or modify the environment variable */
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}
