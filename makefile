# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

# Raylib link flags (adjust path if needed)
LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm

# Source and output
SRC = src/main.cpp
OUT = snake

# Default target
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(LDFLAGS)

# Run the game (Windows)
run: $(OUT)
	./$(OUT)

# Clean build files
clean:
	rm -f $(OUT)