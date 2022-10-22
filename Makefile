NAME = minirt

SRCS_PATH = srcs/

GET_NEXT_LINE_PATH = ./includes/get_next_line/

SRCS =	main.c \
		draw.c \
		vector.c \
		hooks.c \
		intersect.c \
		color.c \
		shadow.c \
		parser.c \
		parser_scene.c \
		ft_stof.c \
		parser_figures.c \
		utils.c \

GET_NEXT_LINE_SRCS =	get_next_line.c \
						get_next_line_utils.c \

BREWU = /Users/${USER}/.brew/

BREW = .brew

HOMEBREW = "~/.brewconfig.zsh"

LIBFT = ${LIBFT_PATH}libft.a

MLX = $(MLX_PATH)libmlx.a

OBJS_PATH = objs

OBJS = $(patsubst $(SRCS_PATH)/%.c, $(OBJS_PATH)/%.o, $(addprefix $(SRCS_PATH), $(SRCS)))

OBJS_GNL = $(patsubst %.c, %.o, $(GET_NEXT_LINE_SRCS))

LIBFT_PATH	= ./includes/libft/

MLX_PATH = ./minilibx/

RED = \033[1;31m

GREEN = \033[1;32m

YELL = \033[1;33m

BLUE = \033[1;34m

WHITE = \033[0m

CC		=		gcc

CFLAGS	=		-Wall -Wextra -Werror -D BUFFER_SIZE=1

#MLXFLAGS =		$(MLX) -framework Cocoa -framework OpenGL -framework IOKit
MLXFLAGS =		-framework Cocoa -framework OpenGL -framework IOKit

all:	obj $(NAME)

${LIBFT}:
	@make -C $(LIBFT_PATH)

mlx:
	@make -C $(MLX_PATH)

obj:
	@mkdir -p $(OBJS_PATH)

$(NAME): ${LIBFT} $(OBJS)
	$(CC) $(CFLAGS) -c $(addprefix $(GET_NEXT_LINE_PATH), $(GET_NEXT_LINE_SRCS)) $(addprefix $(SRCS_PATH), $(SRCS))
	@mv *.o $(OBJS_PATH)
#	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(addprefix $(GET_NEXT_LINE_PATH), $(GET_NEXT_LINE_SRCS)) ${LIBFT_PATH}libft.a -o $(NAME) -I $(MLX_PATH)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(addprefix $(GET_NEXT_LINE_PATH), $(GET_NEXT_LINE_SRCS)) ${LIBFT_PATH}libft.a -o $(NAME) ./MLX42/libmlx42.a -I include -lglfw -L "/Users/jmehlig/.brew/opt/glfw/lib/"
#	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(addprefix $(GET_NEXT_LINE_PATH), $(GET_NEXT_LINE_SRCS)) ${LIBFT_PATH}libft.a -o $(NAME)


install:
	@if [ -f $(BREWU) ];then \
		brew install glfw; \
		echo "$(GREEN)Brew is already installed.\n$(WHITE)";else \
		echo "$(YELL)Installing Brew:\n$(WHITE)"; \
		curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh; \
		brew install glfw; \
		touch $(BREW); \
		echo "$(GREEN)Brew is now installed.\n$(WHITE)"; \
	fi;

clean:
			make clean -C $(LIBFT_PATH)
			rm -rf $(OBJS_PATH)
			rm .brew

fclean_libft:
			make fclean -C $(LIBFT_PATH)


fclean:		clean fclean_libft
			$(RM) $(NAME)

re:			fclean
			$(MAKE)

.PHONY:	target_libft