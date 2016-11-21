/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmoreaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 15:26:49 by qmoreaux          #+#    #+#             */
/*   Updated: 2016/11/17 11:31:58 by qmoreaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKERS_H
# define CHECKERS_H

# include "struct.h"

int	is_register(int value, int codage, int num);
int	is_direct(int value, int codage, int num);
int	is_indirect(int value, int codage, int num);
int	is_valid_player(int value, t_env *env);

#endif
