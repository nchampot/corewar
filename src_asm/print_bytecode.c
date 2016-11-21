/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bytecode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adompe <adompe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:19:38 by adompe            #+#    #+#             */
/*   Updated: 2016/11/09 14:19:40 by adompe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_print_uint_hex(int fd, unsigned int nb, char l)
{
	unsigned int	b;

	b = 0;
	while (l > 4)
	{
		write(fd, &b, 1);
		l--;
	}
	if (l >= 4)
	{
		b = (nb & 0xFF000000) >> 24;
		write(fd, &b, 1);
		b = (nb & 0x00FF0000) >> 16;
		write(fd, &b, 1);
	}
	if (l >= 2)
	{
		b = (nb & 0x0000FF00) >> 8;
		write(fd, &b, 1);
	}
	b = (nb & 0x000000FF);
	write(fd, &b, 1);
}

void	ft_print_header(t_asm *data, int fd)
{
	header_t	*header;
	int			i;
	char		c = 0;

	i = 0;
	header = data->header;
	ft_print_uint_hex(fd, header->magic, 4);
	while (i < PROG_NAME_LENGTH + 4)
	{
		if (header->prog_name[i])
			write(fd, &(header->prog_name[i]), 1);
		else
			ft_print_uint_hex(fd, 0, 1);
		i++;
	}
	i = 0;
	ft_print_uint_hex(fd, header->prog_size, 4);
	while (i < COMMENT_LENGTH)
	{
			write(fd, &(header->comment[i]), 1);
		i++;
	}
}

void	ft_print_bytecode(t_asm *data, char *name)
{
	int fd;


	fd = open(ft_strcat(ft_strsplit(name, '.')[0], ".cor"), O_RDWR | O_CREAT, S_IRWXO | S_IRWXU | S_IRWXG);
	ft_print_header(data, fd);
	ft_print_ins(data, fd);
}
