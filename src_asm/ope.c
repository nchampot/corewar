/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adompe <adompe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 21:45:38 by adompe            #+#    #+#             */
/*   Updated: 2016/10/23 21:45:41 by adompe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_error(char *message)
{
	ft_putstr(message);
	exit(0);
}

t_bool	ft_valid_label_char(char c, char *label_chars)
{
	int i;

	i = 0;
	while (i < ft_strlen(label_chars))
	{
		if (label_chars[i] != c)
			i++;
		else
			return (TRUE);
	}
	return (FALSE);
}

void	debug(t_asm *data)
{
	t_list	*tmp;
	t_ins	*ins;
	int i;

	t_op    op_tab[17] =
	{
		{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
		{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
		{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
		{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
		{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
		{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
			"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
		{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
			"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
		{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
			"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
		{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
		{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
			"load index", 1, 1},
		{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
			"store index", 1, 1},
		{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
		{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
		{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
			"long load index", 1, 1},
		{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
		{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
		{0, 0, {0}, 0, 0, 0, 0, 0}
	};

	tmp = data->ins;
	t_param *p;
	t_list *l;
	i = 0;
	while (tmp)
	{
		ins = tmp->content;
		printf("INS:\tOPCODE:%d - LABEL:%s - CODING:%d - SIZE: %d\n\tPARAM:\n", ins->opcode, ins->label, ins->coding_byte, ins->size);
		l = ins->param;
		while (l)
		{
			p = l->content;
			printf("\t\tTYPE:%d, VALUE:%d, LABEL:%s\n", p->type, p->value, p->label);
			l = l->next;
		}
		i = 0;
		tmp = tmp->next;
	}
}
