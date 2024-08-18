# Compiler
CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++11 -Iinclude 

LDFLAGS = -lssl -lcrypto

SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/configparser.cpp $(SRC_DIR)/setup.cpp \
      $(SRC_DIR)/pihole.cpp $(SRC_DIR)/packages.cpp $(SRC_DIR)/unbound.cpp 

OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

TARGET = main

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)  # Create build directory if it doesn't exist
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

.PHONY: clean
