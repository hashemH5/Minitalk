NAME	= libft.a
CC = cc
CFLAGS	= -Wall -Wextra -Werror
SRCS = 	ft_strlen.c \
	ft_atoi.c \
	ft_isdigit.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putnbr_fd.c \

OBJS = $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	ar -rcs $(NAME) $(OBJS)
	
clean:	
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)
	
re: fclean all

.PHONY : all clean fclean re
