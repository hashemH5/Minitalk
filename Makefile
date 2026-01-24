SERVER       = server
CLIENT       = client

SRC_SERVER   = server.c
SRC_CLIENT   = client.c

OBJ_SERVER  = $(SRC_SERVER:.c=.o)
OBJ_CLIENT  = $(SRC_CLIENT:.c=.o)

SERVER_B     = server_bonus
CLIENT_B     = client_bonus

SRC_SERVER_B = server_bonus.c
SRC_CLIENT_B = client_bonus.c

OBJ_SERVER_B = $(SRC_SERVER_B:.c=.o)
OBJ_CLIENT_B = $(SRC_CLIENT_B:.c=.o)

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

LIBFT       = libft/libft.a

all: $(SERVER) $(CLIENT)

bonus: $(SERVER_B) $(CLIENT_B)

$(SERVER): $(OBJ_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT) -o $(SERVER)

$(CLIENT): $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) -o $(CLIENT)

$(SERVER_B): $(OBJ_SERVER_B) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SERVER_B) $(LIBFT) -o $(SERVER_B)

$(CLIENT_B): $(OBJ_CLIENT_B) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT_B) $(LIBFT) -o $(CLIENT_B)

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_SERVER_B) $(OBJ_CLIENT_B)
	make -C libft clean
	
fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVER_B) $(CLIENT_B) libft/libft.a

re: fclean all

.PHONY: all bonus clean fclean re
