# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 16:26:47 by stdevis           #+#    #+#              #
#    Updated: 2025/02/11 16:58:11 by stdevis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES = \
    ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
    ft_strlen ft_memset ft_bzero ft_memcpy ft_memmove \
    ft_strlcpy ft_strlcat ft_toupper ft_tolower ft_strchr \
    ft_strrchr ft_strncmp ft_memchr ft_memcmp ft_strnstr \
    ft_atoi ft_calloc ft_strdup ft_substr ft_strjoin ft_strtrim \
    ft_split ft_itoa ft_strmapi ft_striteri ft_putchar_fd \
    ft_putendl_fd ft_putnbr_fd ft_putstr_fd \
	ft_lstadd_front_bonus ft_lstnew_bonus ft_lstsize_bonus ft_lstlast_bonus \
	ft_lstadd_back_bonus ft_lstdelone_bonus ft_lstclear_bonus ft_lstiter_bonus \
	ft_lstmap_bonus ft_free
	
OBJ_DIR = obj/
SRC_DIR = src/
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
OBJF = .cache_exists

GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[36m
RESET = \033[0m

BOLD = \033[1m
UNDERLINE = \033[4m
ITALIC = \033[3m

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(OBJF)
	@echo "📦 $(ITALIC)$(YELLOW)Compiling $< $(RESET)"
	@cc $(CFLAGS) -c $< -o $@

$(OBJF):
	@mkdir -p $(OBJ_DIR)
	@touch $(OBJF)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo ""
	@echo "	📚 $(BLUE)SUCCESS: $(NAME) has been created$(RESET) 📚 "

clean:
	@echo "💾 $(YELLOW)Cleaning libft object files$(RESET)"
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJF)
	@echo "   ↪️ $(GREEN)libft object files have been deleted$(RESET)"
		
fclean: clean
	@echo "💾 $(YELLOW)Cleaning libft.a$(RESET)"
	@rm -f $(NAME)
	@echo "   ↪️ $(GREEN)libft.a has been cleaned$(RESET) "
	
re: fclean all

.PHONY:
	re make all fclean clean