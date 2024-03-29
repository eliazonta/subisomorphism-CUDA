#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// too messy, more work needed :/


// Header for row col val format 
void read_matrix(int **row_ptr, int **col_ind, float **values, const char *filename, int *num_rows, int *num_cols, int *num_vals)

//void read_matrix(int **row_ptr, int **col_ind, const char *filename, int *num_rows, int *num_cols, int *num_vals)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stdout, "File cannot be opened!\n");
        exit(0);
    }
    
    // Get number of rows, columns, and non-zero values
    fscanf(file, "%d %d %d\n", num_rows, num_cols, num_vals);
    
    int *row_ptr_t = (int *) malloc((*num_rows + 1) * sizeof(int));
    int *col_ind_t = (int *) malloc(*num_vals * sizeof(int));
    float *values_t = (float *) malloc(*num_vals * sizeof(float));
    
    // Collect occurances of each row for determining the indices of row_ptr
    int *row_occurances = (int *) malloc(*num_rows * sizeof(int));
    for (int i = 0; i < *num_rows; i++) {
        row_occurances[i] = 0;
    }
    
    int row, column;

    // UNCOMMENT FOR FORMAT : ROW COL VAL
    float value;
    while (fscanf(file, "%d %d %f\n", &row, &column, &value) != EOF) {
        // Subtract 1 from row and column indices to match C format
        row--;
        column--;
        row_occurances[row]++;
    }

    // FORMAT : ROW COL 
    // while (fscanf(file, "%d %d \n", &row, &column) != EOF) {
    //     // Subtract 1 from row and column indices to match C format
    //     row--;
    //     column--;
    //     row_occurances[row]++;
    // }
    
    // Set row_ptr
    int index = 0;
    for (int i = 0; i < *num_rows; i++) {
        row_ptr_t[i] = index;
        index += row_occurances[i];
    }
    row_ptr_t[*num_rows] = *num_vals;
    free(row_occurances);
    
    // Set the file position to the beginning of the file
    rewind(file);
    
    // Read the file again, save column indices and values
    for (int i = 0; i < *num_vals; i++) {
        col_ind_t[i] = -1;
    }
    fscanf(file, "%d %d %d\n", num_rows, num_cols, num_vals);
    int i = 0;
    while (fscanf(file, "%d %d %f\n", &row, &column, &value) != EOF) {
        row--;
        column--;
        
        // Find the correct index (i + row_ptr_t[row]) using both row information and an index i
        while (col_ind_t[i + row_ptr_t[row]] != -1) {
            i++;
        }
        col_ind_t[i + row_ptr_t[row]] = column;
        // UNCOMMENT FOR FORMAT : ROW COL VAL 
        values_t[i + row_ptr_t[row]] = value;
        i = 0;
    }
    
    
    fclose(file);
    
    *row_ptr = row_ptr_t;
    *col_ind = col_ind_t;
    // UNCOMMENT FOR FORMAT : ROW COL VAL 
    *values = values_t;
}

#endif