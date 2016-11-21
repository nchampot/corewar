/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmoreaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 15:31:35 by qmoreaux          #+#    #+#             */
/*   Updated: 2016/11/17 13:18:44 by qmoreaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checkers.h"

int	is_register(int value, int codage, int num)
{
	if (value < 0 || value > REG_NUMBER)
		return (0);
	if (num == 0)
		codage = codage >> 6;
	else if (num == 1)
	{
		codage = codage << 2;
		codage = codage << 6;
	}
	else if(num == 2)
	{
		codage = codage << 4;
		codage = codage >> 6;
	}
	else if (num == 3)
	{
		codage = codage << 6;
		codage = codage >> 6;
	}
	if (codage == 1)
		return (1);
	else
		return (0);

}

int	is_direct(int value, int codage, int num)
{
	if (num == 0)
		codage = codage >> 6;
	else if(num == 1)
	{
		codage = codage << 2;
		codage = codage << 6;
	}
	else if(num == 2)
	{
		codage = codage << 4;
		codage = codage >> 6;
	}
	else if (num == 3)
	{
		codage = codage << 6;
		codage = codage >> 6;
	}
	if (codage == 2)
		return (1);
	else
		return (0);
}

int	is_indirect(int value, int codage, int num)
{
	if (num == 0)
		codage = codage >> 6;
	else if(num == 1)
	{
		codage = codage << 2;
		codage = codage << 6;
	}
	else if(num == 2)
	{
		codage = codage << 4;
		codage = codage >> 6;
	}
	else if (num == 3)
	{
		codage = codage << 6;
		codage = codage >> 6;
	}
	if (codage == 3)
		return (1);
	else
		return (0);
}

int	is_valid_player(int nb, t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_player)
	{
		if (env->champion[i]->num_player == i)
			return (1);
	}
	return (0);
}
