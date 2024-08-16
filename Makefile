# Compiler
CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++11 -Iinclude

SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/configparser.cpp $(SRC_DIR)/setup.cpp $(SRC_DIR)/packages.cpp

OBJ = $(BUILD_DIR)/main.o $(BUILD_DIR)/configparser.o $(BUILD_DIR)/setup.o $(SRC_DIR)/packages.o

TARGET = main

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)  # Create build directory if it doesn't exist
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

.PHONY: clean
