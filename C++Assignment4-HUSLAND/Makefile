

# Compiler and flags
CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -Iinclude
OBJ_DIR = obj
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include

SOURCES = 
HEADERS = $(wildcard *.h)

# List all source files
SRCS = $(wildcard *.cpp) 

# Convert each source file into a corresponding object file in the obj/ directory
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Target executable
TARGET = $(BIN_DIR)/HUSLAND

# Ensure directories exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

all: $(TARGET)

# Main build rule
$(TARGET): $(BIN_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp files into .o files in obj/ directory
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile main.cpp separately
$(OBJ_DIR)/main.o: main.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(OBJ_DIR)/main.o

# Clean rule to remove generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run:
	./bin/HUSLAND io/initial_world.txt io/initial_realm_shapers.txt io/access.log io/duels.log io/current_isles.txt io/current_map.txt io/current_realm_shapers.txt io/current_shaper_tree.txt

mem: all
	valgrind --leak-check=full --track-origins=yes ./bin/HUSLAND io/initial_world.txt io/initial_realm_shapers.txt io/access.log io/duels.log io/current_isles.txt io/current_map.txt io/current_realm_shapers.txt io/current_shaper_tree.txt

.PHONY: clean
