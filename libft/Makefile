# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/22 15:05:32 by hbui-vu           #+#    #+#              #
#    Updated: 2023/07/27 14:15:16 by zsyyida          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INC_DIR = include
SRC_DIR = sources
OBJ_DIR = objects

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c gnl.c

# to add prefix (put into folder) called objects all o files
OBJS_SRC = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CC	= gcc
RM	= rm -rf
CFLAGS = -Wextra

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
# to put all in one line use @printf "\033[A\033[2K\r"
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

all:	$(NAME)

$(NAME): $(OBJS_SRC)
	@ar rcs $(NAME) $(OBJS_SRC)
	@echo "libft ready"

clean:
	$(RM) $(OBJ_DIR)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
