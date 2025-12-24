# Nom du projet
NAME = cub3d

# Fichiers sources
SRCS = src/cub3d.c \
       src/map.c \
       src/player.c \
	   src/hook.c \
	   src/move.c \
	   src/minimap.c \
	   raycasting/render.c \
	   raycasting/dda.c \
	   src/textures.c \
	   src/init.c \

# Compilateur
CC = cc

# Couleurs pour afficher les messages
RED = \033[31m
GREEN = \033[32m
CYAN = \033[36m
RESET = \033[0m

# Flags
CFLAGS = -Wall -Wextra -Werror -g

# Dossier pour les .o
OBJ_DIR = obj

# Fichiers objets générés
OBJS = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Répertoires des bibliothèques
LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux

# Fichiers des bibliothèques
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

# --- Règles principales ---

all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT) $(OBJS)
	@echo "$(CYAN)Édition des liens...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) -lm -lXext -lX11 -o $(NAME)
	@echo "$(GREEN)✅ Compilation terminée !$(RESET)"

# Règle pour compiler la MiniLibX
$(MLX_LIB):
	@echo "$(GREEN)🔨 Compilation de la MiniLibX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) -s

# Règle pour compiler la Libft
$(LIBFT):
	@echo "$(GREEN)🔨 Compilation de la Libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) -s

# Crée le dossier obj si nécessaire
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compilation des .c en .o
$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@echo "$(GREEN)🔨 Compilation de $<...$(RESET)"
	@$(CC) $(CFLAGS) -I. -c $< -o $@

# Nettoyage des objets
clean:
	@echo "$(RED)🗑️  Nettoyage des objets...$(RESET)"
	@$(MAKE) clean -C $(LIBFT_DIR) -s
	@$(MAKE) clean -C $(MLX_DIR) -s
	@rm -rf $(OBJ_DIR)

# Nettoyage complet
fclean: clean
	@echo "$(RED)🗑️  Nettoyage complet...$(RESET)"
	@$(MAKE) fclean -C $(MLX_DIR) -s
	@$(MAKE) fclean -C $(LIBFT_DIR) -s
	@rm -f $(NAME)

# Recompile tout
re: fclean all

.PHONY: all clean fclean re minilibx
