/*  Copyright (C) 2018 Federico klez Culloca
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* parrot = "\
       \\[49m\n\
        \\     [38;5;16m▄▄▄[38;5;232m▄[38;5;16m▄▄▄▄\n\
         \\  ▄[48;5;16m [38;5;75m▄[48;5;75m      [48;5;232m▄[48;5;16m▄ [49m[38;5;16m▄\n\
          ▄[48;5;16m [38;5;75m▄[48;5;75m           [48;5;16m [49m[38;5;16m▄\n\
         [48;5;16m [38;5;75m▄[48;5;75m   [48;5;16m [48;5;75m  [38;5;232m▄[48;5;16m[38;5;132m▄▄▄[48;5;75m[38;5;16m▄ [48;5;16m [48;5;75m [48;5;16m [49m\n\
        [48;5;16m [38;5;75m▄[48;5;75m      [48;5;16m [48;5;132m     [48;5;16m [48;5;75m  [48;5;16m▄ [49m[38;5;16m▄\n\
       [48;5;16m [38;5;75m▄[48;5;75m       [48;5;16m [48;5;132m     [48;5;16m [48;5;75m    [48;5;16m [49m\n\
       [48;5;16m [48;5;75m        [48;5;16m [48;5;132m[38;5;233m▄    [48;5;16m [48;5;75m    [48;5;16m [49m\n\
       [48;5;16m [48;5;75m         [48;5;16m [48;5;132m[38;5;232m▄ [38;5;16m▄[48;5;16m [48;5;75m     [48;5;16m [49m\n\
       [48;5;16m  [48;5;75m▄        [48;5;16m[38;5;75m▄ ▄[48;5;75m      [48;5;16m▄▄ [49m[38;5;16m▄\n\
        [48;5;16m  [48;5;75m▄                   [48;5;233m[38;5;75m▄[48;5;16m▄ [49m[38;5;16m▄\n\
        [48;5;16m [48;5;75m [48;5;16m[38;5;75m▄ [48;5;75m[38;5;16m▄▄▄▄                 [48;5;16m[38;5;75m▄▄ [49m[38;5;16m▄\n\
        [48;5;16m [48;5;75m     [48;5;16m[38;5;75m▄▄▄▄[48;5;75m                  [48;5;232m▄[48;5;16m▄ [49m\n\
        [38;5;16m▀[38;5;232m▀▀▀[38;5;16m▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n\
\n\
        [39m\n";

int charcnt(char* s, char c) {
    int n = 0;
    for(int i = 0; s[i] != 0; i++) {
        if(s[i] == c) n++;
    }
    return n;
}

char* tabstospaces(char* s, int n) {
    int tabscount = charcnt(s, '\t');
    size_t len = strlen(s);
    char *new_s = calloc((1 + len + tabscount * (n - 1)), sizeof(char)); 
    char *new_p = new_s;
    for(;*s != 0;s++) {
        if(*s == '\t') {
            for(int k = 0; k < n; k++) {
                *(new_p++) = ' ';
            }
        } else {
            *(new_p++) = *s;
        }
    }

    return new_s;
}

void printline(int length) {
    putchar('+');
    for(int i = 0; i < length; i++) {
        putchar('-');
    }
    putchar('+');
    putchar('\n');
}

int main(int argc, char** argv) {
    char** message_rows = malloc(sizeof(char*));
    size_t rows = 0;
    int buffer_size = 1;
    int longest_line_size = 0;

    if(argc > 1) {
        *message_rows = calloc(1, sizeof(char));
        for(int i = 1; i < argc; i++) {
            *message_rows = realloc(*message_rows, sizeof(char) * (  strlen(*message_rows)
                                                                   + strlen(*(argv + i))
                                                                   + (i == 1 ? 0 : 1)));
            if(i != 1) {
                *message_rows = strcat(*message_rows, " ");
            }
            *message_rows = strcat(*message_rows, *(argv + i));
        }
        rows = 1;
        longest_line_size = strlen(*message_rows);
    } else {
        size_t line_length = 0;
        ssize_t nread;
        char* line = NULL;
        while((nread = getline(&line, &line_length, stdin)) != -1) {
            if(rows + 1 >= buffer_size) {
                buffer_size *= 2;
                message_rows = realloc(message_rows, sizeof(char*) * buffer_size);
            }
            char *untabbed_line = tabstospaces(line, 4);
            size_t untabbed_line_length = strlen(untabbed_line);
            message_rows[rows] = calloc(1 + untabbed_line_length, sizeof(char));
            strcpy(message_rows[rows], untabbed_line);
            message_rows[rows][strcspn(untabbed_line, "\n")] = 0;
            rows++;
            if(untabbed_line_length > longest_line_size) {
                longest_line_size = untabbed_line_length;
            }
        }
        if (line != NULL) free(line);
    }

    printline(longest_line_size + 2);

    for (size_t i = 0; i < rows; i++) {
        printf("| %s%*s |\n", message_rows[i], longest_line_size - strlen(message_rows[i]), "");
        free(message_rows[i]);
    }

    printline(longest_line_size + 2);

    free(message_rows);

    printf("%s", parrot);

    return 0;
}


