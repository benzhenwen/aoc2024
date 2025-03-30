#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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

    
    int left_points[input_size];
    int right_points[input_size];

    for (int i = 0; i < input_size; i++) {
        left_points[i] = lowest_val(left_data);
        right_points[i] = lowest_val(right_data);
    }

    free(left_data);
    free(right_data);

    int total_distance = 0;
    for (int i = 0; i < input_size; i++) {

        total_distance += abs(left_points[i] - right_points[i]);

    }

    printf("%d", total_distance);
    printf("\n");
    return 0;
}


int lowest_val(int * data) {
    int val = 100000;
    int index = -1;
    for (int i = 0; i < input_size; i++) {
        if (data[i] < val) {
            val = data[i];
            index = i;
        }
    }

    data[index] = 999999; // ignore for future calls

    return val;
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