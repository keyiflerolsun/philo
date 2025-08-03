CFILES = atoi.c \
		 init.c \
		 utils.c \
		 routine.c \
		 main.c

OBJDIR = obj
OFILES = $(addprefix $(OBJDIR)/, $(CFILES:.c=.o))

NAME   = philo
CC     = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -fsanitize=thread

GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;36m
RED     = \033[0;31m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
RESET   = \033[0m

all: $(NAME)

$(NAME): $(OFILES) $(SRC)
	@printf "$(GREEN)» 📦 Linking   $(RESET)» $(MAGENTA)./$(NAME)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OFILES) $(SRC) -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@printf "$(BLUE)» ⚙️  Compiling $(RESET)» $(YELLOW)%9s$(RESET) | $(GREEN)%s$(RESET)\n" "$<" "$@"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(RED)» 🧹 Cleaning  $(RESET)» $(CYAN)./$(OBJDIR) $(RESET)\n"
	@rm -rf $(OBJDIR)

fclean: clean
	@printf "$(RED)» 🔥 Removing  $(RESET)» $(MAGENTA)./$(NAME)$(RESET)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
