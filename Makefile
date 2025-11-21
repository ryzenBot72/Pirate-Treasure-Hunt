# Source and include directories
SRC = core
INCLUDE_DIR = $(SRC)/include

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g -lm
IFLAGS = -I$(INCLUDE_DIR)

# Source files
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)


ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXE = game
	CLEAN_CMD = del /q /s /f $(SRC)\*.o

else
    RM = rm -f
    EXE = game
	CLEAN_CMD = $(RM) $(SRC)/*.o $(EXE)
endif


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
	-$(CLEAN_CMD)

# Phony targets
.PHONY: all clean
