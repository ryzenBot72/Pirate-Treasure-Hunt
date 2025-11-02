# Output executable name
EXE = game

# Source and include directories
SRC = core
INCLUDE_DIR = $(SRC)/include

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g
IFLAGS = -I$(INCLUDE_DIR)

# Source files
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(EXE)

# Link object files to create executable
$(EXE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE)

# Compile .cpp to .o (automatic dependency on corresponding header if #include'd)
$(SRC)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(SRC)/*.o $(EXE)

# Phony targets
.PHONY: all clean
