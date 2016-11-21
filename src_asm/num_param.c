/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adompe <adompe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 18:51:59 by adompe            #+#    #+#             */
/*   Updated: 2016/11/16 14:28:28 by qmoreaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_get_num_param(t_param *p, char *str)
{
	p->value = ft_atoi(str);
	if (!(p->type & T_DIR))
		p->type += T_IND;
	p->label = NULL;
}
