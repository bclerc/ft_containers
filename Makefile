
NAME = containers
PROJECT_NAME = ft_containers

SOURCES_FOLDER = ./
INCLUDES_FOLDER = includes

OBJECTS_FOLDER = ./

LIBS =
PURPLE = \033[1;35m
CYAN = \033[1;36m
GREEN = \033[1;32m

SOURCES =	srcs/main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

FSANITIZE = -fsanitize=address 
CFLAGS = --std=c++98 -g3 -Werror -Wall -Wextra
.PHONY: all re clean fclean libft force doclean

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBS)
	@c++ $(CFLAGS) -o $(NAME) $(OBJECTS) -L$(INCLUDES_FOLDER)
	@printf "$(PURPLE)$(NAME) $(CYAN)successfully compiled. $(GREEN)✓$(CYAN)\n"
force: $(OBJECTS)
	@printf "$(CYAN) All objectsfor $(PURPLE)$(PROJECT_NAME)$(CYAN) where successfully created.\n"
	@c++ $(CFLAGS) -o $(NAME) $(OBJECTS) -g
	@printf "$(PURPLE)$(NAME)$(CYAN) successfully compiled. $(CGREEN)✓$(CYAN)\n"

%.o: %.cpp
	@c++ $(CFLAGS) -I$(INCLUDES_FOLDER) -c $< -o $@ -Iinclude
	@printf "$(CYAN)Creating $(PURPLE)%-40s$(GREEN) ✓$(CYAN)\r" "$@"

clean:
	@rm -f $(OBJECTS)
	@printf "$(PURPLE)$(PROJECT_NAME) $(CYAN)Removed all objects.\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(PURPLE)$(PROJECT_NAME) $(CYAN)Removed $(PURPLE)$(NAME)$(CYAN).\n"

doclean: all clean

re: fclean all