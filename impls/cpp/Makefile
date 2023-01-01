CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++20 -Ilibs -Iincludes -fsanitize=address

STEP_0 = step0_repl.cpp
STEP_0_RULE = step0_repl

SRCS =	src/tokenizer.cpp\
		src/reader.cpp\
		src/types.cpp\
		src/printer.cpp

STEP_1 =	step1_read_print.cpp $(SRCS)
STEP_1_RULE = step1_read_print
STEP_1_RULE_DEBUG = _step1_read_print

STEP_2 = step2_eval.cpp $(SRCS)
STEP_2_RULE = step2_eval

all: $(STEP_0_RULE) $(STEP_1_RULE)

$(STEP_0_RULE): $(STEP_0)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(STEP_1_RULE): $(STEP_1)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(STEP_1_RULE_DEBUG): $(STEP_1)
	$(CXX) $(CXXFLAGS) -DDEBUG -o $(STEP_1_RULE) $^

$(STEP_2_RULE): $(STEP_2)
	$(CXX) $(CXXFLAGS) -o $(STEP_2_RULE) $^

clean:
	@# Remove executables
	rm -f $(STEP_0_RULE)
	rm -f $(STEP_1_RULE)
	rm -f $(STEP_2_RULE)
	@# Remove debug symbols
	rm -rf $(STEP_0_RULE).dSYM
	rm -rf $(STEP_1_RULE).dSYM
	rm -rf $(STEP_2_RULE).dSYM

fclean: clean
	rm -f .history.txt

re: clean all
