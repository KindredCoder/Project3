# Compiler
CXX := clang++

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic

# Target executable
TARGET := main

# Source files (all .cpp files in the current directory)
SRCS := $(wildcard *.cpp)

# Object files (corresponding .o files)
OBJS := $(SRCS:.cpp=.o)

# Default rule
all: $(TARGET)

# Linking the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compiling each .cpp file to a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (targets that aren't actually files)
.PHONY: all clean