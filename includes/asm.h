/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adompe <adompe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 14:22:33 by adompe            #+#    #+#             */
/*   Updated: 2016/10/11 14:22:37 by adompe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "get_next_line.h"
# include "op.h"
# include <fcntl.h>

// tmp
# include <stdio.h>

typedef	struct	s_param
{
	unsigned int	value;
	char			*label;
	int				type;
}				t_param;

typedef struct	s_ins
{
	char			*label;
	char			opcode;
	char			coding_byte;
	t_bool			two_bytes;
	t_list			*param;
	unsigned int	size;
}				t_ins;

typedef struct	s_asm
{
	header_t		*header;
	t_list			*ins;
	t_list			*label_adress;
}				t_asm;

void	ft_get_data(int argc, char **argv, t_asm *data);
t_bool	ft_get_ins_line(t_ins *new_ins, char *line, t_op op_tab[17]);
t_bool	ft_get_opcode(t_ins *new_ins, char *str, t_op op);

void	ft_get_ins_param(t_ins	*ins, char **tab);

/* OPERATIONS */

t_bool	ft_valid_label_char(char c, char *label_chars);

/*	PARAM PARSING	*/

void	ft_get_label_param(t_param *p, char *str);
void	ft_get_reg_param(t_param *p, char *str);
void	ft_get_num_param(t_param *p, char *str);

/*	CHECK PARAM		*/

void	ft_check_ins(t_asm *data);
void	ft_check_param(t_ins *ins, t_op opcode);

/*	PRINT			*/

void	ft_print_bytecode(t_asm *data, char *name);
void	ft_print_ins(t_asm *data, int fd);
void	ft_print_uint_hex(int fd, unsigned int nb, char l);

/*	SIZE AND LABEL 	*/

void	ft_get_prog_size(t_asm *data);


void	ft_error(char *str);

void	debug(t_asm *data);

#endif
