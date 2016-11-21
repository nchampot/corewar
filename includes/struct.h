/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmoreaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:58:13 by qmoreaux          #+#    #+#             */
/*   Updated: 2016/11/17 17:08:06 by rfernand         ###   ########.fr       */
/*   Updated: 2016/11/17 13:20:43 by qmoreaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STRUCT_H
# define STRUCT_H

# include "op.h"
#define POS parseur[i][n]
#define NBCURSEUR parseur[i][0]
#define CUBE 256*256*256
#define CARRE 256*256

typedef struct	s_joueur
{
	char	*name;
	char	*comment;
	int	num_joueur;
	int	nb_live_total;
	int	nb_live_current_cycle;
	int	last_live;
	char	**reg;
	int	carry;
	int program_control;
	int	*cycle;
}				t_joueur;

typedef struct	s_state
{
	int	nbr_live;
	int	cycle_to_check;
	int	nb_check;
}				t_state;

typedef struct	s_env
{
	int	cycle;
	int	nb_player;
	unsigned char *memory;
	t_joueur	**champion;
}				t_env;

unsigned char	*parsing(t_joueur **players, unsigned char *memory, int nbp, int dumb);
int				nb_arg(unsigned char *str);
void			live(unsigned char *memory);

void			recup_111(unsigned char *str, unsigned int *params);
void			recup_122(unsigned char *str, unsigned int *params);
void			recup_112(unsigned char *str, unsigned int *params);
void			recup_41(unsigned char *str, unsigned int *params);
void			recup_21(unsigned char *str, unsigned int *params);
void			recup_11(unsigned char *str, unsigned int *params);
void			recup_12(unsigned char *str, unsigned int *params);
void			recup_221(unsigned char *str, unsigned int *params);
void			recup_241(unsigned char *str, unsigned int *params);
void			recup_211(unsigned char *str, unsigned int *params);
void			recup_421(unsigned char *str, unsigned int *params);
void			recup_441(unsigned char *str, unsigned int *params);
void			recup_141(unsigned char *str, unsigned int *params);
void			recup_411(unsigned char *str, unsigned int *params);
void			recup_121(unsigned char *str, unsigned int *params);

#endif
