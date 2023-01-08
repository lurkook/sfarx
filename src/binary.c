#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <byteswap.h>
#include <binary.h>

uint32_t get_uint(FILE *file)
{
    uint32_t result;
    fread(&result, sizeof(result), 1, file);

#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
    result = __bswap_32(result);
#endif

    return result;
}

uint16_t get_ushort(FILE *file)
{
    uint16_t result;
    fread(&result, sizeof(result), 1, file);

#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
    result = __bswap_16(result);
#endif

    return result;
}

char *get_string(FILE *file)
{
    /* trying to get string size */
    int start = ftell(file);
    int string_size = 0;
    char current_character = '\xff';

    while (current_character != '\0')
    {
        fread(&current_character, sizeof(current_character), 1, file);
        string_size++;
    }

    /* reading the string */
    char *string = malloc(string_size + 1);

    fseek(file, start, SEEK_SET);
    fread(string, string_size, 1, file);
    string[string_size] = '\0';

    /* returning the string */
    return string;
}

char *get_fixed_string(FILE *file, int size)
{
    /* reading the string */
    char *string = malloc(size + 1);
    fread(&string, sizeof(char), 2, file);
    string[size] = '\0';

    /* returning the string*/
    return string;
}

void rewind_pos(FILE *file, int size)
{
    int start_position = ftell(file);
    fseek(file, start_position - size, SEEK_SET);
}
