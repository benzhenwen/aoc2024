#include <stdio.h>
#include <string.h>
#include <stdlib.h>


const int input_size = 1000;

int first_index_of(char * input, char to_find, int start_index, int end_index) {
    for (int i = start_index; i < end_index; i++) {
        if (input[i] == to_find) {
            return i;
        }
    }
    return -1;
}

int abs(int input) {
    if (input >= 0) return input;
    return -input;
}

void print_list(int * list, int list_size) {
    printf("[");
    for (int i = 0; i < list_size; i++) {
        printf("%d", list[i]);
        if (i+1 < list_size) printf(", ");
    }
    printf("]\n");
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[128];
    int line_index = 0;

    int total_safe = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        int start_index = 0;

        int prev_val = -1;
        int prev_step = -9999;
        int is_safe = 1; // bool

        while(start_index < strlen(line)) {
            int end_index = first_index_of(line, ' ', start_index+1, strlen(line));
            if (end_index == -1) end_index = strlen(line);

            char buffer[32];
            int length = end_index - start_index;
            strncpy(buffer, &line[start_index], length);
            buffer[length] = '\0';  // null-terminate the string

            int val = strtol(buffer, NULL, 10);
            
            // printf("v: %d - ", val);

            // process val
            if (start_index != 0) {
                int step = prev_val - val;

                // printf("s: %d\n", step);

                if (abs(step) < 1 || abs(step) > 3) {
                    is_safe = 0;
                    break;
                }

                if (prev_step != -9999) {
                    if ((step > 0) != (prev_step > 0)) {
                        is_safe = 0;
                        break;
                    }
                }

                prev_step = step;
            }

            prev_val = val;
            
            start_index = end_index + 1;
        }

        // printf("%s -> %d\n\n", line, is_safe);

        if (is_safe) total_safe++;
    }

    printf("output: %d\n", total_safe);

    fclose(file);    
    
    return 0;
}