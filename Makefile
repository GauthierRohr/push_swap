# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grohr <grohr@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/29 13:13:00 by grohr             #+#    #+#              #
#    Updated: 2025/04/11 14:44:54 by grohr            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = cc
FLAGS = -Wall -Wextra -Werror -g

# Répertoires
LIBFT_DIR = libft
SRC_DIR = src/
OBJ_DIR = obj/

# Sources et objets
SRCS = 	free_exit.c \
		main.c \
		push_swap_rotate.c \
		radix_sort.c \
		sort_3_to_5.c \
		utils.c
SRC = $(addprefix $(SRC_DIR),$(SRCS))
OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

# Réinitialisation de COMPILED avant chaque compilation
COMPILED = 0

# Librairies
LIBFT = $(LIBFT_DIR)/libft.a

# Couleurs
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[0;33m
BLUE    = \033[34m
PURPLE  = \033[0;35m
CYAN    = \033[36m
RESET   = \033[0m

# Barre de progression
define PROGRESS_BAR
	$(eval TOTAL_FILES := $(words $(OBJ)))
	$(eval PERCENT := $(shell echo $$(( $(COMPILED) * 100 / $(TOTAL_FILES) ))))
	@printf "\r$(CYAN)[push_swap]$(RESET): Compilation... %-20s %3d%% " \
		$$(printf '$(GREEN)%0.s▮$(RESET)' $$(seq 1 $$(($(PERCENT) / 5)))) \
		$(PERCENT)
endef

# Règles
all: $(LIBFT) $(NAME)
	@echo "\n$(CYAN)[push_swap]$(RESET):$(GREEN) Compilation terminée ! 🥳$(RESET)"

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "\n$(GREEN) Compilation de push_swap réussie ! $(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@ -I./$(LIBFT_DIR)
	$(eval COMPILED := $(shell echo $$(( $(COMPILED) + 1 ))))
	$(PROGRESS_BAR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -s -C $(LIBFT_DIR) clean
	@echo "$(CYAN)[push_swap]$(RESET):$(GREEN) Fichiers objets => Cleaned!$(RESET)"
	@echo "$(CYAN)[libft]$(RESET):$(GREEN) Fichiers objets => Cleaned!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -s -C $(LIBFT_DIR) fclean
	@echo "$(CYAN)[push_swap]$(RESET):$(GREEN) Exécutable => Cleaned!$(RESET)"

re: fclean all

# Autisme 
flex:
	@echo "🎉 Flexing those muscles! 📸"
	@sleep 0.5
	@echo "\n    ${RED}✨ ᕙ(⇀‸↼‶)ᕗ ✨${NC}\n"
	@sleep 0.5
	@echo "\n    ${GREEN}   ᕙ(✧ڡ✧)ᕗ  ${NC}\n"
	@sleep 0.5
	@echo "\n    ${YELLOW}⚡️ ᕙ(^▽^)ᕗ ⚡️${NC}\n"
	@sleep 0.5
	@echo "\n    ${BLUE}   ᕦ(ò_óˇ)ᕤ  ${NC}\n"
	@sleep 0.5
	@echo "\n    ${PURPLE}💥 ᕙ(▀̿̿Ĺ̯̿̿▀̿ ̿)ᕗ 💥${NC}\n"
	@sleep 0.5
	@echo "\n🏆 Flex session complete! I'm a fcking boss"!

seum:
	@echo "\n ${RED}   ༼;´༎ຶ ۝ ༎ຶ༽ ${NC}\n"
	@sleep 0.5
	@echo "\n ${GREEN}   (˚ ˃̣̣̥⌓˂̣̣̥ ) ${NC}\n"
	@sleep 0.5
	@echo "\n ${CYAN}╭∩╮( •̀_•́ )╭∩╮${NC}\n"
	@sleep 0.5
	@echo "\n ${PURPLE}   (ﾉಥ益ಥ) ${NC}\n"
	@sleep 0.5
	@echo "\n ${YELLOW}   ᶠᶸᶜᵏᵧₒᵤ!${NC}\n"
	@sleep 0.5

.PHONY: all clean fclean re flex seum