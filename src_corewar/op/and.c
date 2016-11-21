/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmoreaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:26:05 by qmoreaux          #+#    #+#             */
/*   Updated: 2016/11/17 13:29:53 by qmoreaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ope.h"

int	and(t_env *env, int num_player, unsigned int op_args[4], char codage)
{
	int	value;
	int	value2;

	env->champion[num_player]->carry = 0;
	if (is_register(op_args[0], codage, 0))
		value = reg_to_int(env->champion[num_player]->reg[op_args[0]]);
	else if (is_indirect(op_args[0], codage, 0))
		value = env->memory[ind_to_int(op_args[0], env->champion[num_player]->program_control)];
	else if (is_direct(op_args[0], codage, 0))
		value = op_args[0];
	if (is_register(op_args[1], codage, 1))
		value2 = reg_to_int(env->champion[num_player]->reg[op_args[0]]);
	else if (is_indirect(op_args[1], codage, 1))
		value2 = env->memory[ind_to_int(op_args[1], env->champion[num_player]->program_control)];
	else if (is_direct(op_args[1], codage, 1))
		value2 = op_args[1];
	if (!is_register(op_args[2], codage, 2))
		return (-1);
	ft_strncpy(env->champion[num_player]->reg[op_args[2]], int_to_reg(value & value2), REG_SIZE * 2);
	env->champion[num_player]->carry = 1;
	return (0);
}
