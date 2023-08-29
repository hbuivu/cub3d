# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 16:22:28 by hbui-vu           #+#    #+#              #
#    Updated: 2023/08/29 12:35:44 by hbui-vu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

INC_DIR = include
SRC_DIR = sources
BSRC_DIR = sources_b
OBJ_DIR = object
BOBJ_DIR = object_b
LIBFT_DIR = libft
LIBFT = libft.a
# MLX_DIR = mlx_linux
MLX_DIR = mlx
MLX = libmlx.a

SRCS = error.c utils.c test.c \
	identify.c identify_colour.c identify_path.c parse_map.c \
	walled_check.c walled_check_utilities.c \
	mlx_imgs.c \
	calc.c coord_check.c draw_utils.c draw.c raycasting.c \
	wall_collision.c mlx_hooks.c \
	main.c \

BSRCS = error.c utils.c test.c \
	identify.c identify_colour.c identify_path.c parse_map.c \
	walled_check.c walled_check_utilities.c \
	mlx_hooks.c mlx_imgs.c textures_bonus.c \
	calc.c coord_check.c draw.c draw_utils.c raycasting.c \
	main.c minimap.c \
# SRCS = resize_ex.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
BOBJS = $(addprefix $(BOBJ_DIR)/, $(BSRCS:.c=.o))

CC = cc
RM	= rm -rf

CFLAGS = -Wall -Wextra -Werror 
# -g3 -fsanitize=address
# -fsanitize=address
MLX_FLAGS = -Lmlx -lmlx -Ofast -framework OpenGL -g -framework AppKit
# MLX_FLAGS = -g -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -Ofast -lm


#to create all of the .o files from files in SRC_DIR in OBJ_DIR
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR) -I $(MLX_DIR) -c $< -o $@
#because the include directory for libft  is in libft.

$(BOBJ_DIR)/%.o : $(BSRC_DIR)/%.c
	@mkdir -p $(BOBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR) -I $(MLX_DIR) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(LIBFT_DIR)/$(LIBFT) $(MLX_DIR)/$(MLX) $(OBJS) -Llibft -lft -o $(NAME)
# @$(CC) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(MLX_DIR)/$(MLX) $(CFLAGS) $(MLX_FLAGS) -Llibft -lft -o $(NAME)

all: $(NAME)

bonus: $(NAME) $(BOBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(LIBFT_DIR)/$(LIBFT) $(MLX_DIR)/$(MLX) $(BOBJS) -Llibft -lft -o $(NAME)

clean:
	$(MAKE) clean -C $(MLX_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJ_DIR)
	$(RM) $(BOBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

rebonus:	fclean bonus

.PHONY: all clean fclean re rebonus