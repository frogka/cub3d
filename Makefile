# Nom du projet
NAME = cub3d

# Fichiers sources
SRCS = cub3d.c

# Compilateur
CC = cc

# Couleurs pour afficher les messages
RED = \033[31m
GREEN = \033[32m
CYAN = \033[36m
RESET = \033[0m

# Flags
CFLAGS = -Wall -Wextra -Werror -g

# Fichiers objets générés
OBJS = $(SRCS:.c=.o)

# Répertoires des bibliothèques
LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux

# Fichiers des bibliothèques
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a


# Règle par défaut pour créer le programme final
$(NAME): $(MLX_LIB) $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -lm -lXext -lX11 -o $@ $(OBJS) $(LIBFT) $(MLX_LIB)

# Règle pour compiler la MiniLibX
$(MLX_LIB):
	@echo "$(GREEN)Compilation de la MiniLibX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) --silent

# Règle pour compiler la Libft
$(LIBFT):
	@echo "$(GREEN)Compilation de la Libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --silent

# Règle générique pour compiler les fichiers .c en .o
%.o: %.c
	@echo "$(GREEN)Compilation de $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ -I .

# Règle par défaut pour compiler le programme
all: $(NAME)

# Nettoyage des fichiers objets
clean:
	@echo "$(RED)Nettoyage des objets...$(RESET)"
	@$(MAKE) clean -C $(LIBFT_DIR) --silent
	@$(MAKE) clean -C $(MLX_DIR) --silent
	@rm -f $(OBJS)

# Nettoyage complet (objets + programme)
fclean: clean
	@echo "$(RED)Nettoyage complet...$(RESET)"
	@$(MAKE) fclean -C $(LIBFT_DIR) --silent
	@$(MAKE) fclean -C $(MLX_DIR) --silent	
	@rm -f $(NAME)

# Règle pour tout refaire (nettoyage complet + recompilation)
re: fclean all

# Déclaration des cibles sans fichiers associés
.PHONY: all clean fclean re
