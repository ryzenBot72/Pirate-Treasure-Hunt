//Program to display all the ANSI 256-colors

#include <stdio.h>

void color_print(int n, int mode) { // mode = 0(light text); mode = 1(dark text);
    if(mode == 1) {
        printf("\x1b[38;5;238m");   // for dark(238) text color;
    }
    printf("\x1b[48;5;%dm", n);     // \x1b[48;5;<n>m; sets the text background as per the value of n;
                                    
    printf("%4d", n);               //printing the actual number associated to the color; '5' in %5d sets the character field width to 5 units, basically sets the width of the color box;

    //printf("%5c", ' ');           //if you don't want the numbers to be printed for each color, then uncomment this command and comment-out the above one;

    printf("\x1b[0m");              // reseting all the attributes to default value; (!important)
}

int main() {
    int n = 0;
    printf("\n");

    //printing the 0-15 colors (0-7 : standard; 8-15 : bright)
    for(int i = 0; i < 16; i++) {
        color_print(n++, 1);
        if(n == 8)
            printf("\n");
    }
    printf("\n\n");

    //printing the 16-231 colors
    for(int i = 0; i < 36; i++) {
        for(int j = 0; j < 6; j++) {
            color_print(n++, 1);
        }
        printf("\n");
    }
    printf("\n");

    //printing the 232-255 colors (grayscale colors)
    for(int i = 0; i < 24; i++) {
        if(i < 12)
            color_print(n++, 0);
        else
            color_print(n++, 1);
    }
    printf("\n\n");

    return 0;
}
