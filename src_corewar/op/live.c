/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmoreaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:10:34 by qmoreaux          #+#    #+#             */
/*   Updated: 2016/11/17 13:31:55 by qmoreaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ope.h"

int		op_live(t_env *env, int num_player, unsigned int op_args[4], char codage)
{
	if (!is_valid_player(op_args[0], env))
		return (-1);
	env->champion[op_args[0]]->last_live = env->cycle;
	env->champion[op_args[0]]->nb_live_total++;
	env->champion[num_playe]r->nb_live_current_cycle++;
	return (0);
	codage = 0;
}
