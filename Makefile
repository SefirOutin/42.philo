SRCS_DIR	=	srcs
OBJS_DIR	=	objs
HEADER		=	include/

NAME 		=	philo

SRCS		=	srcs/main.c srcs/utils.c srcs/init.c srcs/actions_functions.c srcs/monitoring.c

OBJS		=	$(SRCS:$(SRCS)/%.c=$(OBJS_DIR)/%.o)

CPPFLAGS	=	-I $(HEADER)
CFLAGS		=	-Wall -Werror -Werror -g3 -O3 -pthread #-fsanitize=thread #-ltsan #TSAN_OPTIONS=second_deadlock_stack=1 

$(NAME):		$(OBJS) $(HEADER)
					clang $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)

# $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
# 	cc $(CPPFLAGS) $(CFLAGS) -c $< -o $@

all:			$(NAME)

clean:
					rm -f objs

fclean:			clean
					rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re