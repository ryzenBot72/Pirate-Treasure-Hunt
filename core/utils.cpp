#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void clear_input_buffer() {
    char ch;
    while((ch = getchar()) != '\n' && ch != EOF) {}
}


// Function to get a character from the user in canonical mode;
void set_raw_input_mode() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);  // Get current terminal settings;
    newt = oldt;  // Copy settings;
    newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo; result is that single key input is read instantly, and input characters won't be displayed on the screen;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Set the new settings;
}


// Function to reset the terminal setting to accept input in non-canonical mode;
void reset_input_mode() {
    struct termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    oldt.c_lflag |= (ICANON | ECHO); // Enable canonical mode and echo;
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
