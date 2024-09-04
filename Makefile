NAME =		ft_ssl

CC =		gcc
CFLAGS =	-Wall -Werror -Wextra -Wunused

FT_PRINTF_FOLDER	=	src/ft_printf
INCLUDES =	-Iinclude -I$(FT_PRINTF_FOLDER)/include

SRCS_DIR =	src
OBJS_DIR =	.objs

SRCS_FILE =	main.c \
			option.c	\
			error.c	\
			display.c	\
			utils.c	\
			md5.c	\
			sha256.c


OBJ_FILE =	$(SRCS_FILE:.c=.o)

SRCS	=	$(addprefix $(SRCS_DIR)/,$(SRCS_FILE))
OBJS	=	$(addprefix $(OBJS_DIR)/,$(OBJ_FILE))

RM		=	rm -f
RMDIR	=	rmdir

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ${FT_PRINTF_FOLDER}
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -L$(FT_PRINTF_FOLDER) -lftprintf -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

clean:
	@make clean -C $(FT_PRINTF_FOLDER)
	@$(RM) $(OBJS)
	@if [ -d "$(OBJS_DIR)" ]; then rmdir $(OBJS_DIR); fi

fclean: clean
	@make fclean -C $(FT_PRINTF_FOLDER)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re