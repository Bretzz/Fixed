
NAME		= Fixed
CXXFLAGS	= -Wall -Werror -Wextra -std=c++98
CXX			= c++

SRC			= main.cpp \
			Fixed.cpp

OBJ_DIR 	= obj/
OBJS 		= $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: %.cpp | $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -c $^ -o $@

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME) $(OBJ_DIR)

re: fclean all

.PHONY: clean fclean re