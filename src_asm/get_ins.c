/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adompe <adompe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 15:09:34 by adompe            #+#    #+#             */
/*   Updated: 2016/11/16 14:28:02 by qmoreaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool	ft_check_opcode(t_ins *new_ins, char **tab, t_op op_tab[17])
{
	int i;

	i = 0;
	while (i < 16 && *tab)
	{
		if (ft_strcmp(op_tab[i].name, *tab) == 0
		&& ft_strlen(*tab) == ft_strlen(op_tab[i].name))
		{
			tab++;
			new_ins->opcode = op_tab[i].opcode;
			ft_get_ins_param(new_ins, tab);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

t_bool	ft_get_label_ins(t_ins *ins, char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_valid_label_char(str[i], LABEL_CHARS))
		i++;
	if (str[i] == LABEL_CHAR && i == ft_strlen(str) - 1)
	{
		ins->label = ft_strdup(str);
		ins->label[i] = '\0';
		return (TRUE);
	}
	return (FALSE);
}

char	**ft_split_line(char *line)
{
	char	**tab;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
	tab = ft_strsplit(line, ' ');
	return (tab);
}

t_bool	ft_get_ins_line(t_ins *ins, char *line, t_op op_tab[17])
{
	char	**tab;
	int i;

	i = 0;
	tab = ft_split_line(line);
	while (tab[i])
	{
		ft_get_label_ins(ins, tab[i]);
		ft_check_opcode(ins, tab + i, op_tab);
		i++;
	}
	return (TRUE);
}
