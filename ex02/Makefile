NAME = PmergeMe

SRC = main.cpp PmergeMe.cpp
DEP = PmergeMe.hpp

CXX = c++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRC) $(DEP)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all