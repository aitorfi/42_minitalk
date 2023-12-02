CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_CLIENT = client.c
OBJS_CLIENT = $(SRC_CLIENT:.c=.o)
SRC_SERVER = server.c
OBJS_SERVER = $(SRC_SERVER:.c=.o)
NAME_CLIENT = client
NAME_SERVER = server
RM = rm -f
DIR_LIBFT = ./libft
NAME_LIBFT = $(DIR_LIBFT)/libft.a

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(NAME_LIBFT) $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(NAME_LIBFT) $(OBJS_CLIENT)

$(NAME_SERVER): $(NAME_LIBFT) $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(NAME_LIBFT) $(OBJS_SERVER)

$(NAME_LIBFT):
	make -C $(DIR_LIBFT) improved

clean:
	$(RM) $(OBJS_CLIENT) $(OBJS_SERVER)
	make -C $(DIR_LIBFT) clean

fclean: clean
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)
	make -C $(DIR_LIBFT) fclean

re: fclean all

