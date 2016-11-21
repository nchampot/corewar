# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmoreaux <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 13:04:54 by qmoreaux          #+#    #+#              #
#    Updated: 2016/11/16 15:18:00 by qmoreaux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_ASM = asm
NAME_COREWAR = corewar

SRC_PATH_ASM = ./src_asm/
SRC_NAME_ASM = main.c \
			   parsing.c \
			   get_ins.c \
			   get_ins_param.c \
			   check_param.c \
		   	   label_param.c \
		   	   reg_param.c \
			   num_param.c \
			   check_ins .c \
			   print_bytecode.c \
			   print_ins.c \
			   prog_size.c \
			   ope.c

SRC_PATH_COREWAR = ./src_corewar/
SRC_NAME_COREWAR = main.c \
				   parsing.c \
				   checkers.c \
				   convert.c \
				   op/add.c \
				   op/aff.c \
				   op/and.c \
				   op/fork.c \
				   op/ld.c \
				   op/ldi.c \
				   op/lfork.c \
				   op/live.c \
				   op/lld.c \
				   op/lldi.c \
				   op/or.c \
				   op/st.c \
				   op/sti.c \
				   op/sub.c \
				   op/xor.c \
				   op/zjmp.c \

OBJ_PATH_ASM = ./obj_asm/
OBJ_NAME_ASM = $(SRC_NAME_ASM:.c=.o)

OBJ_PATH_COREWAR = ./obj_corewar/
OBJ_NAME_COREWAR = $(SRC_NAME_COREWAR:.c=.o)

INC_PATH = ./includes/

LIB_PATH = ./lib/
LIB_NAME = -lft \
		   -lftprintf

SRC_ASM = $(addprefix $(SRC_PATH_ASM), $(SRC_NAME_ASM))
OBJ_ASM = $(addprefix $(OBJ_PATH_ASM), $(OBJ_NAME_ASM))

SRC_COREWAR = $(addprefix $(SRC_PATH_COREWAR), $(SRC_NAME_COREWAR))
OBJ_COREWAR = $(addprefix $(OBJ_PATH_COREWAR), $(OBJ_NAME_COREWAR))

LIB = $(addprefix -L, $(LIB_PATH))
INC = $(addprefix -I, $(INC_PATH))

CC = gcc
CFLAGS = -Werror -Wall -Wextra

all: $(NAME_ASM) $(NAME_COREWAR)

$(NAME_ASM): $(OBJ_ASM)
	make -C lib/Libft
	make -C lib/Ft_printf
	$(CC) $(LIB) $(LIB_NAME) $(OBJ_ASM) -o asm

$(OBJ_PATH_ASM)%.o: $(SRC_PATH_ASM)%.c
	@mkdir $(OBJ_PATH_ASM) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME_COREWAR): $(OBJ_COREWAR)
	make -C lib/Libft
	make -C lib/Ft_printf
	$(CC) $(LIB) $(LIB_NAME) $(OBJ_COREWAR) -o asm

$(OBJ_PATH_COREWAR)%.o: $(SRC_PATH_COREWAR)%.c
	@mkdir $(OBJ_PATH_COREWAR) 2> /dev/null || echo "" > /dev/null
	@mkdir $(OBJ_PATH_COREWAR)/op 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	make -C lib/Libft/ clean
	rm -rf $(OBJ_PATH_ASM) $(OBJ_PATH_COREWAR)

fclean: clean
	make -C lib/Libft/ fclean
	rm -f $(NAME_ASM) $(NAME_COREWAR)

re: fclean all

norme:
	norminette $(SRC_ASM) $(SRC_COREWAR)
	norminette $(INC_PATH)*.h
