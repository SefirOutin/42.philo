SRCS_DIR	=	srcs
OBJS_DIR	=	objs
HEADER		=	include/

NAME 		=	philo

SRCS		=	srcs/main.c \
				srcs/utils.c

OBJS		=	$(SRCS:$(SRCS)/%.c=$(OBJS_DIR)/%.o)

CPPFLAGS	=	-I $(HEADER)
CFLAGS		=	-Wall -Werror -Werror -g3 -O3 -pthread

$(NAME):		$(OBJS) $(HEADER)
					cc $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)

# $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
# 	cc $(CPPFLAGS) $(CFLAGS) -c $< -o $@

all:			$(NAME)

clean:
					rm -f objs

fclean:			clean
					rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re