SRCS = $(shell find srcs -name '*.c')

OBJS = $(SRCS:.c=.o)

NAME = server.out

INCLUDES = -Iincludes

LIBS = -lenet -llua -lm -ldl -lpthread

CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=gnu99 $(INCLUDES)

all: $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBS)

dbg: CFLAGS += -g
dbg: all

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(OBJS)

re: fclean all
