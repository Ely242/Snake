# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

# Files
SRC = $(SRC_DIR)/main.cpp
OBJ = $(OBJ_DIR)/main.o
TARGET = $(BIN_DIR)/game.exe

# Default target
all: $(TARGET)

# Compile
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run game
run: all
	./game.exe

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
