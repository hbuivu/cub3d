# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 16:22:28 by hbui-vu           #+#    #+#              #
#    Updated: 2023/07/27 14:21:48 by zsyyida          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

INC_DIR = include
SRC_DIR = sources
OBJ_DIR = object
LIBFT_DIR = libft
LIBFT = libft.a
MLX_DIR = mlx
MLX = libmlx.a

SRCS = parse.c test.c error.c space_check.c space_check_utilies.c main.c download.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CC = cc
RM	= rm -rf

CFLAGS = -Wall -Wextra -Werror -fsanitize=address
# why 0fast?
MLX_FLAGS = -Lmlx -lmlx -Ofast -framework OpenGL -g -framework AppKit

#BOBJS = $(addprefix $(BOBJ_DIR)/, $(BSRCS:.c=.o))

#to create all of the .o files from files in SRC_DIR in OBJ_DIR
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR) -I $(MLX_DIR) -c $< -o $@
#because the include directory for libft  is in libft.

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(LIBFT_DIR)/$(LIBFT) $(MLX_DIR)/$(MLX) $(OBJS) -Llibft -lft -o $(NAME)
#$(CC) $(LIBS) $(CFLAGS) $(MLX_FLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

# bonus: $(NAME) $(BOBJS)
# 	$(MAKE) -C $(MLX_DIR)
# 	$(MAKE) -C $(LIBFT_DIR)
# 	$(CC) $(LIBS) $(MLX_FLAGS) $(BOBJS) -o $(NAME)

clean:
	$(MAKE) clean -C $(MLX_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	#rm -rf *.o
	$(RM) $(OBJ_DIR)

fclean: clean
	#rm -rf $(NAME)
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re