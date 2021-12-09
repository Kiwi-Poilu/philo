NAME = philo

INC = include

SRCS =	srcs/main.c \
		srcs/parsing.c \
		srcs/ft_strtol.c \
		srcs/utils.c \
		srcs/utils2.c

OBJS = ${SRCS:.c=.o}

CC = clang

RM = rm -f

CFLAGS = -g3 -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -lpthread -o $(NAME)

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re : fclean all
