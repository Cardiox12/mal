CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++20 -Ilibs

STEP_0 = step0_repl.cpp
STEP_0_RULE = step0_repl

all: $(STEP_0_RULE)

$(STEP_0_RULE): $(STEP_0)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(STEP_0_RULE)

fclean: clean
	rm -f .history.txt

re: clean all
