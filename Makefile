NAME = philo
MAKE = make
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c \
		error_handling.c \
		monitor_utils.c \
		parse_utils.c \
		set_get.c \
		simulation_utils.c \
		simulation.c \

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
		@rm -f $(OBJS)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re