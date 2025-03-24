# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grohr <grohr@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 22:14:00 by huaydin           #+#    #+#              #
#    Updated: 2025/02/18 13:45:25 by grohr            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = libft
LIBFT = ./libft/libft.a

RM = rm -rf

SRCS =	utils.c \
		move.c \
		sort.c \
		main.c

SRC	= $(addprefix ./src/,$(SRCS))
OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME) 
	@echo "Make done!"
	@echo "Run 'make test' or 'make test size=x'"

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

# -s : silent --> ne pas voir l'affichage des commandes executees
# -C : Change --> change de repertoire vers $(LIBFT_DIR), puis execute make dedans

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L./$(LIBFT_DIR) -lft

# @ : Empêche l'affichage de la commande dans le terminal (juste l'exécution)
# -o : output --> nom du fichier de sortie = a ce qui suit le -o (ici NAME)
# -L : Library path --> indiquer le chemin vers la librairie libft.a
# ./ : repertoire courant = dossier actuel.

$(OBJ): $(SRC)
	@$(CC) $(CFLAGS) -c $? -I./$(LIBFT_DIR)
	@mv *.o src

# -c : compile les .o sans creer d'executable
# $? : Liste uniquement les fichiers sources plus récents que leurs objets .o (opti)
# -I : Include path
# -I./$(LIBFT_DIR) : Ajoute $(LIBFT_DIR) aux chemins de recherche des fichiers .h
#					 (nécessaire si libft.h dedans par exemple)

clean:	
	@$(RM) src/*.o
	@make -s -C $(LIBFT_DIR) clean

fclean:	clean
	@$(RM) $(NAME)
	@make -s -C $(LIBFT_DIR) fclean

re:	fclean all
	@$(RM) src/*.o
	@make -s -C $(LIBFT_DIR) clean

size ?= 30

# Si size pas definie avec "make test size=x", size = 30.

CHECKER = valgrind ./push_swap $(ARG) | ./checker_linux $(ARG)

test:
	@$(eval ARG = $(shell seq -10000 10000 | shuf -n $(size)))
	@echo "Checker result: "
	$(CHECKER)
	@echo "Instructions count:` "
	@./push_swap $(ARG) | wc -l

# $(eval ...) : évalue l'expression à l'intérieur et affecte la valeur résultante à ARG.
# seq A B : Génère une séquence de nombres allant de A à B.
# shuf : mélange des lignes de texte ou des nombres de manière aléatoire.
# -n : permet de spécifier le nombre de lignes que shuf doit retourner après avoir mélangé la séquence.


# ---------------------------------------------------
# Autisme 2.0
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
NC=\033[0m # (No Color)

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
	@echo "\n ${RED}     -_- ${NC}\n"
	@sleep 0.5
	@echo "\n ${GREEN}   (˚ ˃̣̣̥⌓˂̣̣̥ ) ${NC}\n"
	@sleep 0.5
	@echo "\n ${CYAN}╭∩╮( •̀_•́ )╭∩╮${NC}\n"
	@sleep 0.5
	@echo "\n ${PURPLE}   (ﾉಥ益ಥ) ${NC}\n"
	@sleep 0.5
	@echo "\n ${YELLOW}   ᶠᶸᶜᵏᵧₒᵤ!${NC}\n"
	@sleep 0.5

.PHONY: all clean fclean test re
