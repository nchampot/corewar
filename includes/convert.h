/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmoreaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 15:26:49 by qmoreaux          #+#    #+#             */
/*   Updated: 2016/11/17 11:20:54 by qmoreaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_H
# define CONVERT_H

# include "struct.h"
# include "libft.h"

int		reg_to_int(char *reg);
char*	int_to_reg(int value);
int		ind_to_int(int ind, int pc);
int		int_to_ind(int value);

#endif
