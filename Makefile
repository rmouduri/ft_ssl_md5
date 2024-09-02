NAME =		ft_ssl

CC =		gcc
CFLAGS =	-Wall -Werror -Wextra -Wunused

INCLUDES =	-Iinclude

SRCS_DIR =	src
OBJS_DIR =	.objs

SRCS_FILE =	main.c \
			option.c	\
			error.c	\
			utils.c	\
			md5.c

OBJ_FILE =	$(SRCS_FILE:.c=.o)

SRCS	=	$(addprefix $(SRCS_DIR)/,$(SRCS_FILE))
OBJS	=	$(addprefix $(OBJS_DIR)/,$(OBJ_FILE))

RM		=	rm -f
RMDIR	=	rmdir

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
#	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)

clean:
	@$(RM) $(OBJS)
	@if [ -d "$(OBJS_DIR)" ]; then rmdir $(OBJS_DIR); fi

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re