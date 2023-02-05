PHILO_NAME	=	philo_bonus

SRCS_DIR = srcs/

PHILO_SRCS	=	main.c					\
				${SRCS_DIR}checker.c	\
				${SRCS_DIR}init.c		\
				${SRCS_DIR}life_line.c	\
				${SRCS_DIR}life.c		\
				${SRCS_DIR}make_philo.c	\
				${SRCS_DIR}parsing.c	\
				${SRCS_DIR}time.c		\
				${SRCS_DIR}utils.c


PHILO_OBJS	= $(PHILO_SRCS:%.c=%.o)

GREEN	=	\033[1;32m
RED		=	\033[1;31m
DEFAULT	=	\033[0m

CFLAGS	=	-Wall -Werror -Wextra -g3 -pthread

CC		=	clang

all : $(PHILO_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PHILO_NAME): $(PHILO_OBJS)
	$(CC) $(CFLAGS) $(PHILO_OBJS) -o $(PHILO_NAME)
	@echo "$(GREEN)##### Philosophers compiling finished! #####$(DEFAULT)"

clean :
	rm -rf $(PHILO_OBJS)

fclean : clean
	rm -f $(PHILO_NAME)

re : fclean all

.PHONY : re all fclean clean
