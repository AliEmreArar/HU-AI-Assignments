# Compiler and flags
CXX = g++
CXXFLAGS = -g -std=c++11

# Project name
TARGET = clearvision

# Source and header files
SOURCES = main.cpp SecretImage.cpp GrayscaleImage.cpp Filter.cpp Crypto.cpp
HEADERS = SecretImage.h GrayscaleImage.h Filter.h stb_image.h stb_image_write.h Crypto.h

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default rule to build the project
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Rule to compile source files into object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
