NAME = btc

SRC = main.cpp BitcoinExchange.cpp
DEP = BitcoinExchange.hpp

CXX = c++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRC) $(DEP)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all