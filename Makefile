# this Makefile make two exuctable of C++ code with includes folder at ./includes and srcs folder at ./srcs/
# the executable name are containers_ft and containers_std.
# containers_ft compile all obects with flag "-d TESTED_NAMESPECE=ft"
# containers_std compile all obects with flag "-d TESTED_NAMESPECE=std"
EXEC_NAME_FT = containers_ft
EXEC_NAME_STD = containers_std

PROJECT_NAME = ft_containers

SOURCES_FOLDER = ./srcs
INCLUDES_FOLDER = includes/

SOURCES_FILES = ./srcs/main.cpp
OBJECTS_FILES_FT = $(patsubst $(SOURCES_FOLDER)%.cpp, $(OBJECTS_FOLDER)%_ft.o, $(SOURCES_FILES))
OBJECTS_FILES_STD = $(patsubst $(SOURCES_FOLDER)%.cpp, $(OBJECTS_FOLDER)%_std.o, $(SOURCES_FILES))

OBJECTS_FOLDER = ./objs/

INCLUDES_FLAGS = -I $(INCLUDES_FOLDER)

CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(EXEC_NAME_FT) $(EXEC_NAME_STD)

$(EXEC_NAME_FT): $(OBJECTS_FILES_FT)
	@$(CC) $(CFLAGS) $(INCLUDES_FLAGS) $(OBJECTS_FILES_FT) -o $(EXEC_NAME_FT) -D TESTED_NAMESPACE=ft

$(EXEC_NAME_STD): $(OBJECTS_FILES_STD)
	@$(CC) $(CFLAGS) $(INCLUDES_FLAGS) $(OBJECTS_FILES_STD) -o $(EXEC_NAME_STD) -D TESTED_NAMESPACE=std

$(OBJECTS_FOLDER)%_ft.o: $(SOURCES_FOLDER)/%.cpp
	@mkdir -p $(OBJECTS_FOLDER)
	@$(CC) $(CFLAGS) $(INCLUDES_FLAGS) -c $< -o $@ -D TESTED_NAMESPACE=ft

$(OBJECTS_FOLDER)%_std.o: $(SOURCES_FOLDER)/%.cpp
	@mkdir -p $(OBJECTS_FOLDER)
	@$(CC) $(CFLAGS) $(INCLUDES_FLAGS) -c $< -o $@ -D TESTED_NAMESPACE=std
	@echo "Compiling $< \r"

clean:
	@rm -rf $(OBJECTS_FOLDER)

fclean: clean
	@rm -f $(EXEC_NAME_FT)
	@rm -f $(EXEC_NAME_STD)
	@echo "clean"

re: fclean all

.PHONY: all clean fclean re