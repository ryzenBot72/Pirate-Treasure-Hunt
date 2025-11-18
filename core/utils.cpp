#ifndef UTILS_H
#define UTILS_H

//manually defining the flag as per its bit position (because it is apparently not already defined in windows.h)
#ifndef ENABLE_VIRTUAL_TERMINAL_INPUT
#define ENABLE_VIRTUAL_TERMINAL_INPUT 0x0200
#endif

//headers and global variables
#include <stdio.h>

#if defined(_WIN32)
    #include <windows.h>
    #include "render.hpp"
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD original_mode;
#else
    #include <termios.h>
    #include <unistd.h>
#endif



// Function to get a character from the user in canonical mode;
void set_raw_input_mode() {
    #if defined(_WIN32)
        GetConsoleMode(hStdin, &original_mode);
        DWORD mode = original_mode;

        mode |= ENABLE_VIRTUAL_TERMINAL_INPUT;
        mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);

        SetConsoleMode(hStdin, mode);
        fflush(stdout);

    #else
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);          // Get current terminal settings;
        newt = oldt;                             // Copy settings;
        newt.c_lflag &= ~(ICANON | ECHO);        // Disable canonical mode and echo; result is that single key input is read instantly, and input characters won't be displayed on the screen;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Set the new settings;
    #endif

    setvbuf(stdout, NULL, _IOLBF, (40 * (DISPLAY_X * DISPLAY_Y + TEXT_X * TEXT_Y))); //actual size of each box(pixel) is 18 bytes, but added 2 more bytes for safety and for the newline characters at the end of each line
    setvbuf(stderr, NULL, _IOLBF, (40 * (DISPLAY_X * DISPLAY_Y + TEXT_X * TEXT_Y)));
}



// Function to reset the terminal setting to accept input in non-canonical mode;
void reset_input_mode() {
    #if defined(_WIN32)
        SetConsoleMode(hStdin, original_mode);
    #else
        struct termios oldt;
        tcgetattr(STDIN_FILENO, &oldt);
        oldt.c_lflag |= (ICANON | ECHO); // Enable canonical mode and echo;
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    #endif

    setvbuf(stdout, NULL, _IOFBF, 4096);
}


void clear_input_buffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

#endif