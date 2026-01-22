SERVER      = server
CLIENT      = client

SRC_SERVER  = server.c
SRC_CLIENT  = client.c

OBJ_SERVER  = $(SRC_SERVER:.c=.o)
OBJ_CLIENT  = $(SRC_CLIENT:.c=.o)

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

LIBFT       = libft/libft.a

all: $(SERVER) $(CLIENT)

bonus: all

$(SERVER): $(OBJ_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT) -o $(SERVER)

$(CLIENT): $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) -o $(CLIENT)

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)
	make -C libft clean
	
fclean: clean
	rm -f $(SERVER) $(CLIENT) libft/libft.a

re: fclean all

.PHONY: all bonus clean fclean re
