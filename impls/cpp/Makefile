CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++20 -Ilibs -Iincludes

STEP_0 = step0_repl.cpp
STEP_0_RULE = step0_repl

STEP_1 =  main.cpp src/reader.cpp
STEP_1_RULE = step1_read_print

all: $(STEP_0_RULE) $(STEP_1_RULE)

$(STEP_0_RULE): $(STEP_0)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(STEP_1_RULE): $(STEP_1)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(STEP_0_RULE)
	rm -f $(STEP_1_RULE)

fclean: clean
	rm -f .history.txt

re: clean all
