#ifndef BINARY_H_
#define BINARY_H_

#include <stdio.h>
#include <stdint.h>

uint32_t get_uint(FILE *file);
uint16_t get_ushort(FILE *file);

char *get_string(FILE *file);
char *get_fixed_string(FILE *file, int size);

void rewind_pos(FILE *file, int size);

#endif