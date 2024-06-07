/**
 * @file binpatcher.c
 * @brief
 *
 * This source file contains the main program for the binpatcher project.
 * binpatcher is a command-line tool for searching and replacing binary blocks in files.
 *
 * This file is part of the binpatcher project.
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Juan José Ponteprino
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @author Juan José Ponteprino
 * @date October 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function prototypes
void print_help();
void replace_block(const char *input_file, const char *output_file, const char *search_block_file, const char *replace_block_file);
unsigned char *load_file(const char *filename, size_t *size);
void save_file(const char *filename, unsigned char *data, size_t size);
unsigned char *find_and_replace(unsigned char *data, size_t data_size, unsigned char *search_block, size_t search_size, unsigned char *replace_block, size_t replace_size);

int main(int argc, char *argv[]) {
    int opt;
    const char *input_file = NULL;
    const char *output_file = NULL;
    const char *search_block_file = NULL;
    const char *replace_block_file = NULL;

    while ((opt = getopt(argc, argv, "hi:o:s:r:")) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                return 0;
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 's':
                search_block_file = optarg;
                break;
            case 'r':
                replace_block_file = optarg;
                break;
            default:
                print_help();
                return 1;
        }
    }

    if (!input_file || !search_block_file || !replace_block_file) {
        print_help();
        return 1;
    }

    if (!output_file) {
        output_file = input_file;
    }

    replace_block(input_file, output_file, search_block_file, replace_block_file);

    return 0;
}

// Print help message
void print_help() {
    printf("Binary Patcher v1.1 - (c) 2024 Juan José Ponteprino (SplinterGU)\n\n");
    printf("Usage: binpatcher -i <input_file> [-o <output_file>] -s <search_block_file> -r <replace_block_file>\n");
    printf("A command-line tool for searching and replacing binary blocks in files.\n\n");
    printf("Options:\n");
    printf("  -h                        Display this help message and exit.\n");
    printf("  -i <input_file>           The path to the input file.\n");
    printf("  -o <output_file>          The path to the output file (optional, defaults to input file).\n");
    printf("  -s <search_block_file>    The path to the binary file containing the block to search for.\n");
    printf("  -r <replace_block_file>   The path to the binary file containing the block to replace with.\n\n");
    printf("This software is provided under the terms of the MIT License.\n");
    printf("You may freely use, modify, and distribute this software, subject\n");
    printf("to the conditions and limitations of the MIT License.\n\n");
    printf("For more details, please see the LICENSE file included with this software.\n\n");
    printf("Report bugs to: splintergu@gmail.com\n");
    printf("Home page: <https://github.com/SplinterGU/binpatcher>\n");
}

// Function to replace a block in the input file and save to the output file
void replace_block(const char *input_file, const char *output_file, const char *search_block_file, const char *replace_block_file) {
    size_t input_size, search_size, replace_size;
    unsigned char *input_data = load_file(input_file, &input_size);
    unsigned char *search_block = load_file(search_block_file, &search_size);
    unsigned char *replace_block = load_file(replace_block_file, &replace_size);

    if (!input_data || !search_block || !replace_block) {
        fprintf(stderr, "Error loading files.\n");
        free(input_data);
        free(search_block);
        free(replace_block);
        return;
    }

    if (search_size != replace_size) {
        fprintf(stderr, "Error: The search block and replace block must be of the same size.\n");
        free(input_data);
        free(search_block);
        free(replace_block);
        return;
    }

    unsigned char *modified_data = find_and_replace(input_data, input_size, search_block, search_size, replace_block, replace_size);

    if (modified_data) {
        save_file(output_file, modified_data, input_size);
        free(modified_data);
        printf("Replacement successful. Output saved to %s\n", output_file);
    } else {
        printf("Search block not found in the input file.\n");
    }

    free(input_data);
    free(search_block);
    free(replace_block);
}

// Function to load a file into a buffer
unsigned char *load_file(const char *filename, size_t *size) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(*size);
    if (!buffer) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, *size, file);
    fclose(file);

    return buffer;
}

// Function to save a buffer to a file
void save_file(const char *filename, unsigned char *data, size_t size) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    fwrite(data, 1, size, file);
    fclose(file);
}

// Function to find and replace a block in the data
unsigned char *find_and_replace(unsigned char *data, size_t data_size, unsigned char *search_block, size_t search_size, unsigned char *replace_block, size_t replace_size) {
    for (size_t i = 0; i <= data_size - search_size; i++) {
        if (memcmp(&data[i], search_block, search_size) == 0) {
            unsigned char *modified_data = (unsigned char *)malloc(data_size);
            memcpy(modified_data, data, data_size);
            memcpy(&modified_data[i], replace_block, replace_size);
            return modified_data;
        }
    }
    return NULL;
}
