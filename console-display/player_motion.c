// Program to take user input(arrow key strokes) using non-canonical input mode of terminal, and updating the matrix accordingly.

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

#define SIZE 20

// Function to get a character from the user without pressing Enter
char getKey() {
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);  // Get current terminal settings
    newt = oldt;  // Copy settings
    newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo; result is that single key input is read instantly, and input characters won't be displayed on the screen
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Set new settings

    ch = getchar();  // Read the character

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore old settings

    return ch;
}

// Function to print the matrix
void printMatrix(int x, int y) {
    system("clear");  // Clears the screen (for Linux/macOS)

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == y && j == x) {
                printf("%3c", 'O');  // Print 'O' at the current position
            } else {
                printf("%3c", '.');  // . for representing empty space
            }
        }
        printf("\n");
    }
}

int main() {
    int x = SIZE / 2;  // Starting position (middle of the matrix)
    int y = SIZE / 2;  // Starting position (middle of the matrix)
    char ch, arrow;

    // Initially print the matrix
    printMatrix(x, y);

    while (1) {
        ch = getKey();  // Get a key press

        if (ch == 27) {  // Escape sequence (for arrow keys)
            arrow = getKey();  // Get the next character in the sequence (arrow key)
            if (arrow == '[') {
                arrow = getKey();  // Get the actual arrow key code

                switch (arrow) {
                    case 'A':   //Up Arrow
                        if (y > 0) y--;
                        break;
                    case 'B':   //Down Arrow
                        if (y < SIZE - 1) y++;
                        break;
                    case 'C':   //Right Arrow
                        if (x < SIZE - 1) x++;
                        break;
                    case 'D':   //Left Arrow
                        if (x > 0) x--;
                        break;
                }
            }
        }

        // Exit condition (press 'e' to exit)
        if (ch == 'e' || ch == 'E') {
            break;
        }

        // Reprint the matrix after every move
        printMatrix(x, y);
    }

    printf("Game Over!\n");
    return 0;
}

