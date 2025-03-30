#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct pointThing {
    int val;
    int count;
};


const int input_size = 1000;

int main() {

    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int count = 0;
    
    int * left_data = malloc(sizeof(int) * input_size);
    int * right_data = malloc(sizeof(int) * input_size);

    char line[32];
    while (fgets(line, sizeof(line), file) != NULL) {
        char first_digit[8];
        memcpy(first_digit, line, 5);
        left_data[count] = strtol(first_digit, first_digit[5], 10);
        
        char second_digit[8];
        memcpy(second_digit, line+8, 5);

        right_data[count] = strtol(second_digit, second_digit[5], 10);

        count++;
    }
    fclose(file);

    int total_similarity = 0;
    for (int i = 0; i < input_size; i++) {
        int cnt = 0;
        for (int j = 0; j < input_size; j++) {
            if (right_data[j] == left_data[i]) {
                cnt++;
            }
        }
        total_similarity += left_data[i] * cnt;
    }

    free(left_data);
    free(right_data);

    printf("%d", total_similarity);
    printf("\n");
    return 0;
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