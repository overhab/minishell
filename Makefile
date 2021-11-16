dir		=   .

SRCS	=	fork.c 				\
			multalloc.c 		\
			find_path.c 		\
			builtins.c  		\
			builtins_2.c  		\
			dict_func.c 		\
			dict_func_2.c 		\
			environ.c   		\
			exiting.c   		\
			main.c 				\
			dispatch_process.c	\
			err.c				\
			process_utils.c		\
			start_process.c		\
			util.c

P_DIR	= 	pars/

PARSERS	=	${P_DIR}mini_parser.c 		\
			${P_DIR}error_out.c 		\
			${P_DIR}ft_list_utils.c 	\
			${P_DIR}env_func.c 			\
			${P_DIR}parsers.c 			\
			${P_DIR}command.c 			\
			${P_DIR}check_cmd.c			\
			${P_DIR}heredoc.c 			\
			${P_DIR}parser_utils.c 		\
			${P_DIR}util.c 

LIBFTDIR = ./libft

LIBFT = $(LIBFTDIR)libft.a

OBJS	=	${SRCS:.c=.o}

P_OBJS  =   ${PARSERS:.c=.o}

CFLAGS	=   -O0 -Wall -Wextra -Werror

HEAD	=	minishell.h

CC		=	clang

RM		=	-rm	-f

NAME	=	minishell

all: libs $(NAME)

%.o: %.c $(HEAD)
	$(CC) -I $(LIBFTDIR) ${CFLAGS} -c $< -o ${<:.c=.o}

libs:
	@make -C $(LIBFTDIR)

${NAME}: ${OBJS} ${P_OBJS}
		$(CC) ${CFLAGS} ${OBJS} ${P_OBJS} -L$(LIBFTDIR) -lft -lreadline \
		-L/Users/mehtel/.brew/Cellar/readline/8.1/lib \
		-I/Users/mehtel/.brew/Cellar/readline/8.1/include \
		-o ${NAME}
clean:
	rm -f $(OBJS) ${P_OBJS}
	make clean -C $(LIBFTDIR)

fclean:	clean
	rm -f $(NAME)
	make fclean -C $(LIBFTDIR)

re:		fclean all

.PHONY:	all bonus clean fclean re
