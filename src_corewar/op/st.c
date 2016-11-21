/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmoreaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:21:08 by qmoreaux          #+#    #+#             */
/*   Updated: 2016/11/17 13:32:47 by qmoreaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ope.h"

int		op_st(t_env *env, int num_player, unsigned int op_args[4], char codage)
{
	int	value;

	if (is_register(op_args[0], codage, 0))
		value = reg_to_int(env->champion[num_player]->reg[op_args[1]]);
	else
		return (-1);
	if (is_register(op_args[1], codage, 1))
		ft_strncpy(env->champion[num_player]->reg[op_args[1]], int_to_reg(value), REG_SIZE * 2);
	else if (is_indirect(op_args[1], codage, 1))
		ft_strncpy(&env->memory[env->champion[num_player]->program_control + (op_args[1] % IDX_MOD)], int_to_reg(value), REG_SIZE * 2);
	else
		return (-1);
	return (0);
}
