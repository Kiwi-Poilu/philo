NAME = philo

INC = include

SRCS =	srcs/main.c

OBJS = ${SRCS:.c=.o}

CC = clang

RM = rm -f

CFLAGS = -g3 -Wall -Werror -Wextra

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $< -I$(INC) -c -o $@

$(NAME) : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re : fclean all