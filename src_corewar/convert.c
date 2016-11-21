/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmoreaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 15:23:00 by qmoreaux          #+#    #+#             */
/*   Updated: 2016/11/17 12:01:07 by qmoreaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"

int	reg_to_int(char *reg)
{
	int value;
	int	i;
	int	j;
	int	tmp;
	
	i = 0;
	value = 0;
	while (i < REG_SIZE * 2)
	{
		j = 0;
		while (j <= 1)
		{
			if (reg[i] == 'F')
				tmp = 15;
			else if (reg[i] == 'E')
				tmp = 14;
			else if (reg[i] == 'D')
				tmp = 13;
			else if (reg[i] == 'C')
				tmp = 12;
			else if (reg[i] == 'B')
				tmp = 11;
			else if (reg[i] == 'A')
				tmp = 10;
			else
				tmp = reg[i] - '0';
			value += ft_power(value, (REG_SIZE - i - 1));
		}
	}
	return (value);
}

char	*int_to_reg(int value)
{
	char	*tmp;
	int		tmp2;
	int		i;
	
	tmp2 = 0;
	tmp = (char *)malloc(sizeof(char) * (REG_SIZE * 2));
	bzero(tmp, 16);
	i = 0;
	while (value > 16)
	{
		tmp2 = value % 16;
		value /= 16;
		if (tmp2 == 15)
			tmp[REG_SIZE - i - 1] = 'F';
		else if (tmp2 == 14)
			tmp[REG_SIZE - i - 1] = 'E';
		else if (tmp2 == 13)
			tmp[REG_SIZE - i - 1] = 'D';
		else if (tmp2 == 12)
			tmp[REG_SIZE - i - 1] = 'C';
		else if (tmp2 == 11)
			tmp[REG_SIZE - i - 1] = 'B';
		else if (tmp2 == 10)
			tmp[REG_SIZE - i - 1] = 'A';
		else
			tmp[REG_SIZE - i - 1] = '0' + tmp2;
		i++;
	}
	return (tmp);
}

int	ind_to_int(int ind, int	pc)
{
	return (pc + (ind % IDX_MOD));
}
