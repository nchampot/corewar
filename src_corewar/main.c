/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 12:34:12 by rfernand          #+#    #+#             */
/*   Updated: 2016/11/17 15:56:23 by rfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "struct.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

char	*get_name(int fd)
{
	char *str;

	lseek(fd, 1, SEEK_SET);
	get_next_line(fd, &str);
	return (ft_strdup(&str[3]));
}

char	*get_comment(int fd)
{
	char *str;

	str = (char *) malloc(2 * sizeof(char));
	ft_bzero(str, 2);
	read(fd, str, 1);
	while (!str[0])
		read(fd, str, 1);
	get_next_line(fd, &str);
	return (ft_strdup(str));
}

int		nb_arg(unsigned char *str)
{
	if (str[0] == 1 || str[1] == 0x54 || str[1] == 0xd0 || str[1] == 0x70)
		return (3);
	if (str[0] == 9 || str[0] == 12 || str[0] == 15 || str[0] == 16)
		return (1);
	if (str[1] == 0x68 || str[1] == 0x90 || str[1] == 0x78 || str[1] == 0xf4 || ((str[1] == 0xa4 || str[1] == 0xe4) && (str[0] == 10 || str[0] == 14)))
		return (5);
	if (str[0] == 3)
		return (2);
	if (((str[1] == 0x58 || str[1] == 0x64 || str[1] == 0x94) && str[0] == 11) || str[1] == 0x74 || str[1] == 0xd4)
		return (4);
	if ((str[1] == 0x64 || str[1] == 0x94) && str[0] >= 6 && str[0] <= 8)
		return (6);
	if ((str[0] >= 6 && str[0] <= 8) && (str[1] == 0xb4 || str[1] == 0xe4))
		return (7);
	if (str[1] == 0xa4 && str[0] >= 6 && str[0] <= 8)
		return (9);
/*	if (str[0] == 9 || str[0] == 12 ||  str[0] == 16)
		return (2);
	else if (str[0] == 3)
		return (3);
	else if (str[0] == 4 || str[0] == 5 || str[0] == 1)
		return (4);
	else if (str[0] == 15)
		return (5);
	else if (str[0] == 10 || str[0] == 11 || str[0] == 2 || str[0] == 13 || str[0] == 14)
		return (6);
	else if (str[0] == 7 || str[0] == 6 || str[0] == 8)
		return (10);
*/	return (-1);
}

unsigned char	*resize(unsigned char *instruct, unsigned char *str, int nb, int i)
{
	unsigned char *tmp;

	tmp = (unsigned char *) malloc((i + 1) * sizeof(unsigned char));
	ft_bzero(tmp, i + 1);
	ft_memcpy(tmp, instruct, i);
	free(instruct);
	instruct = (unsigned char *)malloc((nb + i + 1) * sizeof(unsigned char));
	ft_memcpy(instruct, tmp, i);
	ft_memcpy(instruct + i, str, nb);
	free(tmp);
	return (instruct);
}

unsigned char	*save_instruct(unsigned char *instruct, int i)
{
	unsigned char *str;

	str = (unsigned char *) malloc(1024 * sizeof(unsigned char));
	ft_bzero(str, 1024);
	ft_memcpy(str, instruct, i);
	free(instruct);
	return (str);
}

unsigned char	*get_instruct(int fd)
{
	int i;
	int n;
	unsigned char *str;
	unsigned char *instruct;

	instruct = (unsigned char *) malloc(1 * sizeof(unsigned char));
	instruct[0] = '\0';
	str = (unsigned char *) malloc(8 * sizeof(unsigned char));
	ft_bzero(str, 8);
	i = 0;
	read(fd, str, 1);
	while (!str[0])
		read(fd, str, 1);
	read(fd, str + 1, 1);
	while (str[0])
	{
		instruct = resize(instruct, str, 2, i);
		i += 2;
		n = nb_arg(str);
		read(fd, str, n);
		instruct = resize(instruct, str, n, i);
		i += n;
		ft_bzero(str, 8);
		read(fd, str, 2);
	}
	return (save_instruct(instruct, i));
}

int		flag_dump(char **argv, int argc, int *dumb)
{
	if (!(ft_strcmp(argv[1], "-dumb")))
	{
		if (argc == 2)
			return (0);
		if (argc == 3)
			return (0);
		*dumb = ft_atoi(argv[2]);
		return (3);
	}
	return (1);
}

int		count_param(char **argv, int argc)
{
	int i;
	int n;

	i = 1;
	n = 1;
	if (!(ft_strcmp(argv[1], "-dumb")))
	{
		i += 2;
		n = 3;
	}
	while (n < argc)
	{
		if (!(ft_strcmp(argv[n], "-n")))
		{
			i += 2;
			n += 2;
		}
		n++;
	}
	return (i);
}

int		main(int argc, char **argv)
{
	unsigned char *str;
	unsigned char *memory;
	t_joueur **players;
	int fd;
	int i;
	int	n;
	int	dumb;

	i = flag_dump(argv, argc, &dumb);
	n = 0;
	if (argc == 1)
		return (0);
	players = (t_joueur **)malloc(argc * sizeof(t_joueur *));
	memory = (unsigned char *) malloc(4096 * sizeof(unsigned char));
	ft_bzero(memory, 4096);
	while (i < argc)
	{
		if (!(ft_strcmp(argv[i], "-n")))
		{
			players[n]->num_joueur = ft_atoi(argv[i + 1]);
			i += 2;
		}
		fd = open(argv[i], O_RDONLY);
		players[n] = (t_joueur *) malloc(sizeof(t_joueur));
		players[n]->name = get_name(fd);
		players[n]->comment = get_comment(fd);
		players[n]->nb_live_current_cycle = 0;
		players[n]->cycle = (int *) malloc(2 * sizeof(int));
		players[n]->cycle[1] = 0;
		ft_printf("%s\n%s\n", players[i - 1]->name, players[i - 1]->comment);
		str = get_instruct(fd);
		ft_memcpy(memory + ((4096 / (argc - 1)) * (i - 1)), str, 1024);
		free(str);
		close(fd);
		i++;
		n++;
	}
	parsing(players, memory, argc - count_param(argv, argc), dumb);
	i = 0;
	while (i < 4096)
	{
		if (!(i % 1024))
			ft_printf("\n---------------------------------------------------------------------------------------------------------\n");
		ft_printf("%02x ", memory[i]);
		i++;
	}
	close(fd);
	return(0);
}
