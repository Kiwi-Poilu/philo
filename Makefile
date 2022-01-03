NAME = philo

INC = include

SRCS =	srcs/main.c \
		srcs/parsing.c \
		srcs/ft_strtol.c \
		srcs/utils.c \
		srcs/actions.c \
		srcs/death_check.c \
		srcs/init.c

OBJS = ${SRCS:.c=.o}

CC = clang

RM = rm -f

CFLAGS = -g3 -Wall -Werror -Wextra #-fsanitize=thread 
all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -lpthread -o $(NAME) #-fsanitize=thread

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re : fclean all
