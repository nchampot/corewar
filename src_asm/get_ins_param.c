/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opcode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adompe <adompe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 14:49:29 by adompe            #+#    #+#             */
/*   Updated: 2016/11/16 14:28:08 by qmoreaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_param	*ft_get_tparam(char *str)
{
	t_param		*p;
	int			i;

	i = 0;
	p = (t_param  *)malloc(sizeof(t_param));
	if (str[i] == '%')
	{
		p->type += T_DIR;
		i++;
	}
	if (str[i] == 'r')
		ft_get_reg_param(p, str);
	else if (str[i] == ':')
		ft_get_label_param(p, str);
	else if (ft_isdigit(str[i]))
		ft_get_num_param(p, str);
	return (p);
}

void	ft_get_ins_param(t_ins *ins, char **tab)
{
	t_param		*par;
	char		**ntab;

	while (*tab)
	{
		ntab = ft_strsplit(*tab, ',');
		while (*ntab)
		{
			par = ft_get_tparam(*ntab);
			if (ins->param == NULL)
				ins->param = ft_lstnew(par, sizeof(t_param));
			else
				ft_lstappend(&(ins->param), ft_lstnew(par, sizeof(t_param)));
			ntab++;
		}
		tab++;
	}
}
