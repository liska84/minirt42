NAME = minirt

SRCS_PATH = srcs/

GET_NEXT_LINE_PATH = ./includes/get_next_line/

SRCS =	main.c \
		draw.c \
		vector.c \
		vector2.c \
		hooks.c \
		intersect.c \
		color.c \
		shadow.c \
		parser.c \
		parser_scene.c \
		parser_utils.c \
		parser_figures.c \
		utils.c \
		error.c \

GET_NEXT_LINE_SRCS =	get_next_line.c \
						get_next_line_utils.c \

LIBFT = ${LIBFT_PATH}libft.a

MLX = $(MLX_PATH)libmlx.a

OBJS_PATH = objs

OBJS = $(patsubst $(SRCS_PATH)/%.c, $(OBJS_PATH)/%.o, $(addprefix $(SRCS_PATH), $(SRCS)))

OBJS_GNL = $(patsubst %.c, %.o, $(GET_NEXT_LINE_SRCS))

LIBFT_PATH	= ./includes/libft/

MLX_PATH = ./MLX42/

CC		=		gcc

CFLAGS	=		-Wall -Wextra -Werror -D BUFFER_SIZE=1

#MLXFLAGS =		$(MLX) -framework Cocoa -framework OpenGL -framework IOKit
MLXFLAGS =		-framework Cocoa -framework OpenGL -framework IOKit

all:	obj $(MLX) $(NAME)

${LIBFT}:
	@make -C $(LIBFT_PATH)

$(MLX):
	@make -C $(MLX_PATH)

obj:
	@mkdir -p $(OBJS_PATH)

$(NAME):	${LIBFT} $(OBJS)
	$(CC) $(CFLAGS) -c $(addprefix $(GET_NEXT_LINE_PATH), $(GET_NEXT_LINE_SRCS)) $(addprefix $(SRCS_PATH), $(SRCS))
	@mv *.o $(OBJS_PATH)
#	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(addprefix $(GET_NEXT_LINE_PATH), $(GET_NEXT_LINE_SRCS)) ${LIBFT_PATH}libft.a -o $(NAME) -I $(MLX_PATH)
#	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(addprefix $(GET_NEXT_LINE_PATH), $(GET_NEXT_LINE_SRCS)) ${LIBFT_PATH}libft.a -o $(NAME) ./MLX42/libmlx42.a -I include -lglfw -L "/Users/jmehlig/.brew/opt/glfw/lib/"
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(addprefix $(GET_NEXT_LINE_PATH), $(GET_NEXT_LINE_SRCS)) ${LIBFT_PATH}libft.a -o $(NAME) ./MLX42/libmlx42.a -I include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"
#	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(addprefix $(GET_NEXT_LINE_PATH), $(GET_NEXT_LINE_SRCS)) ${LIBFT_PATH}libft.a -o $(NAME)

$(OBJS_PATH)/%.o:	$(SRCS_PATH)/%.c
	$(CC) $(CFLAGS) -c $(addprefix $(GET_NEXT_LINE_PATH), $(GET_NEXT_LINE_SRCS)) $<

install:
	@if [ -f $(BREWU) ];then \
		brew install glfw; \
		echo "$(GREEN)Brew is already installed.\n$(WHITE)";else \
		echo "$(YELL)Installing Brew:\n$(WHITE)"; \
		curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh; \
		brew install glfw; \
		@mv /Users/${USER}/.brew/opt/glfw/include/GLFW ./MLX42/include
		echo "$(GREEN)Brew is now installed.\n$(WHITE)"; \
	fi;

clean:
			make clean -C $(LIBFT_PATH)
			rm -rf $(OBJS_PATH)

fclean_libft:
			make fclean -C $(LIBFT_PATH)


fclean:		clean fclean_libft
			$(RM) $(NAME)

re:			fclean
			$(MAKE)

.PHONY:	target_libft