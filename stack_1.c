#include "monty.h"


/**
 * add_stack - Adds a node to the stack.
 * @n_node: Pointer to the new node.
 * @l_num: Interger representing the line number of of the opcode.
 */
void add_stack(stack_t **n_node, __attribute__((unused))unsigned int l_num)
{
	stack_t *tmp;

	if (n_node == NULL || *n_node == NULL)
		exit(EXIT_FAILURE);
	if (head == NULL)
	{
		head = *n_node;
		return;
	}
	tmp = head;
	head = *n_node;
	head->next = tmp;
	tmp->prev = head;
}


/**
 * p_stack - Adds a node to the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @l_num: line number of  the opcode.
 */
void p_stack(stack_t **stack, unsigned int l_num)
{
	stack_t *tmp;

	(void) l_num;
	if (stack == NULL)
		exit(EXIT_FAILURE);
	tmp = *stack;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}

/**
 * pop_top - Adds a node to the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @l_num: Interger representing the line number of of the opcode.
 */
void pop_top(stack_t **stack, unsigned int l_num)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL)
		more_err(7, l_num);

	tmp = *stack;
	*stack = tmp->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(tmp);
}

/**
 * print_top - Prints the top node of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @l_num: Interger representing the line number of of the opcode.
 */
void print_top(stack_t **stack, unsigned int l_num)
{
	if (stack == NULL || *stack == NULL)
		more_err(6, l_num);
	printf("%d\n", (*stack)->n);
}
