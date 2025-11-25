# Source and include directories
SRC = core
INCLUDE_DIR = $(SRC)/include

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -lm
IFLAGS = -I$(INCLUDE_DIR)

EXE = game

# Source files
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)


ifeq ($(OS),Windows_NT)
    RM = del /Q
else
    RM = rm -f
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
	-$(RM) core/*.o core/*.obj core/*.d *.exe *.exe.manifest 2>nul || \
	del /Q /F core\*.o core\*.obj core\*.d *.exe *.exe.manifest >nul 2>&1 || \
	cmd /C exit 0

# Phony targets
.PHONY: all clean
