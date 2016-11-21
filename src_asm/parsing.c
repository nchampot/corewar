/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adompe <adompe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 20:22:59 by adompe            #+#    #+#             */
/*   Updated: 2016/11/16 13:52:47 by qmoreaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

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

t_ins	*ft_init_new_ins()
{
	t_ins	*new_ins;

	new_ins = (t_ins *)malloc(sizeof(t_ins));
	new_ins->opcode = 0;
	new_ins->param = NULL;
	new_ins->coding_byte = 0;
	new_ins->size = 1;
	new_ins->label = NULL;
	return (new_ins);
}

t_bool	ft_get_instruction(t_asm *data, int fd)
{
	t_ins	*new_ins;
	char	*line;

	new_ins = ft_init_new_ins();
	while (get_next_line(fd, &line))
	{
		ft_get_ins_line(new_ins, line, op_tab);
		if (new_ins->opcode)
		{
			if (data->ins == NULL)
				data->ins = ft_lstnew(new_ins, sizeof(t_ins));
			else
				ft_lstappend(&(data->ins), ft_lstnew(new_ins, sizeof(t_ins)));
			free(new_ins);
			new_ins = ft_init_new_ins();
		}
	}
	return (TRUE);
}

void	ft_get_name_name_desc(t_asm *data, int fd)
{
	char	*line;
	char	**tab;

	get_next_line(fd, &line);
	if (ft_strncmp(line, ".name", 5) != 0)
		return ;
	tab = ft_strsplit(line, '\"');
	if (tab[1] && ft_strlen(tab[1]) <= PROG_NAME_LENGTH)
		ft_strcpy(data->header->prog_name, tab[1]);
	else
	{
		ft_putstr("Invalid name\n");
		return ;
	}
	get_next_line(fd, &line);
	tab = NULL;
	tab = ft_strsplit(line, '\"');
	if (tab[1] && ft_strlen(tab[1]) <= COMMENT_LENGTH)
		ft_strcpy(data->header->comment, tab[1]);
	else
	{
		ft_putstr("Invalid comment\n");
		return ;
	}
}

void	ft_get_data(int argc, char **argv, t_asm *data)
{
	int		fd;
	char	*line;

	if (!argv[1])
		return ;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return ;
	ft_get_name_name_desc(data, fd);
	ft_get_instruction(data, fd);
}
