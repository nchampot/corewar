/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adompe <adompe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:17:34 by adompe            #+#    #+#             */
/*   Updated: 2016/11/16 14:27:49 by qmoreaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_check_param(t_ins *ins, t_op opcode)
{
	t_list	*tmp;
	t_param	*tmp_param;
	int		i;

	i = 0;
	tmp = ins->param;
	if (opcode.coding_byte)
		ins->size++;
	while (tmp)
	{
		tmp_param = tmp->content;
		if (!(tmp_param->type & opcode.param[i]))
			printf("BAD ARGUMENT\n");
		if (opcode.coding_byte)
			ins->coding_byte += (tmp_param->type << (6 - (2*i)));
		if (tmp_param->type == T_REG)
			ins->size++;
		else if (tmp_param->type == T_IND)
			ins->size += 2;
		else if (tmp_param->type == T_DIR)
		{
			if (opcode.two_bytes)
				ins->size += 2;
			else
				ins->size += 4;
		}
		i++;
		tmp = tmp->next;
	}
	if (i != opcode.nb_param)
		printf("BAD ARGUMENT ON %s\n", opcode.full_name);
}
