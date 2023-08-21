# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 16:22:28 by hbui-vu           #+#    #+#              #
#    Updated: 2023/08/21 14:32:01 by hbui-vu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

INC_DIR = include
SRC_DIR = sources
OBJ_DIR = object
LIBFT_DIR = libft
LIBFT = libft.a
# MLX_DIR = mlx_linux
MLX_DIR = mlx
MLX = libmlx.a

SRCS = error.c utils.c test.c \
	identify.c identify_colour.c identify_path.c parse_map.c \
	walled_check.c walled_check_utilities.c \
	textures.c mlx_hooks_linux.c mlx.c  \
	calc.c coord_check.c draw.c draw_utils.c raycasting.c \
	main.c 
	
# SRCS = resize_ex.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CC = cc
RM	= rm -rf

CFLAGS = -Wall -Wextra -Werror 
#-fsanitize=address
MLX_FLAGS = -Lmlx -lmlx -Ofast -framework OpenGL -g -framework AppKit
# MLX_FLAGS = -g -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -Ofast -lm

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
# @$(CC) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(MLX_DIR)/$(MLX) $(CFLAGS) $(MLX_FLAGS) -Llibft -lft -o $(NAME)

all: $(NAME)

# bonus: $(NAME) $(BOBJS)
# 	$(MAKE) -C $(MLX_DIR)
# 	$(MAKE) -C $(LIBFT_DIR)
# 	$(CC) $(LIBS) $(MLX_FLAGS) $(BOBJS) -o $(NAME)

clean:
	$(MAKE) clean -C $(MLX_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJ_DIR)
	#rm -rf *.o

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	#rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re