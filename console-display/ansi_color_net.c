//Program to print the ANSI-256 colors in a cube-net format

#include <stdio.h>

void color_print(int n, int mode) { // mode = 0(light text); mode = 1(dark text);
     printf("\x1b[48;5;%dm", n);     // \x1b[48;5;<n>m; sets the text background as per the value of n;
    
    if(mode == 0) {
        printf("\x1b[38;5;253m");
    }
    if(mode == 1) {
        printf("\x1b[38;5;238m");   // for dark(238) text color;
    }
                                    
    printf("%4d", n);               //printing the actual number associated to the color; '5' in %5d sets the character field width to 5 units, basically sets the width of the color box;

//    printf("%4c", ' ');           //if you don't want the numbers to be printed for each color, then uncomment this command and comment-out the above one;

    printf("\x1b[0m");              // reseting all the attributes to default value; (!important)
}


int main() {
    int n = 16, k = 1, c;

    printf("\n");

    //printing the 0-15 colors (0-7 : standard; 8-15 : bright)
    for(int i = 0; i < 16; i++) {
        color_print(c++, 1);
        if(c == 8)
            printf("\n");
    }
    printf("\n\n");
 
    //-------printing the net of the color cube----------------
    c = n;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            printf("%4c", ' ');
        }
        for(int j = 0; j < 6; j++) {
            color_print(c, 1);
            c++;
        }
        printf("\n");
    }

    c = n;
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 5; j++) {
            color_print(c, 1);
            c += k * 6;
        }
        for(int j = 0; j < 5; j++) {
            color_print(c, 1);
            c += k;
        }
        k = -k;
        if(k == 1) {
            color_print(c, 1);
            printf("\n");
            c += 36;
        }
    }

    c = 220;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            printf("%4c", ' ');
        }
        for(int j = 0; j < 6; j++) {
            color_print(c, 1);
            c++;
        }
        c -= 12;
        printf("\n");
    }
    printf("\n");
    //-------------------------------------------------
    
    c = 232;
    //printing the 232-255 colors (grayscale colors)
    for(int i = 0; i < 24; i++) {
        if(i < 12)
            color_print(c++, 0);
        else
            color_print(c++, 1);
    }
    printf("\n\n");

    return 0;
}
