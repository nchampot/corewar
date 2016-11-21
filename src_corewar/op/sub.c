/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmoreaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:09:01 by qmoreaux          #+#    #+#             */
/*   Updated: 2016/11/17 13:33:10 by qmoreaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ope.h"

int		op_sub(t_env *env, int num_player, unsigned int op_args[4], char codage)
{
	env->champion[num_player]->carry = 0;
	if (is_register(op_args[0], codage, 0) && is_register(op_args[1], codage, 1) && is_register(op_args[2], codage, 2))
			return (-1);
	ft_strncpy(env->champion[num_player]->reg[op_args[2]], int_to_reg(reg_to_int(env->champion[num_player]->reg[op_args[0]]) - reg_to_int(env->champion[num_player]->reg[op_args[1]])), REG_SIZE * 2);
	env->champion[num_player]->carry = 1;
	return (0);
}
