# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 16:22:28 by hbui-vu           #+#    #+#              #
#    Updated: 2023/07/24 17:29:07 by hbui-vu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cubed

SRCS = test.c

# BSRCS = 

CC = cc

CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lmlx -lmlx -Ofast -framework OpenGL -g -framework AppKit

# LIBFT_DIR = ./libft
MLX_DIR = ./mlx

LIBS = ./libft/libft.a

OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)

$(NAME): $(OBJS) 
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJS) -o $(NAME)
# $(CC) $(LIBS) $(CFLAGS) $(MLX_FLAGS) $(OBJS) -o $(NAME)
# $(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

# bonus: $(NAME) $(BOBJS)
# 	$(MAKE) -C $(MLX_DIR)
# 	$(MAKE) -C $(LIBFT_DIR)
# 	$(CC) $(LIBS) $(MLX_FLAGS) $(BOBJS) -o $(NAME)

clean:
	$(MAKE) clean -C $(MLX_DIR)
	rm -rf *.o
# $(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
# $(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re