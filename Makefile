CXXFLAGS ?= -std=c++17 -Wall -Wextra -Werror

.PHONY: test
test: build/test_math_utils
	./build/test_math_utils

build/test_math_utils: test/unit/test_math_utils.cpp src/math_utils.h
	mkdir -p build
	$(CXX) $(CXXFLAGS) $< -o $@
