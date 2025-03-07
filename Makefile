# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 15:05:03 by stdevis           #+#    #+#              #
#    Updated: 2025/03/07 18:22:09 by stdevis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[36m
RESET = \033[0m
RED = \033[31m

BOLD = \033[1m
UNDERLINE = \033[4m
ITALIC = \033[3m

NAME = fdf
NAME_TEST = fdf_test
OBJ_DIR = obj/
SRC_DIR = src/

SRC = error.c free.c initialization.c main.c print.c parsing.c translate.c rotate.c \
	  scaling+zoom.c color.c draw.c initialization2.c key_handle.c projection.c utils.c \
	  windows.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))
OBJ_TEST = $(addprefix $(OBJ_TEST_DIR), $(TEST:%.c=%.o))

CFLAGS = -Wall -Wextra -Werror -g3 -O3
MiniLibX_Flags = -lXext -lX11
FSANITIZE = -fsanitize=address
MAKE = make --no-print-directory

LIBFT_DIR = libft/libft_original
PRINTF_DIR = libft/Printf
GNL_DIR = libft/GNL
Mini_Libx_DIR = minilibx-linux/
All_L = -L $(LIBFT_DIR) -L $(PRINTF_DIR) -L $(GNL_DIR) -L $(Mini_Libx_DIR)
All_l = -lft -lftprintf -l:GNL.a -lmlx_Linux -lm

LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a
GNL = $(GNL_DIR)/GNL.a
MINI_LIBX = $(Mini_Libx_DIR)/libmlx_Linux.a

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@mkdir -p $(OBJ_DIR)
	@echo "📦 $(ITALIC)$(YELLOW)Compiling $< $(RESET)"
	@cc $(CFLAGS) -c $< -o $@

$(OBJ_TEST_DIR)%.o: $(SRC_TEST_DIR)%.c 
	@mkdir -p $(OBJ_TEST_DIR)
	@echo "📦 $(ITALIC)$(YELLOW)Compiling $< $(RESET)"
	@cc $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(PRINTF) $(GNL) $(MINI_LIBX) $(OBJ)
	@echo ""
	@echo "		🚀 $(BOLD)$(YELLOW)Linking $(NAME)...$(RESET)"
	@cc $(CFLAGS) $(OBJ) -o $(NAME) $(All_L) $(All_l) $(MiniLibX_Flags)
	@echo ""
	@echo "	🎉 $(BOLD)$(GREEN)SUCCESS: $(NAME) has been created$(RESET) ✅ "
	@echo ""

$(MINI_LIBX):
	@echo ""
	@echo "		⚙ $(UNDERLINE)$(BOLD)Building Mini_Libx$(RESET) ⚙"
	@echo ""
	@$(MAKE) -C $(Mini_Libx_DIR)
	@echo ""
	@echo "	📚 $(BLUE)SUCCESS: Mini_Libx has been created$(RESET) 📚"
	@echo ""
	@echo "		⚙ $(UNDERLINE)$(BOLD)Building $(NAME)$(RESET) ⚙"
	@echo ""

$(LIBFT):
	@echo ""
	@echo "		⚙ $(UNDERLINE)$(BOLD)Building libft$(RESET) ⚙"
	@echo ""
	@$(MAKE) -C $(LIBFT_DIR)
	
$(GNL):
	@echo ""
	@echo "		⚙ $(UNDERLINE)$(BOLD)Building GNL$(RESET) ⚙"
	@echo ""
	@$(MAKE) -C $(GNL_DIR)

$(PRINTF):
	@echo ""
	@echo "		⚙ $(UNDERLINE)$(BOLD)Building printf$(RESET) ⚙"
	@echo ""
	@$(MAKE) -C $(PRINTF_DIR)
	@echo ""

clean:
	@echo ""
	@echo "		🧹 $(BOLD)$(BLUE)Cleaning object files 🧹$(RESET)"
	@echo ""
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(PRINTF_DIR) clean
	@$(MAKE) -C $(GNL_DIR) clean
	@$(MAKE) -C $(Mini_Libx_DIR) clean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_TEST_DIR)
	@echo "💾 $(YELLOW)Cleaning $(NAME) object files$(RESET)"
	@echo "   ↪️ $(GREEN)$(NAME) object files have been deleted$(RESET)"
	@echo ""
	@echo "	👉 $(BOLD)$(GREEN)Object files have been deleted$(RESET) ❎"


fclean: clean
	@echo ""
	@echo "		🧹 $(BOLD)$(BLUE)Cleaning everything 🧹$(RESET)"
	@echo ""
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@$(MAKE) -C $(GNL_DIR) fclean
	@echo "💾 $(YELLOW)Cleaning $(NAME)$(RESET)"
	@echo "   ↪️ $(GREEN)$(NAME) has been deleted$(RESET)"
	@rm -f $(NAME)
	@rm -f $(NAME_TEST)
	@echo ""
	@echo "	👉 $(BOLD)$(GREEN)Everything has been cleaned$(RESET) ❎"

re: fclean $(NAME)

.PHONY: all clean fclean re