NAME = philo

SRC =	main.c			ft_timer.c			ft_strutils.c			ft_math_utils.c			\
		ft_list_utils.c	ft_philo_action.c	ft_putnbr_fd.c			ft_philo_get_forks.c	\
		ft_monitor.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -g

RM = rm -rf

MHDR = philo.h

MAKE = Makefile

all: $(NAME)

#%.o: %.c
#	$(CC) $(CFLAGS) $< $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o  $(NAME)

$(OBJ): $(MHDR) $(MAKE)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: re