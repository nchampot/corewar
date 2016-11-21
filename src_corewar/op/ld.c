/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmoreaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:12:15 by qmoreaux          #+#    #+#             */
/*   Updated: 2016/11/17 13:31:28 by qmoreaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ope.h"

int		op_ld(t_env *env, int num_player, unsigned int op_args[4], char codage)
{
	int	value;

	env->champion[num_player]->carry = 0;
	if (is_direct(op_args[0], codage, 0))
		value = op_args[0];
	else if (is_indirect(op_args[0], codage, 0))
		value = ind_to_int(op_args[0], env->champion[num_player]->program_control);
	else
		return (-1);
	if (!is_register(op_args[1], codage, 1))
		return (-1);
	ft_strncpy(env->champion[num_player]->reg[op_args[1]], int_to_reg(value), REG_SIZE * 2);
	env->champion[num_player]->carry = 1;
	return (0);
}
