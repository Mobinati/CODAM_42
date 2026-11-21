NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g
SRCS = main.c parsing.c init.c coder.c dongle.c monitor.c utils.c
OBJS = $(SRCS:.c=.o)
HEADER = codexion.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re