# The C++ compiler
CC = g++

# Compiler flags:
# -std=c++11: Use the C++11 standard
# -Wall: Show all warnings (good practice)
# -g: Include debug symbols
CFLAGS = -std=c++11 -Wall -g

# List of all .o (object) files needed
OBJS = main.o MemberA_Player.o MemberB_Map.o MemberC_Clues.o MemberD_Engine.o

# The name of our final executable
TARGET = TreasureHuntGame

# The default rule: "make all" or just "make"
all: $(TARGET)

# Rule to link all .o files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile main.cpp into main.o
main.o: main.cpp MemberD_Engine.h
	$(CC) $(CFLAGS) -c main.cpp

# Rule to compile MemberA_Player.cpp into MemberA_Player.o
MemberA_Player.o: MemberA_Player.cpp MemberA_Player.h
	$(CC) $(CFLAGS) -c MemberA_Player.cpp

# Rule to compile MemberB_Map.cpp into MemberB_Map.o
MemberB_Map.o: MemberB_Map.cpp MemberB_Map.h
	$(CC) $(CFLAGS) -c MemberB_Map.cpp

# Rule to compile MemberC_Clues.cpp into MemberC_Clues.o
MemberC_Clues.o: MemberC_Clues.cpp MemberC_Clues.h
	$(CC) $(CFLAGS) -c MemberC_Clues.cpp

# Rule to compile MemberD_Engine.cpp into MemberD_Engine.o
MemberD_Engine.o: MemberD_Engine.cpp MemberD_Engine.h MemberA_Player.h MemberB_Map.h MemberC_Clues.h
	$(CC) $(CFLAGS) -c MemberD_Engine.cpp

# Rule to clean up build files
clean:
	rm -f *.o $(TARGET) $(TARGET).exe