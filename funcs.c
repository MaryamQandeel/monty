#include "monty.h"

/**
 * ofile - opens a file
 * @file_name: the file namepath
 * Return: void
 */

void ofile(char *file_name)
{
	FILE *fd = fopen(file_name, "r");

	if (file_name == NULL || fd == NULL)
		_err(2, file_name);

	rfile(fd);
	fclose(fd);
}


/**
 * rfile - reads a file
 * @fd: pointer to file descriptor
 * Return: void
 */

void rfile(FILE *fd)
{
	int l_num, format = 0;
	char *buff = NULL;
	size_t len = 0;

	for (l_num = 1; getline(&buff, &len, fd) != -1; l_num++)
	{
		format = parse_l(buff, l_num, format);
	}
	free(buff);
}


/**
 * parse_l - Separates each line into tokens to determine
 * which function to call
 * @buff: line from the file
 * @line_num: line number
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */

int parse_l(char *buff, int line_num, int format)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (buff == NULL)
		_err(4);

	opcode = strtok(buff, delim);
	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	find_func(opcode, value, line_num, format);
	return (format);
}

/**
 * find_func - find the appropriate function for the opcode
 * @opcode: opcode
 * @value: argument of opcode
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * @ln: line number
 * if 1 nodes will be entered as a queue.
 * Return: void
 */
void find_func(char *opcode, char *value, int ln, int format)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", add_stack},
		{"pall", p_stack},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", _swap},
		{"add", _add},
		{"sub", _sub},
		{"div", _div},
		{"mul", _mul},
		{"mod", _mod},
		{"pchar", print_c},
		{"pstr", print_s},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			call_fun(func_list[i].f, opcode, value, ln, format);
			flag = 0;
		}
	}
	if (flag == 1)
		err(3, ln, opcode);
}


/**
 * call_fun - Calls the required function.
 * @func: Pointer to the function that is about to be called.
 * @op: string representing the opcode.
 * @v: string representing a numeric value.
 * @ln: line numeber for the instruction.
 * @format: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 */
void call_fun(op_func func, char *op, char *v, int ln, int format)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (v != NULL && v[0] == '-')
		{
			v = v + 1;
			flag = -1;
		}
		if (v == NULL)
			err(5, ln);
		for (i = 0; v[i] != '\0'; i++)
		{
			if (isdigit(v[i]) == 0)
				err(5, ln);
		}
		node = create_node(atoi(v) * flag);
		if (format == 0)
			func(&node, ln);
		if (format == 1)
			add_to_queue(&node, ln);
	}
	else
		func(&head, ln);
}
