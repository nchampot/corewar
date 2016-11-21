/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmoreaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:09:01 by qmoreaux          #+#    #+#             */
/*   Updated: 2016/11/17 13:32:59 by qmoreaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ope.h"

int		op_sti(t_env *env, int num_player, unsigned int op_args[4], char codage)
{
	int	value;
	
	if (!is_register(op_args[0], codage, 0))
		return (-1);
	if (is_register(op_args[1], codage, 1))
		value = reg_to_int(env->champion[num_player]->reg[op_args[1]]);
	else if (is_indirect(op_args[1], codage, 1))
		value = ind_to_int(op_args[1], env->champion[num_player]->program_control);
	else if (is_direct(op_args[1], codage, 1))
		value = op_args[1];
	if (is_register(op_args[2], codage, 2))
		value += reg_to_int(env->champion[num_player]->reg[op_args[2]]);
	else if (is_direct(op_args[2], codage, 2))
		value += op_args[2];
	else
		return (-1);
	ft_strncpy(&env->memory[env->champion[num_player]->program_control + (value % IDX_MOD)], env->champion[num_player]->reg[op_args[2]], REG_SIZE * 2);
	return (0);
}
