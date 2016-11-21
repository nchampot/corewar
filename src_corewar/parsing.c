/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:25:39 by rfernand          #+#    #+#             */
/*   Updated: 2016/11/17 17:35:59 by rfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "ope.h"
#include "stdlib.h"
#include <stdio.h>

int		check_alive(int **parseur, int nbp)
{
	int i;
	int n;

	i = 1;
	n = 0;
	while (n < nbp)
	{
		if (parseur[n][0] != 0)
			i = 0;
		n++;
	}
	return (i);
}

int		check_live(t_joueur **players, t_state *state, int ** parseur, int nbp)
{
	int i;

	i = 0;
	while (i < nbp)
	{
		if (!players[i]->nb_live_current_cycle)
			parseur[i][0] = 0;
		else
		{
			state->nbr_live += players[i]->nb_live_current_cycle;
			players[i]->nb_live_current_cycle = 0;
		}
		i++;
	}
	return (check_alive(parseur, nbp));
}

int		**create_parseur(int nbp)
{
	int **parseur;
	int i;

	i = 0;
	parseur = (int **) malloc(nbp * sizeof(int*));
	while (i < nbp)
	{
		parseur[i] = (int *) malloc(2 * sizeof(int));
		parseur[i][0] = 1;
		parseur[i][1] = ((4096 / nbp) * i);
		i++;
	}
	return (parseur);
}

t_env			*create_env(t_joueur **players, unsigned char *memory, int nbp)
{
	t_env *envi;

	envi = (t_env *) malloc(sizeof(t_env));
	envi->nb_player = nbp;
	envi->memory = memory;
	envi->champion = players;
	return (envi);
}

int				get_codage(unsigned char *str)
{
	if (str[0] == 1 || str[0] == 9 || str[0] == 12 || str[0] == 15)
		return (0);
	else
		return (str[1]);
}

unsigned int	*get_op_arg(unsigned char *str)
{
	unsigned int *params;

	params = (unsigned int *) malloc(4 * sizeof(unsigned int));
	if (str[1] == 0x54)
		recup_111(str, params);
	if (str[0] == 11 && (str[1] == 0x68 || str[1] == 0x78))
		recup_122(str, params);
	if (str[1] == 0x74 || ((str[0] == 11 || str[0] == 10 || str[0] == 11) && str[1] == 0x64))
		recup_121(str, params);
	if (str[1] == 0x58)
		recup_112(str, params);
	if (str[1] == 0x90)
		recup_41(str, params);
	if (str[1] == 0xd0)
		recup_21(str, params);
	if (str[1] == 0x50)
		recup_11(str, params);
	if (str[1] == 0x70)
		recup_12(str, params);
	if ((str[0] >= 6 && str[0] <= 8 && str[1] == 0xf4) || ((str[0] == 10 || str[0] == 14) && (str[1] == 0xa4 || str[1] == 0xe4)))
		recup_221(str, params);
	if (str[0] >= 6 && str[0] <= 8 && str[1] == 0xe4)
		recup_241(str, params);
	if (str[1] == 0xd4 || ((str[0] == 10 || str[0] == 14) && str[1] == 0x94))
		recup_211(str, params);
	if (str[1] == 0xb4)
		recup_421(str, params);
	if (str[0] >= 6 && str[0] <= 8 && str[1] == 0xa4)
		recup_441(str, params);
	if (str[0] >= 6 && str[0] <= 8 && str[1] == 0x64)
		recup_141(str, params);
	if (str[0] >= 6 && str[0] <= 8 && str[1] == 0x94)
		recup_411(str, params);
	if (str[0] == 9 || str[0] == 12 || str[0] == 15)
		params[0] = 256 * str[1];
	if (str[0] == 16)
		params[0] = str[2];
	if (str[0] == 1)
		params[0] = CUBE * str[1] + CARRE * str[2] + 256 * str[3] + str[4];
	return (params);
}

void			moove_parseur(t_joueur **players, int **parseur, unsigned char *memory, int nbp, void (**execute_op)(unsigned char *memory))
{
	int i;
	int n;

	i = 0;
	n = 1;
	while (i < nbp)
	{
		if (NBCURSEUR)
		{
			while (n <= NBCURSEUR)
			{
				if (players[i]->cycle[n])
					players[i]->cycle[n]--;
				if (!players[i]->cycle[n])
				{
					execute_op[POS](memory);
					POS += (nb_arg(memory + POS) + 2);
				}
				if (POS == 4095)
					POS = 0;
				n++;
			}
		}
		n = 1;
		i++;
	}
}

int				get_nb_cycle(char c)
{
	if (c == 1 ||  c == 4 | c == 5 || c == 13)
		return (10);
	if (c == 2 || c == 3)
		return (5);
	if (c == 6 || c == 7 || c == 8)
		return (6);
	if (c == 9)
		return (20);
	if (c == 10 || c == 11)
		return (25);
	if (c == 12)
		return (800);
	if (c == 14)
		return (50);
	if (c == 15)
		return (1000);
	if (c == 16)
		return (2);
	return (0);
}

void			check_instruct(t_joueur **players, int **parseur, unsigned char *memory, int nbp)
{
	int i;
	int n;

	i = 0;
	n = 1;
	while (i < nbp)
	{
		while (n <= parseur[i][0])
		{
			if(!players[i]->cycle[n])
				players[i]->cycle[n] += get_nb_cycle(memory[POS]);
			n++;
		}
		n = 1;
		i++;
	}
}

void			reduc_cycle_to_check(t_state *state)
{
	if (state->nbr_live >= NBR_LIVE)
		state->cycle_to_check -= CYCLE_DELTA;
	else
		state->nb_check++;
	if (state->nb_check == MAX_CHECKS)
	{
		state->cycle_to_check -= CYCLE_DELTA;
		state->nb_check = 0;
	}
	if (state->cycle_to_check < 0)
		state->cycle_to_check = 0;
}

void			init_execute_op(void (**execute_op)(unsigned char *memory))
{
	execute_op[1] = &op_live;
	execute_op[2] = &op_ld;
	execute_op[3] = &op_st;
	execute_op[4] = &op_add;
	execute_op[5] = &op_sub;
	execute_op[6] = &op_and;
	execute_op[7] = &op_or;
	execute_op[8] = &op_xor;
	execute_op[9] = &op_zjmp;
	execute_op[10] = &op_ldi;
	execute_op[11] = &op_sti;
	execute_op[12] = &op_fork;
	execute_op[13] = &op_lld;
	execute_op[14] = &op_lldi;
	execute_op[15] = &op_lfork;
	execute_op[16] = &op_aff;
}

unsigned char	*parsing(t_joueur **players, unsigned char *memory, int nbp, int dumb)
{
	int **parseur;
	int cycle;
	int totalcycle;
	t_state	*state;
	void	(*execute_op[17])(unsigned char *memory);

	cycle = 0;
	totalcycle = 0;
	parseur = create_parseur(nbp);
	init_execute_op(execute_op);
	state = (t_state *) malloc(sizeof(t_state));
	state->cycle_to_check = CYCLE_TO_DIE;
	state->nb_check = 0;
	state->nbr_live = 0;
	while (state->cycle_to_check)
	{
		cycle++;
		totalcycle++;
//		printf("%i\n", parseur[0][1]);
		printf("%i\n", totalcycle);
		check_instruct(players, parseur, memory, nbp);
		moove_parseur(players, parseur, memory, nbp, execute_op);
		if (totalcycle == dumb)
			return (memory);
		if (cycle == state->cycle_to_check)
		{
			if (check_live(players, state, parseur, nbp))
				return (memory);
			reduc_cycle_to_check(state);
			cycle = 0;
		}
	}
	return (memory);
}
