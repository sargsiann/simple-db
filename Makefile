NAME = simple-db

CC = cc 

CFLAGS = -Wall -Wextra -Werror 

INCLUDES = includes

SRCS = $(shell find src -name "*.c")

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -I $(INCLUDES) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re