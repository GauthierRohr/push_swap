# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grohr <grohr@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 19:08:20 by grohr             #+#    #+#              #
#    Updated: 2025/03/28 19:14:48 by grohr            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = push_swap

# Compilateur et flags
CC = cc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

# Répertoires
LIBFT_DIR = libft
SRC_DIR = src/
OBJ_DIR = obj/

# Fichiers sources et objets
SRCS = utils.c move.c sort.c main.c
SRC = $(addprefix $(SRC_DIR),$(SRCS))
OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

# Réinitialisation de COMPILED avant chaque compilation
COMPILED = 0

# Librairie
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
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) -L./$(LIBFT_DIR) -lft
	@echo "$(GREEN) Compilation de push_swap réussie ! $(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@ -I./$(LIBFT_DIR)
	$(eval COMPILED := $(shell echo $$(( $(COMPILED) + 1 ))))
	$(PROGRESS_BAR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@make -s -C $(LIBFT_DIR) clean
	@echo "$(CYAN)[push_swap]$(RESET):$(GREEN) Fichiers objets => Cleaned!$(RESET)"
	@echo "$(CYAN)[libft]$(RESET):$(GREEN) Fichiers objets => Cleaned!$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@make -s -C $(LIBFT_DIR) fclean
	@echo "$(CYAN)[push_swap]$(RESET):$(GREEN) Exécutable => Cleaned!$(RESET)"

re: fclean all

# Fun targets
flex:
	@echo "🎉 Flexing those muscles! 📸"
	@sleep 0.5
	@echo "\n    ${RED}✨ ᕙ(⇀‸↼‶)ᕗ ✨${RESET}\n"
	@sleep 0.5
	@echo "\n    ${GREEN}   ᕙ(✧ڡ✧)ᕗ  ${RESET}\n"
	@sleep 0.5
	@echo "\n🏆 Flex session complete! I'm a fcking boss!"

seum:
	@echo "\n ${RED}   Pls... ${RESET}\n"
	@sleep 0.5
	@echo "\n ${CYAN}╭∩╮( •̀_•́ )╭∩╮${RESET}\n"
	@sleep 0.5
	@echo "\n🤬 SEUM MODE ACTIVATED!"

.PHONY: all clean fclean re flex seum